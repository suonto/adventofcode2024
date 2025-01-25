use super::Track;

pub fn solve(example: &str, _variant_b: bool) -> usize {
    let mut track = Track::new(example);

    track.populate();

    return 0;
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, 2);
    }
}
