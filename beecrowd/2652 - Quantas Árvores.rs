#![allow(unused_imports)]
#![allow(dead_code)]
use std::collections::{BTreeMap, HashSet, VecDeque};
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

   fn read_line(&mut self) -> io::Result<String> {
      let mut input = String::new();

      match self.reader.read_line(&mut input) {
         Ok(0) => {
            return Err(Error::new(ErrorKind::UnexpectedEof, "End Of File"));
         } Ok(_) => {
            
         } Err(e) => {
            return Err(e);
         }
      }

      Ok(input)
   }
}

type Graph = Vec<Vec<usize>>;

struct Isomorphism {
   pattern: BTreeMap<Vec<i32>, i32>   
}

impl Isomorphism {

   fn new() -> Self {

      Self {
         pattern: BTreeMap::new()
      }
   }

   fn dfs(&mut self, g: &Graph, u: usize, p: usize) -> i32 {
      let mut patterns = Vec::new();

      for &v in g[u].iter() {
         if v != p {
            patterns.push(self.dfs(g, v, u));
         }
      }

      patterns.sort();

      if !self.pattern.contains_key(&patterns) {
         let id = self.pattern.len() as i32;

         self.pattern.insert(patterns, id);

         return id;
      }

      return *self.pattern.get(&patterns).unwrap();
   }

   fn get_tree_pattern(&mut self, g: &Graph, root: usize) -> i32 {
      return self.dfs(g, root, root);
   }
}

fn center(g: &Graph) -> Vec<usize> {
   let n = g.len();
   let mut deg = vec![0; n];
   let mut exc = vec![0; n];
   let mut queue = VecDeque::new();
   let mut max_exc = 0;

   for v in 0..n {
      deg[v] = g[v].len();

      if deg[v] == 1 {
         exc[v] = 0;
         queue.push_back(v);
      }
   }

   while !queue.is_empty() {
      let u = queue.pop_front().unwrap();

      max_exc = max_exc.max(exc[u]);

      for &v in g[u].iter() {
         deg[v] -= 1;

         if deg[v] == 1 {
            exc[v] = exc[u] + 1;
            queue.push_back(v);
         }
      }
   }

   let c = exc.iter()
   .enumerate()
   .filter(|p| *p.1 == max_exc)
   .map(|p| p.0)
   .collect::<Vec<usize>>();

   return c;
}

fn main() {
   let mut writer = io::BufWriter::new(io::stdout());

   let mut sc = Scanner::new();

   let n = sc.next::<usize>().unwrap();

   let mut trees = HashSet::new();

   let mut iso = Isomorphism::new();

   for _ in 0..n {
      let m = sc.next::<usize>().unwrap();

      let mut g = vec![vec![]; m];

      for i in 1..m {
         let j = sc.next::<usize>().unwrap() - 1;

         g[i].push(j);
         g[j].push(i);
      }

      let mut pattern = i32::MIN;

      for c in center(&g) {
         pattern = pattern.max(iso.get_tree_pattern(&g, c));
      }

      trees.insert(pattern);
   }

   writeln!(writer, "{}", trees.len()).ok();
}
