#pragma GCC target("popcnt")

class Solution {
public:
    static constexpr int N = 30;

    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        const bitset<N * N> img[] = {img2Bitset(img1), img2Bitset(img2)};
        const int n = static_cast<int>(img1.size());
        int max_overlaps {};
        
        for(int dx = -n + 1; dx < n; ++dx) {
            for(int dy = -n + 1; dy < n; ++dy) {
                auto timg = translate(img[0], n, dx, dy);
                max_overlaps = max(max_overlaps, countOverlaps(timg, img[1]));
            }
        }
    
        return max_overlaps;
    }

private:

    bitset<N * N> img2Bitset(const vector<vector<int>>& img) {
        const auto n = img.size();
        bitset<N * N> answer;

        for(size_t i = 0; i < n; ++i)
            for(size_t j = 0; j < n; ++j)
                answer[i * n + j] = img[i][j];

        return answer;
    }

    int countOverlaps(const bitset<N * N>& img1, const bitset<N * N>& img2) {
        return (img1 & img2).count();
    }

    bitset<N * N> translate(const bitset<N * N>& img, size_t length, int dx, int dy) {
        const auto n = static_cast<int>(length);
        bitset<N * N> answer;

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                int dest_x = i + dx, dest_y = j + dy;

                if(dest_x < 0 || dest_y < 0 || dest_x >= n || dest_y >= n || img[i * n + j] == 0)
                    continue;

                answer[dest_x * n + dest_y] = 1;    
            }
        }

        return answer;
    }
};