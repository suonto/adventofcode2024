use super::towels::{parse, print, select};

pub fn solve(example: &str) -> usize {
    let (patterns, designs) = parse(example);

    println!("Patterns {:?}", patterns);

    let mut count: usize = 0;
    for design in designs.iter() {
        let filtered: Vec<&str> = patterns
            .clone()
            .into_iter()
            .filter(|p| design.contains(p) && select(&patterns, p, true).is_none())
            .collect();
        println!("Design {}", design);
        println!("Filtered patterns {:?}", filtered);
        let selection = select(&filtered, design, false);

        if selection.is_some() {
            count += 1;
            print(&filtered, &selection.unwrap());
        } else {
            println!("Impossible");
        }
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
