// leetcode-349-kmp.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include <cstdio>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <queue>
#include<iomanip>
#include <ctype.h>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        sort(nums1.begin(),nums1.end());
        sort(nums2.begin(),nums2.end());
        int i=0,j=0;
        vector<int> res;
        while(i<nums1.size()&&j<nums2.size())
        {
            if(nums1[i]==nums2[j])
            {
                if(res.empty()||res[res.size()-1]!=nums1[i])
                res.push_back(nums1[i]);
                i++;
                j++;
            }
            else nums1[i]<nums2[j]? i++:j++;
        }
        return res;
    }
};
int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
	vector<int> nums1;
	vector<int> nums2;
	nums1.push_back(1);
	nums1.push_back(2);
	//nums1.push_back(2);
	//nums1.push_back(1);
	nums2.push_back(2);
	nums2.push_back(1);
	Solution s;
	s.intersection(nums1,nums2);
}

