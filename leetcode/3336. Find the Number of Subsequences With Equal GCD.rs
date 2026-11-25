impl Solution {
    pub fn subsequence_pair_count(nums: Vec<i32>) -> i32 {
        const MOD: i32 = 1_000_000_007;
        let N = *nums.iter().max().unwrap() as usize + 1;

        let mut dp = vec![0; N * N];
        let mut memo = vec![0; N * N];

        let gcd = |mut a: usize, mut b: usize| {
            if a > b {
                std::mem::swap(&mut a, &mut b);
            }

            while b != 0 {
                a %= b;
                std::mem::swap(&mut a, &mut b);
            }

            a
        };

        for i in 0..N {
            for j in 0..N {
                memo[i * N + j] = gcd(i, j);
            }
        }

        dp[0] = 1;

        let mut tmp = vec![0; N * N];

        for val in nums {
            tmp.copy_from_slice(&dp);

            for i in 0..N {
                let k = memo[i * N + val as usize];

                for j in 0..N {
                    tmp[k * N + j] += dp[i * N + j];

                    if tmp[k * N + j] >= MOD {
                        tmp[k * N + j] -= MOD;
                    }

                    let l = memo[j * N + val as usize];

                    tmp[i * N + l] += dp[i * N + j];

                    if tmp[i * N +l] >= MOD {
                        tmp[i * N + l] -= MOD;
                    }
                }
            }

            std::mem::swap(&mut dp, &mut tmp);
        }

        let mut answer = MOD - 1;

        for i in 0..N {
            let cnt = dp[i * N + i];
            answer = (answer + cnt) % MOD;
        }

        answer
    }
}