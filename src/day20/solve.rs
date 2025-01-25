use std::collections::HashSet;

use super::{Cheat, Track};

pub fn solve(example: &str, min: usize) -> usize {
    let mut track = Track::new(example);

    track.populate();
    track.cheats(min);

    let mut cheats: Vec<(&usize, &HashSet<Cheat>)> = track.cheats.iter().collect();
    cheats.sort_by(|(a0, _), (b0, _)| a0.cmp(b0));

    let mut result: usize = 0;
    for (save, cheats) in cheats {
        println!(
            "There are {} cheats that save {} picoseconds.",
            cheats.len(),
            save
        );

        if *save >= min {
            result += cheats.len();
        }
    }

    return result;
}

#[cfg(test)]
mod tests {

    use super::super::*;

    // #[test]
    // fn solve_a_example() {
    //     let result = solve(EXAMPLE, 100);
    //     assert_eq!(result, 0);
    // }

    #[test]
    fn solve_b_example() {
        let result = solve(EXAMPLE, 50);
        assert_eq!(result, 285);
    }
}
