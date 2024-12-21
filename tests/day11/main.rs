#[cfg(test)]
mod tests {
    use aoc2024::day11::blink;

    #[test]
    fn test_blink_once() {
        let mut data: Vec<u64> = vec![125, 17];
        let expected: Vec<u64> = vec![253000, 1, 7];
        data = blink(&data);
        assert_eq!(data, expected);
    }

    #[test]
    fn test_blink_6_times() {
        let mut data: Vec<u64> = vec![125, 17];
        let expected: Vec<u64> = vec![
            2097446912, 14168, 4048, 2, 0, 2, 4, 40, 48, 2024, 40, 48, 80, 96, 2, 8, 6, 7, 6, 0, 3,
            2,
        ];
        for _i in 0..6 {
            data = blink(&data);
        }

        assert_eq!(data, expected);
    }

    #[test]
    fn test_blink_25_times() {
        let mut data: Vec<u64> = vec![125, 17];

        for _i in 0..25 {
            data = blink(&data);
        }

        assert_eq!(data.len(), 55312);
    }
}
