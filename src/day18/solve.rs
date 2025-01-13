use std::collections::HashSet;

use direction::Coord;

use super::{Path, Ram};

pub fn solve(example: &str, size: usize, limit: usize) -> usize {
    let start = Path {
        steps: vec![Coord { x: 0, y: 0 }],
        visited: HashSet::from([Coord { x: 0, y: 0 }]),
    };

    let mut ram = Ram {
        paths: vec![start],
        ram: vec![vec![0; size]; size],
    };

    ram.corrupt(example, limit);
    println!("Corrupted:");
    ram.print();

    let result = ram.find_path();
    println!("Path:");
    ram.print();

    return result.len() - 1;
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, 7, 12);
        assert_eq!(result, 22);
    }
}
