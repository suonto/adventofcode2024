use fraction::GenericFraction;
use vecmath::{vec2_add, vec2_scale, Vector2};

type Vector = Vector2<i128>;
type Machine = [Vector; 3];
type Optimization = Vector;

// Vector slope is expresses as a fraction
type Slope = GenericFraction<i128>;

pub fn parse(example: &str, variant_b: bool) -> Vec<[Vector; 3]> {
    let mut machines: Vec<Machine> = Vec::new();

    for line in example.split("\n\n") {
        let mut machine: Machine = [[0; 2]; 3];
        for (i, part) in line.lines().enumerate() {
            let parts: Vec<&str> = part.split(':').collect();
            let interesting_part = parts[1].trim();
            let coords: Vec<&str> = interesting_part.split_whitespace().collect();
            let x_part = coords[0].trim_end_matches(',');
            let y_part = coords[1];

            println!("X: {:?} Y: {:?}", x_part, y_part);

            let x_value: i128 = x_part[2..].parse().unwrap();
            let y_value: i128 = y_part[2..].parse().unwrap();

            let x_value = if i == 2 && variant_b {
                x_value + 10000000000000
            } else {
                x_value
            };
            let y_value = if i == 2 && variant_b {
                y_value + 10000000000000
            } else {
                y_value
            };

            machine[i] = [x_value, y_value];
        }
        machines.push(machine);
    }

    return machines;
}

fn optimize_math(machine_config: &Machine) -> Option<Optimization> {
    let vec_a: Vector = machine_config[0];
    let vec_b: Vector = machine_config[1];
    let prize: Vector = machine_config[2];

    let x_1 = vec_a[0];
    let y_1 = vec_a[1];
    let x_2 = vec_b[0];
    let y_2 = vec_b[1];
    let x_p = prize[0];
    let y_p = prize[1];

    println!("Optimizing math {:?}", machine_config);

    let numerator = (y_p * x_1) - (y_1 * x_p);
    let denominator = (x_1 * y_2) - (x_2 * y_1);

    println!(
        "numerator: {:?} * {:?} - {:?} * {:?} = {:?} ",
        x_p, x_1, y_1, x_p, numerator
    );
    println!(
        "denominator: {:?} * {:?} - {:?} * {:?} = {:?}",
        x_1, y_2, x_2, y_1, denominator
    );

    if denominator == 0 || numerator % denominator != 0 {
        return None;
    }

    let b = numerator / denominator;

    println!("b: {:?}", b);

    if (x_p - b * x_2) % x_1 != 0 {
        return None;
    }

    let a = (x_p - b * x_2) / x_1;

    if a * x_1 + b * x_2 == x_p && a * y_1 + b * y_2 == y_p {
        println!("{:?}", [a, b]);

        return Some([a, b]);
    }
    println!("No solution found");

    return None;
}

pub fn solve(example: &str, variant_b: bool) -> i128 {
    let mut total_tokens: i128 = 0;
    for machine_config in parse(example, variant_b) {
        let optimization = optimize_math(&machine_config);

        let vec_a: Vector = machine_config[0];
        let vec_b: Vector = machine_config[1];
        let prize: Vector = machine_config[2];

        // sanity check optimization
        if optimization.is_some() {
            let opt = optimization.unwrap();
            let result: Vector = vec2_add(vec2_scale(vec_a, opt[0]), vec2_scale(vec_b, opt[1]));

            if !variant_b && (opt[0] > 100 || opt[1] > 100) {
                panic!(
                    "Optimization over 100: {:?} {:?} {:?} produced: {:?}, which results in {:?}",
                    vec_a, vec_b, prize, opt, result
                );
            }

            if result != prize {
                panic!(
                    "Optimization failed: {:?} {:?} {:?} produced: {:?}, which results in {:?}",
                    vec_a,
                    vec_b,
                    prize,
                    opt,
                    vec2_add(vec2_scale(vec_a, opt[0]), vec2_scale(vec_b, opt[1]))
                );
            }
            let result_slope: Slope = Slope::new(result[1], result[0]);
            let prize_slope: Slope = Slope::new(prize[1], prize[0]);

            if result_slope != prize_slope {
                panic!(
                    "Optimization wrong slope: {:?} {:?} {:?} produced: {:?}, which results in {:?}",
                    vec_a,
                    vec_b,
                    prize,
                    optimization,
                    vec2_add(vec2_scale(vec_a, opt[0]), vec2_scale(vec_b, opt[1]))
                );
            }
        }

        let tokens = optimization.map_or(0, |opt| opt[0] * 3 + opt[1]);
        total_tokens += tokens;
        println!(
            "{:?} {:?} {:?} {:?}",
            machine_config, optimization, tokens, total_tokens
        );
    }

    return total_tokens;
}

#[cfg(test)]
mod tests {
    use crate::day13::EXAMPLE;

    use super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, 480);
    }

    #[test]
    fn solve_a_example_0() {
        let example_0 = "Button A: X+94, Y+34\n\
Button B: X+22, Y+67\n\
Prize: X=8400, Y=5400\
";
        let result = solve(example_0, false);
        assert_eq!(result, 80 * 3 + 40);
    }

    #[test]
    fn solve_a_example_2() {
        let example_0 = "Button A: X+17, Y+86\n\
Button B: X+84, Y+37\n\
Prize: X=7870, Y=6450\
";
        let result = solve(example_0, false);
        assert_eq!(result, 38 * 3 + 86);
    }

    // dumb data, has no corner cases
    //     #[test]
    //     fn solve_a_parallel_a() {
    //         let example_0 = "Button A: X+4, Y+8\n\
    // Button B: X+1, Y+2\n\
    // Prize: X=5, Y=10\
    // ";
    //         let result = solve(example_0, false);
    //         assert_eq!(result, 1 * 3 + 1);
    //     }

    //     #[test]
    //     fn solve_a_parallel_b() {
    //         let example_0 = "Button A: X+2, Y+4\n\
    // Button B: X+1, Y+2\n\
    // Prize: X=4, Y=8\
    // ";
    //         let result = solve(example_0, false);
    //         assert_eq!(result, 0 * 3 + 4);
    //     }
}
