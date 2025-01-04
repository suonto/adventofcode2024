use std::collections::HashMap;

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

pub fn solve_b(example: &str) -> u32 {
    let x_dimension: i32 = 101;
    let y_dimension: i32 = 103;

    let mut robots = parse(example);

    let mut count: u32 = 0;
    loop {
        let mut positions: HashMap<[i32; 2], u32> = HashMap::new();

        /*
         * The first condition might be that the robots don't overlap.
         * Second condition might be that each robot has a neighbor.
         */
        let mut tree_possible = true;
        count += 1;
        for robot in robots.iter_mut() {
            robot.teleport(1, x_dimension, y_dimension);

            if !tree_possible {
                continue;
            }

            let pos: [i32; 2] = [robot.x, robot.y];

            if positions.contains_key(&pos) {
                println!("After {:?}, more than one robot at {:?}", count, pos);
                tree_possible = false;
            }

            let count = *positions.get(&pos).or(Some(&0)).unwrap();

            if tree_possible {
                positions.insert(pos, count + 1);
            }
        }

        if tree_possible {
            for y in 0..y_dimension {
                for x in 0..x_dimension {
                    let pos: [i32; 2] = [x, y];
                    let count = *positions.get(&pos).or(Some(&0)).unwrap();
                    if count == 0 {
                        print!(".");
                    } else {
                        print!("{}", count);
                    }
                }
                print!("\n");
            }
            println!("count {:?}", count);
            return count;
        }
    }
}

pub fn solve(example: &str) -> u32 {
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
        let result = solve(EXAMPLE);
        assert_eq!(result, 12);
    }
}
