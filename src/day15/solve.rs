use super::Warehouse;

pub fn solve(example: &str) -> u32 {
    let mut warehouse = Warehouse::new(example);
    warehouse.do_moves_like_jagger();

    println!("Result:");
    let result = warehouse.print();
    return result;
}

#[cfg(test)]
mod tests {

    use super::super::{EXAMPLE, EXAMPLE_SMALL};
    use super::*;

    #[test]
    fn solve_a_example_small() {
        let result = solve(EXAMPLE_SMALL);
        assert_eq!(result, 2028);
    }

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE);
        assert_eq!(result, 10092);
    }
}
