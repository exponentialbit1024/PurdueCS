class Point{

public:

    // constructor
    Point(int _x, int _y) : x(_x), y(_y) {} 
	
    // is this point lexicographically smaller than that one?
    bool operator<(const Point& d) const {
		// your code here
    }

    // are the 3 points p, q, and r collinear?
    static bool areCollinear(const Point& p, const Point& q, const Point& r) {
    	// your code here
    }
  
    // are the 4 points p, q, r, and s collinear?
   	static bool areCollinear(const Point& p, const Point& q, const Point& r, const Point& s) {
   		// your code here
   	}
	
	int x;
	int y;    
};
