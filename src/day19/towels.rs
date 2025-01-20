use std::collections::HashMap;

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

pub fn select<'a, 'b>(
    patterns: &'a Vec<&'a str>,
    design: &'b str,
    cache: &mut HashMap<&'b str, usize>,
) -> usize
where
    'b: 'a,
{
    let mut count: usize = 0;
    for pattern in patterns.iter() {
        if design.starts_with(pattern) {
            let remaining = &design[pattern.len()..];

            if remaining.is_empty() {
                count += 1;
            }

            let sub_result = cache.get(remaining);
            if sub_result.is_some() {
                let sub_result = sub_result.unwrap();
                count += sub_result;
            } else {
                let sub_result = select(patterns, remaining, cache);
                cache.insert(remaining, sub_result);
                count += sub_result;
            }
        }
    }

    return count;
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
