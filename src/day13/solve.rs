use fraction::GenericFraction;
use vecmath::Vector2;

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
            let parts: Vec<&str> = part.split_whitespace().collect();
            let x_part = parts[1];
            let y_part = parts[2];

            let x_value: u32 = x_part[2..].parse().unwrap();
            let y_value: u32 = y_part[2..].parse().unwrap();

            machine[i] = [x_value, y_value];
        }
        machines.push(machine);
    }

    return machines;
}

fn optimize(machine_config: &Machine) -> Option<Optimization> {
    let mut optimization: Option<Optimization> = None;

    let button_a: Vector = machine_config[0];
    let button_b: Vector = machine_config[1];
    let prize: Vector = machine_config[2];

    /*
     * Button A costs 3 times as much as button B.
     * Therefore button B is preferred unless A yield is at least 3 times as much as B.
     */
    let preferred: Vector = if button_a[1] / button_a[0] == button_b[1] / button_b[0]
        && button_a[1] % button_a[0] == button_b[1] % button_b[0]
        && button_a[0] > button_b[0] * 3
    {
        button_a
    } else {
        button_b
    };

    let other: Vector = if preferred == button_a {
        button_b
    } else {
        button_a
    };

    let prize_slope: Slope = Slope::new(prize[1], prize[0]);
    let preferred_slope: Slope = Slope::new(preferred[1], preferred[0]);
    let other_slope: Slope = Slope::new(other[1], other[0]);

    /*
     * There is a solution only if the prize slope is between the preferred and other slopes.
     * There is a solution only if prize x is a * preferred x + b * other x.
     * and prize y is a * preferred y + b * other y.
     */
    // if preferred_slope < prize_slope && other_slope < prize_slope {
    //     return None;
    // }

    // if preferred_slope > prize_slope && other_slope > prize_slope {
    //     return None;
    // }

    optimization
}

pub fn solve(example: &str, _variant_b: bool) -> u32 {
    let mut total_tokens: u32 = 0;
    for machine_config in parse(example) {
        let optimization = optimize(&machine_config);
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
}
