pub fn blink(data: &mut Vec<u32>) {
    for i in 0..data.len() {
        let x = data[i];
        if x == 0 {
            data[i] = 1;
        }

        let digits = x.to_string();
        let digits_count = digits.len();
        // 9999
        if digits_count % 2 == 0 {
            let front = &digits[0..(digits_count/2)];
            let back = &digits[(digits_count/2)..digits_count];

            // Convert front and back to u32 using unwrap
            let front: u32 = front.parse().unwrap();
            let back: u32 = back.parse().unwrap();

            data[i] = front;
            data.insert(i+1, back);
        }

    }
}