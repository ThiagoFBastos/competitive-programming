impl Solution {
    pub fn maximum_sale_items(items: Vec<Vec<i32>>, budget: i32) -> i32 {
        const N: usize = 1501;
        const INF: i32 = 1_000_000_000;
        let mut factors = [0; N];
        let mut dp = [[-INF; N]; 2];

        for item in &items {
            assert_eq!(item.len(), 2);
            let factor = item[0];
            factors[factor as usize] += 1;
        }

        dp[0][0] = 0;

        for item in &items {
            let factor = item[0] as usize;
            let price = item[1] as usize;
            let mut multiples = 0;

            for i in (factor..N).step_by(factor) {
                multiples += factors[i];
            }

            for i in 0..=budget as usize {
                dp[1][i] = -INF;
            }

            for i in 0..=budget as usize {
                let sum = price + i;

                if sum > budget as usize {
                    break;
                }

                dp[1][sum] = dp[1][sum].max(dp[0][i] + multiples);
                dp[1][sum] = dp[1][sum].max(dp[1][i] + 1);
            }

            for i in 0..=budget as usize {
                dp[0][i] = dp[0][i].max(dp[1][i]);
            }
        }

        let answer = *dp[0].iter().max().unwrap();

        answer
    }
}