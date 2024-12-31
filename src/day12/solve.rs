use std::collections::{HashMap, HashSet};

use super::garden::{Plot, Pos};

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

fn get_neighbors(
    pos: &Pos,
    x_size: usize,
    y_size: usize,
) -> HashMap<direction::CardinalDirection, Option<Pos>> {
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
            if pos.x < x_size - 1 {
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
            if pos.y < y_size - 1 {
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

    return neighbors;
}

pub fn solve(example: &str, discounts: bool) -> u32 {
    // all plots
    let mut plots: HashMap<Pos, Plot> = HashMap::new();

    // garden regions by pos and positions of plots in the region
    let mut regions: HashMap<Pos, HashSet<Pos>> = HashMap::new();

    let x_size = example.lines().next().unwrap().len();
    let y_size = example.lines().count();

    for (y, line) in example.lines().enumerate() {
        for (x, plant) in line.chars().enumerate() {
            let pos = Pos { x, y };

            let neighbors = get_neighbors(&pos, x_size, y_size);

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
            for (dir, &fence) in plot.fences.iter() {
                if fence {
                    if !discounts {
                        perimeter += 1;
                    } else {
                        // count only the right most fence for each side
                        let neighbor = get_neighbors(&plot.pos, x_size, y_size)
                            .get(&dir.right90())
                            .and_then(|n| n.as_ref())
                            .and_then(|n| plots.get(n));

                        if neighbor.is_none()
                            || neighbor.unwrap().plant() != plot.plant()
                            || !neighbor.unwrap().fences.get(&dir).unwrap()
                        {
                            perimeter += 1;
                        }
                    }
                }
            }
        }
        // let plant = plots.get(pos).unwrap().plant();
        result += area * perimeter;
        // println!("{}: {} {} {}", plant, area, perimeter, result);
    }

    return result;
}

#[cfg(test)]
mod tests {
    use crate::day12::{EXAMPLE1, EXAMPLE2, EXAMPLE3};

    use super::*;

    #[test]
    fn solve_a_example1() {
        let result = solve(EXAMPLE1, false);
        assert_eq!(result, 140);
    }

    #[test]
    fn solve_a_example2() {
        let result = solve(EXAMPLE2, false);
        assert_eq!(result, 772);
    }

    #[test]
    fn solve_a_example3() {
        let result = solve(EXAMPLE3, false);
        assert_eq!(result, 1930);
    }

    #[test]
    fn solve_b_example1() {
        let result = solve(EXAMPLE1, true);
        assert_eq!(result, 80);
    }

    #[test]
    fn solve_b_example2() {
        let result = solve(EXAMPLE2, true);
        assert_eq!(result, 436);
    }

    #[test]
    fn solve_b_example3() {
        let result = solve(EXAMPLE3, true);
        assert_eq!(result, 1206);
    }
}
