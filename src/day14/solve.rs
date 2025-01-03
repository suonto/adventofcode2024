use super::Robot;

pub fn parse(example: &str) -> Vec<Robot> {
    let mut robots: Vec<Robot> = Vec::new();

    for line in example.split("\n") {
        let parts: Vec<&str> = line.split_whitespace().collect();

        let pos_part = parts[0];
        let pos = &pos_part[2..];
        let coords: Vec<&str> = pos.split(',').collect();
        let x: i32 = coords[0].parse().unwrap();
        let y: i32 = coords[1].parse().unwrap();

        let velocity_part = parts[1];
        let velocity = &velocity_part[2..];
        let components: Vec<&str> = velocity.split(',').collect();
        let dx: i32 = components[0].parse().unwrap();
        let dy: i32 = components[1].parse().unwrap();

        robots.push(Robot { x, y, dx, dy });
    }

    return robots;
}

pub fn solve(example: &str, _variant_b: bool) -> u32 {
    let y_dimension: i32 = 7;
    let x_dimension: i32 = 11;

    let mut q1: u32 = 0;
    let mut q2: u32 = 0;
    let mut q3: u32 = 0;
    let mut q4: u32 = 0;
    for mut robot in parse(example) {
        robot.teleport(100, x_dimension, y_dimension);

        if robot.y < y_dimension / 2 {
            if robot.x < x_dimension / 2 {
                q1 += 1;
            } else if robot.x > x_dimension / 2 {
                q2 += 1;
            }
        } else if robot.y > y_dimension / 2 {
            if robot.x < x_dimension / 2 {
                q3 += 1;
            } else if robot.x > x_dimension / 2 {
                q4 += 1;
            }
        }
    }

    let result = q1 * q2 * q3 * q4;

    println!("{:?} * {:?} * {:?} * {:?} = {:?}", q1, q2, q3, q4, result);

    return result;
}

#[cfg(test)]
mod tests {

    use super::super::EXAMPLE;
    use super::*;

    #[test]
    fn solve_a_example() {
        let result = solve(EXAMPLE, false);
        assert_eq!(result, 12);
    }
}
