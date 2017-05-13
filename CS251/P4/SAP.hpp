#ifndef SAP_HPP
#define SAP_HPP

#include <algorithm>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>
#include <vector>

#include "Digraph.hpp"

class SAP {
	// constructor
	SAP(Digraph G); // Use the C++ implementation of Digraph provided below
	
	// return length of shortest ancestral path of v and w; -1 if no such path
	int length(int v, int w) const;
	
	// return a common ancestor of v and w that participates in a shortest 
	// ancestral path; -1 if no such path
	int ancestor(int v, int w) const;
	
};


#endif