#![allow(dead_code)]
use std::{
    collections::VecDeque,
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

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new();

    while sc.has_next() {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();

        let mut adj = vec![vec![]; n];
        let mut keys_loc = vec![vec![]; n];
        let mut vis = vec![false; n];
        let mut at_border = vec![false; n];
        let mut has_key = vec![false; n];
        let mut queue = VecDeque::new();

        for _ in 0..m {
            let u = sc.next::<usize>() - 1;
            let v = sc.next::<usize>() - 1;

            adj[u].push(v);
            adj[v].push(u);
        }

        for i in 1..n {
            let loc = sc.next::<usize>() - 1;
            keys_loc[loc].push(i);
        }

        vis[0] = true;
        queue.push_back(0);

        while let Some(u) = queue.pop_front() {
            for &v in &keys_loc[u] {
                has_key[v] = true;

                if !vis[v] && at_border[v] {
                    vis[v] = true;
                    queue.push_back(v);
                }
            }

            for &v in &adj[u] {
                if vis[v] {
                    continue;
                } else if has_key[v] {
                    vis[v] = true;
                    queue.push_back(v);
                } else {
                    at_border[v] = true;
                }
            }
        }

        if vis.iter().all(|status| *status) {
            writeln!(writer, "sim").ok();
        } else {
            writeln!(writer, "nao").ok();
        }
    }
}
