#ifndef KEY_HPP
#define KEY_HPP

#include <algorithm>
#include <array>
#include <cassert>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef C_IS_SET
#undef C_IS_SET
#endif

static constexpr int B=5;  // number of bits per character
static constexpr int R=32; // size of alphabet (2^B)

#ifdef USE_4_CHARS

static constexpr int C=4;  // number of characters per word
static constexpr int N=20; // number of bits per word
#define C_IS_SET

#endif

#ifdef USE_6_CHARS

static constexpr int C=6;  // number of characters per word
static constexpr int N=30; // number of bits per word
#define C_IS_SET

#endif

#ifdef USE_7_CHARS

static constexpr int C=7;  // number of characters per word
static constexpr int N=35; // number of bits per word
#define C_IS_SET

#endif

#ifdef USE_8_CHARS

static constexpr int C=8;  // number of characters per word
static constexpr int N=40; // number of bits per word
#define C_IS_SET

#endif

#ifdef USE_9_CHARS

static constexpr int C=9;  // number of characters per word
static constexpr int N=45; // number of bits per word
#define C_IS_SET

#endif

#ifdef USE_10_CHARS

static constexpr int C=10;  // number of characters per word
static constexpr int N=50; // number of bits per word
#define C_IS_SET

#endif

#ifndef C_IS_SET

static constexpr int C=5;   // number of characters per word
static constexpr int N=25;  // number of bits per word

#endif

#define ALPHABET "abcdefghijklmnopqrstuvwxyz012345"
typedef std::array<char, C> word_type; // fixed size word

// map a string to its representation in given alphabet
static inline word_type to_string(const std::string& s) {
	word_type w;
	int j;
	for (int i = 0; i < C; ++i) {
		for (j = 0; j < R; ++j) {
			if (s[i] == ALPHABET[j]) {
				w[i] = j;
				break;
			}
		}
		if (j == R) throw std::out_of_range("invalid character");
	}
	return w;
}

class Key {
private:
	word_type m_digit;

	int bit(int) const;

public:
    // Default Constructor
	Key();

	// Initialize the Key from a compatible character string
	Key(const std::string&);

	// Initialize the Key from a word of 32 bit characters
	Key(const word_type&);

	// Assignment operators
	Key& operator=(const Key&);
	Key& operator+=(const Key&);

	// Comparison operators
	bool operator==(const Key&) const;
	bool operator<(const Key&) const;

	// Print the contents of the Key (for debugging mostly)
    void show() const;

	// Assign the Key generated from the argument string to the current Key
	void set_string(const std::string&);

	// Add subset of the integers T[i] indexed by the bits of k
	// and return subset sum. Do sum mod 2^N.
    Key subset_sum(const std::vector<Key>&, bool verbose=false);
		Key subtractor(Key, Key);
	 std::string returnEnc();
};

inline int Key::bit(int i) const {
	// j=i/m_b: j-th character contains i-th bit
	// k=i%m_b: i-th bit is k-th bit of j-th character
	// m_digit[j] >> k & 1 (=00000001)
	// we return m_b-1-j-th bit since we count bits from the left
	return (m_digit[i/B] >> (B - 1 - i % B)) & 1;
}

inline Key::Key() {
	std::fill(m_digit.begin(), m_digit.end(), 0);
}

inline Key::Key(const std::string& s) {
	set_string(s);
}

inline Key::Key(const word_type& w) : m_digit(w) {}

inline Key& Key::operator=(const Key& other) {
	std::copy(other.m_digit.begin(), other.m_digit.end(), m_digit.begin());
	return *this;
}

inline void Key::set_string(const std::string& s) {
	if (s.size() < C) {
		throw std::invalid_argument("input string is too short");
	}
	m_digit = to_string(s);
}

inline bool Key::operator==(const Key& other) const {
	return m_digit == other.m_digit;
}

inline bool Key::operator<(const Key& other) const {
	return m_digit < other.m_digit; // lexicographical order
}

Key& Key::operator+=(const Key& other) {
    int t;
    int carry = 0;
    for (int i = C-1; i >= 0; --i) {
       t = m_digit[i];
       m_digit[i] = (t + other.m_digit[i] + carry)  % R;
       carry      = (t + other.m_digit[i] + carry) >= R;
    }
	return *this;
}

Key Key::subtractor(Key a, Key b){
	int t;
	int carry = 0;
	for (int i = C-1; i >= 0; --i) {
		 t = a.m_digit[i];
		 a.m_digit[i] = (t - b.m_digit[i] - carry);
		 if(a.m_digit[i] > 0){
			 a.m_digit[i] %= R;
		 }else{
			 a.m_digit[i] += R;
			 a.m_digit[i] %= R;
		 }
		 carry      = (t - b.m_digit[i] - carry) < 0;
	}
	return a;
}

Key Key::subset_sum(const std::vector<Key>& T, bool verbose) {
	if (T.size() != N)
		throw std::invalid_argument("dictionary has wrong size");
	Key sum;
	for (int i = 0; i < N; ++i) {
		if (bit(i)) {
			sum += T[i];
			if (verbose) {
				std::cout << std::setw(2) << i << " ";
				T[i].show();
			}
		}
	}
    return sum;
}

inline void Key::show() const {
	std::for_each(m_digit.begin(), m_digit.end(), [](const char& c)
	{
		std::cout << ALPHABET[c];
	});
    std::cout << "  ";
    std::for_each(m_digit.begin(), m_digit.end(), [](const char& c)
    {
    	std::cout << std::setw(2) << static_cast<int>(c) << ' ';
    });
    std::cout << "  ";
    for (int i = 0; i < N; ++i) {
    	std::cout << bit(i) << std::flush;
    }
    std::cout << '\n';
}

std::string Key::returnEnc() {
	std::string encrypKey("");

	for(int i = 0; i < m_digit.size(); i++){
		encrypKey += ALPHABET[m_digit[i]];
	}
	return encrypKey;
}

#endif // KEY_HPP
