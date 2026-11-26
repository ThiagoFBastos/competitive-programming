class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int greatest_commom_divisor {};

        for(const int val : nums)
            greatest_commom_divisor = gcd(greatest_commom_divisor, val);

        return greatest_commom_divisor == 1;
    }
};