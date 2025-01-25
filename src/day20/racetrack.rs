use std::collections::{HashMap, HashSet};

use direction::{CardinalDirections, Coord};
use std::cmp;

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
    pub cheats: HashMap<usize, HashSet<Cheat>>,
    y_size: usize,
    x_size: usize,
}

impl Track {
    pub fn new(input: &str) -> Self {
        let mut segments: HashMap<Coord, Segment> = HashMap::new();
        let mut walls: HashSet<Coord> = HashSet::new();
        let mut start: Option<Coord> = None;
        let mut end: Option<Coord> = None;
        let mut y_size: usize = 0;
        let mut x_size: usize = 0;

        for (y, line) in input.split("\n").enumerate() {
            y_size = y + 1;
            for (x, c) in line.chars().enumerate() {
                x_size = x + 1;
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
            y_size,
            x_size,
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

    pub fn cheats(&mut self, min: usize) {
        let keys: Vec<Coord> = self.segments.keys().map(|coord| coord.clone()).collect();
        for coord in keys {
            self.cheat(coord, min);
        }
    }

    // cheat if possible
    fn cheat(&mut self, pos: Coord, min: usize) {
        let mut limit: usize = 20;
        if min == 0 {
            limit = 2;
        }

        let from_seg = self.segments.get(&pos).unwrap();

        for y in
            cmp::max(0, pos.y - limit as i32)..cmp::min(self.y_size as i32, pos.y + limit as i32)
        {
            let y_diff: usize = (y - pos.y).abs() as usize;
            let x_min = cmp::max(0, pos.x - (limit as i32 - y_diff as i32));
            let x_max = cmp::min(self.x_size as i32, pos.y + (limit as i32 - y_diff as i32));
            for x in x_min..x_max {
                let x_diff = (x - pos.x).abs() as usize;
                let cheat_len = x_diff + y_diff;
                let next_pos = Coord { x, y };
                if let Some(to_seg) = self.segments.get(&next_pos) {
                    // require min save
                    if from_seg.e_dist >= to_seg.e_dist + cheat_len + min {
                        let save = from_seg.e_dist - to_seg.e_dist - cheat_len;
                        let cheat = Cheat {
                            from: pos,
                            to: next_pos,
                        };
                        if let Some(cheats) = self.cheats.get_mut(&save) {
                            cheats.insert(cheat);
                        } else {
                            self.cheats.insert(save, HashSet::from([cheat]));
                        }
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
