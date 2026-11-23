class ProductOfNumbers {
public:
    ProductOfNumbers() {
        prefix.push_back(array<int, N> {});
    }
    
    void add(int num) {
        array<int, N> frequency {};

        ++frequency[num];

        for(int i = 0; i < N; ++i)
            frequency[i] += prefix.back()[i];

        prefix.push_back(move(frequency));
    }
    
    int getProduct(int k) {
        constexpr long long MOD = 1LL << 31;
        const int n = static_cast<int>(prefix.size());
        long long ans = 1;

        for(int i = 0; i < N; ++i) {
            const int cnt = prefix[n - 1][i] - prefix[n - k - 1][i];
            ans = (ans * fastExp(i, cnt, MOD)) & (MOD - 1);
        }

        return (int)ans;
    }

private:
    static constexpr int N = 101;
    vector<array<int, N>> prefix;

    long long fastExp(long long n, long long p, long long mod) {
        long long ans = 1;

        for(; p > 0; p >>= 1) {
            if(p & 1)
                ans = (ans * n) & (mod - 1);
            n = (n * n) & (mod - 1);
        }

        return ans;
    } 
};

/**
 * Your ProductOfNumbers object will be instantiated and called as such:
 * ProductOfNumbers* obj = new ProductOfNumbers();
 * obj->add(num);
 * int param_2 = obj->getProduct(k);
 */