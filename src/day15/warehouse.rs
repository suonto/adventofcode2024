use std::collections::HashSet;

use direction::CardinalDirection;

#[derive(Debug, PartialEq, Eq, Hash)]
struct Box {
    pub x: usize,
    pub y: usize,
}

#[derive(Debug, PartialEq, Eq, Hash)]
struct Wall {
    pub x: usize,
    pub y: usize,
}

// There's only one robot. Intuitively named Jagger.
struct Jagger {
    pub x: usize,
    pub y: usize,
    pub moves: Vec<CardinalDirection>,
}

pub struct Warehouse {
    walls: HashSet<Wall>,
    boxes: HashSet<Box>,
    x_size: usize,
    y_size: usize,
    // a robot named Jagger, as it moves
    jagger: Jagger,
}

impl Warehouse {
    pub fn new(input: &str) -> Self {
        let mut walls: HashSet<Wall> = HashSet::new();
        let mut boxes: HashSet<Box> = HashSet::new();

        let mut y_size: usize = 0;
        let mut x_size: usize = 0;

        let mut jagger_x: usize = 0;
        let mut jagger_y: usize = 0;
        let mut jagger_moves: Vec<CardinalDirection> = Vec::new();

        for (y, line) in input.split("\n").enumerate() {
            if line.is_empty() {
                continue;
            }

            if line.starts_with('#') {
                x_size = line.len();
                y_size += 1;

                for (x, char) in line.chars().enumerate() {
                    if char == '#' {
                        walls.insert(Wall { x, y });
                    } else if char == 'O' {
                        boxes.insert(Box { x, y });
                    } else if char == '@' {
                        jagger_x = x;
                        jagger_y = y;
                    }
                }
            } else {
                for m in line.chars() {
                    if m == '^' {
                        jagger_moves.push(CardinalDirection::North);
                    } else if m == '>' {
                        jagger_moves.push(CardinalDirection::East);
                    } else if m == 'v' {
                        jagger_moves.push(CardinalDirection::South);
                    } else {
                        jagger_moves.push(CardinalDirection::West);
                    }
                }
            }
        }
        Self {
            walls,
            boxes,
            x_size,
            y_size,
            jagger: Jagger {
                x: jagger_x,
                y: jagger_y,
                moves: jagger_moves,
            },
        }
    }

    pub fn print(&self) -> u32 {
        let mut result: u32 = 0;
        for y in 0..self.y_size {
            for x in 0..self.x_size {
                if self.boxes.contains(&Box { x, y }) {
                    print!("O");
                    result += 100 * y as u32 + x as u32;
                } else if self.walls.contains(&Wall { x, y }) {
                    print!("#");
                } else if self.jagger.x == x && self.jagger.y == y {
                    print!("@");
                } else {
                    print!(".");
                }
            }
            print!("\n");
        }

        return result;
    }

    pub fn do_moves_like_jagger(&mut self) {
        for i in 0..self.jagger.moves.len() {
            self.move_jagger(i);
            self.print();
            println!();
        }
    }

    fn move_jagger(&mut self, i: usize) -> bool {
        let x = self.jagger.x;
        let y = self.jagger.y;
        let dir = self.jagger.moves[i];
        println!("Move {:?}:", dir);

        // new position of jagger if it moves
        let (j_x, j_y) = Warehouse::step(x, y, dir);

        // while there's a box in front, check what's in front of the box
        let mut push_boxes = false;
        let (mut n_x, mut n_y) = Warehouse::step(x, y, dir);
        while self.boxes.contains(&Box { x: n_x, y: n_y }) {
            push_boxes = true;
            (n_x, n_y) = Warehouse::step(n_x, n_y, dir);
        }

        // if a wall is encountered, nothing moves
        if self.walls.contains(&Wall { x: n_x, y: n_y }) {
            return false;
        }

        // push boxes
        if push_boxes {
            println!("Push ({:?},{:?}) -> ({:?},{:?})", j_x, j_y, n_x, n_y);
            self.boxes.insert(Box { x: n_x, y: n_y });
            self.boxes.remove(&Box { x: j_x, y: j_y });
        }

        // move like Jagger
        self.jagger.x = j_x;
        self.jagger.y = j_y;

        return true;
    }

    fn step(x: usize, y: usize, dir: CardinalDirection) -> (usize, usize) {
        let mut n_x: usize = x;
        let mut n_y: usize = y;

        if dir == CardinalDirection::North {
            n_y -= 1;
        } else if dir == CardinalDirection::East {
            n_x += 1;
        } else if dir == CardinalDirection::South {
            n_y += 1;
        } else if dir == CardinalDirection::West {
            n_x -= 1;
        }

        return (n_x, n_y);
    }
}
