struct Data {
    graph: Vec<Vec<usize>>,
    sum_subtree_dist: Vec<i32>,
    sz_subtree: Vec<i32>,
    sum_dist: Vec<i32>
}

impl Data {

    fn new(n: usize) -> Self {

        Self {
            graph: vec![vec![]; n],
            sum_subtree_dist: vec![0; n],
            sz_subtree: vec![0; n],
            sum_dist: vec![0; n]
        }
    }

    fn add_edge(&mut self, u: usize, v: usize) {
        self.graph[u].push(v);
        self.graph[v].push(u);
    }
}

impl Solution {
    pub fn sum_of_distances_in_tree(n: i32, edges: Vec<Vec<i32>>) -> Vec<i32> {
        
        let mut data = Data::new(n as usize);

        for edge in edges {
            assert_eq!(edge.len(), 2);
            let u = edge[0] as usize;
            let v = edge[1] as usize;
            data.add_edge(u as usize, v as usize);
        }

        Self::calculate_required_information(&mut data, 0, None);
        Self::calculate_sum_dist(&mut data, 0, None);

        data.sum_dist
    }

    fn calculate_required_information(data: &mut Data, u: usize, p: Option<usize>) {
        
        data.sz_subtree[u] = 1;
        data.sum_subtree_dist[u] = 0;

        for v in data.graph[u].clone() {
            if Some(v) == p {
                continue;
            }

            Self::calculate_required_information(data, v, Some(u));

            data.sz_subtree[u] += data.sz_subtree[v];
            data.sum_subtree_dist[u] += data.sum_subtree_dist[v] + data.sz_subtree[v];
        }
    }

    fn calculate_sum_dist(data: &mut Data, u: usize, p: Option<usize>) {
        
        data.sum_dist[u] = data.sum_subtree_dist[u];

        for v in data.graph[u].clone() {
            if Some(v) == p {
                continue;
            }

            let original_dist = data.sum_subtree_dist[v];
            let original_sz = data.sz_subtree[v];

            data.sum_subtree_dist[v] = data.sum_subtree_dist[u] + data.sz_subtree[u] - 2 * data.sz_subtree[v];
            data.sz_subtree[v] = data.sz_subtree[u];

            Self::calculate_sum_dist(data, v, Some(u));

            data.sz_subtree[v] = original_sz;
            data.sum_subtree_dist[v] = original_dist;
        }
    }
}