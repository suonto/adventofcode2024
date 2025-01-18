use super::Ram;

pub fn solve(example: &str, size: usize, limit: usize, variant_b: bool) -> usize {
    let mut ram = Ram {
        paths: Vec::new(),
        ram: vec![vec![0; size]; size],
    };

    let lines: Vec<&str> = example.lines().collect();

    ram.corrupt(&lines, 0, limit);
    println!("Corrupted:");
    ram.print();

    let mut result = ram.find_path();

    if !variant_b {
        println!("Final:");
        ram.print();

        return match result {
            Some(p) => {
                println!("Path:");
                ram.print();

                return p.len() - 1;
            }
            None => 0,
        };
    }

    let mut start = limit;
    if result.is_none() {
        return 0;
    }

    let mut path = result.clone().unwrap();
    println!("{:?}\n", path);

    loop {
        let corruption = ram.corrupt(&lines, start, start + 1);
        println!("Corrupted {start}: ({},{})", corruption.x, corruption.y);

        if path.contains(&corruption) {
            result = ram.find_path();
            ram.print();
            if result.is_none() {
                return start;
            }
            path = result.clone().unwrap();
        }

        start += 1;
    }
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, 7, 12, false);
        assert_eq!(result, 22);
    }

    #[test]
    fn solve_a_too_corrupted() {
        let result = solve(EXAMPLE, 7, 21, false);
        assert_eq!(result, 0);
    }

    #[test]
    fn solve_b_example() {
        let result = solve(EXAMPLE, 7, 12, true);
        assert_eq!(result, 20);
    }
}
