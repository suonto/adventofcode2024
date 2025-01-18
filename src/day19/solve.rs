use super::towels::{parse, print, select};

pub fn solve(example: &str) -> usize {
    let (patterns, designs) = parse(example);

    println!("Patterns {:?}", patterns);

    let mut count: usize = 0;
    for design in designs.iter() {
        println!("Design {}", design);
        let selection = select(&patterns, design);

        if selection.is_some() {
            count += 1;
            print(&patterns, &selection.unwrap());
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
