pub fn blink(data: &Vec<u64>) -> Vec<u64> {
    let mut vec: Vec<u64> = Vec::new();
    for x in data.iter() {
        if *x == 0 {
            vec.push(1);
            continue;
        }

        let digits: String = x.to_string();
        let digits_count: usize = digits.len();

        if digits_count % 2 == 0 {
            let front = &digits[0..(digits_count / 2)];
            let back = &digits[(digits_count / 2)..digits_count];

            // Convert front and back to u64 using unwrap
            let front: u64 = front.parse().unwrap();
            let back: u64 = back.parse().unwrap();

            vec.push(front);
            vec.push(back);
            continue;
        }

        vec.push(*x * 2024);
    }
    return vec;
}
