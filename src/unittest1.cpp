#include "stdafx.h"
#include "CppUnitTest.h"
#include <string>
#include <unordered_map>
#include "../word_frequency/stdhead.cpp"
#include "direct.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{

	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(TestM_isalpha)
		{

			char c = 'a';
			bool expectOutput = true;
			bool realOutput = m_isalpha(c);
			Assert::AreEqual(expectOutput, realOutput);

			c = 1;
			expectOutput = false;
			realOutput = m_isalpha(c);
			Assert::AreEqual(expectOutput, realOutput);

			c = -1;
			expectOutput = false;
			realOutput = m_isalpha(c);
			Assert::AreEqual(expectOutput, realOutput);

		}

		TEST_METHOD(TestCharacterCount)
		{
			// text:right
			string text = "abcd";
			unordered_map<string, double> expectOutput;
			for (int i = 0; i < 4; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 25;
			}
			for (int i = 4; i < 26; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 00;
			}
			unordered_map<string, double> realOutput;
			CharacterCount(text, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

			// text:space
			text = "  ";
			for (int i = 0; i < 26; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 00;
			}
			CharacterCount(text, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

			// text:blank
			text = "";
			for (int i = 0; i < 26; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 00;
			}
			CharacterCount(text, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

			// text:include Chinese and symbols
			text = "abcd中文,,efgh";
			for (int i = 0; i < 8; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 12.5;
			}
			for (int i = 8; i < 26; i++) {
				int a = 97 + i;
				char c = (char)a;
				string s = "a";
				s[0] = c;
				expectOutput[s] = 00;
			}
			CharacterCount(text, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

		}

		TEST_METHOD(TestWordCount)
		{
			// -f test
			string text;
			for (int i = 0; i < 10; ++i)
				text += "last ";
			for (int i = 0; i < 10; ++i)
				text += "ahc ";
			unordered_map<string, double> expectOutput;
			expectOutput["last"] = 10;
			expectOutput["ahc"] = 10;
			unordered_map<string, double> realOutput;
			bool isXExist = false;
			string stopWordsPath = "";
			WordCount(text, realOutput, isXExist, stopWordsPath);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			int len = expectOutput.size();
			int len_2 = realOutput.size();
			Assert::AreEqual(len, len_2);
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

			// -f -x test
			ofstream ofile("../word_frequency/stopwords.txt");
			ofile << "the " << "\n" << "a " << "\n" << "an ";
			ofile.close();
			stopWordsPath = "../word_frequency/stopwords.txt";
			text = "a an, the, last, first";
			expectOutput["last"] = 1;
			expectOutput["first"] = 1;
			expectOutput["a"] = 0;
			expectOutput["the"] = 0;
			expectOutput["an"] = 0;
			isXExist = true;
			WordCount(text, realOutput, isXExist, stopWordsPath);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

		}
		TEST_METHOD(TestPhraseCount)
		{
			
			// -q test
			string text = "go to,hello,world the like to";
			int len = 2;
			unordered_map<string, double> expectOutput;
			unordered_map<string, double> realOutput;
			bool isXExist = false;
			bool isVExist = false;
			string verbPaths;
			string stopPaths;
			
			PhraseCount(text, len, realOutput, isVExist, verbPaths, isXExist, stopPaths);
			expectOutput["go to"] = 1;
			expectOutput["world the"] = 1;
			expectOutput["the like"] = 1;
			expectOutput["like to"] = 1;
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();
			
			// -q -x -v test
			text = "goes to,hello,a an world the likes to";
			isXExist = true;
			stopPaths = "../word_frequency/stopwords.txt";
			isVExist = true;
			verbPaths = "../word_frequency/verbs.txt";
			PhraseCount(text, len, realOutput, isVExist, verbPaths, isXExist, stopPaths);
			expectOutput["go to"] = 1;
			expectOutput["world like"] = 1;
			expectOutput["like to"] = 1;
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();
			
		}

		TEST_METHOD(TestPairCount)
		{
			string text = "goes to, does to, play with";
			string prfile = "../word_frequency/prepositions.txt";
			string vrfile = "../word_frequency/verbs.txt";
			unordered_map<string, double> expectOutput;
			unordered_map<string, double> realOutput;
			expectOutput["go to"] = 1;
			expectOutput["do to"] = 1;
			expectOutput["play with"] = 1;
			PairCount(text, prfile, vrfile, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

			text = "go to, do to, play with";
			expectOutput["go to"] = 1;
			expectOutput["do to"] = 1;
			expectOutput["play with"] = 1;
			PairCount(text, prfile, vrfile, realOutput);
			Assert::AreEqual(expectOutput.size(), realOutput.size());
			for (auto it : expectOutput)
				Assert::AreEqual(expectOutput[it.first], realOutput[it.first]);
			expectOutput.clear();
			realOutput.clear();

		}

		TEST_METHOD(TestDirSearch)
		{
			string dirPath = "../word_frequency/test/";
			bool isRecursive = true;
			string realOutput, expectOutput;
			bool flag = mkdir(dirPath.c_str());
			ofstream ofile("../word_frequency/test/tmp.txt");
			ofile << "abcd,efgh";
			ofile.close();
			string dirPath1 = "../word_frequency/test/test_1";
			mkdir(dirPath1.c_str());
			ofstream ofile1("../word_frequency/test/test_1/tmp.txt");
			ofile1 << "abcd,efgh";
			ofile1.close();
			expectOutput = " abcd,efgh abcd,efgh";
			DirSearch(dirPath, isRecursive, realOutput);
			Assert::AreEqual(expectOutput, realOutput);

		}
	};
}