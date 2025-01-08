use super::Maze;

pub fn solve(example: &str, _variant_b: bool) -> u32 {
    let mut maze = Maze::new(example);
    while !maze.move_reindeers() {
        maze.print(None);
    }

    for reindeer in maze.finished.iter() {
        println!("Reindeer {}", reindeer.score,);
        maze.print(Some(reindeer));
    }

    return maze.winner_score();
}

#[cfg(test)]
mod tests {

    use super::super::*;

    #[test]
    fn solve_a_example_1() {
        let result = solve(EXAMPLE_1, false);
        assert_eq!(result, 7036);
    }

    #[test]
    fn solve_a_example_2() {
        let result = solve(EXAMPLE_2, false);
        assert_eq!(result, 11048);
    }

    // #[test]
    // fn solve_b_example() {
    //     let result = solve(EXAMPLE, true);
    //     assert_eq!(result, 9021);
    // }
}
