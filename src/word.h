#pragma once
#include <string>
using namespace std;
class WordFreq {
public:
	string word;
	double freq;

	WordFreq() = default;
	WordFreq(string w, double f):word(w), freq(f){}
	bool operator< (const WordFreq& other) const {
		if (other.freq == freq) 
			return word < other.word;
		else
			return freq > other.freq;
	}
	/*
	bool operator> (const WordFreq& other) const {
		return other.freq < freq;
	}
	*/
};
