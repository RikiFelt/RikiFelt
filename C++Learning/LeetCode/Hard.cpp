#include "Hard.h"

int No32_longestValidParentheses( string s )
{
  int maxCount = 0;
  stack<int> stk;
  stk.push( -1 );
  for( int pos = 0; pos < s.length(); pos++ )
  {
    if( s[pos] == '(' )
    {
      stk.push( pos );
    }
    else
    {
      stk.pop();
      if( stk.empty() )
      {
        stk.push( pos );
      }
      else
      {
        maxCount = max( maxCount, pos - stk.top() );
      }
    }
  }
  return maxCount;
}

bool No37_isValid( vector<vector<char>>& board, int row, int col, char val )
{
  // 判断行重复
  for( int i = 0; i < 9; i++ )
    if( board[row][i] == val ) return false;
  // 判断列重复
  for( int j = 0; j < 9; j++ )
    if( board[j][col] == val ) return false;
  // 判断9方格重复
  int startRow = ( row / 3 ) * 3;
  int startCol = ( col / 3 ) * 3;
  for( int i = startRow; i < startRow + 3; i++ )
    for( int j = startCol; j < startCol + 3; j++ )
      if( board[i][j] == val ) return false;
  return true;
}

bool No37_backtracking( vector<vector<char>>& board )
{
  for( int row = 0; row < board.size(); row++ )
  {
    for( int col = 0; col < board.size(); col++ )
    {
      if( board[row][col] != '.' ) continue; // 不为空,即已填写数字
      for( char val = '1'; val <= '9'; val++ )
      {
        if( !No37_isValid( board, row, col, val ) ) continue; // 该数字不合法,找下一个
        board[row][col] = val; // 合法，填写数字
        if( No37_backtracking( board ) ) return true; // 递归，找到一组后就返回
        board[row][col] = '.'; // 回溯
      }
      return false; // 找完最后一层9个数字后，如果都不行，返回false
    }
  }
  return true;
}

void No37_solveSudoku( vector<vector<char>>& board )
{
  No37_backtracking( board );
}

bool No51_isValid( vector<string>& chessboard, int row, int col, int floor )
{
  // 检查列是否有皇后
  for( int i = 0; i < row; i++ )
    if( chessboard[i][col] == 'Q' ) return false;
  // 向上检查45度角是否有皇后，向下不用，因为下面还没开始填
  for( int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j-- )
    if( chessboard[i][j] == 'Q' ) return false;
  // 检查135度角是否有皇后
  for( int i = row - 1, j = col + 1; i >= 0 && j < floor; i--, j++ )
    if( chessboard[i][j] == 'Q' ) return false;
  return true;
}

void No51_backtracking( vector<string>& chessboard, vector<vector<string>>& ans, int row, int floor )
{
  if( row == floor )
  {
    ans.push_back( chessboard );
    return;
  }
  for( int col = 0; col < floor; col++ )
  {
    if( No51_isValid( chessboard, row, col, floor ) )
    {
      chessboard[row][col] = 'Q'; // 放置皇后
      No51_backtracking( chessboard, ans, row + 1, floor );
      chessboard[row][col] = '.'; // 回溯，撤销皇后
    }
  }
}

vector<vector<string>> No51_solveNQueens( int n )
{
  int floor = n; // 换个名字而已
  vector<vector<string>> ans;
  // 创建一个nXn，全为点.的棋盘
  std::vector<std::string> chessboard( floor, std::string( floor, '.' ) );
  No51_backtracking( chessboard, ans, 0, floor );
  return ans;
}

int No72_minDistance( string word1, string word2 )
{
  // 动态规划
  // dp[i][j] 表示以下标i-1为结尾的字符串word1，和以下标j-1为结尾的字符串word2，最近编辑距离为dp[i][j]。
  vector<vector<int>> dp( word1.size() + 1, vector<int>( word2.size() + 1, 0 ) );
  // 初始化，假设全部做删除操作，则边缘操作数为递增
  for( int i = 0; i <= word1.size(); i++ ) dp[i][0] = i;
  for( int j = 0; j <= word2.size(); j++ ) dp[0][j] = j;
  // 遍历
  for( int i = 1; i <= word1.size(); i++ )
  {
    for( int j = 1; j <= word2.size(); j++ )
    {
      // 如果相等，操作数相同。
      // 如果不等，操作数为左上斜角三个方向递推操作数最小值+1
      if( word1[i - 1] == word2[j - 1] ) dp[i][j] = dp[i - 1][j - 1];
      else dp[i][j] = min( {dp[i - 1][j - 1],dp[i - 1][j],dp[i][j - 1]} ) + 1;
    }
  }
  return dp[word1.size()][word2.size()];
}

int No115_numDistinct( string s, string t )
{
  // 这道题目如果不是子序列，而是要求连续序列的，那就可以考虑用KMP。
  // dp[i][j]：以i-1为结尾的s子序列中出现以j-1为结尾的t的个数为dp[i][j]。
  vector<vector<uint64_t>> dp( s.size() + 1, vector<uint64_t>( t.size() + 1 ) );
  for( int i = 0; i < s.size(); i++ ) dp[i][0] = 1;
  for( int j = 1; j < t.size(); j++ ) dp[0][j] = 0;
  // 推导过程画图会更清晰
  for( int i = 1; i <= s.size(); i++ )
  {
    for( int j = 1; j <= t.size(); j++ )
    {
      // 如果相等，值由头顶和左上的值推导而来
      if( s[i - 1] == t[j - 1] ) dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
      // 如果不相等，值仅有头顶推导而来
      else dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[s.size()][t.size()];
}

int No123_maxProfit( vector<int>& prices )
{
  // 动态规划
  // 一天一共就有五个状态
  // 0.没有操作 （其实我们也可以不设置这个状态）
  // 1.第一次持有股票
  // 2.第一次不持有股票
  // 3.第二次持有股票
  // 4.第二次不持有股票
  if( prices.size() == 0 ) return 0;
  vector<vector<int>> dp( prices.size(), vector<int>( 5, 0 ) );
  // 初始化，0,2,4状态初始为0
  dp[0][1] = -prices[0];
  dp[0][3] = -prices[0];
  for( int i = 1; i < prices.size(); i++ )
  {
    dp[i][0] = dp[i - 1][0];
    dp[i][1] = max( dp[i - 1][1], dp[i - 1][0] - prices[i] );
    dp[i][2] = max( dp[i - 1][2], dp[i - 1][1] + prices[i] );
    dp[i][3] = max( dp[i - 1][3], dp[i - 1][2] - prices[i] );
    dp[i][4] = max( dp[i - 1][4], dp[i - 1][3] + prices[i] );
  }
  return dp[prices.size() - 1][4];
}

int No188_maxProfit( int k, vector<int>& prices )
{
  // 动态规划
  // 和No.123相比，要做抽象
  // 除了0以外，偶数就是卖出，奇数就是买入
  if( prices.size() == 0 ) return 0;
  vector<vector<int>> dp( prices.size(), vector<int>( 2 * k + 1, 0 ) );
  // 初始化，第0天的买入均为-prices[0],卖出均为0
  for( int j = 1; j < 2 * k; j += 2 ) dp[0][j] = -prices[0];
  // 状态迁移
  for( int i = 1; i < prices.size(); i++ )
  {
    for( int j = 0; j < 2 * k; j += 2 ) // 2步一走
    {
      dp[i][j + 1] = max( dp[i - 1][j + 1], dp[i - 1][j] - prices[i] ); // 买入
      dp[i][j + 2] = max( dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i] ); // 卖出
    }
  }
  return dp[prices.size() - 1][2 * k];
}

vector<int> No239_maxSlidingWindow( vector<int>& nums, int k )
{
  vector<int> ans;
  // 优先队列,具有最高值的元素被认为是最高优先级的元素。
  priority_queue<pair<int, int>> que;

  // 先取前3个数
  for( int pos = 0; pos < k; pos++ ) que.emplace( nums[pos], pos );
  ans.emplace_back( que.top().first );
  // 遍历之后的数
  for( int pos = k; pos < nums.size(); pos++ )
  {
    que.emplace( nums[pos], pos );
    // 根据下标去掉超出范围的值
    while( que.top().second <= pos - k ) que.pop();
    ans.emplace_back( que.top().first );
  }

  return ans;
}

static bool No347_cmp( pair<int, int>& m, pair<int, int>& n )
{
  return m.second > n.second;
}

vector<int> No347_topKFrequent( vector<int>& nums, int k )
{
  // 统计数字出现次数
  unordered_map<int, int> map;
  for( const int num : nums ) map[num]++;

  // 优先队列, pair<值，出现次数>, vector<> 比较容器， bool 比较类型
  priority_queue< pair<int, int>, vector<pair<int, int>>, decltype( &No347_cmp )> que( No347_cmp );
  for( auto iter = map.begin(); iter != map.end(); iter++ )
  {
    que.push( *iter );
    if( que.size() > k ) que.pop();
  }

  // 取前k个数
  vector<int> ans( k );
  for( int pos = k - 1; pos >= 0; pos-- )
  {
    ans[pos] = que.top().first;
    que.pop();
  }

  return ans;
}
