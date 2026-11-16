#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{VecDeque};
use std::io::{self, BufRead, Error, ErrorKind, Read, Write};
 
struct Scanner {
   buffer: VecDeque<String>,
   reader: io::BufReader<io::Stdin>
}
 
impl Scanner {
 
   fn new() -> Self {
      Self {
         buffer: VecDeque::new(),
         reader: io::BufReader::new(io::stdin())
      }
   }
   
   fn next<T: std::str::FromStr>(&mut self) -> io::Result<T> {
 
      if self.buffer.is_empty() {
         let mut input = String::new();
 
         match self.reader.read_line(&mut input) {
            Ok(0) => {
               return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
            } Ok(_) => {
               
            } Err(e) => {
               return Err(e);
            }
         }
 
         self.buffer = input.split_whitespace()
                            .map(|x| x.to_string())
                            .collect();
 
         if self.buffer.is_empty() {
            self.buffer.push_back("".to_string());
         }
      }
 
      let front = self.buffer.pop_front().unwrap();
      
      Ok(front.parse::<T>().ok().unwrap())
   }
 
   fn ignore(&mut self) {
      if !self.buffer.is_empty() {
         self.buffer.pop_front();
      }
   }
}
 
#[derive(Clone, Copy, Default)]
struct Node {
   sum: i64,
   prefix: i64,
   suffix: i64,
   max_sum: i64
}
 
impl Node {
 
   fn new(value: i64) -> Self {
 
      Self {
         sum: value,
         prefix: value,
         suffix: value,
         max_sum: value
      }
   }
}
 
mod data_structures {
 
   pub mod ranges {
 
      pub struct SegTree<T, OP> where OP: Fn(T, T) -> T {
         data: Vec<T>,
         size: usize,
         op: OP
      }
 
      impl<T: Copy + Default, OP> SegTree<T, OP> where OP: Fn(T, T) -> T {
 
         pub fn new(values: &[T], op: OP) -> Self {
            let n = values.len();
 
            let mut st = Self {
               data: vec![T::default(); 4 * n],
               size: values.len(),
               op
            };
 
            st.build(values, 0, n - 1, 1);
 
            return st;
         }
 
         fn build(&mut self, values: &[T], lo: usize, hi: usize, p: usize) {
            if lo == hi {
               self.data[p] = values[lo];
               return;
            }
 
            let mid = (lo + hi) / 2;
 
            self.build(values, lo, mid, 2 * p);
            self.build(values, mid + 1, hi, 2 * p + 1);
 
            self.data[p] = (self.op)(self.data[2 * p], self.data[2 * p + 1]);
         }
 
         fn change(&mut self, k: usize, value: T, lo: usize, hi: usize, p: usize) {
            if lo == hi {
               self.data[p] = value;
               return;
            }
 
            let mid = (lo + hi) / 2;
 
            if k <= mid {
               self.change(k, value, lo, mid, 2 * p);
            } else {
               self.change(k, value, mid + 1, hi, 2 * p + 1);
            }
 
            self.data[p] = (self.op)(self.data[2 * p], self.data[2 * p + 1]);
         }
 
         fn answer(&self, l: usize, r: usize, lo: usize, hi: usize, p: usize) -> T {
            if lo >= l && hi <= r {
               return self.data[p];
            }
 
            let mid = (lo + hi) / 2;
 
            if r <= mid {
               return self.answer(l, r, lo, mid, 2 * p);
            } else if l > mid {
               return self.answer(l, r, mid + 1, hi, 2 * p + 1);
            }
 
            let res1 = self.answer(l, r, lo, mid, 2 * p);
            let res2 = self.answer(l, r, mid + 1, hi, 2 * p + 1);
 
            return (self.op)(res1, res2);
         }
 
         pub fn update(&mut self, k: usize, value: T) {
            assert!(k < self.size);
            self.change(k, value, 0, self.size - 1, 1);
         }
 
         pub fn query(&self, l: usize, r: usize) -> T {
            assert!(l <= r && r < self.size);
            return self.answer(l, r, 0, self.size - 1, 1);
         }
      }
   }
}
 
fn main() {
   let mut handle = io::BufWriter::new(io::stdout());
 
   let mut sc = Scanner::new();
 
   let n = sc.next::<usize>().unwrap();
   let q = sc.next::<usize>().unwrap();
 
   let values = (0..n).map(|_| Node::new(sc.next::<i64>().unwrap())).collect::<Vec<_>>();
 
   let operation = |a: Node, b: Node| {
 
      Node {
         sum: a.sum + b.sum,
         prefix: a.prefix.max(a.sum + b.prefix),
         suffix: b.suffix.max(a.suffix + b.sum),
         max_sum: a.max_sum.max(b.max_sum.max(a.suffix + b.prefix))
      }
   };
 
   let mut st = data_structures::ranges::SegTree::new(&values, operation);
   
   for _ in 0..q {
 
      let k = sc.next::<usize>().unwrap() - 1;
      let value = sc.next::<i64>().unwrap();
 
      st.update(k, Node::new(value));
 
      writeln!(handle, "{}", st.query(0, n - 1).max_sum.max(0)).ok();
   }
}