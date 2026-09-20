#![allow(dead_code)]
use std::{
    collections::VecDeque,
    io::{self, Error, Read, Write},
    marker::PhantomData,
};

pub struct Scanner<R> {
    buffer: Vec<u8>,
    index: usize,
    reader: PhantomData<R>,
}

impl<R: Read> Scanner<R> {
    pub fn new(mut reader: R) -> Self {
        let mut input = Vec::new();

        reader.read_to_end(&mut input).unwrap();

        Self {
            buffer: input,
            index: 0,
            reader: PhantomData,
        }
    }

    pub fn has_next(&mut self) -> bool {
        while self.index < self.buffer.len() && self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        self.index < self.buffer.len()
    }

    #[allow(clippy::should_implement_trait)]
    pub fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
        if !self.has_next() {
            return Err(Error::new(io::ErrorKind::UnexpectedEof, "End Of File"));
        }

        let start = self.index;

        while self.index < self.buffer.len() && !self.buffer[self.index].is_ascii_whitespace() {
            self.index += 1;
        }

        let res = std::str::from_utf8(&self.buffer[start..self.index])
            .unwrap()
            .parse::<T>();

        if res.is_ok() {
            return Ok(res.ok().unwrap());
        }

        Err(Error::new(io::ErrorKind::InvalidInput, "Invalid Input"))
    }
}

pub struct ConvexHullTrick {
    cht: VecDeque<(i64, i64)>,
}

impl Default for ConvexHullTrick {
    fn default() -> Self {
        Self::new()
    }
}

pub trait Evaluation {
    fn evaluate(&mut self, x: i64) -> i64;
}

fn overshadow(a: (i64, i64), b: (i64, i64), c: (i64, i64)) -> bool {
    if a.0 == b.0 || b.0 == c.0 {
        return true;
    }

    let num1 = (b.1 - a.1) as i128;
    let den1 = (a.0 - b.0) as i128;

    let num2 = (c.1 - b.1) as i128;
    let den2 = (b.0 - c.0) as i128;

    num1 * den2 >= num2 * den1
}

fn value_of(function: (i64, i64), x: i64) -> i64 {
    function.0 * x + function.1
}

impl ConvexHullTrick {
    pub fn new() -> Self {
        Self {
            cht: VecDeque::new(),
        }
    }

    pub fn add(&mut self, function: (i64, i64)) {
        let mut len = self.cht.len();

        while len >= 2 && overshadow(self.cht[len - 2], self.cht[len - 1], function) {
            len -= 1;
            self.cht.pop_back();
        }

        self.cht.push_back(function);
    }
}

const INF: i64 = 1 << 62;

impl Evaluation for ConvexHullTrick {
    fn evaluate(&mut self, x: i64) -> i64 {
        if self.cht.is_empty() {
            return i64::MAX;
        }

        while self.cht.len() >= 2 {
            let v1 = value_of(self.cht[0], x);
            let v2 = value_of(self.cht[1], x);

            if v1 < v2 {
                break;
            }

            self.cht.pop_front();
        }

        let f = self.cht[0];

        value_of(f, x)
    }
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new(io::stdin());

    let n = sc.next::<usize>().unwrap();
    let b = sc.next::<i64>().unwrap();
    let c = sc.next::<i64>().unwrap();

    let mut f = vec![0; n + 1];
    let mut g = vec![0; n + 1];
    let mut dp = vec![vec![INF; n + 1]; 2];

    for i in 1..=n {
        let h = sc.next::<i64>().unwrap();
        f[i] = f[i - 1] + h;
        g[i] = g[i - 1] + i as i64 * h;
    }

    for i in 1..=n {
        let mut good = ConvexHullTrick::new();
        let mut bad = ConvexHullTrick::new();
        let mut answer = INF;

        if i == 1 {
            bad.add((0, 0));
        }

        for j in 1..=n {
            let k = j as i64;

            good.add((-k, dp[0][j] - g[j] + k * f[j]));

            let backward = good.evaluate(f[j]) + g[j];

            bad.add((-f[j], backward + g[j]));

            dp[1][j] = bad.evaluate(k) + f[j] * k - g[j];

            answer = answer.min(dp[1][j] + g[n] - g[j] - k * (f[n] - f[j]));
        }

        write!(writer, "{}", answer * c + b * i as i64).ok();

        if i < n {
            write!(writer, " ").ok();
        }

        dp.reverse();
    }

    writeln!(writer).ok();
}
