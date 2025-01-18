/// returns (patterns, designs) tuple
pub fn parse(input: &str) -> (Vec<&str>, Vec<&str>) {
    let mut patterns: Vec<&str> = Vec::new();
    let mut designs: Vec<&str> = Vec::new();
    for (i, line) in input.lines().enumerate() {
        if i == 0 {
            line.split(", ").for_each(|part| patterns.push(part));
        } else if i > 1 {
            designs.push(line);
        }
    }

    return (patterns, designs);
}

/// returns a selection, which is a vector of pattern indices if design is possible
pub fn select(patterns: &Vec<&str>, design: &str, without_exact: bool) -> Option<Vec<usize>> {
    for (i, pattern) in patterns.iter().enumerate() {
        if design.starts_with(pattern) {
            if design == *pattern && without_exact {
                continue;
            }
            let remaining = &design[pattern.len()..];

            let mut result: Vec<usize> = Vec::from([i]);
            if remaining.is_empty() {
                return Some(result);
            }

            let sub_design = select(patterns, remaining, false);

            if sub_design.is_some() {
                result.extend(sub_design.unwrap().into_iter());
                return Some(result);
            }
        }
    }

    return None;
}

pub fn print(patterns: &Vec<&str>, selection: &Vec<usize>) {
    println!("{:?}", selection);
    for (i, s) in selection.iter().enumerate() {
        print!("{}", patterns[*s]);
        if i < selection.len() - 1 {
            print!(",");
        }
    }
    print!("\n");
}
