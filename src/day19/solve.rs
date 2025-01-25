use std::collections::HashMap;

use super::towels::{parse, select};

pub fn solve(example: &str) -> usize {
    let (patterns, designs) = parse(example);

    println!("Patterns {:?}", patterns);

    let mut count: usize = 0;
    let mut cache: HashMap<&str, usize> = HashMap::new();
    for design in designs.iter() {
        let included: Vec<&str> = patterns
            .clone()
            .into_iter()
            .filter(|p| design.contains(p))
            .collect();
        println!("Design {}", design);
        println!("Included patterns {:?}", included);
        let selection = select(&included, design, &mut cache);

        count += selection;
        println!("Design {design} count: {selection}, total {count}");
    }

    return count;
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE);
        assert_eq!(result, 6);
    }
}
