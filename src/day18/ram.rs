use core::fmt;
use std::{collections::HashSet, ops::Index};

use direction::{CardinalDirections, Coord};

#[derive(PartialEq, Eq, Clone)]
pub struct Path {
    pub visited: HashSet<Coord>,
    pub steps: Vec<Coord>,
}

impl fmt::Debug for Path {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Path[{:?}]", self.steps)
    }
}

impl Index<usize> for Path {
    type Output = Coord;

    #[inline]
    fn index(&self, i: usize) -> &Self::Output {
        &self.steps[i]
    }
}

impl Path {
    pub fn add(&mut self, coord: Coord) {
        self.visited.insert(coord);
        self.steps.push(coord);
    }

    pub fn len(&self) -> usize {
        self.steps.len()
    }

    pub fn contains(&self, coord: &Coord) -> bool {
        return self.visited.contains(coord);
    }
}

#[derive(Debug, PartialEq, Eq, Clone)]
pub struct Ram {
    pub paths: Vec<Path>,
    // -1 is corrupted
    // 0 is undetermined
    // other i32 is distance from start
    pub ram: Vec<Vec<i32>>,
}

impl Ram {
    pub fn corrupt(&mut self, input: &str, limit: usize) {
        for (i, line) in input.lines().enumerate() {
            if i == limit {
                break;
            }

            let parts: Vec<usize> = line
                .split(',')
                .map(|s| s.parse::<usize>().unwrap())
                .collect();

            let x = parts[0];
            let y = parts[1];
            println!("Corrupted {x},{y}");
            self.ram[y][x] = -1;
        }
    }

    fn contains(&self, coord: &Coord) -> bool {
        coord.x >= 0
            && coord.x < self.ram.len() as i32
            && coord.y >= 0
            && coord.y < self.ram.len() as i32
    }

    pub fn find_path(&mut self) -> Path {
        let result = 'outer: loop {
            let mut new_paths: Vec<Path> = Vec::new();
            for path in self.paths.iter() {
                let pos = path[path.len() - 1];
                for d in CardinalDirections {
                    let neighbor = pos + d.coord();

                    if neighbor.y == self.ram.len() as i32 - 1
                        && neighbor.x == self.ram[0].len() as i32 - 1
                    {
                        let mut p = path.clone();
                        p.add(neighbor);
                        break 'outer p;
                    }

                    // avoid bad coords
                    if !self.contains(&neighbor) {
                        continue;
                    }

                    // avoid going backwards
                    if path.len() > 1 && path[path.len() - 2] == neighbor {
                        continue;
                    }

                    // avoid if any other path contains neighbor
                    if self.paths.iter().any(|p| p.contains(&neighbor))
                        || new_paths.iter().any(|p| p.contains(&neighbor))
                    {
                        continue;
                    }

                    // avoid walls
                    let is_wall = self.ram[neighbor.y as usize][neighbor.x as usize] == -1;
                    println!("Checking if is wall {:?}: {:?}", neighbor, is_wall);
                    if is_wall {
                        continue;
                    }

                    println!("{:?} -> {:?}", pos, neighbor);

                    let mut new_path = path.clone();
                    new_path.add(neighbor);
                    new_paths.push(new_path);
                }
            }
            self.paths = new_paths;
            self.print();
        };

        self.paths = vec![result.clone()];
        return result;
    }

    pub fn print(&self) {
        // The example is diagonally flipped and inaccurate
        // x and y are switched here accordingly.
        for x in 0..self.ram.len() {
            for y in 0..self.ram[x].len() {
                let tile = self.ram[x][y];
                if tile == -1 {
                    print!("#");
                } else {
                    let is_path = self.paths.iter().any(|p| {
                        p.contains(&Coord {
                            x: y as i32,
                            y: x as i32,
                        })
                    });
                    if is_path {
                        print!("O");
                    } else {
                        print!(".");
                    }
                }
            }
            println!();
        }
        println!();
    }
}
