#[derive(Debug)]
pub struct Robot {
    pub x: i32,
    pub y: i32,
    pub dx: i32,
    pub dy: i32,
}

impl Robot {
    pub fn teleport(&mut self, steps: i32, x_dimension: i32, y_dimension: i32) {
        self.x = (self.x + (self.dx * steps) % x_dimension) + x_dimension;
        self.y = (self.y + self.dy * steps) % y_dimension + y_dimension;
        if self.x < 0 || self.y < 0 {
            panic!("invalid coords");
        }
    }
}
