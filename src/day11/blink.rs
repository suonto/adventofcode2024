use std::collections::HashMap;

fn process_stone(stone: &u64) -> Vec<u64> {
    let mut result: Vec<u64> = Vec::new();
    if *stone == 0 {
        result.push(1);
        return result;
    }

    let digits: String = stone.to_string();
    let digits_count: usize = digits.len();

    if digits_count % 2 == 0 {
        let front = &digits[0..(digits_count / 2)];
        let back = &digits[(digits_count / 2)..digits_count];

        // Convert front and back to u64 using unwrap
        let front: u64 = front.parse().unwrap();
        let back: u64 = back.parse().unwrap();

        result.push(front);
        result.push(back);
        return result;
    }

    result.push(*stone * 2024);

    return result;
}

pub fn blink(data: &Vec<u64>) -> Vec<u64> {
    let mut vec: Vec<u64> = Vec::new();
    for x in data.iter() {
        for processed in process_stone(x) {
            vec.push(processed);
        }
    }
    return vec;
}

/**
 * Ingests a HashMap of stone and the count of that stone.
 * Blinks current stones, and returns a new HashMap.
 */
pub fn blink_b(data: &HashMap<u64, u64>) -> HashMap<u64, u64> {
    let mut result: HashMap<u64, u64> = HashMap::new();

    for (stone, count) in data.into_iter() {
        for processed in process_stone(stone) {
            *(result.entry(processed).or_insert(0)) += count;
        }
    }

    for (stone, count) in result.iter() {
        println!("stone {:?} count {:?}", stone, count);
    }

    return result;
}
