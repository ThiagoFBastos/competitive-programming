#include <bits/stdc++.h>

using namespace std;

class MergeSort
{
public:

	MergeSort(const vector<int>& v):
		elements(v.begin(), v.end()),
		inv(0)
	{
		temp.resize(v.size());
	}

	long long inversions() 
	{
		merge_sort(0, (int)elements.size() - 1);
		return inv;
	}

private:
	vector<int> elements, temp;
	long long inv;

	void merge(int lo, int hi)
	{
		int mid = (lo + hi) / 2;
		int i = lo, k = mid + 1, j = 0;

		while(i <= mid && k <= hi) 
		{
			if(elements[i] <= elements[k])
				temp[j++] = elements[i++];
			else 
			{
				inv += mid - i + 1;
				temp[j++] = elements[k++];
			}
		}

		while(i <= mid) temp[j++] = elements[i++];
		while(k <= hi) temp[j++] = elements[k++];

		copy(temp.begin(), temp.begin() + hi - lo + 1, elements.begin() + lo);
	}

	void merge_sort(int lo, int hi)
	{
		if(lo == hi)
			return;

		int mid = (lo + hi) / 2;

		merge_sort(lo, mid);
		merge_sort(mid + 1, hi);
		merge(lo, hi);
	}
};

int main() {
	ios_base :: sync_with_stdio(false);
	cin.tie(0);

	while(true) {

		int n;

		cin >> n;

		if(n == 0)
			break;

		vector<int> a(n);

		for(auto& value : a) cin >> value;

		MergeSort ms(a);

		cout << ms.inversions() << '\n';
	}

	return 0;
}
