#[derive(Debug, PartialEq, Eq, Hash, Clone)]
pub struct Computer {
    pub a: u32,
    pub b: u32,
    pub c: u32,
    pub program: Vec<u32>,
}

impl Computer {
    pub fn new(input: &str) -> Self {
        let mut a: u32 = 0;
        let mut b: u32 = 0;
        let mut c: u32 = 0;
        let mut program: Vec<u32> = Vec::new();
        for line in input.lines() {
            if line.len() == 0 {
                continue;
            }

            if line.starts_with("R") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                let reg: Vec<char> = parts[1].chars().collect();
                let reg = reg[0];
                let val: u32 = parts[2].trim().parse().unwrap();
                if reg == 'A' {
                    a = val;
                } else if reg == 'B' {
                    b = val;
                } else {
                    c = val;
                }
            } else {
                let parts: Vec<&str> = line.split_whitespace().collect();
                println!("{:?}", parts[1]);
                for c in parts[1].split(',') {
                    let val: u32 = c.parse().unwrap();
                    program.push(val);
                }
            }
        }

        Self { a, b, c, program }
    }
}
