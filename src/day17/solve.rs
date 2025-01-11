use super::Computer;

pub fn solve(example: &str, variant_b: bool) -> String {
    let mut computer = Computer::new(example);
    println!("Initial state: {:?}", computer);
    computer.run(variant_b);

    println!("Output: {:?}", computer.output());
    return computer.output();
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, "4,6,3,5,6,3,5,2,1,0");
    }

    #[test]
    fn a_12_produces_2() {
        let a = 12;
        let result = ((((a % 8) ^ 3) ^ 5) ^ (a / 16)) % 8;
        assert_eq!(result, 2);
    }

    #[test]
    fn a_703_produces_4() {
        let a = 703;
        // 7 ^ 3 = 4
        // 4 ^ 5 = 1
        // 1 ^ (703 / 16) = 1 ^ 43 = 42
        // 42 % 8 = 4
        let result = ((((a % 8) ^ 3) ^ 5) ^ (a / 16)) % 8;
        assert_eq!(result, 2);
    }

    // #[test]
    // fn solve_a_example() {
    //     let result = solve(EXAMPLE, false);
    //     assert_eq!(result, 10092);
    // }

    // #[test]
    // fn solve_b_example() {
    //     let result = solve(EXAMPLE, true);
    //     assert_eq!(result, 9021);
    // }
}
