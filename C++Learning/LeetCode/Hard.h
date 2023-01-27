#ifndef __LeetCode_Hard_H__
#define __LeetCode_Hard_H__

#include "Base.h"

// 32. 最长有效括号
int No32_longestValidParentheses( string s );

// 37. 解数独
void No37_solveSudoku( vector<vector<char>>& board );

// 51. N 皇后
vector<vector<string>> No51_solveNQueens( int n );

// 72. 编辑距离
int No72_minDistance( string word1, string word2 );

// 115. 不同的子序列
int No115_numDistinct( string s, string t );

// 123. 买卖股票的最佳时机 III
int No123_maxProfit( vector<int>& prices );

// 188. 买卖股票的最佳时机 IV
int No188_maxProfit( int k, vector<int>& prices );

// 239. 滑动窗口最大值
vector<int> No239_maxSlidingWindow( vector<int>& nums, int k );

// 347. 前 K 个高频元素
vector<int> No347_topKFrequent( vector<int>& nums, int k );


#endif
