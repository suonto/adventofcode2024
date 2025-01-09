use super::Computer;

pub fn solve(example: &str, _variant_b: bool) -> &str {
    let computer = Computer::new(example);
    println!("Initial state: {:?}", computer);

    return "0";
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, "4,6,3,5,6,3,5,2,1,0");
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
