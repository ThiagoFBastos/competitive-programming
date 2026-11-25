use std::cmp::Reverse;

impl Solution {
    pub fn max_satisfaction(mut satisfaction: Vec<i32>) -> i32 {
        satisfaction.sort_by_key(|v| Reverse(*v));
    
        let mut sum = 0;
        let mut current_coefficient = 0;
        let mut coefficient = 0;

        for v in satisfaction {
            sum += v;
            current_coefficient += sum;
            coefficient = coefficient.max(current_coefficient);
        }

        coefficient
    }
}