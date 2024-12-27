use std::collections::{HashMap, HashSet};

use aoc2024::day12::{Plot, Pos, Region};

const EXAMPLE1: &str = "\
AAAA\n\
BBCD\n\
BBCC\n\
EEEC\
";

fn main() {
    // all plots
    let plots: HashMap<Pos, Plot> = HashMap::new();

    // garden regions by pos and plots in the region
    let regions: HashMap<Pos, HashSet<Plot>> = HashMap::new();

    for (y, line) in EXAMPLE1.lines().enumerate() {
        for (x, plant) in line.chars().enumerate() {
            // Neighbors
            let north_neighbor = plots.get(&Pos { x: x, y: y - 1 });
            let east_neighbor = plots.get(&Pos { x: x + 1, y: y });
            let south_neighbor = plots.get(&Pos { x: x, y: y + 1 });
            let west_neighbor = plots.get(&Pos { x: x - 1, y: y });

            // Plot
            let pos = Pos { x, y };
            let plot = Plot::new( pos, plant );

            plots.insert(pos, plot);

            // Determine region
            if (north_neighbor.is_none()) {
                plot.
            }
        }
        println!("{i}: {line}");
    }
}
