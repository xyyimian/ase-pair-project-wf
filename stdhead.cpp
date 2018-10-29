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

	string wordNow;

	//flag=0,outside, flag=1,within
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
	if (flag == 1) {
		umap[wordNow] += 1;
	}

	if (isXExist) {
		ifstream input;
		input.open(stopWordsPath, ios::in);
		stringstream ss;
		ss << input.rdbuf();
		string text(ss.str());
		const char *delim = " \n\t";

		char *token = strtok(const_cast<char *>(text.c_str()), delim);
		while (token != NULL) {
			umap[token] = 0;
			token = strtok(NULL, delim);
		}
	}
}

void m_output(unordered_map<string, double>& umap, int limit) {

	vector<WordFreq> wordList;
	/*
	double sum = 0;
	for (auto w : umap) {
		sum += w.second;
	}

	for (auto& w : umap) {
		w.second = (long long)(w.second / sum * 10000) / 100.0;
	}
	*/
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
		inputString = inputString + " " + text;
	}
	m_tolower1(inputString);
}

void PhraseCount(string& inputString, int len, unordered_map<string, double>& umap, bool isVExist, string verbDictPath, bool isXExist, string stopwordsPath) {
	//since one word who appears in stopwords may appear in verb-dict, so we firstly, change every word to 
	//suppose all stopwords appear in their original form

	

	
	unordered_map<string, string> verbMap;
	
	if (isVExist) {
		ifstream verbDict;
		verbDict.open(verbDictPath, ios::in);
		
		string rule;
		string arrow, index, value;
		
		while (getline(verbDict, rule)) {
			stringstream srule(rule);
			srule >> value >> arrow >> index;
			const char* delim = ",";
			char* token = strtok(const_cast<char *>(index.c_str()), delim);
			while (token != NULL) {
				verbMap[token] = value;
				token = strtok(NULL, delim);
			}
		}
	}
	unordered_set<string> stopwordsList;
	if (isXExist) {
		ifstream stopwordsFile;
		stopwordsFile.open(stopwordsPath, ios::in);
		string stopword;
		while (stopwordsFile>> stopword) {
			stopwordsList.insert(stopword);
		}
	}
	

	vector<vector<string>> inputStringVec;

	m_search(inputString, inputStringVec);
	
	

	for (auto& contString : inputStringVec) {
		for (auto it = contString.begin(); distance(it,contString.end()) >= len; ++it) {
			//string phrase = boost::algorithm::join(vector<string>(it, it+len), " ");
			string phrase = m_join(vector<string>(it, it + len), " ");
			umap[phrase] += 1;
		}
	}
}

inline string m_join(vector<string> vec, string sep) {
	if (vec.size() == 0)
		return "";
	string s = vec[0];
	for (auto it = vec.begin() + 1; it != vec.end(); ++it) {
		s += (sep + *it);
	}
	return s;
}

void m_search(string& inputString, vector<vector<string>>& inputStringVec) {
	bool isin = false;
	string::iterator sbegin;
	vector<string> segment;
	for (auto it = inputString.begin();  it != inputString.end(); ++it) {
		if (isin) {
			char temp = *it;
			if (!m_isalnum(temp)){
				segment.push_back(string(sbegin, it));
				isin = false;
				if ((temp != ' ') && (temp != '\t') && (temp != '\n')){
					inputStringVec.push_back(segment);
					segment.clear();
				}
				
			}
		}
		else {
			if(m_isalpha(*it)) {
				sbegin = it;
				isin = true;
			}
		}
	}
	if (isin) {
		segment.push_back(string(sbegin, inputString.end()));
		inputStringVec.push_back(segment);
	}
}

inline bool m_isalnum(char c) {
	return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9';
}



void PairCount(string& inputString, string prepFilePath, string verbDictFile, unordered_map<string, double>& umap) {
	ifstream prepFile(prepFilePath);
	ifstream verbFile(verbDictFile);

	unordered_map<string, string> verbMap;

	string rule;
	string arrow, index, value;

	while (getline(verbFile, rule)) {
		stringstream srule(rule);
		srule >> value >> arrow >> index;
		const char* delim = ",";
		char* token = strtok(const_cast<char *>(index.c_str()), delim);
		while (token !=  NULL) {
			verbMap[token] = value;
			token = strtok(NULL, delim);
		}

	}
	string prep;
	unordered_set<string> prepList;
	while (getline(prepFile, prep)) {
		prepList.insert(prep);
	}


	vector<vector<string>> inputStringVec;
	m_search(inputString, inputStringVec);
	for (auto& contString : inputStringVec) {
		for (auto it = contString.begin(); distance(it, contString.end()) >= 2; it += 2) {
			auto it1 = verbMap.find(*it);
			if (it1 != verbMap.end() && prepList.find(*(it + 1)) != prepList.end()) {
				auto test = verbMap.find(*it);
				string vp = m_join(vector<string>{it1->second, *(it + 1)}, " ");
				umap[vp] += 1;
			}
		}
	}
}

void m_tolower1(string &s) {
	for (char& c : s) {
		if (c >= 65 && c <= 90)
			c += 32;
	}
}