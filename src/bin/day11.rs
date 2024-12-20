use aoc2024::day11::blink;


fn main() {
    let mut data = vec![1, 2, 3, 4, 5];
    blink(&mut data);
    println!("{:?}", data);
}
