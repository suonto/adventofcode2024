#[derive(Debug, PartialEq, Eq, Hash, Clone)]
pub struct Computer {
    pub a: usize,
    pub b: usize,
    pub c: usize,
    pub program: Vec<usize>,
    pub output: Vec<usize>,
}

impl Computer {
    pub fn new(input: &str) -> Self {
        let mut a: usize = 0;
        let mut b: usize = 0;
        let mut c: usize = 0;
        let mut program: Vec<usize> = Vec::new();
        for line in input.lines() {
            if line.len() == 0 {
                continue;
            }

            if line.starts_with("R") {
                let parts: Vec<&str> = line.split_whitespace().collect();
                let reg: Vec<char> = parts[1].chars().collect();
                let reg = reg[0];
                let val: usize = parts[2].trim().parse().unwrap();
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
                    let val: usize = c.parse().unwrap();
                    program.push(val);
                }
            }
        }

        Self {
            a,
            b,
            c,
            program,
            output: Vec::new(),
        }
    }

    pub fn run(&mut self) {
        let mut i = 0;
        while i < self.program.len() {
            i = self.exec(i);
        }
    }

    pub fn output(&self) -> String {
        let mut result = String::new();
        for i in &self.output {
            result.push_str(&i.to_string());
            result.push(',');
        }
        return result.trim_end_matches(',').to_string();
    }

    /// execute one, return next instruction index
    fn exec(&mut self, i: usize) -> usize {
        let opcode = self.program[i];
        let operand = self.program[i + 1];

        // adv
        if opcode == 0 {
            self.a = self.division(operand);
        }
        // bxl
        else if opcode == 1 {
            self.b = self.b ^ operand;
        }
        // bst
        else if opcode == 2 {
            let combo_operand = self.combo(operand);
            self.b = combo_operand % 8;
        }
        // jnz
        else if opcode == 3 {
            if self.a != 0 {
                return operand;
            }
        }
        // bxc
        else if opcode == 4 {
            self.b = self.b ^ self.c;
        }
        // out
        else if opcode == 5 {
            let combo_operand = self.combo(operand);
            self.output.push(combo_operand % 8);
        }
        // bdv
        else if opcode == 6 {
            self.b = self.division(operand);
        }
        // jro
        else if opcode == 7 {
            self.c = self.division(operand);
        }
        return i + 2;
    }

    fn division(&self, operand: usize) -> usize {
        let numerator = self.a;
        let base: usize = 2;
        let combo_operand = self.combo(operand);
        let denominator: usize = base.pow(combo_operand as u32);
        return numerator / denominator;
    }

    fn combo(&self, operand: usize) -> usize {
        if operand < 4 {
            return operand;
        }

        if operand == 4 {
            return self.a;
        } else if operand == 5 {
            return self.b;
        } else if operand == 6 {
            return self.c;
        }

        panic!("Invalid operand: {}", operand);
    }
}
