#ifndef __LeetCode_Base_H__
#define __LeetCode_Base_H__
// 数据结构
#include <string>          // 字符串
#include <vector>          // 向量
#include <map>             // 哈希表
#include <stack>           // 栈
#include <unordered_set>   // 哈希集合
#include <unordered_map>   // 哈希表
#include <queue>           // 队列
#include <algorithm>       // 一些数学函数，如max
#include <iostream>        // 标准输入输出
#pragma warning(disable:4267) // 从“size_t”转换到“int”，可能丢失数据

using namespace std;

// 定义链表
// Definition for a binary list node.
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 定义树
// Definition for a binary tree node.
struct TreeNode
{
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

/// <summary>
/// 组合数公式C( N, K )
/// </summary>
/// <param name="N"></param>
/// <param name="k"></param>
/// <returns>组合数</returns>
int Combination( int N, int k );

/// <summary>
/// 打印字符串向量
/// </summary>
/// <param name="strVector"></param>
void
PrintStrVector( const vector<string>& strVector );

/// <summary>
/// 打印一维整型
/// </summary>
/// <param name="intVector"></param>
void
PrintIntVector( const vector<int>& intVector );

/// <summary>
/// 打印二维整型
/// </summary>
/// <param name="doubleIntVector"></param>
void
PrintDoubleIntVector( const vector<vector<int>>& doubleIntVector );

#endif // !__LeetCode_Base_H__

