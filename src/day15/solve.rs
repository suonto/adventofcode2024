use super::{WarehouseA, WarehouseB};

pub fn solve(example: &str, variant_b: bool) -> u32 {
    if !variant_b {
        let mut warehouse = WarehouseA::new(example);
        warehouse.do_moves_like_jagger();

        println!("Result:");
        let result = warehouse.print();
        return result;
    } else {
        let mut warehouse = WarehouseB::new(example);
        println!("Initial state:");
        warehouse.print();

        warehouse.do_moves_like_jagger();

        println!("Result:");
        let result = warehouse.print();
        return result;
    }
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example_small() {
        let result = solve(EXAMPLE_SMALL, false);
        assert_eq!(result, 2028);
    }

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, 10092);
    }

    #[test]
    fn solve_b_example() {
        let result = solve(EXAMPLE, true);
        assert_eq!(result, 9021);
    }
}
