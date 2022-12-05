#ifndef __LeetCode_East_H__
#define __LeetCode_East_H__

#include "Base.h"

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

// 69. x 的平方根 
int No69_mySqrt( int x );

// 70.爬楼梯
int No70_climbStairs( int n );

// 83. 删除排序链表中的重复元素
ListNode* No83_deleteDuplicates(ListNode* head);

// 88. 合并两个有序数组
void No88_merge( vector<int>& nums1, int m, vector<int>& nums2, int n );

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

// 125. 验证回文串
bool No125_isPalindrome( string s );

// 136. 只出现一次的数字
int No136_singleNumber( vector<int>& nums );

// 141. 环形链表
bool No141_hasCycle( ListNode *head );

// 160. 相交链表
ListNode* No160_getIntersectionNode( ListNode* headA, ListNode* headB );

// 168. Excel表列名称
string No168_convertToTitle( int columnNumber );

// 169. 多数元素
int No169_majorityElement( vector<int>& nums );

// 190. 颠倒二进制位
uint32_t No190_reverseBits( uint32_t n );

// 191. 位1的个数
int No191_hammingWeight( uint32_t n );

// 202. 快乐数
bool No202_isHappy( int n );

// 203. 移除链表元素
ListNode* No203_removeElements( ListNode* head, int val );

// 205. 同构字符串
bool No205_isIsomorphic( string s, string t );

// 206. 反转链表
ListNode* No206_reverseList( ListNode* head );

// 217. 存在重复元素
bool No217_containsDuplicate( vector<int>& nums );

// 219. 存在重复元素 II
bool No219_containsNearbyDuplicate( vector<int>& nums, int k );

// 228. 汇总区间
vector<string> No228_summaryRanges( vector<int>& nums );
#endif // !__LeetCode_East_H__

