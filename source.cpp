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
#include "stdhead.h"
using namespace std;



int main(int argc, char* argv[]) {
	

	vector<argparse> param;
	string path = "";
	parse(argc, argv, param,path);
	unordered_map<string, double> umap;
	string inputString;
	vector<argparse>::iterator it;

	char p;
	auto f = [&p](argparse arg)->bool {return arg.getName() == p; };
	p = 'd';
	it = find_if(param.begin(), param.end(), f);
	if (it != param.end()) {
		DirSearch(path, it->getAssist(), inputString);
	}
	else {
		ifstream input;
		input.open(path, ios::in);
		stringstream ss;
		ss << input.rdbuf();
		inputString = ss.str();
		m_tolower1(inputString);
	
	}

	vector<char> funcParam = { 'c','f','p','q' };

	p = 'v';
	bool isVExist = ((it = find_if(param.begin(), param.end(), f)) != param.end());
	string verbDictPath;
	if (isVExist)
		verbDictPath = it->getValue();
	p = 'x';
	bool isXExist = ((it = find_if(param.begin(), param.end(), f)) != param.end());

	string stopwordsPath;
	if (isXExist)
		stopwordsPath = it->getValue();




	for (char p1 : funcParam) {
		p = p1;
		auto it = find_if(param.begin(), param.end(), f);
		if (it != param.end()) {
			switch (it->getName())
			{
			case 'c':
				CharacterCount(inputString, umap);
				break;
			case 'f':
				WordCount(inputString, umap, isXExist, stopwordsPath);
				break;
			case 'p':
				PhraseCount(inputString,stoi(it->getValue()), umap, isVExist, verbDictPath, isXExist, stopwordsPath);
				break;
			case 'q':
				if (!isVExist) {
					cerr << "[Error] With -q option while without -v option";
					exit(1);
				}
				PairCount(inputString, it->getValue(),verbDictPath,umap);
				break;
			default:
				break;
			}
		}
	}

	bool isNExist = ((it = find_if(param.begin(), param.end(), [](argparse arg)->bool {return arg.getName() == 'n'; })) != param.end());
	if (isNExist)
		m_output(umap, stoi(it->getValue()));
	else
		m_output(umap);
}
