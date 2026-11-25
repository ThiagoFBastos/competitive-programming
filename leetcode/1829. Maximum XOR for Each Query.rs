impl Solution {
    pub fn get_maximum_xor(nums: Vec<i32>, maximum_bit: i32) -> Vec<i32> {
        let n = nums.len();
        let mut prefix = vec![0; n + 1];
        let mut answer = Vec::with_capacity(n);

        for i in 1..=n {
            prefix[i] = prefix[i - 1] ^ nums[i - 1];
        }

        for i in (0..n).rev() {
            let mask = 1 << maximum_bit;
            let k = !prefix[i + 1] & (mask - 1);

            answer.push(k);
        }

        answer
    }
}