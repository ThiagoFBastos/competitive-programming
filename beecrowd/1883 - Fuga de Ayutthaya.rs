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

    let t = sc.next::<usize>();

    let delta = [(1, 0), (-1, 0), (0, 1), (0, -1)];

    for _ in 0..t {
        let n = sc.next::<usize>();
        let m = sc.next::<usize>();

        let grid = (0..n)
            .map(|_| sc.next::<String>().chars().collect::<Vec<_>>())
            .collect::<Vec<_>>();

        let mut starting = None;
        let mut ending = None;

        let mut fire_time = vec![vec![-1; m]; n];
        let mut my_time = vec![vec![-1; m]; n];

        let mut queue = VecDeque::new();

        for (i, row) in grid.iter().enumerate() {
            for (j, &c) in row.iter().enumerate() {
                if c == 'S' {
                    starting = Some((i, j));
                } else if c == 'E' {
                    ending = Some((i, j));
                } else if c == 'F' {
                    queue.push_back((i, j));
                }
            }
        }

        assert!(starting.is_some());

        while let Some((x, y)) = queue.pop_front() {
            for &(dx, dy) in &delta {
                let dest_x = x as i32 + dx;
                let dest_y = y as i32 + dy;

                if dest_x < 0 || dest_y < 0 || dest_x >= n as i32 || dest_y >= m as i32 {
                    continue;
                }

                let n_x = dest_x as usize;
                let n_y = dest_y as usize;

                if fire_time[n_x][n_y] != -1 || grid[n_x][n_y] == '#' {
                    continue;
                }

                fire_time[n_x][n_y] = fire_time[x][y] + 1;
                queue.push_back((n_x, n_y));
            }
        }

        let (x0, y0) = starting.unwrap();

        queue.push_back((x0, y0));

        while let Some((x, y)) = queue.pop_front() {
            if Some((x, y)) == ending {
                break;
            }

            for &(dx, dy) in &delta {
                let dest_x = x as i32 + dx;
                let dest_y = y as i32 + dy;

                if dest_x < 0 || dest_y < 0 || dest_x >= n as i32 || dest_y >= m as i32 {
                    continue;
                }

                let n_x = dest_x as usize;
                let n_y = dest_y as usize;

                if my_time[n_x][n_y] != -1
                    || fire_time[n_x][n_y] <= my_time[x][y] + 1
                    || grid[n_x][n_y] == '#'
                {
                    continue;
                }

                my_time[n_x][n_y] = my_time[x][y] + 1;
                queue.push_back((n_x, n_y));
            }
        }

        if let Some((xf, yf)) = ending {
            if my_time[xf][yf] != -1 {
                writeln!(writer, "Y").ok();
            } else {
                writeln!(writer, "N").ok();
            }
        } else {
            writeln!(writer, "N").ok();
        }
    }
}
