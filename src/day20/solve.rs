use super::{Cheat, Track};

pub fn solve(example: &str, _variant_b: bool) -> usize {
    let mut track = Track::new(example);

    track.populate();
    track.cheats();

    let mut cheats: Vec<(&usize, &Vec<Cheat>)> = track.cheats.iter().collect();
    cheats.sort_by(|(a0, _), (b0, _)| a0.cmp(b0));

    let mut result: usize = 0;
    for (save, cheats) in cheats {
        println!(
            "There are {} cheats that save {} picoseconds.",
            cheats.len(),
            save
        );

        if *save >= 100 {
            result += cheats.len();
        }
    }

    return result;
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, 0);
    }
}
