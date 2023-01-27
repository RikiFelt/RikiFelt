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
  // �ж����ظ�
  for( int i = 0; i < 9; i++ )
    if( board[row][i] == val ) return false;
  // �ж����ظ�
  for( int j = 0; j < 9; j++ )
    if( board[j][col] == val ) return false;
  // �ж�9�����ظ�
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
      if( board[row][col] != '.' ) continue; // ��Ϊ��,������д����
      for( char val = '1'; val <= '9'; val++ )
      {
        if( !No37_isValid( board, row, col, val ) ) continue; // �����ֲ��Ϸ�,����һ��
        board[row][col] = val; // �Ϸ�����д����
        if( No37_backtracking( board ) ) return true; // �ݹ飬�ҵ�һ���ͷ���
        board[row][col] = '.'; // ����
      }
      return false; // �������һ��9�����ֺ���������У�����false
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
  // ������Ƿ��лʺ�
  for( int i = 0; i < row; i++ )
    if( chessboard[i][col] == 'Q' ) return false;
  // ���ϼ��45�Ƚ��Ƿ��лʺ����²��ã���Ϊ���滹û��ʼ��
  for( int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j-- )
    if( chessboard[i][j] == 'Q' ) return false;
  // ���135�Ƚ��Ƿ��лʺ�
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
      chessboard[row][col] = 'Q'; // ���ûʺ�
      No51_backtracking( chessboard, ans, row + 1, floor );
      chessboard[row][col] = '.'; // ���ݣ������ʺ�
    }
  }
}

vector<vector<string>> No51_solveNQueens( int n )
{
  int floor = n; // �������ֶ���
  vector<vector<string>> ans;
  // ����һ��nXn��ȫΪ��.������
  std::vector<std::string> chessboard( floor, std::string( floor, '.' ) );
  No51_backtracking( chessboard, ans, 0, floor );
  return ans;
}

int No72_minDistance( string word1, string word2 )
{
  // ��̬�滮
  // dp[i][j] ��ʾ���±�i-1Ϊ��β���ַ���word1�������±�j-1Ϊ��β���ַ���word2������༭����Ϊdp[i][j]��
  vector<vector<int>> dp( word1.size() + 1, vector<int>( word2.size() + 1, 0 ) );
  // ��ʼ��������ȫ����ɾ�����������Ե������Ϊ����
  for( int i = 0; i <= word1.size(); i++ ) dp[i][0] = i;
  for( int j = 0; j <= word2.size(); j++ ) dp[0][j] = j;
  // ����
  for( int i = 1; i <= word1.size(); i++ )
  {
    for( int j = 1; j <= word2.size(); j++ )
    {
      // �����ȣ���������ͬ��
      // ������ȣ�������Ϊ����б������������Ʋ�������Сֵ+1
      if( word1[i - 1] == word2[j - 1] ) dp[i][j] = dp[i - 1][j - 1];
      else dp[i][j] = min( {dp[i - 1][j - 1],dp[i - 1][j],dp[i][j - 1]} ) + 1;
    }
  }
  return dp[word1.size()][word2.size()];
}

int No115_numDistinct( string s, string t )
{
  // �����Ŀ������������У�����Ҫ���������еģ��ǾͿ��Կ�����KMP��
  // dp[i][j]����i-1Ϊ��β��s�������г�����j-1Ϊ��β��t�ĸ���Ϊdp[i][j]��
  vector<vector<uint64_t>> dp( s.size() + 1, vector<uint64_t>( t.size() + 1 ) );
  for( int i = 0; i < s.size(); i++ ) dp[i][0] = 1;
  for( int j = 1; j < t.size(); j++ ) dp[0][j] = 0;
  // �Ƶ����̻�ͼ�������
  for( int i = 1; i <= s.size(); i++ )
  {
    for( int j = 1; j <= t.size(); j++ )
    {
      // �����ȣ�ֵ��ͷ�������ϵ�ֵ�Ƶ�����
      if( s[i - 1] == t[j - 1] ) dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
      // �������ȣ�ֵ����ͷ���Ƶ�����
      else dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[s.size()][t.size()];
}

int No123_maxProfit( vector<int>& prices )
{
  // ��̬�滮
  // һ��һ���������״̬
  // 0.û�в��� ����ʵ����Ҳ���Բ��������״̬��
  // 1.��һ�γ��й�Ʊ
  // 2.��һ�β����й�Ʊ
  // 3.�ڶ��γ��й�Ʊ
  // 4.�ڶ��β����й�Ʊ
  if( prices.size() == 0 ) return 0;
  vector<vector<int>> dp( prices.size(), vector<int>( 5, 0 ) );
  // ��ʼ����0,2,4״̬��ʼΪ0
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
  // ��̬�滮
  // ��No.123��ȣ�Ҫ������
  // ����0���⣬ż������������������������
  if( prices.size() == 0 ) return 0;
  vector<vector<int>> dp( prices.size(), vector<int>( 2 * k + 1, 0 ) );
  // ��ʼ������0��������Ϊ-prices[0],������Ϊ0
  for( int j = 1; j < 2 * k; j += 2 ) dp[0][j] = -prices[0];
  // ״̬Ǩ��
  for( int i = 1; i < prices.size(); i++ )
  {
    for( int j = 0; j < 2 * k; j += 2 ) // 2��һ��
    {
      dp[i][j + 1] = max( dp[i - 1][j + 1], dp[i - 1][j] - prices[i] ); // ����
      dp[i][j + 2] = max( dp[i - 1][j + 2], dp[i - 1][j + 1] + prices[i] ); // ����
    }
  }
  return dp[prices.size() - 1][2 * k];
}

vector<int> No239_maxSlidingWindow( vector<int>& nums, int k )
{
  vector<int> ans;
  // ���ȶ���,�������ֵ��Ԫ�ر���Ϊ��������ȼ���Ԫ�ء�
  priority_queue<pair<int, int>> que;

  // ��ȡǰ3����
  for( int pos = 0; pos < k; pos++ ) que.emplace( nums[pos], pos );
  ans.emplace_back( que.top().first );
  // ����֮�����
  for( int pos = k; pos < nums.size(); pos++ )
  {
    que.emplace( nums[pos], pos );
    // �����±�ȥ��������Χ��ֵ
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
  // ͳ�����ֳ��ִ���
  unordered_map<int, int> map;
  for( const int num : nums ) map[num]++;

  // ���ȶ���, pair<ֵ�����ִ���>, vector<> �Ƚ������� bool �Ƚ�����
  priority_queue< pair<int, int>, vector<pair<int, int>>, decltype( &No347_cmp )> que( No347_cmp );
  for( auto iter = map.begin(); iter != map.end(); iter++ )
  {
    que.push( *iter );
    if( que.size() > k ) que.pop();
  }

  // ȡǰk����
  vector<int> ans( k );
  for( int pos = k - 1; pos >= 0; pos-- )
  {
    ans[pos] = que.top().first;
    que.pop();
  }

  return ans;
}
