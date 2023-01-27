#ifndef __LeetCode_Normal_H__
#define __LeetCode_Normal_H__

#include "Base.h"

// 2. 两数相加
ListNode* No2_addTwoNumbers( ListNode* l1, ListNode* l2 );

// 3. 无重复字符的最长子串
int No3_lengthOfLongestSubstring( string s );

// 5. 最长回文子串
string No5_longestPalindrome( string s );

// 6. Z 字形变换
string No6_convert( string s, int numRows );

// 8. 字符串转换整数 (atoi)
int No8_myAtoi( string s );

// 11. 盛最多水的容器
int No11_maxArea( vector<int>& height );

// 15. 三数之和
vector<vector<int>> No15_threeSum( vector<int>& nums );

// 16. 最接近的三数之和
int No16_threeSumClosest( vector<int>& nums, int target );

// 17. 电话号码的字母组合
vector<string> No17_letterCombinations( string digits );

// 18. 四数之和
vector<vector<int>> No18_fourSum( vector<int>& nums, int target );

// 19. 删除链表的倒数第 N 个结点
ListNode* No19_removeNthFromEnd( ListNode* head, int n );

// 22. 括号生成
vector<string> No22_generateParenthesis( int n );
vector<string> No22_generateParenthesis_2( int n );

// 24. 两两交换链表中的节点
ListNode* No24_swapPairs( ListNode* head );

// 39. 组合总和
vector<vector<int>> No39_combinationSum( vector<int>& candidates, int target );

// 40. 组合总和 II
vector<vector<int>> No40_combinationSum2( vector<int>& candidates, int target );

// 45. 跳跃游戏 II
int No45_jump( vector<int>& nums );

// 46. 全排列
vector<vector<int>> No46_permute( vector<int>& nums );

// 47. 全排列 II
vector<vector<int>> No47_permuteUnique( vector<int>& nums );

// 53. 最大子数组和
int No53_maxSubArray( vector<int>& nums );

// 55. 跳跃游戏
bool No55_canJump( vector<int>& nums );

// 59. 螺旋矩阵 II
vector<vector<int>> No59_generateMatrix( int n );

// 62. 不同路径
int No62_uniquePaths( int m, int n );

// 63. 不同路径 II
int No63_uniquePathsWithObstacles( vector<vector<int>>& obstacleGrid );

// 77. 组合
vector<vector<int>> No77_combine( int n, int k );

// 78. 子集
vector<vector<int>> No78_subsets( vector<int>& nums );

// 90. 子集 II
vector<vector<int>> No90_subsetsWithDup( vector<int>& nums );

// 93. 复原 IP 地址
vector<string> No93_restoreIpAddresses( string s );

// 96. 不同的二叉搜索树
int No96_numTrees( int n );

// 98. 验证二叉搜索树
bool No98_isValidBST( TreeNode* root );

// 122. 买卖股票的最佳时机 II
int No122_maxProfit( vector<int>& prices );

// 131. 分割回文串
vector<vector<string>> No131_partition( string s );

// 139. 单词拆分
bool No139_wordBreak( string s, vector<string>& wordDict );

// 142. 环形链表 II
ListNode* No142_detectCycle( ListNode* head );

// 150. 逆波兰表达式求值
int No150_evalRPN( vector<string>& tokens );

// 151. 反转字符串中的单词
string No151_reverseWords( string s );

// 198. 打家劫舍
int No198_rob( vector<int>& nums );

// 209. 长度最小的子数组
int No209_minSubArrayLen( int target, vector<int>& nums );

// 213. 打家劫舍 II
int No213_rob( vector<int>& nums );

// 216. 组合总和 III
vector<vector<int>> No216_combinationSum3( int k, int n );

// 222. 完全二叉树的节点个数
int No222_countNodes( TreeNode* root );

// 235. 二叉搜索树的最近公共祖先
TreeNode* No235_lowestCommonAncestor( TreeNode* root, TreeNode* p, TreeNode* q );

// 236. 二叉树的最近公共祖先
TreeNode* No236_lowestCommonAncestor( TreeNode* root, TreeNode* p, TreeNode* q );

// 279. 完全平方数
int No279_numSquares( int n );

// 300. 最长递增子序列
int No300_lengthOfLIS( vector<int>& nums );

// 309. 最佳买卖股票时机含冷冻期
int No309_maxProfit( vector<int>& prices );

// 322. 零钱兑换
int No322_coinChange( vector<int>& coins, int amount );

// 337. 打家劫舍 III
int No337_rob( TreeNode* root );

// 343. 整数拆分
int No343_integerBreak( int n );

// 376. 摆动序列
int No376_wiggleMaxLength( vector<int>& nums );

// 377. 组合总和 Ⅳ
int No377_combinationSum4( vector<int>& nums, int target );

// 416. 分割等和子集
bool No416_canPartition( vector<int>& nums );

// 450. 删除二叉搜索树中的节点
TreeNode* No450_deleteNode( TreeNode* root, int key );

// 454. 四数相加 II
int No454_fourSumCount( vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4 );

// 474. 一和零
int No474_findMaxForm( vector<string>& strs, int m, int n );

// 491. 递增子序列
vector<vector<int>> No491_findSubsequences( vector<int>& nums );

// 494. 目标和
int No494_findTargetSumWays( vector<int>& nums, int target );

// 513. 找树左下角的值
int No513_findBottomLeftValue( TreeNode* root );

// 516. 最长回文子序列
int No516_longestPalindromeSubseq( string s );

// 518. 零钱兑换 II
int No518_change( int amount, vector<int>& coins );

// 538. 把二叉搜索树转换为累加树
TreeNode* No538_convertBST( TreeNode* root );

// 583. 两个字符串的删除操作
int No583_minDistance( string word1, string word2 );

// 647. 回文子串
int No647_countSubstrings( string s );

// 654. 最大二叉树
TreeNode* No654_constructMaximumBinaryTree( vector<int>& nums );

// 669. 修剪二叉搜索树
TreeNode* No669_trimBST( TreeNode* root, int low, int high );

// 701. 二叉搜索树中的插入操作
TreeNode* No701_insertIntoBST( TreeNode* root, int val );

// 714. 买卖股票的最佳时机含手续费
int No714_maxProfit( vector<int>& prices, int fee );

// 718. 最长重复子数组
int No718_findLength( vector<int>& nums1, vector<int>& nums2 );

// 1035. 不相交的线
int No1035_maxUncrossedLines( vector<int>& nums1, vector<int>& nums2 );

// 1049. 最后一块石头的重量 II
int No1049_lastStoneWeightII( vector<int>& stones );

// 1143. 最长公共子序列
int No1143_longestCommonSubsequence( string text1, string text2 );

#endif // !__LeetCode_East_H__

