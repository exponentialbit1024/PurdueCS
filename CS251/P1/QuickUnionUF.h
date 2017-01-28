#ifndef QUICKUNIONUF_H
#define QUICKUNIONUF_H
#include <vector>
#include <string>

class QuickUnionUF
{
private:
	std::vector<int> id;
public:
	std::string title;
	QuickUnionUF(int n);
	int find(int a);
	void Union(int a, int b);
	std::vector<int> getID();
	bool connected(int p, int q);

};
#endif 
