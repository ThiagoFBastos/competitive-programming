class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        const int bitwise_xor = ranges::fold_left(nums, 0, bit_xor<>());
        return __builtin_popcount(bitwise_xor ^ k);
    }
};