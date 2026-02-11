#include <bits/stdc++.h>

using namespace std;

int inversions(const string& dna) {
	char nucleotide[] = "ACGT";
	int cnt[4] = {0}, inv {};
	
	for(auto it = dna.rbegin(); it != dna.rend(); ++it) {

		int pos = find(begin(nucleotide), end(nucleotide), *it) - begin(nucleotide);

		for(int i = 0; i < pos; ++i) inv += cnt[i];

		++cnt[pos];
	}

	return inv;
}

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	int t;

	cin >> t;

	for(int i = 0; i < t; ++i) {
		int n, m;

		cin >> n >> m;

		vector<string> dna(m);
		vector<size_t> index(m);
		vector<int> inversion(m);

		for(int j = 0; j < m; ++j) {
			cin >> dna[j];

			index[j] = j;
			inversion[j] = inversions(dna[j]);
		}

		stable_sort(index.begin(), index.end(), [&inversion](size_t lhs, size_t rhs) {
			return inversion[lhs] < inversion[rhs];
		});

		if(i > 0) cout << '\n';

		for(int idx : index)
			cout << dna[idx] << '\n';
	}

	return 0;
}
