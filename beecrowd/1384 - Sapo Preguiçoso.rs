#![allow(dead_code)]
use std::{
    cmp::Reverse,
    collections::BinaryHeap,
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

#[derive(Debug, Clone, Copy)]
struct Delta {
    dx: i32,
    dy: i32,
    weight: i32,
}

fn main() {
    let mut writer = io::BufWriter::with_capacity(1 << 20, io::stdout());

    let mut sc = Scanner::new(io::stdin());

    let deltas = [
        // Peso 2
        Delta {
            dx: 0,
            dy: -1,
            weight: 2,
        },
        Delta {
            dx: -1,
            dy: 0,
            weight: 2,
        },
        Delta {
            dx: 1,
            dy: 0,
            weight: 2,
        },
        Delta {
            dx: 0,
            dy: 1,
            weight: 2,
        },
        // Peso 3
        Delta {
            dx: -1,
            dy: -1,
            weight: 3,
        },
        Delta {
            dx: 1,
            dy: -1,
            weight: 3,
        },
        Delta {
            dx: -1,
            dy: 1,
            weight: 3,
        },
        Delta {
            dx: 1,
            dy: 1,
            weight: 3,
        },
        // Peso 5
        Delta {
            dx: 0,
            dy: -2,
            weight: 5,
        },
        Delta {
            dx: -2,
            dy: 0,
            weight: 5,
        },
        Delta {
            dx: 2,
            dy: 0,
            weight: 5,
        },
        Delta {
            dx: 0,
            dy: 2,
            weight: 5,
        },
        // Peso 6
        Delta {
            dx: -1,
            dy: -2,
            weight: 6,
        },
        Delta {
            dx: 1,
            dy: -2,
            weight: 6,
        },
        Delta {
            dx: -2,
            dy: -1,
            weight: 6,
        },
        Delta {
            dx: 2,
            dy: -1,
            weight: 6,
        },
        Delta {
            dx: -2,
            dy: 1,
            weight: 6,
        },
        Delta {
            dx: 2,
            dy: 1,
            weight: 6,
        },
        Delta {
            dx: -1,
            dy: 2,
            weight: 6,
        },
        Delta {
            dx: 1,
            dy: 2,
            weight: 6,
        },
        // Peso 7
        Delta {
            dx: -2,
            dy: -2,
            weight: 7,
        },
        Delta {
            dx: 2,
            dy: -2,
            weight: 7,
        },
        Delta {
            dx: -2,
            dy: 2,
            weight: 7,
        },
        Delta {
            dx: 2,
            dy: 2,
            weight: 7,
        },
    ];

    const INF: i32 = 1_000_000_000;

    while sc.has_next() {
        let columns = sc.next::<usize>().unwrap();
        let rows = sc.next::<usize>().unwrap();

        if columns + rows == 0 {
            break;
        }

        let starting_col = sc.next::<usize>().unwrap();
        let starting_row = sc.next::<usize>().unwrap();

        let ending_col = sc.next::<usize>().unwrap();
        let ending_row = sc.next::<usize>().unwrap();

        let wet = sc.next::<usize>().unwrap();

        let mut marked = vec![vec![0; columns + 2]; rows + 2];
        let mut cost = vec![vec![INF; columns + 1]; rows + 1];

        for _ in 0..wet {
            let x0 = sc.next::<usize>().unwrap();
            let y0 = sc.next::<usize>().unwrap();

            let x1 = sc.next::<usize>().unwrap();
            let y1 = sc.next::<usize>().unwrap();

            marked[y0][x0] += 1;
            marked[y1 + 1][x0] -= 1;
            marked[y0][x1 + 1] -= 1;
            marked[y1 + 1][x1 + 1] += 1;
        }

        for i in 1..=rows {
            for j in 1..=columns {
                marked[i][j] += marked[i - 1][j] + marked[i][j - 1] - marked[i - 1][j - 1];
            }
        }

        let mut pq = BinaryHeap::new();

        pq.push(Reverse((0, starting_row, starting_col)));
        cost[starting_row][starting_col] = 0;

        while let Some(Reverse((cst, x, y))) = pq.pop() {
            if cst != cost[x][y] {
                continue;
            }

            let ix = x as i32;
            let iy = y as i32;

            for &delta in &deltas {
                let dx = delta.dx;
                let dy = delta.dy;
                let w = delta.weight;

                let target_x = ix + dx;
                let target_y = iy + dy;

                if target_x <= 0
                    || target_y <= 0
                    || target_x > rows as i32
                    || target_y > columns as i32
                {
                    continue;
                }

                let utarget_x = target_x as usize;
                let utarget_y = target_y as usize;

                if marked[utarget_x][utarget_y] > 0 || cost[utarget_x][utarget_y] <= cost[x][y] + w
                {
                    continue;
                }

                cost[utarget_x][utarget_y] = cost[x][y] + w;
                pq.push(Reverse((cost[utarget_x][utarget_y], utarget_x, utarget_y)));
            }
        }

        let cost = cost[ending_row][ending_col];

        if cost == INF {
            writeln!(writer, "impossible").ok();
        } else {
            writeln!(writer, "{}", cost).ok();
        }
    }
}
