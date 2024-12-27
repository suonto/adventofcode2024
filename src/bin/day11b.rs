use std::collections::HashMap;

use aoc2024::day11::blink_b;

fn main() {
    let mut data: HashMap<u64, u64> = HashMap::from([(125, 1), (17, 1)]);
    for i in 0..75 {
        data = blink_b(&data);

        let mut total: u64 = 0;
        for count in data.values() {
            total += count;
        }
        println!("after blinking {:?} times: {:?}", i + 1, total);
    }
}
