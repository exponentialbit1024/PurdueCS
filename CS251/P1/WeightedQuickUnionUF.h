#ifndef WEIGHTEDQUICKUNIONH_H
#define WIGHTEDQUICKUNIONH_H
#include <iostream>
#include <vector>
#include <string>

class WeightedQuickUnionUF
{
private:
	std::vector<int> size;
	std::vector<int> id;
public:
	std::string title;
	WeightedQuickUnionUF(int n);
	int find(int a);
	void Union(int a, int b);
	std::vector<int> getID();
	bool connected(int p, int q);

};

#endif
