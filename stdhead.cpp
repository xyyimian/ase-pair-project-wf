#include "stdhead.h"




void parse(int argc, char** argv, vector<argparse>& param, string& path) {
	char name;
	for (int i = 1; i < argc; ) {
		if ((name = argv[i][1]) == 'f' || (name = argv[i][1]) == 'c') {
			param.emplace_back(name, "");
			i += 1;
		}
		else if ((name = argv[i][1]) == 'd') {
			if (strcmp(argv[i + 1], "-s") == 0) {
				param.emplace_back(name, "", true);
				i += 2;
			}
			else {
				param.emplace_back(name, "");
				i += 1;
			}
		}
		else if (argv[i][0] != '-') {
			path = argv[i];
			i += 1;
		}
		else {
			param.emplace_back(name, argv[i + 1]);
			i += 2;
		}
	}
	if (path == "") {
		cerr << "No path in paramters!";
		exit(1);
	}
}

void CharacterCount(string& text, unordered_map<string, double> umap) {

	vector<double> frequency(26, 0);
	vector<Freq> wf;

	for (char c = 'a'; c <= 'z'; ++c) {
		frequency[c - 'a'] = count(text.begin(), text.end(), c) + count(text.begin(), text.end(), c - 32);
	}

	double sum = 0;
	for (auto i : frequency) {
		sum += i;
	}
	for (auto& i : frequency) {
		i = (long long)(i / sum * 10000) / 100.0;
	}
	for (int i = 0; i < 26; ++i) {
		wf.emplace_back('a' + i, frequency[i]);
	}
	for (int i = 0; i < 26; i++) {
		umap["" + ('a' + i)] = frequency[i];
	}


}

inline bool m_isalpha(char c) {
	return (c >= 65 && c <= 90 || c >= 97 && c <= 122);
}





void WordCount(string& text, unordered_map<string, double>& umap, bool isXExist, string stopWordsPath) {


	for (auto& w : text) {

		if (m_isalpha(w)) {
			tolower(w);
		}
	}

	string wordNow;

	//flag=0,word begin, flag=1,in a word
	int flag = 0;
	for (unsigned char c : text) {
		if (flag == 0) {
			if (m_isalpha(c)) {
				flag = 1;
				wordNow += c;
			}
		}
		else if (flag == 1) {
			if (isalnum(c)) {
				wordNow += c;
			}
			else {
				flag = 0;

				umap[wordNow] += 1;
				wordNow = "";
			}
		}
	}
	if (isXExist) {
		ifstream input;
		input.open(stopWordsPath, ios::in);
		stringstream ss;
		ss << input.rdbuf();
		string text(ss.str());
		const char *delim = " \n\t";

		string token = strtok(const_cast<char *>(text.c_str()), delim);
		umap[token] = 0;
		while (token != "") {
			token = strtok(NULL, delim);
			umap[token] = 0;
		}
	}
}

void m_output(unordered_map<string, double>& umap, int limit) {

	vector<WordFreq> wordList;
	double sum = 0;
	for (auto w : umap) {
		sum += w.second;
	}
	for (auto& w : umap) {
		w.second = (long long)(w.second / sum * 10000) / 100.0;
	}
	for (auto& w : umap) {
		wordList.emplace_back(w.first, w.second);
	}
	stable_sort(wordList.begin(), wordList.end());

	if (limit != 0) {
		long counter = 0;
		for (auto w : wordList) {
			++counter;
			if (counter > limit || w.freq == 0)
				break;
			cout << fixed << setprecision(2) << w.word << ": " << w.freq << "%" << endl;
		}
	}
	else {
		for (auto w : wordList) {
			if (w.freq == 0)
				break;
			cout << fixed << setprecision(2) << w.word << ": " << w.freq << "%" << endl;
		}
	}
	cout.unsetf(ios::fixed);
}


void DirSearch(string dirPath, bool isRecursive, string& inputString) {
	vector<string> files;
	for (auto& f : fs::directory_iterator(dirPath)) {
		cout << f << endl;
		if (is_directory(f)) {
			if (isRecursive) {
				DirSearch(f.path().u8string(), isRecursive, inputString);
				continue;
			}
		}
		ifstream inputFile;
		inputFile.open(f.path(), ios::in);
		stringstream ss;
		ss << inputFile.rdbuf();

		string text(ss.str());
		inputString += text;
	}
}

void PhraseCount(string& inputString, unordered_map<string, double>& umap, bool isVExist, string verbDictPath, bool isXExist, string stopwordsPath) {
	if (isXExist) {
	}
	;
}


void PairCount(string& inputString, unordered_map<string, double>& umap, bool isVExist, string verbDictPath) {
	;
}
