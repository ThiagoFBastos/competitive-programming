#![allow(dead_code)]
use std::{
    io::{self, Read, Write},
    writeln,
};

struct Scanner {
    buffer: Vec<u8>,
    index: usize,
}

impl Scanner {
    fn new() -> Self {
        let mut input = Vec::new();

        io::stdin().read_to_end(&mut input).unwrap();

        Self {
            buffer: input,
            index: 0,
        }
    }

    fn has_next(&mut self) -> bool {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        self.index < self.buffer.len()
    }

    fn next<T: std::str::FromStr>(&mut self) -> T {
        if !self.has_next() {
            panic!("End Of File");
        }

        let start = self.index;

        while self.index < self.buffer.len() && !self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        std::str::from_utf8(&self.buffer[start..self.index])
            .unwrap()
            .parse::<T>()
            .ok()
            .unwrap()
    }
}

fn removal_game(nums: &[i64]) -> i64 {
    const INF: i64 = 0x1000000000000;

    let n = nums.len();
    let mut turn = !n & 1;
    let sum = nums.iter().sum::<i64>();

    let mut dp = vec![[0, 0]; n];

    for i in 0..n {
        dp[i][turn] = nums[i];
    }

    for len in (1..n).rev() {
        turn ^= 1;

        let my = turn;
        let your = turn ^ 1;

        for item in dp.iter_mut().take(len) {
            item[my] = -INF;
        }

        for i in 0..len {
            dp[i][my] = dp[i][my].max(nums[i] - dp[i + 1][your]);
        }

        for i in 0..len {
            dp[i][my] = dp[i][my].max(nums[i + n - len] - dp[i][your]);
        }
    }

    (sum + dp[0][0]) / 2
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    while sc.has_next() {
        let n = sc.next::<usize>();

        let nums = (0..n).map(|_| sc.next::<i64>()).collect::<Vec<_>>();

        writeln!(writer, "{}", removal_game(&nums)).ok();
    }
}
