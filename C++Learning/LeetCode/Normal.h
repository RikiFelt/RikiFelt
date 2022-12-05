#ifndef __LeetCode_Normal_H__
#define __LeetCode_Normal_H__

#include "Base.h"

// 2. 两数相加
ListNode* No2_addTwoNumbers( ListNode* l1, ListNode* l2 );

// 3. 无重复字符的最长子串
int No3_lengthOfLongestSubstring(string s);

// 5. 最长回文子串
string No5_longestPalindrome( string s );

// 6. Z 字形变换
string No6_convert( string s, int numRows );

// 11. 盛最多水的容器
int No11_maxArea( vector<int>& height );

// 15. 三数之和
vector<vector<int>> No15_threeSum( vector<int>& nums );

// 16. 最接近的三数之和
int No16_threeSumClosest( vector<int>& nums, int target );

// 17. 电话号码的字母组合
vector<string> No17_letterCombinations(string digits);

// 22. 括号生成
vector<string> No22_generateParenthesis( int n );
vector<string> No22_generateParenthesis_2( int n );

// 45. 跳跃游戏 II
int No45_jump( vector<int>& nums );
int No45_jump_2( vector<int>& nums );

bool No55_canJump( vector<int>& nums );

// 62. 不同路径
int No62_uniquePaths( int m, int n );

#endif // !__LeetCode_East_H__

