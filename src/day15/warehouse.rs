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

pub struct WarehouseA {
    walls: HashSet<Wall>,
    boxes: HashSet<Box>,
    x_size: usize,
    y_size: usize,
    // a robot named Jagger, as it moves
    jagger: Jagger,
}

impl WarehouseA {
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
        let (j_x, j_y) = WarehouseA::step(x, y, dir);

        // while there's a box in front, check what's in front of the box
        let mut push_boxes = false;
        let (mut n_x, mut n_y) = WarehouseA::step(x, y, dir);
        while self.boxes.contains(&Box { x: n_x, y: n_y }) {
            push_boxes = true;
            (n_x, n_y) = WarehouseA::step(n_x, n_y, dir);
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

pub struct WarehouseB {
    walls: HashSet<Wall>,
    boxes: HashSet<Box>,
    x_size: usize,
    y_size: usize,
    // a robot named Jagger, as it moves
    jagger: Jagger,
}

impl WarehouseB {
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
                x_size = line.len() * 2;
                y_size += 1;

                for (x, char) in line.chars().enumerate() {
                    if char == '#' {
                        walls.insert(Wall { x: x * 2, y });
                        walls.insert(Wall { x: x * 2 + 1, y });
                    } else if char == 'O' {
                        boxes.insert(Box { x: x * 2, y });
                    } else if char == '@' {
                        jagger_x = x * 2;
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
                    print!("[");
                    result += 100 * y as u32 + x as u32;
                } else if x > 1 && self.boxes.contains(&Box { x: x - 1, y }) {
                    print!("]");
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
        let (j_x, j_y) = WarehouseB::step(x, y, dir, 1);

        // if a wall is encountered, do not move
        if self.walls.contains(&Wall { x: j_x, y: j_y }) {
            return false;
        }

        // if a box is not encountered, move
        if !self.boxes.contains(&Box { x: j_x, y: j_y })
            && !self.boxes.contains(&Box { x: j_x - 1, y: j_y })
        {
            self.jagger.x = j_x;
            self.jagger.y = j_y;
            return true;
        }

        // if there is a box in front of jagger, begin box stack.
        // record current_boxes to be deleted and new boxes
        // in case there are any issues pushing boxes, return false
        let mut current_boxes: Vec<Box> = Vec::new();
        let mut moved_boxes: Vec<Box> = Vec::new();

        // vertical push
        if [CardinalDirection::North, CardinalDirection::South].contains(&dir) {
            let mut xses = HashSet::from([x]);
            let mut ny = y;

            loop {
                println!("Moving {:?} at y {:?}, xses: {:?}", dir, ny, xses);
                // false if any of the current xses is blocked from moving (by a wall)
                for nx in &xses {
                    let (step_x, step_y) = WarehouseB::step(*nx, ny, dir, 1);
                    if self.walls.contains(&Wall {
                        x: step_x,
                        y: step_y,
                    }) {
                        println!(
                            "Wall blocks ({:?},{:?}) -> ({:?},{:?})",
                            nx, ny, step_x, step_y
                        );
                        return false;
                    }
                }

                // resolve next boxes and add to stack
                let next_boxes = self.next_vertical_boxes(&xses, ny, dir);
                xses.clear();
                for bx in &next_boxes {
                    ny = bx.y;

                    // xses about to move
                    xses.insert(bx.x);
                    xses.insert(bx.x + 1);
                }

                // no more boxes
                if next_boxes.is_empty() {
                    break;
                }

                for bx in next_boxes {
                    let (nx, ny) = WarehouseB::step(bx.x, bx.y, dir, 1);
                    current_boxes.push(bx);

                    moved_boxes.push(Box { x: nx, y: ny });
                }
            }
        }

        // horizontal push
        if [CardinalDirection::East, CardinalDirection::West].contains(&dir) {
            let mut nx = x;
            let mut ny = y;
            loop {
                let (step_x, step_y) = WarehouseB::step(nx, ny, dir, 1);
                if self.walls.contains(&Wall {
                    x: step_x,
                    y: step_y,
                }) {
                    return false;
                }
                let next_box = self.next_horizontal_box(nx, ny, dir);

                if let Some(next_box) = next_box {
                    current_boxes.push(next_box);

                    moved_boxes.push(Box {
                        x: WarehouseB::step(nx, ny, dir, 3).0,
                        y: step_y,
                    });
                    (nx, ny) = WarehouseB::step(nx, ny, dir, 2);
                } else {
                    break;
                }
            }
        }

        // push boxes
        for rm_box in current_boxes {
            let (b_x, b_y) = WarehouseB::step(rm_box.x, rm_box.y, dir, 1);
            self.boxes.remove(&Box {
                x: rm_box.x,
                y: rm_box.y,
            });

            println!(
                "Push ({:?},{:?}) -> ({:?},{:?})",
                rm_box.x, rm_box.y, b_x, b_y
            );
        }

        for add_box in moved_boxes {
            self.boxes.insert(Box {
                x: add_box.x,
                y: add_box.y,
            });
        }

        // if there was no issue pushing boxes, move like Jagger
        self.jagger.x = j_x;
        self.jagger.y = j_y;

        return true;
    }

    fn next_vertical_boxes(
        &self,
        xses: &HashSet<usize>,
        y: usize,
        dir: CardinalDirection,
    ) -> Vec<Box> {
        let mut boxes: Vec<Box> = Vec::new();
        if [CardinalDirection::East, CardinalDirection::West].contains(&dir) {
            panic!("Invalid vertical dir {:?}", dir);
        }

        for x in xses {
            let (n_x, n_y) = WarehouseB::step(*x, y, dir, 1);
            let bx1 = Box { x: n_x, y: n_y };
            let bx2 = Box { x: n_x - 1, y: n_y };

            if self.boxes.contains(&bx1) {
                boxes.push(bx1);
            } else if self.boxes.contains(&bx2) {
                boxes.push(bx2);
            }
        }

        return boxes;
    }

    fn next_horizontal_box(&self, x: usize, y: usize, dir: CardinalDirection) -> Option<Box> {
        if [CardinalDirection::North, CardinalDirection::South].contains(&dir) {
            panic!("Invalid horizontal dir {:?}", dir);
        }

        let (n_x, n_y) = WarehouseB::step(x, y, dir, 2);
        let bx = Box { x: n_x, y: n_y };

        if self.boxes.contains(&bx) {
            return Some(bx);
        }

        return None;
    }

    // returns new x, new y
    fn step(x: usize, y: usize, dir: CardinalDirection, steps: usize) -> (usize, usize) {
        let mut n_x: usize = x;
        let mut n_y: usize = y;

        if dir == CardinalDirection::North {
            n_y -= steps;
        } else if dir == CardinalDirection::East {
            n_x += steps;
        } else if dir == CardinalDirection::South {
            n_y += steps;
        } else if dir == CardinalDirection::West {
            n_x -= steps;
        }

        return (n_x, n_y);
    }
}
