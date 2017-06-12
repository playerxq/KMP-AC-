// leetcode-616-trie.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;
class trie{
public:
	bool isWord;
	trie* fail;
	unordered_map<char, trie*> next;
	trie(){
		isWord = false;
	}
};
class Solution {
public:
	queue<trie*> Q;
	int build_ac(trie* root)
	{
		root->fail = NULL;
		Q.push(root);
		while (!Q.empty())
		{
			trie* p = NULL;
			trie* temp = Q.front();
			Q.pop();
			for (unordered_map<char, trie*>::iterator iter = (temp->next).begin(); iter != (temp->next).end(); iter++)
			{
				if (temp == root)
					iter->second->fail = root;
				else
				{
					p = temp->fail;
					while (p)
					{
						if (p->next.find(iter->first) != p->next.end())
						{
							iter->second->fail = p->next[iter->first];
							break;
						}
						else
							p = p->fail;
					}
					if (!p)
						iter->second->fail = root;
				}
				Q.push(iter->second);
			}
		}
		return 0;
	}
	string addBoldTag(string s, vector<string>& dict) {
		trie* root = new trie();
		for (auto& word : dict){
			trie* node = root;
			for (char& c : word){
				if (node->next.find(c) == node->next.end()){
					node->next[c] = new trie();
				}
				node = node->next[c];
			}
			node->isWord = true;
		}
		build_ac(root);
		string res = "";
		int last = -1;
		for (int i = 0; i < s.size();i++)
		{
			trie* cur = root;
			for (int j = i; j < s.size(); j++)
			{
				if (cur->next.find(s[j]) == cur->next.end())
				{
					break;
				}
				cur = cur->next[s[j]];
				if (cur->isWord)
				{
					if (i > last)
						res += "<b>";
					last = max(last,j);
				}
			}
			res += s[i];
			if (i == last)
				res += "</b>";
		}
		for (int i = 0; i<res.size() - 6; i++){
			if (res.substr(i, 7) == "</b><b>")
				res = res.substr(0, i) + res.substr(i + 7);
		}
		return res;
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	vector<string> ve;
	ve.push_back("abc");
	ve.push_back("123");
	//ve.push_back("bc");
	//ve.push_back("aaabbcc");
	Solution s;
	s.addBoldTag("abcxyz123",ve);
	return 0;
}

