use std::collections::{HashMap, HashSet};

use aoc2024::day12::{Plot, Pos};

const EXAMPLE1: &str = "\
AAAA\n\
BBCD\n\
BBCC\n\
EEEC\
";

const EXAMPLE2: &str = "\
OOOOO\n\
OXOXO\n\
OOOOO\n\
OXOXO\n\
OOOOO\
";

const EXAMPLE3: &str = "\
RRRRIICCFF\n\
RRRRIICCCF\n\
VVRRRCCFFF\n\
VVRCCCJFFF\n\
VVVVCJJCFE\n\
VVIVCCJJEE\n\
VVIIICJJEE\n\
MIIIIIJJEE\n\
MIIISIJEEE\n\
MMMISSJEEE\
";

fn insert_into_region_of(
    regions: &mut HashMap<Pos, HashSet<Pos>>,
    target_plot: &Plot,
    new_plot: Plot,
) {
    let key = regions
        .iter()
        .find_map(|(key, region)| {
            if region.contains(&target_plot.pos) {
                Some(key.clone())
            } else {
                None
            }
        })
        .expect("Region containing the plot not found");

    regions.get_mut(&key).unwrap().insert(new_plot.pos);
}

fn find_region_key(regions: &HashMap<Pos, HashSet<Pos>>, plot: &Plot) -> Pos {
    regions
        .iter()
        .find_map(|(key, region)| {
            if region.contains(&plot.pos) {
                Some(key)
            } else {
                None
            }
        })
        .expect("Region containing the plot not found")
        .clone()
}

fn solve(example: &str) -> u32 {
    // all plots
    let mut plots: HashMap<Pos, Plot> = HashMap::new();

    // garden regions by pos and positions of plots in the region
    let mut regions: HashMap<Pos, HashSet<Pos>> = HashMap::new();

    for (y, line) in example.lines().enumerate() {
        for (x, plant) in line.chars().enumerate() {
            let pos = Pos { x, y };

            let neighbors: HashMap<direction::CardinalDirection, Option<Pos>> = HashMap::from([
                (
                    direction::CardinalDirection::North,
                    if pos.y > 0 {
                        Some(Pos {
                            x: pos.x,
                            y: pos.y - 1,
                        })
                    } else {
                        None
                    },
                ),
                (
                    direction::CardinalDirection::East,
                    if pos.x < line.len() - 1 {
                        Some(Pos {
                            x: pos.x + 1,
                            y: pos.y,
                        })
                    } else {
                        None
                    },
                ),
                (
                    direction::CardinalDirection::South,
                    if pos.y < example.lines().count() - 1 {
                        Some(Pos {
                            x: pos.x,
                            y: pos.y + 1,
                        })
                    } else {
                        None
                    },
                ),
                (
                    direction::CardinalDirection::West,
                    if pos.x > 0 {
                        Some(Pos {
                            x: pos.x - 1,
                            y: pos.y,
                        })
                    } else {
                        None
                    },
                ),
            ]);

            // Plot
            let mut plot = Plot::new(pos, plant);

            // Fences
            for (dir, neighbor) in neighbors.iter().filter(|(dir, _)| {
                *dir == &direction::CardinalDirection::North
                    || *dir == &direction::CardinalDirection::West
            }) {
                match neighbor {
                    Some(neighbor) => {
                        if plots.get(neighbor).unwrap().plant() != &plant {
                            plot.fences.insert(*dir, true);
                            let neighbor = plots.get_mut(neighbor).unwrap();
                            // println!("{:?} {:?}", neighbor.pos, dir.opposite());
                            neighbor.fences.insert(dir.opposite(), true);
                        }
                    }
                    None => {
                        plot.fences.insert(*dir, true);
                    }
                }
            }

            if y == example.lines().count() - 1 {
                plot.fences
                    .insert(direction::CardinalDirection::South, true);
            }

            if x == line.len() - 1 {
                plot.fences.insert(direction::CardinalDirection::East, true);
            }

            let north_neighbor = neighbors
                .get(&direction::CardinalDirection::North)
                .and_then(|n| n.as_ref())
                .and_then(|n| plots.get(n));
            let west_neighbor = neighbors
                .get(&direction::CardinalDirection::West)
                .and_then(|w| w.as_ref())
                .and_then(|w| plots.get(w));

            // Determine region
            if north_neighbor.map_or(false, |n| n.plant() == &plant)
                && west_neighbor.map_or(false, |w| w.plant() == &plant)
            {
                // Determine which region to preserve
                let (primary_region, secondary_region) = if north_neighbor.unwrap().pos().y
                    < west_neighbor.unwrap().pos().y
                    || (north_neighbor.unwrap().pos().y == west_neighbor.unwrap().pos().y
                        && north_neighbor.unwrap().pos().x < west_neighbor.unwrap().pos().x)
                {
                    (
                        find_region_key(&regions, &north_neighbor.unwrap()),
                        find_region_key(&regions, &west_neighbor.unwrap()),
                    )
                } else {
                    (
                        find_region_key(&regions, &west_neighbor.unwrap()),
                        find_region_key(&regions, &north_neighbor.unwrap()),
                    )
                };

                // Merge regions
                if primary_region != secondary_region {
                    let secondary_region_set = regions.get(&secondary_region).unwrap().clone();

                    let primary_region_set = regions.get_mut(&primary_region).unwrap();

                    primary_region_set.extend(secondary_region_set.iter().cloned());
                    primary_region_set.insert(plot.pos.clone());

                    regions.remove(&secondary_region).unwrap();
                } else {
                    regions
                        .get_mut(&primary_region)
                        .unwrap()
                        .insert(plot.pos.clone());
                }
            } else if north_neighbor.map_or(false, |n| n.plant() == &plant) {
                insert_into_region_of(&mut regions, north_neighbor.unwrap(), plot.clone());
            } else if west_neighbor.map_or(false, |w| w.plant() == &plant) {
                insert_into_region_of(&mut regions, west_neighbor.unwrap(), plot.clone());
            } else {
                // Create new region
                let new_region = HashSet::from([plot.pos]);
                regions.insert(pos.clone(), new_region);
            }

            // Insert the plot into the hashmap after modifying it
            plots.insert(pos, plot);
        }
    }

    let mut result: u32 = 0;

    // Calculate area and perimeter of each region
    for region in regions.values() {
        let mut area: u32 = 0;
        let mut perimeter: u32 = 0;
        for plot_pos in region.iter() {
            let plot = plots.get(plot_pos).unwrap();
            area += 1;
            println!("{:?} {:?}", plot.pos, plot.fences);
            for (_, &fence) in plot.fences.iter() {
                if fence {
                    perimeter += 1;
                }
            }
        }
        // let plant = plots.get(pos).unwrap().plant();
        result += area * perimeter;
        // println!("{}: {} {} {}", plant, area, perimeter, result);
    }

    return result;
}

fn main() {
    println!("Example1: {}", solve(EXAMPLE1));
    println!("Example2: {}", solve(EXAMPLE2));
    println!("Example3: {}", solve(EXAMPLE3));
}
