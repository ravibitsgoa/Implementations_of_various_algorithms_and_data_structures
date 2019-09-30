const int DSUSize = 1e6 + 5;
//Union-Find with Union by Rank and path compression.
int parent[DSUSize];
int rank_[DSUSize];
int size_[DSUSize];
class UnionFind {
public:
	void makeSet(int x) {
		parent[x] = x;
		rank_[x] = 0;
		size_[x] = 1;
	}

	int find(int x) {
		if(parent[x]!=x) {
			parent[x] = find(parent[x]);
		}
		size_[x] = size_[parent[x]];
		return parent[x];
	}

	int getSize(int x) {find(x); return size_[x];}
	int unionFind(int x, int y) {
		auto xRoot = find(x);
		auto yRoot = find(y);

		// x and y are already in the same set
		if(xRoot == yRoot)
			return size_[xRoot];

		// x and y are not in same set, so we merge them
		if(rank_[xRoot] < rank_[yRoot])
			swap(xRoot, yRoot);

		// merge yRoot into xRoot
		parent[yRoot] = xRoot;
		size_[xRoot] += size_[yRoot];
		if(rank_[xRoot] == rank_[yRoot])
			rank_[xRoot]++;
		return size_[xRoot];
	}
};

