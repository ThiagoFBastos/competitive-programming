template<int N>
struct SuffixArray {
	int tsa[N], c[N], tc[N], head[N], inv[N], sa[N], lcp[N], length;
	vector<int> str;

	void bucket(int n, int L) {
		memset(head, 0, sizeof head);

		for(int i = 0; i < n; ++i) ++head[c[i]];

		int maxi = max(300, n + 1), k = 0;

		for(int i = 0; i < maxi; ++i) {
			swap(k, head[i]);
			k += head[i];
		}

		for(int i = 0; i < n; ++i) {
			int j = (sa[i] - L + n) % n;
			tsa[head[c[j]]++] = j;
		}

		memcpy(sa, tsa, n * sizeof(int));
	}

	void suffixarray() {
		int n = length + 1;
		for(int i = 0; i < n; ++i) {
			sa[i] = i;
			c[i] = str[i];
		}
		bucket(n, 0);
		for(int L = 1; L < n; L <<= 1) {
			bucket(n, L);
			for(int i = 0, cc = -1; i < n; ++i)
				tc[sa[i]] = !i || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n] ? ++cc : cc;
			memcpy(c, tc, n * sizeof(int));
		}
		for(int i = 0; i < n - 1; ++i) sa[i] = sa[i + 1];
	}

	void computeLCP() {
		int k = 0;
		for(int i = 0; i < length; ++i) inv[sa[i]] = i;
		for(int j = 0; j < length; ++j) {
			int i = inv[j];
			while(i > 0 && str[sa[i] + k] == str[sa[i - 1] + k]) ++k;
			lcp[i] = k;
			k = max(k - 1, 0);
		}
	}

	SuffixArray() = default;

	SuffixArray(const vector<int>& s) {
		build(s);
	}

	void build(const vector<int>& s) {
		length = static_cast<int>(s.size()) - 1;
		str = s;
		suffixarray();
	}
};

constexpr int N = 1e5 + 5;

template class SuffixArray<N>;

class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        auto permutation = nums;

        sort(permutation.begin(), permutation.end());

        for(int& val : nums)
            val = lower_bound(permutation.begin(), permutation.end(), val) - permutation.begin() + 1;

        nums.push_back(0);

        auto sa = make_unique<SuffixArray<N>>(nums);
        sa->computeLCP();

        const int n = static_cast<int>(nums.size()) - 1;
        int answer = n;

        for(int i = 0; i < n; ++i) {
            int lcp = numeric_limits<int>::max();

            if(nums[sa->sa[i] + sa->lcp[i]])
                lcp = sa->lcp[i] + 1;

            if(i < n - 1) {
                if(nums[sa->sa[i] + sa->lcp[i + 1]])
                    lcp = max(lcp, sa->lcp[i + 1] + 1);
                else
                    lcp = n;
            }

            answer = min(answer, lcp);
        }


        return answer;
    }
};