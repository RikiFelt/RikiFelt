#ifndef __LeetCode_East_H__
#define __LeetCode_East_H__

#include "base.h"

// 1. 两数之和
vector<int> No1_twoSum( vector<int>& nums, int target );
vector<int> No1_twoSum_2( vector<int>& nums, int target );

// 7. 整数反转
int No7_reverse( int x );

// 9. 回文数
bool No9_isPalindrome( int x );

// 13. 罗马数字转整数
int No13_romanToInt( string s );

// 14. 最长公共前缀
string No14_longestCommonPrefix( vector<string>& strs );

// 20. 有效的括号
bool No20_isValid( string s );

// 21. 合并两个有序链表
ListNode* No21_mergeTwoLists( ListNode* l1, ListNode* l2 );

// 26. 删除排序数组中的重复项
int No26_removeDuplicates( vector<int>& nums );

// 27. 移除元素
int No27_removeElement(vector<int>& nums, int val);

// 28. 实现 strStr()
int No28_strStr( string haystack, string needle );

// 35. 搜索插入位置
int No35_searchInsert( vector<int>& nums, int target );

// 38. 外观数列
string No38_countAndSay( int n );

// 53. 最大子序和
int No53_maxSubArray( vector<int>& nums );

// 58. 最后一个单词的长度
int No_58_lengthOfLastWord( string s );

// 66. 加一
vector<int> No66_plusOne( vector<int>& digits );

// 67. 二进制求和
string No67_addBinary( string a, string b );

// 94. 二叉树的中序遍历
vector<int> No94_inorderTraversal( TreeNode* root );

// 100.相同的树
bool No100_isSameTree( TreeNode* p, TreeNode* q );

// 101. 对称二叉树
bool No101_isSymmetric( TreeNode* root );

// 104. 二叉树的最大深度
int No104_maxDepth( TreeNode* root );

// 118. 杨辉三角
vector<vector<int>> No118_generate( int numRows );

// 119. 杨辉三角 II
vector<int> No119_getRow( int rowIndex );

// 121. 买卖股票的最佳时机
int No121_maxProfit( vector<int>& prices );

// 122. 买卖股票的最佳时机 II
int No122_maxProfit( vector<int>& prices );

// 141. 环形链表
bool No141_hasCycle( ListNode *head );

#endif // !__LeetCode_East_H__

