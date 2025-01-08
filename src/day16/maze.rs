use std::{collections::HashMap, fmt};

use direction::{CardinalDirection, Coord};

fn dir_to_char(dir: CardinalDirection) -> char {
    match dir {
        CardinalDirection::North => '^',
        CardinalDirection::East => '>',
        CardinalDirection::South => 'v',
        CardinalDirection::West => '<',
    }
}

#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
pub struct Step {
    pub coord: Coord,
    pub dir: CardinalDirection,
}

/// A Reindeer is a magical creature that spawns
/// left and right facing new reindeers to current tile and then
/// tries to advance to the next tile.
/// spawned reindeers will have the same path as the parent reindeer
/// and score + 1
#[derive(Debug, PartialEq, Eq, Clone)]
pub struct Reindeer {
    pub path: Vec<Step>,
    pub pos: Coord,
    pub orientation: CardinalDirection,
    pub score: u32,
}

struct Tile {
    pub char: char,
    // tile contains tracks to each direction where a reindeer has went before
    pub tracks: HashMap<CardinalDirection, bool>,
}
impl fmt::Display for Tile {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "{}", self.char)
    }
}

impl Tile {
    pub fn new(char: char) -> Self {
        Self {
            char,
            tracks: HashMap::from([
                (CardinalDirection::North, false),
                (CardinalDirection::East, false),
                (CardinalDirection::South, false),
                (CardinalDirection::West, false),
            ]),
        }
    }
}

pub struct Maze {
    tiles: Vec<Vec<Tile>>,
    reindeers: Vec<Reindeer>,
    pub finished: Vec<Reindeer>,
}

impl Maze {
    pub fn new(input: &str) -> Self {
        let mut tiles: Vec<Vec<Tile>> = Vec::new();
        let mut start: Option<Coord> = None;

        for (y, line) in input.split("\n").enumerate() {
            let mut row: Vec<Tile> = Vec::new();
            for (x, c) in line.chars().enumerate() {
                if c == 'S' {
                    start = Some(Coord::new(x.try_into().unwrap(), y.try_into().unwrap()));
                }
                row.push(Tile::new(c));
            }
            tiles.push(row);
        }

        let start = start.unwrap();

        Self {
            tiles,
            reindeers: Vec::from([
                Reindeer {
                    pos: start,
                    path: Vec::new(),
                    orientation: CardinalDirection::East,
                    score: 0,
                },
                Reindeer {
                    pos: start,
                    path: Vec::new(),
                    orientation: CardinalDirection::North,
                    score: 1000,
                },
            ]),
            finished: Vec::new(),
        }
    }

    fn blocked(&self, coord: &Coord, dir: &CardinalDirection) -> bool {
        let new_pos = coord + dir.coord();
        let blocked = self.tiles[new_pos.y as usize][new_pos.x as usize].char == '#'
            || self.tiles[coord.y as usize][coord.x as usize].tracks[dir];
        return blocked;
    }

    fn at(&mut self, coord: Coord) -> &mut Tile {
        return &mut self.tiles[coord.y as usize][coord.x as usize];
    }

    /// return true if all reindeers are finished
    pub fn move_reindeers(&mut self) -> bool {
        let mut new_reindeers: Vec<Reindeer> = Vec::new();
        for mut reindeer in self.reindeers.clone() {
            // spawn new reindeer left
            if !self.blocked(&reindeer.pos, &reindeer.orientation.left90()) {
                let mut left = reindeer.clone();
                left.orientation = reindeer.orientation.left90();
                left.score = reindeer.score + 1000;
                new_reindeers.push(left);
            }

            // spawn new reindeer right
            if !self.blocked(&reindeer.pos, &reindeer.orientation.right90()) {
                let mut right = reindeer.clone();
                right.orientation = reindeer.orientation.right90();
                right.score = reindeer.score + 1000;
                new_reindeers.push(right);
            }

            // move current reindeer
            if !self.blocked(&reindeer.pos, &reindeer.orientation) {
                let new_pos = reindeer.pos + reindeer.orientation.coord();
                self.at(reindeer.pos)
                    .tracks
                    .insert(reindeer.orientation, true);
                self.at(new_pos)
                    .tracks
                    .insert(reindeer.orientation.opposite(), true);

                // move reindeer
                reindeer.path.push(Step {
                    coord: reindeer.pos,
                    dir: reindeer.orientation,
                });
                println!("{:?} advancing -> {:?}", reindeer.pos, reindeer.orientation);
                reindeer.pos = new_pos;
                reindeer.score += 1;

                if self.at(new_pos).char == 'E' {
                    self.finished.push(reindeer);
                } else {
                    new_reindeers.push(reindeer);
                }
            }
        }
        self.reindeers = new_reindeers;
        return self.reindeers.len() == 0;
    }

    pub fn winner_score(&self) -> u32 {
        // min score in reindeer scores
        return self.finished.iter().map(|r| r.score).min().unwrap_or(0);
    }

    pub fn print(&self, reindeer: Option<&Reindeer>) {
        for y in 0..self.tiles.len() {
            for x in 0..self.tiles[y].len() {
                let coord = Coord::new(x.try_into().unwrap(), y.try_into().unwrap());
                if self.tiles[y][x].char == 'S' {
                    print!("S");
                    continue;
                }
                if self.tiles[y][x].char == 'E' {
                    print!("E");
                    continue;
                }

                if let Some(reindeer) = reindeer {
                    let mut is_path = false;
                    for step in reindeer.path.iter() {
                        if step.coord == coord {
                            print!("{}", dir_to_char(step.dir));
                            is_path = true;
                            break;
                        }
                    }
                    if !is_path {
                        print!("{}", self.tiles[y][x]);
                    }
                } else if self.reindeers.len() > 1 {
                    let mut is_reindeer = false;
                    for r in self.reindeers.iter() {
                        let pos = r.pos;
                        if pos == coord {
                            print!("{}", dir_to_char(r.orientation));
                            is_reindeer = true;
                            break;
                        }
                    }
                    if !is_reindeer {
                        print!("{}", self.tiles[y][x]);
                    }
                } else {
                    print!("{}", self.tiles[y][x]);
                }
            }
            print!("\n");
        }
    }
}
