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
    if( l1 )
    {
      value1 = l1->val; l1 = l1->next;
    }
    if( l2 )
    {
      value2 = l2->val; l2 = l2->next;
    }
    sum += value1 + value2;
    list->next = new ListNode( sum % 10 );
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
  int strSize = ( --rightIdx ) - ( ++leftIdx ) + 1;
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

int No8_myAtoi( string s )
{
  // 这题目前放弃了，测试用例有点蛋疼，如+-12 视为0之类
  long long ans = 0;
  int sign = 1;
  int size = s.length();
  for( const char& c : s )
  {
    if( c == '-' ) sign = -1;
    if( c == '.' ) break; // 我tm真的佛了，“.1”你答案居然认为是0
    if( isalpha( c ) ) break;
    if( isdigit( c ) )
    {
      int n = c - '0';
      ans = ans * 10 + n;
    }
    else
    {
      if( ans != 0 ) break;
    }
  }
  ans *= sign;
  ans = ans > 0 ? min( ans, (long long)INT_MAX ) :
    max( ans, (long long)INT_MIN );
  return static_cast<int>( ans );
}

int
No11_maxArea( vector<int>& height )
{
  int left = 0;
  int right = height.size() - 1;
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
  sort( nums.begin(), nums.end() ); // 从小到大排序

  int size = nums.size();
  for( int pos = 0; pos < size; pos++ )
  {
    if( nums[pos] > 0 ) break; // 剪枝
    if( pos > 0 && nums[pos] == nums[pos - 1] ) continue; // 去重
    int left = pos + 1;
    int right = size - 1;
    while( left < right )
    {
      int sum = nums[pos] + nums[left] + nums[right];
      if( sum > 0 ) right--;
      else if( sum < 0 ) left++;
      else
      {
        ans.push_back( {nums[pos], nums[left], nums[right]} );
        // 去重
        while( left < right && nums[left] == nums[left + 1] ) left++;
        while( left < right && nums[right] == nums[right - 1] ) right--;
        // 两端收缩
        left++;
        right--;
      }
    }
  }

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
    if( abs( current - target ) < abs( best - target ) )
    {
      best = current;
    };
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

void No17_backtrack( const string& digits,
                     vector<string>& ans,
                     string& s,
                     map<char, string>& letterMap,
                     int index )
{
  if( index == digits.size() )
  {
    ans.push_back( s );
    return;
  }

  string letters = letterMap[digits[index]];
  for( int i = 0; i < letters.size(); i++ )
  {
    s.push_back( letters[i] );
    No17_backtrack( digits, ans, s, letterMap, index + 1 );
    s.pop_back();
  }
}

vector<string>
No17_letterCombinations( string digits )
{
  // 电话号码的字母组合-利用队列
  // 队列-广度遍历
  // 递归-深度遍历
  vector<string> ans;

  // 方法1：迭代法
  queue<string> que;  // 新建队列
  map<char, string> m =
  {{'2',"abc"},
    {'3',"def"},
    {'4',"ghi"},
    {'5',"jkl"},
    {'6',"mno"},
    {'7',"pqrs"},
    {'8',"tuv"},
    {'9',"wxyz"}}; // 映射map哈希表
#if 0
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
#endif
  // 方法二：递归法
  string s;
  if( digits.size() == 0 ) return ans;
  No17_backtrack( digits, ans, s, m, 0 );
  return ans; //返回
}

static bool No18_isCut( const int sum, const int target )
{
  if( target >= 0 && sum > target ) return true;
  return false;
}

vector<vector<int>> No18_fourSum( vector<int>& nums, int target )
{
  // 三数之和的升级版，不过target不为0，要注意剪枝方法
  vector<vector<int>> ans;
  sort( nums.begin(), nums.end() ); // 从小到大排序

  int size = nums.size();
  // 比三数之和多套了一层循环
  for( int first = 0; first < size - 3; first++ )
  {
    // 四数之和可能会超过int型最大值,要定义成long型
    long sum = nums[first];
    if( No18_isCut( sum, target ) ) break; // 剪枝
    if( first > 0 && nums[first] == nums[first - 1] ) continue; // 去重

    // 以下和三数之和代码类似
    for( int pos = first + 1; pos < size - 2; pos++ )
    {
      sum = nums[first] + nums[pos];
      if( No18_isCut( sum, target ) ) break; // 剪枝
      if( pos > first + 1 && nums[pos] == nums[pos - 1] ) continue; // 去重
      int left = pos + 1;
      int right = size - 1;
      while( left < right )
      {
        // 四数之和可能会超过int型最大值,要把第一个数强转成long型，确保int加变成long加不会越界。
        sum = (long)nums[first] + nums[pos] + nums[left] + nums[right];
        if( sum > target ) right--;
        else if( sum < target ) left++;
        else
        {
          ans.push_back( {nums[first], nums[pos], nums[left], nums[right]} );
          // 去重
          while( left < right && nums[left] == nums[left + 1] ) left++;
          while( left < right && nums[right] == nums[right - 1] ) right--;
          // 两端收缩
          left++;
          right--;
        }
      }
    }
  }

  return ans;
}

ListNode* No19_removeNthFromEnd( ListNode* head, int n )
{
  ListNode* dummy = new ListNode( 0 );
  dummy->next = head;
  ListNode* fast = dummy;
  ListNode* slow = dummy;
  // 快指针先走n+1步
  n++;
  while( n-- && fast ) fast = fast->next;
  // 快慢指针一起走，走到底时慢指针所指的就是倒数第n个数
  while( fast )
  {
    fast = fast->next;
    slow = slow->next;
  }
  // 常规链表删除操作
  ListNode* temp = slow->next;
  slow->next = slow->next->next;
  delete temp;

  return dummy->next;
}

static void
No22_backtrack( vector<string>& ans, string& cur, int open, int close, int n )
{
  if( cur.size() == n * 2 )
  {
    ans.push_back( cur );
    return;
  }
  if( open < n )
  {
    cur.push_back( '(' );
    No22_backtrack( ans, cur, open + 1, close, n );
    cur.pop_back();
  }
  if( close < open )
  {
    cur.push_back( ')' );
    No22_backtrack( ans, cur, open, close + 1, n );
    cur.pop_back();
  }
}

vector<string>
No22_generateParenthesis( int n )
{
  // 回溯法
  vector<string> result;
  string current;
  No22_backtrack( result, current, 0, 0, n );
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

ListNode* No24_swapPairs( ListNode* head )
{
  ListNode* dummy = new ListNode( 0 );
  dummy->next = head;
  ListNode* cur = dummy;
  while( cur->next && cur->next->next )
  {
    //            cur ( = dummy )
    //            ↓
    // dummy(0) -> 1 -> 2 -> 3 ...
    ListNode* temp1 = cur->next;
    ListNode* temp2 = cur->next->next;
    ListNode* temp3 = cur->next->next->next;

    //     cur
    //     ↓
    // 1 -> 2 -> 3 ...
    cur->next = temp2;

    //     cur
    //     ↓
    // 1 <- 2  3 ...
    temp2->next = temp1;

    //          cur
    //          ↓
    // 3 <- 1 <- 2
    temp1->next = temp3;

    // cur移动，准备下一轮交换
    //      cur
    //      ↓
    // 3 <- 1 <- 2
    cur = temp1;
  }

  ListNode* ans = dummy->next;
  delete dummy;
  return ans;
}

vector<vector<int>> No39_ans;
vector<int> No39_temp;
void No39_backtracking( const vector<int>& candidates, int sum, int startIndex, const int target )
{
  if( sum > target ) return;
  if( sum == target )
  {
    No39_ans.push_back( No39_temp );
    return;
  }

  for( int i = startIndex; i < candidates.size(); i++ )
  {
    int n = candidates[i];
    No39_temp.push_back( n );
    sum += n;
    No39_backtracking( candidates, sum, i, target );
    No39_temp.pop_back();
    sum -= n;
  }
}

vector<vector<int>> No39_combinationSum( vector<int>& candidates, int target )
{
  No39_backtracking( candidates, 0, 0, target );
  return No39_ans;
}

vector<vector<int>> No40_ans;
vector<int> No40_temp;
void No40_backtracking( const vector<int>& candidates, const int size, const int target, const int startIndex, int sum )
{
  if( sum > target ) return;
  if( sum == target )
  {
    No40_ans.push_back( No40_temp );
    return;
  }

  for( int pos = startIndex; pos < size; pos++ )
  {
    // 剪枝
    if( pos > startIndex && candidates[pos] == candidates[pos - 1] ) continue;
    int n = candidates[pos];
    sum += n;
    if( sum > target ) return;
    No40_temp.push_back( n );
    No40_backtracking( candidates, size, target, pos + 1, sum );
    No40_temp.pop_back();
    sum -= n;
  }
}

vector<vector<int>> No40_combinationSum2( vector<int>& candidates, int target )
{
  sort( candidates.begin(), candidates.end() );
  No40_backtracking( candidates, candidates.size(), target, 0, 0 );
  return No40_ans;
}

int No45_jump( vector<int>& nums )
{
  // 贪心
  // 局部最优：每一步覆盖的最远距离
  // 全局最优：一步尽可能多走，从而达到最小步数
  int step = 0;
  // 当前最远覆盖距离，下一步最远覆盖距离
  int curDistance = 0, nextDistance = 0;
  for( int i = 0; i < nums.size() - 1; i++ ) // 注意这里是小于nums.size() - 1，这是关键所在
  {
    // 记录下一步可覆盖的追远距离
    nextDistance = max( i + nums[i], nextDistance );
    if( i == curDistance )
    {
      // 当前最远覆盖距离都探索玩后，探索下一步最远覆盖距离，步进+1
      curDistance = nextDistance;
      step++;
}
      }
  return step;
#if 0
  int nowPos, maxPos, endPos, step, lastPos;
  nowPos = maxPos = endPos = step = 0;
  lastPos = nums.size() - 1;
  while( endPos < lastPos )
  {
    maxPos = max( maxPos, nums[nowPos] + nowPos );
    if( nowPos == endPos )
    {
      step++;
      endPos = maxPos;
    }
    nowPos++;
  }
  return step;
#endif
}

vector<vector<int>> No46_ans;
vector<int> No46_temp;
void No46_backtracking( const vector<int>& nums, vector<bool>& used, const int size )
{
  if( No46_temp.size() == size )
  {
    No46_ans.push_back( No46_temp );
  }

  for( int pos = 0; pos < size; pos++ )
  {
    if( used[pos] ) continue;
    used[pos] = true;
    No46_temp.push_back( nums[pos] );
    No46_backtracking( nums, used, size );
    No46_temp.pop_back();
    used[pos] = false;
  }
}

vector<vector<int>> No46_permute( vector<int>& nums )
{
  vector<bool> used( nums.size(), false );
  No46_backtracking( nums, used, nums.size() );
  return No46_ans;
}

vector<vector<int>> No47_ans;
vector<int> No47_temp;
void No47_backtracking( const vector<int>& nums, vector<bool>& used, const int size )
{
  if( No47_temp.size() == size )
  {
    No47_ans.push_back( No47_temp );
  }

  for( int pos = 0; pos < size; pos++ )
  {
    if( used[pos] ) continue;
    // 和46题相比多了下面这条判断，当两个相同的数，前一个已经用过时，为了不重复，就continue
    // used[pos-1] == true时做的是树枝上的去重
    // used[pos-1] == false时做的是树层上的去重
    if( pos > 0 && nums[pos] == nums[pos - 1] && !used[pos - 1] ) continue;
    used[pos] = true;
    No47_temp.push_back( nums[pos] );
    No47_backtracking( nums, used, size );
    No47_temp.pop_back();
    used[pos] = false;
  }
}

vector<vector<int>> No47_permuteUnique( vector<int>& nums )
{
  sort( nums.begin(), nums.end() );
  vector<bool> used( nums.size(), false );
  No47_backtracking( nums, used, nums.size() );
  return No47_ans;
}

int No53_maxSubArray( vector<int>& nums )
{
  // dp[i]：包括下标i（以nums[i]为结尾）的最大连续子序列和为dp[i]。
  if( nums.size() == 0 ) return 0;
  vector<int> dp( nums.size() );
  dp[0] = nums[0];
  int result = dp[0];
  for( int i = 1; i < nums.size(); i++ )
  {
    dp[i] = max( dp[i - 1] + nums[i], nums[i] );
    if( dp[i] > result ) result = dp[i];
  }
  return result;

  // 也可去掉数组，直接用前一个数直接推导出下一个，如
#if 0
  int pre = 0, maxAns = nums[0];
  for( const auto& x : nums )
  {
    pre = max( pre + x, x );
    maxAns = max( maxAns, pre );
  }
  return maxAns;
#endif

#if 0
  // 贪心
  // 局部最优的情况下，并记录最大的“连续和”，可以推出全局最优。
  int result = INT32_MIN;
  int sum = 0;
  for(int i=0;i<nums.size();i++ )
  {
    sum += nums[i];
    // 取区间累计的最大值（相当于不断确定最大子序终止位置）
    if( sum > result ) result = sum;
    // 累计和为负时归零
    if( sum <= 0 ) sum = 0;
  }
  return result;
#endif
}

bool No55_canJump( vector<int>& nums )
{
  // 那么这个问题就转化为跳跃覆盖范围究竟可不可以覆盖到终点！
  // 贪心算法局部最优解：每次取最大跳跃步数（取最大覆盖范围），整体最优解：最后得到整体最大覆盖范围，看是否能到终点。
  int cover = 0;
  if( nums.size() == 1 ) return true;
  // 这里要<=cover而不是nums.size()，要确保不会跨过去
  for( int i = 0; i <= cover; i++ )
  {
    cover = max( i + nums[i], cover );
    if( cover >= nums.size() - 1 ) return true;
  }
  return false;
}

vector<vector<int>> No59_generateMatrix( int n )
{
  vector<vector<int>> res( n, vector<int>( n, 0 ) ); // 使用vector定义一个二维数组
  int startx = 0, starty = 0; // 定义每循环一个圈的起始位置
  int loop = n / 2; // 每个圈循环几次，例如n为奇数3，那么loop = 1 只是循环一圈，矩阵中间的值需要单独处理
  int mid = n / 2; // 矩阵中间的位置，例如：n为3， 中间的位置就是(1，1)，n为5，中间位置为(2, 2)
  int count = 1; // 用来给矩阵中每一个空格赋值
  int offset = 1; // 需要控制每一条边遍历的长度，每次循环右边界收缩一位
  int i, j;
  while( loop-- )
  {
    i = startx;
    j = starty;
    // 转圈，左闭右开，顺序上，右，下，左
    for( j = starty; j < n - offset; j++ ) res[startx][j] = count++;
    for( i = startx; i < n - offset; i++ ) res[i][j] = count++;
    for( ; j > starty; j-- ) res[i][j] = count++;
    for( ; i > startx; i-- ) res[i][j] = count++;
    // 第二圈开始的时候，起始位置要各自加1， 例如：第一圈起始位置是(0, 0)，第二圈起始位置是(1, 1)
    startx++;
    starty++;

    // offset 控制每一圈里每一条边遍历的长度
    offset += 1;

  }
  // 如果n为奇数的话，需要单独给矩阵最中间的位置赋值
  if( n % 2 ) res[mid][mid] = count;

  return res;
}

// 排序 C( m + n - 2, m ) 或 C( m + n - 2, n ) 试过了，容易超时
// 动态规划
int
No62_uniquePaths( int m, int n )
{
  // 创建 m x n的网格
  vector<vector<int>> dp( m, vector<int>( n, 0 ) );
  // 两边初始化
  for( int x = 0; x < m; x++ ) dp[x][0] = 1;
  for( int y = 0; y < n; y++ ) dp[0][y] = 1;
  // 动归
  for( int x = 1; x < m; x++ )
    for( int y = 1; y < n; y++ )
      dp[x][y] = dp[x - 1][y] + dp[x][y - 1];
  return dp[m - 1][n - 1];
}

int No63_uniquePathsWithObstacles( vector<vector<int>>& obstacleGrid )
{
  int n = obstacleGrid.size();
  int m = obstacleGrid[0].size();
  vector<vector<int>> dp( n, vector<int>( m ) );
  for( int i = 0; i < n && obstacleGrid[i][0] == 0; i++ )
  {
    dp[i][0] = 1;
  }
  for( int j = 0; j < m && obstacleGrid[0][j] == 0; j++ )
  {
    dp[0][j] = 1;
  }

  for( int i = 1; i < n; i++ )
  {
    for( int j = 1; j < m; j++ )
    {
      if( obstacleGrid[i][j] == 1 ) continue;
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }
  return dp[n - 1][m - 1];
}

vector<int> path_77;
vector<vector<int>> result_77;
void No77_backtracking( int n, int k, int startIndex )
{
  if( path_77.size() == k )
  {
    result_77.push_back( path_77 );
    return;
  }
  for( int i = startIndex; i <= n; i++ )
  {
    path_77.push_back( i );
    No77_backtracking( n, k, i + 1 );
    path_77.pop_back();
  }
}

vector<vector<int>> No77_combine( int n, int k )
{
  No77_backtracking( n, k, 1 );
  return result_77;
}

void No78_backtracking( vector<int>& nums, int startIndex, vector<int>& path, vector<vector<int>>& ans )
{
  ans.push_back( path );
  for( int i = startIndex; i < nums.size(); i++ )
  {
    path.push_back( nums[i] );
    No78_backtracking( nums, i + 1, path, ans );
    path.pop_back();
  }
}

vector<vector<int>> No78_subsets( vector<int>& nums )
{
  vector<int> path;
  vector<vector<int>> ans;
  No78_backtracking( nums, 0, path, ans );
  return ans;
}

void No90_backtracking( vector<int>& nums, int startIndex, vector<int>& path, vector<vector<int>>& ans )
{
  ans.push_back( path );
  unordered_set<int> useSet; // 用set去重,层间不重复，树间可重复
  for( int i = startIndex; i < nums.size(); i++ )
  {
    if( useSet.find( nums[i] ) != useSet.end() ) continue; // 前面一次已用过
    useSet.insert( nums[i] );
    path.push_back( nums[i] );
    No78_backtracking( nums, i + 1, path, ans );
    path.pop_back();
  }
}

vector<vector<int>> No90_subsetsWithDup( vector<int>& nums )
{
  vector<int> path;
  vector<vector<int>> ans;
  sort( nums.begin(), nums.end() );
  No90_backtracking( nums, 0, path, ans );
  return ans;
}

bool No93_isValid( const string& s, int start, int end )
{
  if( start > end )return false;
  if( s[start] == '0' && start != end ) return false; // 0开头的数字不合法
  int num = 0;
  for( int i = start; i <= end; i++ )
  {
    if( s[i] > '9' || s[i] < '0' ) return false; // 遇到非数字字符不合法
    num = num * 10 + ( s[i] - '0' );
    if( num > 255 ) return false; // 如果大于255了不合法
  }
  return true;
}

void No93_backtracking( string& s, vector<string>& ans, int startIndex, int pointNum )
{
  if( pointNum == 3 ) // 逗点数量为3时，分隔结束
  {
    if( No93_isValid( s, startIndex, s.size() - 1 ) ) ans.push_back( s );
    return;
  }
  for( int i = startIndex; i < s.size(); i++ )
  {
    if( No93_isValid( s, startIndex, i ) )
    {
      s.insert( s.begin() + i + 1, '.' ); // 在i的后面插入一个逗点
      No93_backtracking( s, ans, i + 2, pointNum + 1 ); // 递归回溯
      s.erase( s.begin() + i + 1 ); // 回溯
    }
    else break; // 不合法，直接结束本层循环
  }
}

vector<string> No93_restoreIpAddresses( string s )
{
  vector<string> ans;
  if( s.size() < 4 || s.size() > 12 ) return ans;
  No93_backtracking( s, ans, 0, 0 );
  return ans;
}

int No96_numTrees( int n )
{
  vector<int> dp( n + 1 );
  dp[0] = 1;
  for( int i = 1; i <= n; i++ )
  {
    for( int j = 1; j <= i; j++ )
    {
      // 这里是+=，即从1开始加到i的累和
      // dp[j - 1]相当于左子树所有情况
      // dp[i-j]相当于右子树所有情况
      // 相乘即为所有情况
      dp[i] += dp[j - 1] * dp[i - j];
    }
  }
  return dp[n];
}

static long No98_min = LONG_MIN;
bool No98_isValidBST( TreeNode* root )
{
  if( !root ) return true;
  bool left = No98_isValidBST( root->left ); // 左
  if( !left ) return false;
  if( root->val > No98_min ) No98_min = root->val; // 中
  else return false;
  bool right = No98_isValidBST( root->right ); // 右
  return right;
}

int
No122_maxProfit( vector<int>& prices )
{
  // 动态规划法
  // dp[i][0] 表示第i天持有股票所得最多现金
  // dp[i][1] 表示第i天不持有股票所得最多现金
  int size = prices.size();
  if( size == 0 ) return 0;
  vector<vector<int>> dp( size, vector<int>( 2, 0 ) );
  dp[0][0] = 0 - prices[0]; // 当天买进后手里现金
  dp[0][1] = 0;             // 当天买进后又卖出后手里现金
  for( int i = 1; i < size; i++ )
  {
    // 对比前一天买入和今天买入(剩下钱为值钱赚的减去今天买的)，哪个花钱少
    dp[i][0] = max( dp[i - 1][0], dp[i - 1][1] - prices[i] ); // 和No.121唯一区别
    // 对比之前卖出和今天卖出，哪个赚钱多
    dp[i][1] = max( dp[i - 1][1], dp[i - 1][0] + prices[i] );
}
  return dp[size - 1][1];

#if 0
  int size = prices.size();
  if( size < 2 ) return 0;
  int maxProfit = 0;

  // 看答案的，累加连续上升区间即可，即每天都判断是否可交易,不考虑手续费可还行
  for( int i = 1; i < size; i++ )
  {
    int profit = prices[i] - prices[i - 1];
    if( 0 < profit ) maxProfit += profit;
  }
  return maxProfit;
#endif

#if 0
  int buyPrices = prices[0];
  int prePrices = prices[0];

  // 循环交易日，找到每个区间的最大值
  for( int i = 1; i < size; i++ )
  {
    int currentPrices = prices[i];
    if( currentPrices < prePrices )
    {
      int profit = prePrices - buyPrices;
      if( 0 < profit )
      {
        maxProfit += profit;
      }
      buyPrices = currentPrices;
    }
    else if( currentPrices < buyPrices )
    {
      buyPrices = currentPrices;
    }
    prePrices = currentPrices;
  }

  // 最后一天是否需要交易
  int profit = prePrices - buyPrices;
  if( 0 < profit )
  {
    maxProfit += profit;
  }
  return maxProfit;
#endif
}

bool No131_isPalindrome( const string& s, int start, int end )
{
  for( int i = start, j = end; i < j; i++, j-- )
  {
    if( s[i] != s[j] ) return false;
  }
  return true;
}

void No131_backtracking( const string& s, int startIndex, vector<string>& path, vector<vector<string>>& ans )
{
  if( startIndex >= s.size() )
  {
    ans.push_back( path );
    return;
  }
  for( int i = startIndex; i < s.size(); i++ )
  {
    if( No131_isPalindrome( s, startIndex, i ) )
    {
      string temp = s.substr( startIndex, i - startIndex + 1 );
      path.push_back( temp );
    }
    else continue;
    No131_backtracking( s, i + 1, path, ans );
    path.pop_back();
  }
}

vector<vector<string>> No131_partition( string s )
{
  vector<string> path;
  vector<vector<string>> ans;
  No131_backtracking( s, 0, path, ans );
  return ans;
}

bool No139_wordBreak( string s, vector<string>& wordDict )
{
  // dp[i] : 字符串长度为i的话，dp[i]为true，表示可以拆分为一个或多个在字典中出现的单词。
  unordered_set<string> wordSet( wordDict.begin(), wordDict.end() );
  vector<bool> dp( s.size() + 1, false );
  dp[0] = true;
  for( int i = 1; i <= s.size(); i++ ) // 背包
  {
    for( int j = 0; j < i; j++ ) // 物品
    {
      string word = s.substr( j, i - j );
      // j位置在，且j到i之间的单词也在，那i背包为符合
      if( wordSet.count( word ) && dp[j] ) dp[i] = true;
    }
  }
  return dp[s.size()];
}

ListNode* No142_detectCycle( ListNode* head )
{
  ListNode* fast = head;
  ListNode* slow = head;
  while( fast != NULL && fast->next != NULL )
  {
    slow = slow->next;
    fast = fast->next->next;
    if( slow == fast )
    {
      ListNode* pos = head;
      while( pos != slow )
      {
        pos = pos->next;
        slow = slow->next;
      }
      return pos;
    }
  }
  return nullptr;
}

int No150_evalRPN( vector<string>& tokens )
{
  stack<long long> stk;
  map<string, int> ope{{"+",1},{"-",2},{"*",3}, {"/",4}};
  for( const string& token : tokens )
  {
    auto iter = ope.find( token );
    if( iter != ope.end() )
    {
      long long num1 = stk.top(); stk.pop();
      long long num2 = stk.top(); stk.pop();
      long long ans = 0;
      switch( iter->second )
      {
        case 1: ans = num2 + num1; break;
        case 2: ans = num2 - num1; break;
        case 3: ans = num2 * num1; break;
        case 4: ans = num2 / num1; break;
      }
      stk.push( ans );
    }
    else
    {
      stk.push( stoll( token ) );
    }
  }
  int ans = static_cast<int>( stk.top() );
  stk.pop();
  return ans;
}

static void No151_removeExtraSpaces( string& s )
{
  int slow = 0;
  for( int fast = 0; fast < s.size(); fast++ )
  {
    // 去头空格
    if( fast == 0 ) while( s[fast] == ' ' && fast < s.size() ) fast++;

    if( fast < s.size() && s[fast] != ' ' )
    {
      s[slow++] = s[fast];
    }
    else
    {
      // 去中间和尾空格
      while( fast < s.size() && s[fast] == ' ' ) fast++;
      if( fast != s.size() ) s[slow++] = s[--fast];
    }
  }
  s.resize( slow );
}

static void No151_reverse( string& s, int left, int right )
{
  char c = ' ';
  for( ; left < right; left++, right-- )
  {
    c = s[left];
    s[left] = s[right];
    s[right] = c;
  }
}

string No151_reverseWords( string s )
{
  // 请尝试使用 O(1) 额外空间复杂度的 原地 解法。

  // 删除多余空格
  No151_removeExtraSpaces( s );

  // 反转字符串
  No151_reverse( s, 0, s.size() - 1 );

  // 翻转单词
  int left = 0;
  for( int pos = 0; pos <= s.size(); ++pos )
  {
    if( pos == s.size() || s[pos] == ' ' )
    {
      No151_reverse( s, left, pos - 1 );
      left = pos + 1;
    }
  }

  return s;
}

int No198_rob( vector<int>& nums )
{
  // dp[i]：考虑下标i（包括i）以内的房屋，最多可以偷窃的金额为dp[i]。
  if( nums.size() == 0 ) return 0;
  if( nums.size() == 1 ) return nums[0];
  vector<int> dp( nums.size() );
  dp[0] = nums[0];
  dp[1] = max( nums[0], nums[1] );
  for( int i = 2; i < nums.size(); i++ )
    // 当前状态取决于偷当前，即dp[i-2]+当前；不偷当前为上一个状态
    dp[i] = max( dp[i - 2] + nums[i], dp[i - 1] );
  return dp[nums.size() - 1];
}

int No209_minSubArrayLen( int target, vector<int>& nums )
{
  int ans = INT_MAX;
  int left = 0;
  int sum = 0;
  for( int right = 0; right < nums.size(); right++ )
  {
    sum += nums[right];
    while( sum >= target )
    {
      int temp = right - left + 1;
      ans = min( ans, temp );
      sum -= nums[left];
      left++;
    }
  }
  if( ans == INT_MAX ) ans = 0;

  return ans;
}

static int No213_robRange( vector<int>& nums, int start, int end )
{
  // 和198题打家劫舍一样的逻辑
  if( start == end ) return nums[start];
  vector<int> dp( nums.size() );
  dp[start] = nums[start];
  dp[start + 1] = max( nums[start], nums[start + 1] );
  for( int i = start + 2; i <= end; i++ )
    dp[i] = max( dp[i - 2] + nums[i], dp[i - 1] );
  return dp[end];
}

int No213_rob( vector<int>& nums )
{
  // 比198题打家劫舍1多了首尾相连的选项
  // 对于一个数组，成环的话主要有如下三种情况：
  // 情况一：考虑不包含首尾元素 (被情况二和三包括了)
  // 情况二：考虑包含首元素，不包含尾元素
  // 情况三：考虑包含尾元素，不包含首元素
  if( nums.size() == 0 ) return 0;
  if( nums.size() == 1 ) return nums[0];
  int ans1 = No213_robRange( nums, 0, nums.size() - 2 ); // 情况二
  int ans2 = No213_robRange( nums, 1, nums.size() - 1 ); // 情况三
  return max( ans1, ans2 );
}

vector<vector<int>> No216_ans;
vector<int> No216_temp;
void No216_backtracking( const int size, const int target, int startNum, int sum )
{
  if( No216_temp.size() == size )
  {
    if( sum == target )
    {
      No216_ans.push_back( No216_temp );
    }
    return;
  }

  for( int num = startNum; num <= 9; num++ )
  {
    if( sum + num > target ) return;
    sum += num;
    No216_temp.push_back( num );
    No216_backtracking( size, target, num + 1, sum );
    No216_temp.pop_back();
    sum -= num;
  }
}

vector<vector<int>> No216_combinationSum3( int k, int n )
{
  No216_backtracking( k, n, 1, 0 );
  return No216_ans;
}

int No222_countNodes( TreeNode* root )
{
  if( !root ) return 0;
  // 以下为判断是否为满二叉树
  TreeNode* left = root->left;
  TreeNode* right = root->right;
  int leftDepth = 0;
  int rightDepth = 0;
  while( left )
  {
    left = left->left;
    leftDepth++;
  }
  while( right )
  {
    right = right->right;
    rightDepth++;
  }
  int count = 0;
  if( leftDepth == rightDepth )
  {
    count = ( 2 << leftDepth ) - 1; // 满二叉树节点数：2的n次方-1
  }
  else
  {
    int leftCount = No222_countNodes( root->left );
    int rightCount = No222_countNodes( root->right );
    count = leftCount + rightCount + 1;
  }

  return count;
}

TreeNode* No235_lowestCommonAncestor( TreeNode* root, TreeNode* p, TreeNode* q )
{
  // 利用二叉搜索树的特性，均大于往左移，反之往右移，在中间返回即可
  // 第一个符合的节点一定是最近公共祖先,画图来验证一下就明白了。
  while( root )
  {
    if( root->val > p->val && root->val > q->val ) root = root->left;
    else if( root->val < p->val && root->val < q->val ) root = root->right;
    else return root;
  }
  return nullptr;
}

TreeNode* No236_lowestCommonAncestor( TreeNode* root, TreeNode* p, TreeNode* q )
{
  if( !root || root == p || root == q ) return root;
  TreeNode* left = No236_lowestCommonAncestor( root->left, p, q );
  TreeNode* right = No236_lowestCommonAncestor( root->right, p, q );
  if( left && right ) return root;        // 左右子树都有，即找到了，返回根
  else if( left && !right ) return left;  // 只有左子树找到，返回左子树
  else if( !left && right ) return right; // 只有右子树找到了，返回右子树
  else return nullptr;                    // 都没找到返回空
}

int No279_numSquares( int n )
{
  // 我来把题目翻译一下：完全平方数就是物品（可以无限件使用），凑个正整数n就是背包，问凑满这个背包最少有多少物品？
  // dp[j]：和为j的完全平方数的最少数量为dp[j]
  vector<int> dp( n + 1, INT_MAX );
  dp[0] = 0;
  // 遍历循序不影响，先背包还是先物品都行，先遍历背包比较方便
  for( int i = 0; i <= n; i++ )
    for( int j = 1; j * j <= i; j++ )
      dp[i] = min( dp[i - j * j] + 1, dp[i] );
  return dp[n];
}

int No300_lengthOfLIS( vector<int>& nums )
{
  // dp[i]表示i之前包括i的以nums[i]结尾的最长递增子序列的长度
  if( nums.size() <= 1 ) return nums.size();
  vector<int> dp( nums.size(), 1 );
  int result = 0;
  for( int i = 1; i < nums.size(); i++ )
  {
    for( int j = 0; j < i; j++ )
    {
      // 当前位置递增序列的长度
      if( nums[i] > nums[j] ) dp[i] = max( dp[i], dp[j] + 1 );
    }
    // 取最长递增序列的长度
    if( dp[i] > result ) result = dp[i];
  }
  return result;
}

int No309_maxProfit( vector<int>& prices )
{
  // 动态规划
  // 四个状态
  // 状态0：持有股票状态
  // 状态1：保持卖出股票的状态
  // 状态2：今天卖出股票
  // 状态3：今天为冷冻期状态，但冷冻期状态不可持续，只有一天！
  int size = prices.size();
  if( size == 0 ) return 0;
  vector<vector<int>> dp( size, vector<int>( 4, 0 ) );
  // 初始化，持有股票为-prices[0]，其他为0
  dp[0][0] = -prices[0]; // 持有股票
  for( int i = 1; i < size; i++ )
  {
    dp[i][0] = max( dp[i - 1][0], max( dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i] ) );
    dp[i][1] = max( dp[i - 1][1], dp[i - 1][3] );
    dp[i][2] = dp[i - 1][0] + prices[i];
    dp[i][3] = dp[i - 1][2];
  }

  // 返回三种状态的最大值
  return max( dp[size - 1][3], max( dp[size - 1][1], dp[size - 1][2] ) );
}

int No322_coinChange( vector<int>& coins, int amount )
{
  // dp[j]：凑足总额为j所需硬币的最少个数为dp[j]
  vector<int> dp( amount + 1, INT_MAX );
  dp[0] = 0;
  // 遍历循序不影响，先背包还是先物品都行，先遍历物品比较方便
  for( int i = 0; i < coins.size(); i++ )
    for( int j = coins[i]; j <= amount; j++ )
      if( dp[j - coins[i]] != INT_MAX )
        // dp[j - coins[i]] 凑够之前的硬币个数，+1表示加上该硬币后的硬币数
        dp[j] = min( dp[j - coins[i]] + 1, dp[j] );
  // 不能凑足金额时返回-1，能是返回最少硬币数
  return dp[amount] == INT_MAX ? -1 : dp[amount];
}

static pair<int, int> No337_robTree( TreeNode* node )
{
  if( !node ) return {0,0};
  // pair<不偷父节点，偷父节点>
  pair<int, int> left = No337_robTree( node->left );
  pair<int, int> right = No337_robTree( node->right );

  // 偷父节点
  int val1 = node->val + left.first + right.first;
  // 不偷父节点,子节点可偷可不偷
  int val2 = max( left.first, left.second ) + max( right.first, right.second );
  return {val2, val1};
}

int No337_rob( TreeNode* root )
{
  // 方法一，动态规划：
  pair<int, int> ans = No337_robTree( root );
  return max( ans.first, ans.second );

  // 方法二，树递归，超时了：
#if 0
  if( !root ) return 0;
  if( !root->left && !root->right ) return root->val;
  // 偷父节点，跳过子节点，接下来偷左右子节点各自的左右子节点
  int val1 = root->val;
  if( root->left ) val1 += No337_rob( root->left->left ) + No337_rob( root->left->right );
  if( root->right ) val1 += No337_rob( root->right->left ) + No337_rob( root->right->right );
  // 不偷父节点，偷左右子节点
  int val2 = No337_rob( root->left ) + No337_rob( root->right );
  // 返回最大价值
  return max(val1, val2);
#endif
}

int No343_integerBreak( int n )
{
  vector<int> dp( n + 1, 0 );
  dp[0] = 0;
  dp[1] = 0;
  dp[2] = 1;
  for( int i = 3; i <= n; i++ )
  {
    for( int j = 1; j < i - 1; j++ )
    {
      dp[i] = max( j * ( i - j ), max( j * dp[i - j], dp[i] ) );
    }
  }
  return dp[n];
}

int No376_wiggleMaxLength( vector<int>& nums )
{
  // 方法一：贪心
  if( nums.size() <= 1 ) return nums.size();
  int curDiff = 0, preDiff = 0, result = 1;
  for( int i = 0; i < nums.size() - 1; i++ )
  {
    curDiff = nums[i + 1] - nums[i];
    if( ( preDiff <= 0 && curDiff > 0 ) || ( preDiff >= 0 && curDiff < 0 ) )
    {
      // 当峰值出现时，记录
      result++;
      preDiff = curDiff; // 注意这里，只在摆动变化的时候更新preDiff
    }
  }
  return result;

  // 方法二：动态规划
  // 自己看答案去吧
}

int No377_combinationSum4( vector<int>& nums, int target )
{
  // dp[i]: 凑成目标正整数为i的排列个数为dp[i]
  vector<int> dp( target + 1, 0 );
  dp[0] = 1;
  // 求排列数，先遍历背包，再遍历物品
  for( int i = 0; i <= target; i++ )
  {
    for( int j = 0; j < nums.size(); j++ )
    {
      // C++测试用例有两个数相加超过int的数据，所以需要在if里加上dp[i] < INT_MAX - dp[i - num]。
      if( i - nums[j] >= 0 && dp[i] < INT_MAX - dp[i - nums[j]] )
        dp[i] += dp[i - nums[j]];
    }
  }
  return dp[target];
}

bool No416_canPartition( vector<int>& nums )
{
  int sum = 0;
  for( const int num : nums ) sum += num;
  if( sum % 2 != 0 ) return false;

  int target = sum / 2;
  vector<int> dp( target + 1, 0 );
  int size = nums.size();
  for( int i = 0; i < size; i++ )
  {
    for( int j = target; j >= nums[i]; j-- ) // j即是背包数也是重量
    {
      dp[j] = max( dp[j], dp[j - nums[i]] + nums[i] );
    }
  }

  return dp[target] == target;
}

TreeNode* No450_deleteNode( TreeNode* root, int key )
{
  // 以下没有做delete操作，按理说是要做的，懒得写了
  if( !root ) return nullptr;
  if( root->val == key )
  {
    // 均为空返回空，左为空返回右，右为空返回左
    if( !root->left && !root->right ) return nullptr;
    else if( !root->left ) return root->right;
    else if( !root->right ) return root->left;
    else
    {
      // 左右均非空，找到右子树的最左节点,把Root左子树嫁接到该左子树上
      TreeNode* cur = root->right;
      while( cur->left ) cur = cur->left;
      cur->left = root->left;
      // 返回旧的root的右子树作为新的root
      root = root->right;
      return root;
    }
  }
  // 递归树，把左右子树更新
  if( root->val > key ) root->left = No450_deleteNode( root->left, key );
  if( root->val < key ) root->right = No450_deleteNode( root->right, key );
  return root;
}

int No454_fourSumCount( vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4 )
{
  int ans = 0;
  unordered_map<int, int> twoSum;
  for( const int num1 : nums1 )
    for( const int num2 : nums2 )
      twoSum[num1 + num2]++;

  for( const int num3 : nums3 )
  {
    for( const int num4 : nums4 )
    {
      int target = -( num3 + num4 );
      auto iter = twoSum.find( target );
      if( iter != twoSum.end() ) ans += iter->second;
    }
  }
  return ans;
}

int No474_findMaxForm( vector<string>& strs, int m, int n )
{
  // 动态规划
  // 这就是一个典型的01背包！ 只不过物品的重量有了两个维度而已。
  // dp[i][j]：最多有i个0和j个1的strs的最大子集的大小为dp[i][j]。
  vector<vector<int>> dp( m + 1, vector<int>( n + 1, 0 ) );
  for( string& str : strs ) // 遍历物品
  {
    int oneNum = 0, zeroNum = 0;
    for( char c : str )
    {
      if( c == '0' ) zeroNum++;
      else oneNum++;
    }
    for( int i = m; i >= zeroNum; i-- ) // 遍历背包容量且从后向前遍历！
    {
      for( int j = n; j >= oneNum; j-- )
      {
        dp[i][j] = max( dp[i][j], dp[i - zeroNum][j - oneNum] + 1 );
      }
    }
  }
  return dp[m][n];
}

void No491_backtracking( vector<int>& nums, int startIndex, vector<int>& path, vector<vector<int>>& ans )
{
  if( path.size() > 1 ) ans.push_back( path );
  unordered_set<int> useSet; // 用set去重,层间不重复，树间可重复
  for( int i = startIndex; i < nums.size(); i++ )
  {
    if( !path.empty() && nums[i] < path.back() ) continue; // 非递增
    if( useSet.find( nums[i] ) != useSet.end() ) continue; // 前面一次已用过
    useSet.insert( nums[i] );
    path.push_back( nums[i] );
    No491_backtracking( nums, i + 1, path, ans );
    path.pop_back();
  }
}

vector<vector<int>> No491_findSubsequences( vector<int>& nums )
{
  vector<int> path;
  vector<vector<int>> ans;
  No491_backtracking( nums, 0, path, ans );
  return ans;
}

int No494_findTargetSumWays( vector<int>& nums, int target )
{
  int sum = 0;
  for( int i = 0; i < nums.size(); i++ ) sum += nums[i];
  if( abs( target ) > sum ) return 0; // 目标大于总和
  if( ( target + sum ) % 2 == 1 ) return 0; // 为奇数不可等分，如总和5目标2
  int bagSize = ( target + sum ) / 2;
  vector<int> dp( bagSize + 1, 0 );
  dp[0] = 1;
  // 求组合数，先遍历物品，再遍历背包，为防止物品重复，背包从大到小遍历
  for( int i = 0; i < nums.size(); i++ )
    for( int j = bagSize; j >= nums[i]; j-- )
      dp[j] += dp[j - nums[i]];
  return dp[bagSize];
}

void No513_traversal( TreeNode* node, int depth, int& maxDepth, int& value )
{
  if( !node->left && !node->right )
  {
    if( depth > maxDepth )
    {
      value = node->val;
      maxDepth = depth;
    }
    return;
  }

  // 先遍历左，确保是最左边第一个取值
  // depth + 1 是有回溯过程
  if( node->left ) No513_traversal( node->left, depth + 1, maxDepth, value );
  if( node->right ) No513_traversal( node->right, depth + 1, maxDepth, value );
}


int No513_findBottomLeftValue( TreeNode* root )
{
  if( !root ) return 0;
  int depth = 0;
  int maxDepth = 0;
  int value = 0;
  No513_traversal( root, depth + 1, maxDepth, value );
  return value;
}

int No516_longestPalindromeSubseq( string s )
{
  // 动态规划
  // dp[i][j]：字符串s在[i, j]范围内最长的回文子序列的长度为dp[i][j]
  vector<vector<int>> dp( s.size(), vector<int>( s.size(), 0 ) );
  // 当i与j相同，那么dp[i][j]一定是等于1的，即：一个字符的回文子序列长度就是1
  for( int i = 0; i < s.size(); i++ ) dp[i][i] = 1;
  // 从下到上遍历，这样才能保证下一行的数据是经过计算的
  for( int i = s.size() - 1; i >= 0; i-- )
  {
    for( int j = i + 1; j < s.size(); j++ )
    {
      // 相等时，长度等于外层长度加自身2个字符，即+2
      if( s[i] == s[j] ) dp[i][j] = dp[i + 1][j - 1] + 2;
      // 不等时，取两头最大值
      else dp[i][j] = max( dp[i + 1][j], dp[i][j - 1] );
    }
  }
  return dp[0][s.size() - 1];
}

int No518_change( int amount, vector<int>& coins )
{
  // 凑成总金额j的货币组合数为dp[j]
  vector<int> dp( amount + 1 );
  dp[0] = 1;
  // 求组合数，先遍历物品，再遍历背包，物品可重复，背包从小到大小遍历
  for( int i = 0; i < coins.size(); i++ )
    for( int j = coins[i]; j <= amount; j++ )
      dp[j] += dp[j - coins[i]];
  return dp[amount];
}

void No538_traversal( TreeNode* node, int& preSum )
{
  if( !node ) return;
  No538_traversal( node->right, preSum );
  node->val += preSum;
  preSum = node->val;
  No538_traversal( node->left, preSum );
}

TreeNode* No538_convertBST( TreeNode* root )
{
  int preSum = 0;
  No538_traversal( root, preSum );
  return root;
}

int No583_minDistance( string word1, string word2 )
{
  // 动态规划
  // 字符串长度减去最长公共长度即可
  // 和No.1143最长公共子序列基本相同
  vector<vector<int>> dp( word1.size() + 1, vector<int>( word2.size() + 1, 0 ) );
  for( int i = 1; i <= word1.size(); i++ )
  {
    for( int j = 1; j <= word2.size(); j++ )
    {
      if( word1[i - 1] == word2[j - 1] ) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = max( dp[i - 1][j], dp[i][j - 1] );
    }
  }
  // 除了最长公共子序列之外的字符都是必须删除的，最后用两个字符串的总长度减去两个最长公共子序列的长度就是删除的最少步数。
  int step = word1.size() + word2.size() - dp[word1.size()][word2.size()] * 2;
  return step;
}

int No647_countSubstrings( string s )
{
  // 动态规划
  // 布尔类型的dp[i][j]：表示区间范围[i,j] （注意是左闭右闭）的子串是否是回文子串，如果是dp[i][j]为true，否则为false
  // 当s[i]与s[j]不相等，那没啥好说的了，dp[i][j]一定是false。
  // 当s[i]与s[j]相等时，这就复杂一些了，有如下三种情况
  // 情况一：下标i 与 j相同，同一个字符例如a，当然是回文子串
  // 情况二：下标i 与 j相差为1，例如aa，也是回文子串
  // 情况三：下标：i 与 j相差大于1的时候，例如cabac，此时s[i]与s[j]已经相同了，我们看i到j区间是不是回文子串就看aba是不是回文就可以了，那么aba的区间就是 i + 1 与 j - 1区间，这个区间是不是回文就看dp[i + 1][j - 1]是否为true。

  // 初始化为false，因为一开始就不匹配，要推导是否匹配
  vector<vector<bool>> dp( s.size(), vector<bool>( s.size(), false ) );
  int result = 0;
  // 所以一定要从下到上，从左到右遍历，这样保证dp[i + 1][j - 1]都是经过计算的。
  for( int i = s.size() - 1; i >= 0; i-- )
  {
    for( int j = i; j < s.size(); j++ )
    {
      if( s[i] == s[j] )
      {
        // 情况一和二(单双字符都可是回文串) || 情况三(看内层是不是回文串)
        if( j - i <= 1 || dp[i + 1][j - 1] )
        {
          result++;
          dp[i][j] = true;
        }
      }
    }
  }
  return result;
}

TreeNode* No654_traversal( vector<int>& nums, int left, int right )
{
  if( left == right ) return nullptr;

  int maxValueIndex = left;
  for( int index = left + 1; index < right; index++ )
  {
    if( nums[index] > nums[maxValueIndex] ) maxValueIndex = index;
  }

  TreeNode* node = new TreeNode( nums[maxValueIndex] );

  // 左闭右开
  node->left = No654_traversal( nums, left, maxValueIndex );
  node->right = No654_traversal( nums, maxValueIndex + 1, right );
  return node;
}


TreeNode* No654_constructMaximumBinaryTree( vector<int>& nums )
{
  return No654_traversal( nums, 0, nums.size() );
}

TreeNode* No669_trimBST( TreeNode* root, int low, int high )
{
  if( !root ) return nullptr;
  // 如果小于low，则修剪right；如果大于high，则修剪left
  if( root->val < low ) return No669_trimBST( root->right, low, high );
  if( root->val > high ) return No669_trimBST( root->left, low, high );
  root->left = No669_trimBST( root->left, low, high );
  root->right = No669_trimBST( root->right, low, high );
  return root;
}

TreeNode* No701_insertIntoBST( TreeNode* root, int val )
{
  if( !root ) return new TreeNode( val );
  if( root->val > val ) root->left = No701_insertIntoBST( root->left, val );
  if( root->val < val ) root->right = No701_insertIntoBST( root->right, val );
  return root;
}

int No714_maxProfit( vector<int>& prices, int fee )
{
  // 动态规划法
  // dp[i][0] 表示第i天持有股票所得最多现金
  // dp[i][1] 表示第i天不持有股票所得最多现金
  int size = prices.size();
  if( size == 0 ) return 0;
  vector<vector<int>> dp( size, vector<int>( 2, 0 ) );
  dp[0][0] = 0 - prices[0]; // 当天买进后手里现金
  dp[0][1] = 0;             // 当天买进后又卖出后手里现金
  for( int i = 1; i < size; i++ )
  {
    // 对比前一天买入和今天买入(剩下钱为值钱赚的减去今天买的)，哪个花钱少
    dp[i][0] = max( dp[i - 1][0], dp[i - 1][1] - prices[i] );
    // 对比之前卖出和今天卖出，哪个赚钱多
    dp[i][1] = max( dp[i - 1][1], dp[i - 1][0] + prices[i] - fee ); // 和No.122唯一区别
  }
  return dp[size - 1][1];
}

int No718_findLength( vector<int>& nums1, vector<int>& nums2 )
{
  // dp[i][j] ：以下标i - 1为结尾的A，和以下标j - 1为结尾的B，最长重复子数组长度为dp[i][j]
  vector<vector<int>> dp( nums1.size() + 1, vector<int>( nums2.size() + 1, 0 ) );
  int result = 0;
  for( int i = 1; i <= nums1.size(); i++ )
  {
    for( int j = 1; j <= nums2.size(); j++ )
    {
      if( nums1[i - 1] == nums2[j - 1] ) dp[i][j] = dp[i - 1][j - 1] + 1;
      if( dp[i][j] > result ) result = dp[i][j];
    }
  }
  return result;
}

int No1035_maxUncrossedLines( vector<int>& nums1, vector<int>& nums2 )
{
  // 本题说是求绘制的最大连线数，其实就是求两个字符串的最长公共子序列的长度！
  // 解法即同No.1143
  vector<vector<int>> dp( nums1.size() + 1, vector<int>( nums2.size() + 1, 0 ) );
  for( int i = 1; i <= nums1.size(); i++ )
  {
    for( int j = 1; j <= nums2.size(); j++ )
    {
      if( nums1[i - 1] == nums2[j - 1] ) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = max( dp[i - 1][j], dp[i][j - 1] );
    }
  }
  return dp[nums1.size()][nums2.size()];
}

int No1049_lastStoneWeightII( vector<int>& stones )
{
  int sum = 0;
  for( const int num : stones ) sum += num;
  int target = sum / 2;
  vector<int> dp( target + 1, 0 );
  int size = stones.size();
  for( int i = 0; i < size; i++ )
  {
    for( int j = target; j >= stones[i]; j-- )
    {
      dp[j] = max( dp[j], dp[j - stones[i]] + stones[i] );
    }
  }

  // 在计算target的时候，target = sum / 2 因为是向下取整，所以sum - dp[target] 一定是大于等于dp[target]的。
  return sum - dp[target] - dp[target];
}

int No1143_longestCommonSubsequence( string text1, string text2 )
{
  // dp[i][j]：长度为[0, i - 1]的字符串text1与长度为[0, j - 1]的字符串text2的最长公共子序列为dp[i][j]
  vector<vector<int>> dp( text1.size() + 1, vector<int>( text2.size() + 1, 0 ) );
  for( int i = 1; i <= text1.size(); i++ )
  {
    for( int j = 1; j <= text2.size(); j++ )
    {
      if( text1[i - 1] == text2[j - 1] ) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = max( dp[i - 1][j], dp[i][j - 1] );
    }
  }
  return dp[text1.size()][text2.size()];
}

