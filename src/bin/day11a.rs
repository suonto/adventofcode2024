use aoc2024::day11::blink;

fn main() {
    let mut data: Vec<u64> = vec![125, 17];
    for _i in 0..25 {
        data = blink(&data);
        println!("{:?}", data.len());
    }
}
