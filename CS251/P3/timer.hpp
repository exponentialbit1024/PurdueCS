#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <ctime>

class CPU_timer {
public:
	CPU_timer() : m_tic(std::clock()) {}
	
	void tic() {
		m_tic = std::clock();
	}
	
	void toc() {
		m_toc = std::clock();
	}
	
	double elapsed() const {
		return 1000.*(m_toc - m_tic)/CLOCKS_PER_SEC;
	}
	
private:
	std::clock_t m_tic, m_toc;
};


#endif