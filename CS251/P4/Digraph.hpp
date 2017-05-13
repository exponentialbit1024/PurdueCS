#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>


class Digraph {
public:
	typedef std::list<int> bag_type;
	
	Digraph(int V) : m_V(V), m_E(0) {
		if (V<0) 
			throw std::invalid_argument("invalid number of vertices");
		m_indegree.resize(V);
		m_adj.resize(V);
	}
	
	int V() const { return m_V; }
	int E() const { return m_E; }
	
	void addEdge(int v, int w) {
		sanity_check(v);
		sanity_check(w);
		m_adj[v].push_back(w);
		m_indegree[w]++;
		m_E++;
	}
	
	const bag_type& adj(int v) const {
		sanity_check(v);
		return m_adj[v];
	}
	
	int out_degree(int v) const {
		sanity_check(v);
		return m_adj[v].size();
	}
	
	int in_degree(int v) const {
		sanity_check(v);
		return m_indegree[v];
		
	}
	
	Digraph reverse() const {
		Digraph reverse(m_V);
		for (int v=0; v<m_V; ++v) {
			std::for_each(m_adj[v].begin(), m_adj[v].end(); [&](int w)
				{
					reverse.addEdge(w, v);
				});
		}
		return reverse;
	}


private:
	int m_V;
	int m_E;
	std::vector<bag_type> m_adj;
	std::vector<int> m_indegree;
	
	void sanity_check(int v) const {
		if (v < 0 || v >= m_V)
			throw std::invalid_argument("Invalid vertex index");
	}
	
};

inline std::ostream& operator<<(std::ostream& os, const Digraph& dg) {
	os << dg.V() << " vertices, " << dg.E() << " edges " << std::endl;
	for (int v=0; v<dg.V(); ++v) {
		os << v << ": ";
		const Digraph::bag_type& b = dg.adj(v);
		std::for_each(b.begin(), b.end(), [](int w)
			{
				os << w << " ";
			});
		os << std::endl;
	}
	return os;
}

#endif