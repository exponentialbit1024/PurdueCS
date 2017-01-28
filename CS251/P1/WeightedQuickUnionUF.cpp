#include "WeightedQuickUnionUF.h"

WeightedQuickUnionUF::WeightedQuickUnionUF(int n)
{
	title = "Weighted Quick Union Based on Size: \n";
	for (int i = 0; i < n; i++)
	{
		id.push_back(i);
		size.push_back(1);
	}
}

int WeightedQuickUnionUF::find(int a)
{
	while (a != id[a])
	{
		a = id[a];
	}
	return a; // the root
}

bool WeightedQuickUnionUF::connected(int p, int q) {
        //printf("\n%d %d\n", p, q);
        //printf("%d %d", find(p), find(q));
        return find(p) == find(q);        
}

void WeightedQuickUnionUF::Union(int a, int b)
{
	int aRoot = find(a);
	int bRoot = find(b);
	if (aRoot == bRoot) return;

    // make smaller root point to larger one
    if (size[aRoot] < size[bRoot]) {
    	id[aRoot] = bRoot;
        size[bRoot] += size[aRoot];
    }
    else {
        id[bRoot] = aRoot;
        size[aRoot] += size[bRoot];
    }

}

std::vector<int> WeightedQuickUnionUF::getID()
{
	return id;
}
