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
int No27_removeElement( vector<int>& nums, int val );

// 28. 实现 strStr()
int No28_strStr( string haystack, string needle );

// 35. 搜索插入位置
int No35_searchInsert( vector<int>& nums, int target );

// 38. 外观数列
string No38_countAndSay( int n );

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
ListNode* No83_deleteDuplicates( ListNode* head );

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

// 108. 将有序数组转换为二叉搜索树
TreeNode* No108_sortedArrayToBST( vector<int>& nums );

// 110. 平衡二叉树
bool No110_isBalanced( TreeNode* root );

// 111. 二叉树的最小深度
int No111_minDepth( TreeNode* root );

// 112. 路径总和
bool No112_hasPathSum( TreeNode* root, int targetSum );

// 118. 杨辉三角
vector<vector<int>> No118_generate( int numRows );

// 119. 杨辉三角 II
vector<int> No119_getRow( int rowIndex );

// 121. 买卖股票的最佳时机
int No121_maxProfit( vector<int>& prices );

// 125. 验证回文串
bool No125_isPalindrome( string s );

// 136. 只出现一次的数字
int No136_singleNumber( vector<int>& nums );

// 141. 环形链表
bool No141_hasCycle( ListNode* head );

// 144. 二叉树的前序遍历
vector<int> No144_preorderTraversal( TreeNode* root );

// 145. 二叉树的后序遍历
vector<int> No145_postorderTraversal( TreeNode* root );

// 160. 相交链表
ListNode* No160_getIntersectionNode( ListNode* headA, ListNode* headB );

// 168. Excel表列名称
string No168_convertToTitle( int columnNumber );

// 169. 多数元素
int No169_majorityElement( vector<int>& nums );

// 171. Excel 表列序号
int No171_titleToNumber( string columnTitle );

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

// 226. 翻转二叉树
TreeNode* No226_invertTree( TreeNode* root );

// 228. 汇总区间
vector<string> No228_summaryRanges( vector<int>& nums );

// 231. 2 的幂
bool No231_isPowerOfTwo( int n );

// 234. 回文链表
bool No234_isPalindrome( ListNode* head );

// 242. 有效的字母异位词
bool No242_isAnagram( string s, string t );

// 257. 二叉树的所有路径
vector<string> No247_binaryTreePaths( TreeNode* root );

// 258. 各位相加
int No258_addDigits( int num );

// 263. 丑数
bool No263_isUgly( int n );

// 268. 丢失的数字
int No268_missingNumber( vector<int>& nums );

// 278. 第一个错误的版本
int No278_firstBadVersion( int n );

// 283. 移动零
void No283_moveZeroes( vector<int>& nums );

// 290. 单词规律
bool No290_wordPattern( string pattern, string s );

// 292. Nim 游戏
bool No292_canWinNim( int n );

// 338. 比特位计数
vector<int> No338_countBits( int n );

// 342. 4的幂
bool No342_isPowerOfFour( int n );

// 344. 反转字符串
void No344_reverseString( vector<char>& s );

// 345. 反转字符串中的元音字母
string No345_reverseVowels( string s );

// 349. 两个数组的交集
vector<int> No349_intersection( vector<int>& nums1, vector<int>& nums2 );

// 392. 判断子序列
bool No392_isSubsequence( string s, string t );

// 404. 左叶子之和
int No404_sumOfLeftLeaves( TreeNode* root );

// 455. 分发饼干
int No455_findContentChildren( vector<int>& g, vector<int>& s );

// 501. 二叉搜索树中的众数
vector<int> No501_findMode( TreeNode* root );

// 509. 斐波那契数
int No509_fib( int n );

// 530. 二叉搜索树的最小绝对差
int No530_getMinimumDifference( TreeNode* root );

// 617. 合并二叉树
TreeNode* No617_mergeTrees( TreeNode* root1, TreeNode* root2 );

// 674. 最长连续递增序列
int No674_findLengthOfLCIS( vector<int>& nums );

// 700. 二叉搜索树中的搜索
TreeNode* No700_searchBST( TreeNode* root, int val );

// 704. 二分查找
int No704_search( vector<int>& nums, int target );

// 746. 使用最小花费爬楼梯
int No746_minCostClimbingStairs( vector<int>& cost );

// 977. 有序数组的平方
vector<int> No977_sortedSquares( vector<int>& nums );

// 1047. 删除字符串中的所有相邻重复项
string No1047_removeDuplicates( string s );

#endif // !__LeetCode_East_H__

