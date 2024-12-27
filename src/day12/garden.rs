use std::{collections::HashMap, hash::Hash};

#[derive(PartialEq, Eq, Hash)]
pub struct Pos {
    pub x: usize,
    pub y: usize,
}

pub struct Region {
    // id is the Westernmost Plot of the Northest row of the region.
    pub id: Pos,
    pub area: u32,
    pub perimeter: u32,
}

impl Hash for Region {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.id.hash(state);
    }
}

impl Eq for Region {}

impl PartialEq for Region {
    fn eq(&self, other: &Self) -> bool {
        self.id == other.id
    }
}

pub struct Plot {
    // pub region_id: Pos,
    pub pos: Pos,
    pub plant: char,
    pub fences: HashMap<direction::CardinalDirection, bool>,
}

impl Plot {
    pub fn new(pos: Pos, plant: char) -> Self {
        Self {
            pos,
            plant,
            fences: HashMap::from([
                (direction::CardinalDirection::North, false),
                (direction::CardinalDirection::East, false),
                (direction::CardinalDirection::South, false),
                (direction::CardinalDirection::West, false),
            ]),
        }
    }
}

impl Hash for Plot {
    fn hash<H: std::hash::Hasher>(&self, state: &mut H) {
        self.pos.hash(state);
    }
}

impl Eq for Plot {}

impl PartialEq for Plot {
    fn eq(&self, other: &Self) -> bool {
        self.pos == other.pos
    }
}
