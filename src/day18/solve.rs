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

    let lines: Vec<&str> = example.lines().collect();
    let _max = lines.len();

    ram.corrupt(example, limit);
    println!("Corrupted:");
    ram.print();

    let result = ram.find_path();

    println!("Final:");
    ram.print();

    match result {
        Some(p) => {
            println!("Path:");
            ram.print();

            return p.len() - 1;
        }
        None => 0,
    }
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, 7, 12);
        assert_eq!(result, 22);
    }

    #[test]
    fn solve_b_example() {
        let result = solve(EXAMPLE, 7, 21);
        assert_eq!(result, 0);
    }
}
