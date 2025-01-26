use direction::{CardinalDirection, CardinalDirections, Coord};

fn dir_to_char(dir: &CardinalDirection) -> char {
    match dir {
        CardinalDirection::North => '^',
        CardinalDirection::East => '>',
        CardinalDirection::South => 'v',
        CardinalDirection::West => '<',
    }
}

#[derive(Debug, PartialEq, Eq)]
pub enum KeypadVariant {
    Numeric,
    Directional,
}

/// keypad
#[derive(Debug)]
pub struct Keypad {
    cursor: Coord,
    variant: KeypadVariant,
    pub output: Vec<char>,
}

impl Keypad {
    pub fn new(variant: KeypadVariant, output: Vec<char>) -> Self {
        let cursor = match variant {
            KeypadVariant::Numeric => Coord { y: 3, x: 2 },
            KeypadVariant::Directional => Coord { y: 0, x: 2 },
        };

        return Self {
            cursor,
            variant,
            output,
        };
    }
    fn to_coord(&self, c: &char) -> Coord {
        match self.variant {
            KeypadVariant::Numeric => match c {
                '0' => Coord { y: 3, x: 1 },
                'A' => Coord { y: 3, x: 2 },
                '1' => Coord { y: 2, x: 0 },
                '2' => Coord { y: 2, x: 1 },
                '3' => Coord { y: 2, x: 2 },
                '4' => Coord { y: 1, x: 0 },
                '5' => Coord { y: 1, x: 1 },
                '6' => Coord { y: 1, x: 2 },
                '7' => Coord { y: 0, x: 0 },
                '8' => Coord { y: 0, x: 1 },
                '9' => Coord { y: 0, x: 2 },
                _ => panic!("Invalid numeric {c}"),
            },
            KeypadVariant::Directional => match c {
                '^' => Coord { y: 0, x: 1 },
                'A' => Coord { y: 0, x: 2 },
                '<' => Coord { y: 1, x: 0 },
                'v' => Coord { y: 1, x: 1 },
                '>' => Coord { y: 1, x: 2 },
                _ => panic!("Invalid numeric {c}"),
            },
        }
    }

    // gen seq to press the given character, while moving the cursor
    fn press(&mut self, c: &char) -> Vec<char> {
        let mut result: Vec<char> = vec![];

        let target = self.to_coord(c);

        let mut dirs: Vec<CardinalDirection> = CardinalDirections.into_iter().collect();
        if self.variant == KeypadVariant::Directional {
            // Sort directions by their coordinate manhattan distance from cursor asc
            dirs.sort_by(|a, b| {
                a.coord()
                    .manhattan_distance(self.cursor)
                    .cmp(&b.coord().manhattan_distance(self.cursor))
            });
        }

        for dir in dirs {
            // while moving to that dir would make the cursor closer to target,
            // move to that direction
            while (self.cursor + dir.coord()).manhattan_distance(target)
                < self.cursor.manhattan_distance(target)
            {
                self.cursor += dir.coord();
                result.push(dir_to_char(&dir));
            }
        }

        result.push('A');

        return result;
    }

    // gen seq to press the output chars while moving the cursor
    pub fn input(&mut self) -> Vec<char> {
        let mut result: Vec<char> = vec![];

        for c in self.output.clone().iter() {
            let mut char_seq = self.press(c);
            result.append(&mut char_seq);
        }

        for c in result.iter() {
            print!("{c}");
        }
        println!();

        return result;
    }
}
