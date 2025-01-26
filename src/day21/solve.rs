use super::{Keypad, KeypadVariant};

fn solve_one(output: &str) -> usize {
    let mut n_pad = Keypad::new(KeypadVariant::Numeric, output.chars().collect());
    let n_pad_input = n_pad.input();
    let mut d_pad_0 = Keypad::new(KeypadVariant::Directional, n_pad_input);
    let d_pad_0_input = d_pad_0.input();
    let mut d_pad_1 = Keypad::new(KeypadVariant::Directional, d_pad_0_input);
    let d_pad_1_input = d_pad_1.input();

    let len = d_pad_1_input.len();
    print!("{output}: ");
    for c in d_pad_1_input {
        print!("{c}");
    }
    println!();

    let num_part: usize = output[0..3].parse().unwrap();
    let result = len * num_part;
    println!("{0} * {num_part} = {result}", len);

    return result;
}

// solve line at index, or all if None
pub fn solve(example: &str) -> usize {
    let mut result: usize = 0;

    for line in example.lines() {
        result += solve_one(line);
    }

    return result;
}

#[cfg(test)]
mod tests {

    use super::super::*;
    use crate::day21::solve::solve_one;

    #[test]
    fn solve_a_example_0() {
        let examples: Vec<&str> = EXAMPLE.lines().collect();
        let result = solve_one(examples[0]);
        assert_eq!(result, 68 * 29);
    }

    #[test]
    fn solve_a_example_1() {
        let examples: Vec<&str> = EXAMPLE.lines().collect();
        let result = solve_one(examples[1]);
        assert_eq!(result, 60 * 980);
    }

    #[test]
    fn solve_a_example_2() {
        let examples: Vec<&str> = EXAMPLE.lines().collect();
        let result = solve_one(examples[2]);
        assert_eq!(result, 68 * 179);
    }

    #[test]
    fn solve_a_example_3() {
        let examples: Vec<&str> = EXAMPLE.lines().collect();
        let result = solve_one(examples[3]);
        assert_eq!(result, 64 * 456);
    }

    #[test]
    fn solve_a_example_4() {
        let examples: Vec<&str> = EXAMPLE.lines().collect();
        let result = solve_one(examples[4]);
        assert_eq!(result, 64 * 379);
    }
}
