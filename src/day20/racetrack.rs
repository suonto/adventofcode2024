use std::collections::{HashMap, HashSet};

use direction::{CardinalDirections, Coord};

/// track segment stores dist to start and end
#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
pub struct Segment {
    pub s_dist: usize,
    pub e_dist: usize,
}

///cheat stores from, to and save
#[derive(Debug, PartialEq, Eq, Hash, Clone, Copy)]
pub struct Cheat {
    pub from: Coord,
    pub to: Coord,
}

pub struct Track {
    pub start: Coord,
    pub end: Coord,
    segments: HashMap<Coord, Segment>,
    walls: HashSet<Coord>,
    pub cheats: HashMap<usize, Vec<Cheat>>,
}

impl Track {
    pub fn new(input: &str) -> Self {
        let mut segments: HashMap<Coord, Segment> = HashMap::new();
        let mut walls: HashSet<Coord> = HashSet::new();
        let mut start: Option<Coord> = None;
        let mut end: Option<Coord> = None;

        for (y, line) in input.split("\n").enumerate() {
            for (x, c) in line.chars().enumerate() {
                let coord = Coord {
                    x: x as i32,
                    y: y as i32,
                };

                if c == '.' {
                    segments.insert(
                        coord,
                        Segment {
                            s_dist: 0,
                            e_dist: 0,
                        },
                    );
                } else if c == '#' {
                    walls.insert(coord);
                } else if c == 'S' {
                    start = Some(coord);
                    segments.insert(
                        coord,
                        Segment {
                            s_dist: 0,
                            e_dist: 0,
                        },
                    );
                } else if c == 'E' {
                    end = Some(coord);
                    segments.insert(
                        coord,
                        Segment {
                            s_dist: 0,
                            e_dist: 0,
                        },
                    );
                } else {
                    panic!("Weird char: {:?}", c);
                }
            }
        }

        let start = start.unwrap();
        let end = end.unwrap();

        Self {
            start,
            end,
            segments,
            walls,
            cheats: HashMap::new(),
        }
    }

    /// populate segment distances
    pub fn populate(&mut self) {
        // populate start
        let track_len = self.segments.len() - 1;

        let mut pos_opt: Option<Coord> = Some(self.start);
        let mut s_dist: usize = 0;

        while let Some(pos) = pos_opt {
            let seg = self.segments.get_mut(&pos).unwrap();
            seg.s_dist = s_dist;
            seg.e_dist = track_len - s_dist;

            println!("Race track at {:?}: {:?}", &pos, &seg);
            pos_opt = self.next_pos(&pos);
            s_dist += 1;
        }
    }

    pub fn cheats(&mut self) {
        let keys: Vec<Coord> = self.segments.keys().map(|coord| coord.clone()).collect();
        for coord in keys {
            self.cheat(coord);
        }
    }

    // cheat if possible
    fn cheat(&mut self, pos: Coord) {
        for dir in CardinalDirections {
            let wall_pos = pos + dir.coord();
            let next_pos = wall_pos + dir.coord();
            if self.walls.contains(&wall_pos) && self.segments.contains_key(&next_pos) {
                let from_seg = self.segments.get(&pos).unwrap();
                let to_seg = self.segments.get(&next_pos).unwrap();
                if from_seg.e_dist > to_seg.e_dist {
                    // -2 due to it taking 2 picoseconds to get there
                    let save = from_seg.e_dist - to_seg.e_dist - 2;
                    let cheat = Cheat {
                        from: pos,
                        to: next_pos,
                    };
                    if let Some(cheats) = self.cheats.get_mut(&save) {
                        cheats.push(cheat);
                    } else {
                        self.cheats.insert(save, vec![cheat]);
                    }
                }
            }
        }
    }

    fn next_pos(&self, pos: &Coord) -> Option<Coord> {
        for dir in CardinalDirections {
            let next_pos = pos + dir.coord();
            if let Some(seg) = self.segments.get(&next_pos) {
                if seg.e_dist == 0 && seg.s_dist == 0 {
                    return Some(next_pos);
                }
            }
        }

        return None;
    }
}
