class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        constexpr int INF = numeric_limits<int>::max();

		const int n1 = static_cast<int>(nums1.size());
        const int n2 = static_cast<int>(nums2.size());

        auto get = [INF](const auto& nums, int idx) {
            if(idx == 0)
                return -INF;
            else if(idx > (int)nums.size())
                return INF;
            return nums[idx - 1];
        };

        int lo1 = 0, hi1 = n1;
        int lo2 = 0, hi2 = n2;
        const int m = n1 + n2;

        while(lo1 < hi1 || lo2 < hi2) {
            const int m1 = (lo1 + hi1) / 2;
            const int m2 = (lo2 + hi2) / 2;
            
            if(m1 + m2 >= (m + 2 - m % 2) / 2) {
                if(lo1 < hi1 && lo2 < hi2) {
                    if(get(nums1, m1) > get(nums2, m2))
                        hi1 = m1;
                    else
                        hi2 = m2;
                } else if(lo1 < hi1)
                    hi1 = m1;
                else
                    hi2 = m2;
            } else if(lo1 < hi1 && lo2 < hi2) {
                if(get(nums1, m1 + 1) < get(nums2, m2 + 1))
                    lo1 = m1 + 1;
                else
                    lo2 = m2 + 1;
            } else if(lo1 < hi1)
                lo1 = m1 + 1;
            else 
                lo2 = m2 + 1;
        }

        if(m % 2)
            return max<double>(get(nums1, hi1), get(nums2, hi2));

        double median = 0; 

        for(int i = 0; i < 2; ++i) {
            if(get(nums1, hi1) > get(nums2, hi2))
                median += get(nums1, hi1--);
            else
                median += get(nums2, hi2--);
        }

        return median / 2.0;
    }
};