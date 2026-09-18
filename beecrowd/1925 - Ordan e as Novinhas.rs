#![allow(dead_code)]
use std::{
    collections::{HashSet, VecDeque},
    io::{self, Read, Write},
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

    let delta = [(0, 1), (0, -1), (1, 0), (-1, 0)];

    let r = sc.next::<usize>();
    let c = sc.next::<usize>();

    let mut location = None;
    let mut max_adj_places = -1;

    let grid = (0..r)
        .map(|_| sc.next::<String>().chars().collect::<Vec<_>>())
        .collect::<Vec<_>>();

    let mut connected_component_id = vec![vec![None; c]; r];
    let mut connected_component_size = Vec::new();
    let mut count_of_connected_components = 0;

    for (i, row) in grid.iter().enumerate() {
        for (j, &ch) in row.iter().enumerate() {
            if ch != 'n' || connected_component_id[i][j].is_some() {
                continue;
            }

            let mut queue = VecDeque::new();

            connected_component_size.push(0);
            connected_component_id[i][j] = Some(count_of_connected_components);
            queue.push_back((i, j));

            while let Some((x, y)) = queue.pop_front() {
                connected_component_size[count_of_connected_components] += 1;

                for &(dx, dy) in &delta {
                    let dest_x = x as i32 + dx;
                    let dest_y = y as i32 + dy;

                    if dest_x < 0 || dest_y < 0 || dest_x >= r as i32 || dest_y >= c as i32 {
                        continue;
                    }

                    let neigh_x = dest_x as usize;
                    let neigh_y = dest_y as usize;

                    if grid[neigh_x][neigh_y] != 'n'
                        || connected_component_id[neigh_x][neigh_y].is_some()
                    {
                        continue;
                    }

                    connected_component_id[neigh_x][neigh_y] = Some(count_of_connected_components);
                    queue.push_back((neigh_x, neigh_y));
                }
            }

            count_of_connected_components += 1;
        }
    }

    for (i, row) in grid.iter().enumerate() {
        for (j, &ch) in row.iter().enumerate() {
            if ch != '*' {
                continue;
            }

            let mut connected_components = HashSet::new();
            let mut adj_size = 0;

            for &(dx, dy) in &delta {
                let dest_x = i as i32 + dx;
                let dest_y = j as i32 + dy;

                if dest_x < 0 || dest_y < 0 || dest_x >= r as i32 || dest_y >= c as i32 {
                    continue;
                }

                let neigh_x = dest_x as usize;
                let neigh_y = dest_y as usize;

                if let Some(id) = connected_component_id[neigh_x][neigh_y] {
                    let size = connected_component_size[id];

                    if !connected_components.contains(&id) {
                        adj_size += size;
                        connected_components.insert(id);
                    }
                }
            }

            if adj_size > max_adj_places {
                max_adj_places = adj_size;
                location = Some((i, j));
            }
        }
    }

    assert!(location.is_some());

    let (i, j) = location.unwrap();

    writeln!(writer, "{},{}", i + 1, j + 1).ok();
}
