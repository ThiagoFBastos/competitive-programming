use std::cmp::Reverse;

impl Solution {
    pub fn largest_submatrix(mut matrix: Vec<Vec<i32>>) -> i32 {
        let r = matrix.len();
        let c = matrix[0].len();

        let mut last_zero = vec![r; c];
        let mut answer = 0;
        let mut height = Vec::with_capacity(c);

        for (low, row) in matrix.iter().enumerate().rev() {
            height.clear();

            for (j, &val) in row.iter().enumerate() {
                if val == 0 {
                    last_zero[j] = low;
                }

                let length = last_zero[j] - low;
                height.push(length as i32);
            }

            height.sort_by_key(|h| Reverse(*h));

            for (i, &h) in height.iter().enumerate() {
                let area = (i + 1) as i32 * h;
                answer = answer.max(area);
            }
        }

        answer
    }
}