use aoc2024::day11::blink;

fn main() {
    let mut data: Vec<u64> = vec![7568, 155731, 0, 972, 1, 6919238, 80646, 22];
    for _i in 0..25 {
        data = blink(&data);
        println!("{:?}", data.len());
    }
}
