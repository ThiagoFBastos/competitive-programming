impl Solution {

    pub fn all_paths_source_target(graph: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
        let mut paths = Vec::new();
        let mut cur_path = Vec::new();

        Self::retrieve_paths(&graph, &mut paths, &mut cur_path, 0);

        paths
    }

    fn retrieve_paths(graph: &[Vec<i32>], paths: &mut Vec<Vec<i32>>, cur_path: &mut Vec<i32>, u: usize) {
        let n = graph.len();

        cur_path.push(u as i32);

        if(u == n - 1) {
            paths.push(cur_path.clone());
        } else {
            for &v in graph[u].iter() {
                Self::retrieve_paths(graph, paths, cur_path, v as usize);
            }
        }

        cur_path.pop();
    }
}