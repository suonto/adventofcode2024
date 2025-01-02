use std::vec;

use fraction::GenericFraction;
use vecmath::{vec2_add, vec2_scale, Vector2};

type Vector = Vector2<u32>;
type Machine = [Vector; 3];
type Optimization = Vector;

// Vector slope is expresses as a fraction
type Slope = GenericFraction<u32>;

pub fn parse(example: &str) -> Vec<[Vector; 3]> {
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

            let x_value: u32 = x_part[2..].parse().unwrap();
            let y_value: u32 = y_part[2..].parse().unwrap();

            machine[i] = [x_value, y_value];
        }
        machines.push(machine);
    }

    return machines;
}

fn optimize_parallel(machine_config: &Machine) -> Option<Optimization> {
    let vec_a: Vector = machine_config[0];
    let vec_b: Vector = machine_config[1];
    let prize: Vector = machine_config[2];

    /*
     * Button A costs 3 times as much as button B.
     * Therefore button B is preferred unless A yield is at least 3 times as much as B.
     */
    let preferred: Vector = if vec_a[1] / vec_a[0] == vec_b[1] / vec_b[0]
        && vec_a[1] % vec_a[0] == vec_b[1] % vec_b[0]
        && vec_a[0] > vec_b[0] * 3
    {
        vec_a
    } else {
        vec_b
    };

    let mut preferred_count: u32 = if prize[0] / preferred[0] > 100 {
        100
    } else {
        prize[0] / preferred[0]
    };

    loop {
        let remainder: u32 = prize[0] - preferred_count * preferred[0];
        if remainder % vec_b[0] == 0 {
            let other_count: u32 = remainder / vec_b[0];
            if other_count > 100 {
                return None;
            }
            return if preferred == vec_a {
                Some([preferred_count, other_count])
            } else {
                Some([other_count, preferred_count])
            };
        }

        if preferred_count == 0 {
            break;
        }

        preferred_count -= 1;
    }

    return None;
}

/*
 * The prize slope is between the low and high slopes.
 * The prize x is a * low x + b * high x.
 * The prize y is a * low y + b * high y.
 */
fn optimize_nonparallel(machine_config: &Machine) -> Option<Optimization> {
    println!("Optimizing nonparallel {:?}", machine_config);
    let vec_a: Vector = machine_config[0];
    let vec_b: Vector = machine_config[1];
    let prize: Vector = machine_config[2];

    let slope_a: Slope = Slope::new(vec_a[1], vec_a[0]);
    let slope_b: Slope = Slope::new(vec_b[1], vec_b[0]);
    let prize_slope: Slope = Slope::new(prize[1], prize[0]);

    let low: Vector = if slope_a < slope_b { vec_a } else { vec_b };
    let high: Vector = if slope_a < slope_b { vec_b } else { vec_a };

    let mut low_count: u32 = 1;
    let mut high_count: u32 = 0;
    let mut result: Vector = low.clone();
    let mut result_slope: Slope = Slope::new(result[1], result[0]);

    while result_slope != prize_slope {
        if low_count > 100 || high_count > 100 {
            return None;
        }

        if result_slope < prize_slope {
            high_count += 1;
            result = vec2_add(result, high);
        } else {
            low_count += 1;
            result = vec2_add(result, low);
        }

        result_slope = Slope::new(result[1], result[0]);
    }

    if result_slope != prize_slope {
        return None;
    }

    let multiplier: u32 = prize[0] / result[0];

    if low_count * multiplier > 100 || high_count * multiplier > 100 {
        return None;
    }

    let a: u32 = if low == vec_a { low_count } else { high_count };
    let b: u32 = if low == vec_a { high_count } else { low_count };

    return Some([a * multiplier, b * multiplier]);
}

fn optimize(machine_config: &Machine) -> Option<Optimization> {
    let vec_a: Vector = machine_config[0];
    let vec_b: Vector = machine_config[1];
    let prize: Vector = machine_config[2];

    let prize_slope: Slope = Slope::new(prize[1], prize[0]);
    let slope_a: Slope = Slope::new(vec_a[1], vec_a[0]);
    let slope_b: Slope = Slope::new(vec_b[1], vec_b[0]);

    /*
     * There is a solution only if the prize slope is between the preferred and other slopes.
     * There is a solution only if prize x is a * preferred x + b * other x.
     * and prize y is a * preferred y + b * other y.
     */
    if slope_a < prize_slope && slope_b < prize_slope {
        return None;
    }

    if slope_a > prize_slope && slope_b > prize_slope {
        return None;
    }

    if slope_a == prize_slope && slope_b == prize_slope {
        return optimize_parallel(machine_config);
    }

    if slope_a == prize_slope && prize[0] % vec_a[0] == 0 {
        let result = prize[0] / vec_a[0];
        if result > 100 {
            return None;
        }
        return Some([result, 0]);
    }

    if slope_b == prize_slope && prize[0] % vec_b[0] == 0 {
        let result = prize[0] / vec_b[0];
        if result > 100 {
            return None;
        }
        return Some([0, result]);
    }

    return optimize_nonparallel(machine_config);
}

pub fn solve(example: &str, _variant_b: bool) -> u32 {
    let mut total_tokens: u32 = 0;
    for machine_config in parse(example) {
        let optimization = optimize(&machine_config);

        let vec_a: Vector = machine_config[0];
        let vec_b: Vector = machine_config[1];
        let prize: Vector = machine_config[2];

        // sanity check optimization
        if optimization.is_some() {
            let opt = optimization.unwrap();
            let result: Vector = vec2_add(vec2_scale(vec_a, opt[0]), vec2_scale(vec_b, opt[1]));

            if opt[0] > 100 || opt[1] > 100 {
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

    #[test]
    fn solve_a_parallel_a() {
        let example_0 = "Button A: X+4, Y+8\n\
Button B: X+1, Y+2\n\
Prize: X=5, Y=10\
";
        let result = solve(example_0, false);
        assert_eq!(result, 1 * 3 + 1);
    }

    #[test]
    fn solve_a_parallel_b() {
        let example_0 = "Button A: X+2, Y+4\n\
Button B: X+1, Y+2\n\
Prize: X=4, Y=8\
";
        let result = solve(example_0, false);
        assert_eq!(result, 0 * 3 + 4);
    }
}
