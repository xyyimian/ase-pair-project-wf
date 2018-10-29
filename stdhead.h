#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iomanip>
#include <regex>
#include "word.h"
#include <io.h>
#include <filesystem>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
using namespace std;
namespace fs = std::experimental::filesystem;
//#include <boost/algorithm/string/join.hpp>
//#include <boost/algorithm/string.hpp>

class Freq {
public:
	char character;
	double freq;

	Freq() = default;
	Freq(char c, double f) :character(c), freq(f) {}



	bool operator< (const Freq& other) const {
		return freq > other.freq;
	}

	bool operator> (const Freq& other) const {
		return other.freq > freq;
	}
};

class argparse {
private:
	char name;
	string value;
	bool assist = false;
public:
	char getName() {
		return name;
	}
	string getValue() {
		return value;
	}
	bool getAssist() {
		return assist;
	}
	argparse() = default;
	argparse(char c, string v, bool a = false) :name(c), value(v), assist(a) {}

	friend void parse(int argc, char** argv, vector<argparse>& param);
};
void parse(int argc, char** argv, vector<argparse>& param, string& path);
void CharacterCount(string& text, unordered_map<string, double> umap);
inline bool m_isalpha(char c);
void WordCount(string& text, unordered_map<string, double>& umap, bool isXExist, string stopWordsPath);
void m_output(unordered_map<string, double>& umap, int limit = 0);
void DirSearch(string dirPath, bool isRecursive, string& inputString);
void PhraseCount(string& inputString, int len, unordered_map<string, double>& umap, bool isVExist, string verbDictPath, bool isXExist, string stopwordsPath);
void PairCount(string& inputString, string prepFilePath, string verbDictFile, unordered_map<string, double>& umap);
void m_tolower1(string& s);
bool m_isalnum(char c);
void m_search(string& inputString, vector<vector<string>>& inputStringVec);
inline string m_join(vector<string> vec, string sep);