#include "Normal.h"

ListNode*
No2_addTwoNumbers( ListNode* l1, ListNode* l2 )
{
  ListNode head = ListNode( 0 );
  ListNode* list = &head;

  int sum = 0;
  while( l1 || l2 )
  {
    int value1 = 0;
    int value2 = 0;
    if( l1 ){ value1 = l1->val; l1 = l1->next; }
    if( l2 ){ value2 = l2->val; l2 = l2->next; }
    sum += value1 + value2;
    list->next = new ListNode( sum%10 );
    list = list->next;
    sum /= 10;
  }
  if( 0 < sum )
  {
    list->next = new ListNode( sum );
    list = list->next;
  }

  return head.next;
}

int
No3_lengthOfLongestSubstring( string s )
{
  // 哈希集合，记录每个字符是否出现过，这种容器不能存放重复的元素
  unordered_set<char> occ;
  int strSize = s.size();
  // 右指针，初始值为 -1，相当于我们在字符串的左边界的左侧，还没有开始移动
  int rightPointer = -1, ans = 0;
  // 枚举左指针的位置，初始值隐性地表示为 -1
  for( int leftPointer = 0; leftPointer < strSize; ++leftPointer )
  {
    if( leftPointer != 0 ) occ.erase( s[leftPointer - 1] ); // 左指针向右移动一格，移除一个字符
    while( ( rightPointer + 1 < strSize ) &&
           ( !occ.count( s[rightPointer + 1] ) ) ) // count查重
    {
      // 不断地移动右指针
      occ.insert( s[rightPointer + 1] );
      ++rightPointer;
    }
    // 从左到右是一个极长的无重复字符子串
    ans = max( ans, rightPointer - leftPointer + 1 );
  }
  return ans;
}

void
_GetLongestPalindrome( const string& s, int leftIdx, int rightIdx, string& ans )
{
  // 求回文子串最大长度
  while( 0 <= leftIdx && s.size() > rightIdx && s[leftIdx] == s[rightIdx] )
  {
    leftIdx--;
    rightIdx++;
  }

  // 求最大回文子串
  int strSize = ( --rightIdx ) - ( ++leftIdx ) + 1 ;
  if( strSize > 1 && strSize > ans.size() ) ans = s.substr( leftIdx, strSize );
}

string
No5_longestPalindrome( string s )
{
  string ans( "" );
  for( int idx = 1; idx < s.size(); idx++ )
  {
    // 一个元素为中心时的最大回文子串
    _GetLongestPalindrome( s, idx - 1, idx + 1, ans );

    // 两个元素为中心的最大回文子串
    _GetLongestPalindrome( s, idx - 1, idx, ans );

    // 当剩余字符串所组成的最大字符串长度小于当前回文字穿长度时则不需要循环剩下的字符
    if( ( s.size() - 1 - idx ) * 2 + 1 < ans.size() ) break;
  }

  // 没有回文子时，返回输入字符串的第一个字符
  if( ans.empty() && !s.empty() ) ans = s[0];

  return ans;
}

string
No6_convert( string s, int numRows )
{
  if( numRows == 1 ) return s;

  vector<string> rows( numRows );
  int nextRow = 0;
  bool goingDown = false;

  for( char c : s )
  {
    rows[nextRow] += c;
    // 最上层或最下层时，上下交换
    if( nextRow == 0 || nextRow == numRows - 1 ) goingDown = !goingDown;
    nextRow += goingDown ? 1 : -1;
  }

  string ans;
  for( string row : rows ) ans += row;

  return ans;
}

int
No11_maxArea( vector<int>& height )
{
  int left = 0;
  int right = height.size()-1;
  int maxArea = 0;
  while( left < right )
  {
    int area = min( height[left], height[right] ) * ( right - left );
    maxArea = max( maxArea, area );
    if( height[left] <= height[right] ) left++;
    else right--;
  }
  return maxArea;
}

vector<vector<int>>
No15_threeSum( vector<int>& nums )
{
    vector<vector<int>> ans;
    int size = nums.size();
    if( size < 3 ) return ans;

    sort( nums.begin(), nums.end() ); // 从小到大排序
    int target = 0; // 三数之和的目标值

#if 0
    for( int firstIdx = 0; firstIdx < size - 2; firstIdx++ )
    {
      if( 0 != firstIdx && nums[firstIdx] == nums[firstIdx-1] ) continue; // 和上一次重复的直接跳过

      int last = nums[firstIdx] + nums[firstIdx+1] - 1;
      for( int secondIdx = firstIdx + 1; secondIdx < size - 1; secondIdx++ )
      {
        int temp = nums[firstIdx] + nums[secondIdx];
        if( temp <= last ) continue; // 已经比较过的情况，直接跳过
        last = temp;

        for( int thirdIdx = secondIdx + 1; thirdIdx < size; thirdIdx++ )
        {
          int sum = last + nums[thirdIdx];
          if( sum > target ) break; // 再往后循环都是大于，直接跳出
          else if( sum < target ) continue; // 往后循环可能会等于，继续循环
          else // 等于，找到目标值，添加并跳出循环
          {
            ans.push_back( { nums[firstIdx], nums[secondIdx], nums[thirdIdx] } );
            break;
          }
        }
      }
    }
#endif
#if 1
    for( int secondIdx = 1; secondIdx < size - 1; secondIdx++ )
    {
      if( nums[secondIdx] == nums[secondIdx-1] && nums[secondIdx] == nums[secondIdx+1] ) continue; // 过滤第一次和上一次重复的
      for( int firstIdx = 0; firstIdx < secondIdx; firstIdx++ )
      {
        if( 0 != firstIdx && nums[firstIdx] == nums[firstIdx-1] ) continue; // 过滤第一次和上一次重复的
        for( int thirdIdx = secondIdx + 1; thirdIdx < size; thirdIdx++ )
        {
          if( thirdIdx != secondIdx + 1 && nums[thirdIdx] == nums[thirdIdx-1] ) continue; // 过滤第一次和上一次重复的
          int sum = nums[firstIdx] + nums[secondIdx] + nums[thirdIdx];
          if( sum > target ) break; // 再往后循环都是大于，直接跳出
          else if( sum < target ) continue; // 往后循环可能会等于，继续循环
          else // 等于，找到目标值，添加并跳出循环
          {
            ans.push_back( { nums[firstIdx], nums[secondIdx], nums[thirdIdx] } );
            break;
          }
        }
      }
    }
#endif
    return ans;
}


int
No16_threeSumClosest( vector<int>& nums, int target )
{
  sort( nums.begin(), nums.end() );
  int size = nums.size();
  int best = INT_MAX;

  auto update = [&]( int current )
  {
    if( abs( current - target ) < abs( best - target ) ) { best = current; };
  };

  for( int nowIndex = 0; nowIndex < size; nowIndex++ )
  {
    if( nowIndex > 0 && nums[nowIndex] == nums[nowIndex - 1] ) continue;
    int leftIndex = nowIndex + 1;
    int rightIndex = size - 1;
    while( leftIndex < rightIndex )
    {
      // 三数之和
      int sum = nums[nowIndex] + nums[leftIndex] + nums[rightIndex];
      update( sum );
      if( sum == target )
      {
        return target;
      }
      else if( sum > target )
      {
        // 右指针左移
        int temp = rightIndex - 1;
        while( leftIndex < temp && nums[rightIndex] == nums[temp] ) temp--;
        rightIndex = temp;
      }
      else
      {
        // 左指针右移
        int temp = leftIndex + 1;
        while( temp < rightIndex && nums[leftIndex] == nums[temp] ) temp++;
        leftIndex = temp;
      }
    }
  }
  return best;
}

// 电话号码的字母组合-利用队列
// 队列-广度遍历
// 递归-深度遍历
vector<string>
No17_letterCombinations( string digits )
{
  vector<string> ans;
  queue<string> que;  // 新建队列
  map<char, string> m =
  { {'2',"abc" },
    {'3',"def"},
    {'4',"ghi"},
    {'5',"jkl"},
    {'6',"mno"},
    {'7',"pqrs"},
    {'8',"tuv"},
    {'9',"wxyz"} }; // 映射map哈希表

  // 先将第一个元素对应的码表入队
  for( int j = 0; j < m[digits[0]].size(); j++ )
  {
    string s;
    s.push_back( m[digits[0]][j] );
    que.push( s ); // char转string入队
  }

  for( int i = 1; i < digits.size(); i++ )
  {
    int length = que.size(); // 当前队列长度
    while( length-- )
    {
      for( int j = 0; j < m[digits[i]].size(); j++ )
      {
        string s = que.front() + m[digits[i]][j]; // 队头元素加上新元素
        que.push( s ); // 入队
      }
      que.pop(); // 队头出队
    }
  }

  while( !que.empty() )
  {
    ans.push_back( que.front() ); //队头元素存储至ans
    que.pop(); //队头出队
  }
  return ans; //返回
}

static void
backtrack( vector<string>& ans, string& cur, int open, int close, int n )
{
  if( cur.size() == n * 2 ) {
    ans.push_back( cur );
    return;
  }
  if( open < n ) {
    cur.push_back( '(' );
    backtrack( ans, cur, open + 1, close, n );
    cur.pop_back();
  }
  if( close < open ) {
    cur.push_back( ')' );
    backtrack( ans, cur, open, close + 1, n );
    cur.pop_back();
  }
}

vector<string>
No22_generateParenthesis( int n )
{
  // 回溯法
  vector<string> result;
  string current;
  backtrack( result, current, 0, 0, n );
  return result;
}

static void
No22_Dfs( int count, int lc, int rc, string str, vector<string> res )
{
  if( lc == count && rc == count ) res.push_back( str );
  else
  {
    if( lc < count ) No22_Dfs( count, lc + 1, rc, str + '(', res ); // 拼接左括号
    if( rc < count && lc > rc ) No22_Dfs( count, lc, rc + 1, str + ')', res ); // 拼接右括号
  }
}

vector<string>
No22_generateParenthesis_2( int n )
{
  vector<string> res;
  No22_Dfs( n, 0, 0, "", res );
  return res;
}

static int
JumpIndex( int index, vector<int>& nums )
{
  int jumpIndex = index;
  int maxStep = 0;
  for( int n = 1; n <= nums[index]; n++ )
  {
    if( n + index >= nums.size() - 1 )
    {
      jumpIndex = n + index;
      break;
    }
    if( n + nums[n + index] >= maxStep )
    {
      maxStep = n + nums[n + index];
      jumpIndex = n + index;
    }
  }
  return jumpIndex;
}

int No45_jump( vector<int>& nums )
{
  int step = 0;
  int index = 0;
  while( index < nums.size() - 1 )
  {
    step++;
    int jumpIndex = JumpIndex( index, nums );
    if( index == jumpIndex )
    {
      _ASSERT( 0 );
      break;
    }
    index = jumpIndex;
  }
  return step;
}

int No45_jump_2( vector<int>& nums )
{
  int maxPos = 0, nowPos = 0, end = 0, step = 0, n = nums.size() - 1;
  while( end < n )
  {
    maxPos = max( maxPos, nums[nowPos] + nowPos );
    if( nowPos == end )
    {
      step++;
      end = maxPos;
    }
    nowPos++;
  }
  return step;
}

// 排序 C( m + n - 2, m ) 或 C( m + n - 2, n ) 试过了，容易超时
// 动态规划
int
No62_uniquePaths( int m, int n )
{
  vector<vector<int>> dp( n, vector<int>( m ) );
  for( int i = 0; i < n; i++ )
  {
    for( int j = 0; j < m; j++ )
    {
      if( i == 0 || j == 0 )
      {
        dp[i][j] = 1; //最上一行或者最左一列
      }
      else
      {
        dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
      }
    }
  }
  return dp[n - 1][m - 1];
}

