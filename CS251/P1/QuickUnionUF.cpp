#include "QuickUnionUF.h"

QuickUnionUF::QuickUnionUF(int n)
{
	title = "Quick Union: \n";
	for (int i = 0; i < n; i++)
	{
		id.push_back(i);
	}
}

int QuickUnionUF::find(int a) //return root
{
	while (a!=id[a])
	{
		a = id[a];
	}
	return a;

}

bool QuickUnionUF::connected(int p, int q) {
        return find(p) == find(q);
}

void QuickUnionUF::Union(int a, int b)
{
	int aRoot = find(a);
	int bRoot = find(b);
	if (aRoot!=bRoot)
	{
		id[aRoot] = bRoot;
	}
}

std::vector<int> QuickUnionUF::getID()
{
	return id;
}
