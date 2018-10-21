#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Freq {
public:
	char character;
	double freq;

	Freq() = default;
	Freq(char c, double f):character(c), freq(f){}



	bool operator< (const Freq& other) const {
		return freq < other.freq;
	}

	bool operator> (const Freq& other) const {
		return other.freq < freq;
	}
};

class argparse {
private:
	char name;
	string value;
public:
	char getName() {
		return name;
	}
	string getValue() {
		return value;
	}
	argparse() = default;
	argparse(char c, string v) :name(c), value(v) {}

	friend void parse(int argc, char** argv, vector<argparse>& param);
};

void parse(int argc, char** argv, vector<argparse>& param) {
	for (int i = 1; i < argc; i += 2) {
		param.emplace_back(argv[i][1], argv[i + 1]);
	}
}

void WordCount(string filePath) {

	ifstream input;
	input.open(filePath, ios::in);

	stringstream ss;
	ss << input.rdbuf();

	string text(ss.str());
	cout << text << endl;
	vector<double> frequency(26, 0);
	vector<Freq> wf;

	for (char c = 'a'; c <= 'z'; ++c) {
		frequency[c - 'a'] = count(text.begin(), text.end(), c) + count(text.begin(), text.end(), c - 32);
	}

	for (auto e : frequency)
		cout << e << endl;
	cout << endl;


	double sum = 0;
	for (auto i : frequency) {
		sum += i;
	}
	for (auto& i : frequency) {
		i = (long long)(i / sum * 10000) / 100;
	}
	for (int i = 0; i < 26; ++i) {
		wf.emplace_back('a' + i, frequency[i]);
	}

	stable_sort(wf.begin(), wf.end());
	for (auto e : wf) {
		cout << e.character << '\t' << e.freq << '%' << endl;
	}

}



int main(int argc, char** argv) {
	
	vector<argparse> param;
	parse(argc, argv, param);

	for (auto& e : param) {
		switch (e.getName()) {
		case 'f': WordCount(e.getValue());
			break;
		default:
			break;
		}
	}

}