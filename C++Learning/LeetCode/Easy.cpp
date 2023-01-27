#include "Easy.h"

vector<int>
No1_twoSum( vector<int>& nums, int target )
{
#if 0
  // 暴力法(双循环)
  vector<int> resultVector;
  int starIndex = 0;
  int numSize = nums.size();
  for( int num : nums )
  {
    for( int nextIndex = ++starIndex; nextIndex < numSize; nextIndex++ )
    {
      int targetTemp = num + nums[nextIndex];
      if( targetTemp == target )
      {
        resultVector.push_back( starIndex - 1 );
        resultVector.push_back( nextIndex );
        break;
      }
    }
    if( 0 != resultVector.size() )
    {
      break;
    }
  }
  return resultVector;
#endif
  // 哈希表法
  vector<int> ans;
  unordered_map<int, int> map;
  for( int pos = 0; pos < nums.size(); pos++ )
  {
    auto iter = map.find( target - nums[pos] );
    if( iter != map.end() ) return {iter->second, pos};
    map[nums[pos]] = pos;
  }
  return {};
}

vector<int>
No1_twoSum_2( vector<int>& nums, int target )
{
  // 哈希表法
  vector<int> resultVector;
  unordered_map<int, int> umap;
  for( int index = 0; index < nums.size(); index++ )
  {
    umap[nums[index]] = index;
  }

  for( int index = 0; index < nums.size(); index++ )
  {
    int diff = target - nums[index];

    auto itr = umap.find( diff );
    if( itr != umap.end() )
    {
      if( index != itr->second )
      {
        resultVector.emplace_back( index );
        resultVector.emplace_back( itr->second );
        break;
      }
    }
  }
  return resultVector;
}

int
No7_reverse( int x )
{
  int ans = 0;
  while( x != 0 )
  {
    if( ( ans > INT_MAX / 10 ) || // 判断是否将要发生越界
        ( ans < INT_MIN / 10 ) )
    {
      ans = 0;
      break;
    }
    ans *= 10;     // 位数提高
    ans += x % 10; // 取原整数的个位作为新整数的个位
    x /= 10;       // 位数降低
  }
  return ans;
}

bool
No9_isPalindrome( int x )
{
  if( x != 0 && x % 10 <= 0 ) return false;

  int reverseX = 0;
  while( x > reverseX ) // 和上面思路1的循环不同，这里只循环到整数的一半
  {
    reverseX = reverseX * 10 + x % 10;
    x /= 10;
  }

  // 判断是否为回文数
  return x == reverseX || x == reverseX / 10; // 原整数位数为奇数的情况下需要除以10
}

int
No13_romanToInt( string s )
{
  //初始化哈希表
  map<char, int> romanNumMap =
  {{'I',1}, {'V',5}, {'X',10}, {'L',50}, {'C',100}, {'D', 500}, {'M', 1000}};

  int ans = 0;
  int len = s.length();
  for( int i = 0; i < len; i++ )
  {
    int romanNum = romanNumMap[s[i]];
    if( romanNum < romanNumMap[s[i + 1]] )
    {
      romanNum *= -1;
    }
    ans += romanNum;
  }
  return ans;
}

string
No14_longestCommonPrefix( vector<string>& strs )
{
  int size = strs.size();
  if( 0 == strs.size() ) return "";

  string ans;
  for( int charLeng = 0; charLeng < strs[0].size(); charLeng++ )
  {
    for( int vectorIdx = 1; vectorIdx < size; vectorIdx++ )
    {
      if( strs[0][charLeng] != strs[vectorIdx][charLeng] ) return ans;
    }
    ans += strs[0][charLeng];
  }

  return ans;
}

bool
No20_isValid( string s )
{
  // 定义哈希表，左括号大于0，右括号小于0
  map<char, int> bracketsMap =
  {{'(',1}, {')',-1}, {'{',2}, {'}',-2}, {'[',3}, {']',-3}};

  // 定义栈，用于存储,比较和最终结果的判断
  stack<int> stackInt;
  stackInt.push( 0 );
  for( const char sTemp : s )
  {
    int bracketsInt = bracketsMap[sTemp];
    if( 0 < bracketsInt ) // 左括号入栈
    {
      stackInt.push( bracketsInt );
    }
    else if( 0 > bracketsInt ) // 右括号比较
    {
      if( stackInt.top() + bracketsInt != 0 ) return false;
      stackInt.pop(); // 左右括号一致，出栈
    }
    else
    {
    } // 空字符串，或者未定义的字符根据题干的意思，应该是要无视掉
  }

  return stackInt.size() == 1;

#if 0
  // 方法2：不用map
  if( s.size() == 0 || s.size() % 2 != 0 ) return false;
  stack<char> stk;
  for( int pos = 0; pos < s.size(); pos++ )
  {
    if( s[pos] == '(' ) stk.push( ')' );
    else if( s[pos] == '[' ) stk.push( ']' );
    else if( s[pos] == '{' ) stk.push( '}' );
    else if( stk.empty() || stk.top() != s[pos] ) return false;
    else stk.pop();
  }
  return stk.empty();
#endif
}

ListNode*
No21_mergeTwoLists( ListNode* l1, ListNode* l2 )
{

  // 方法1：迭代
#if 0
  ListNode* tempList = new ListNode( 0 );
  ListNode* headListNode = tempList;

  while( l1 && l2 )
  {
    if( l1->val > l2->val )
    {
      tempList->next = l2;
      l2 = l2->next;
    }
    else
    {
      tempList->next = l1;
      l1 = l1->next;
    }
    tempList = tempList->next;
  }

  tempList->next = l1 ? l1 : l2; // 连上最后的链表

  // 返回链表头的下一位，因为第0位是自己创建的，不是所要求的
  return headListNode->next;
#endif

  // 方法2：递归
  if( !l1 ) return l2;
  if( !l2 ) return l1;
  // 把大Node放到小的Node的next
  if( l1->val < l2->val )
  {
    l1->next = No21_mergeTwoLists( l1->next, l2 );
    return l1;
  }
  else
  {
    l2->next = No21_mergeTwoLists( l1, l2->next );
    return l2;
  }
}

int
No26_removeDuplicates( vector<int>& nums )
{
  if( nums.size() == 0 ) return 0; // 这里对应空数组
  int length = 0;
  for( const int num : nums )
  {
    if( nums[length] != num ) nums[++length] = num; // 注意这里先++再赋值
  }
  return ++length;
}

int
No27_removeElement( vector<int>& nums, int val )
{
#if 0
  int length = 0;
  for( int index = 0; index < nums.size(); index++ )
  {
    if( nums[index] != val ) nums[length++] = nums[index];
  }
  return length;
#endif

  // 双指针块慢法
  int slow = 0;
  for( int fast = 0; fast < nums.size(); fast++ )
  {
    if( nums[fast] != val )
    {
      nums[slow] = nums[fast];
      slow++;
    }
  }
  return slow;
}

int
No28_strStr( string haystack, string needle )
{
  if( 0 == needle.size() ) return 0;

  int ans = -1;
  int needleIdx = 0;
  for( int chrIdx = 0; chrIdx < haystack.size(); chrIdx++ )
  {
    if( haystack[chrIdx] == needle[needleIdx] )
    {
      if( ++needleIdx == needle.size() )
      {
        ans = chrIdx - ( needleIdx - 1 );
        break;
      }
    }
    else
    {
      chrIdx -= needleIdx; // 返回初次相同位置的下一位
      needleIdx = 0;
    }
  }
  return ans;
}

int
No35_searchInsert( vector<int>& nums, int target )
{
  int idx = 0;
  for( ; idx < nums.size(); idx++ )
  {
    if( target <= nums[idx] ) break;
  }

  return idx;

  // 应该用二分法，但是懒得写了
}

string
No38_countAndSay( int n )
{
  string ans( "1" );
  for( int number = 2; number <= n; number++ )
  {
    int charCount = 0;
    char currentChar( ans[0] );
    string temp( "" );
    for( int charIdx = 0; charIdx < ans.size(); charIdx++ )
    {
      if( ans[charIdx] != currentChar )
      {
        temp += to_string( charCount );
        temp += currentChar;
        charCount = 0;
        currentChar = ans[charIdx];
      }
      charCount++;
    }
    temp += to_string( charCount );
    temp += currentChar;

    ans = temp;
    printf( "%s\n", ans.c_str() );
  }
  return ans;
}

int No_58_lengthOfLastWord( string s )
{
  int last = s.size() - 1;
  int length = 0;
  while( last >= 0 && s[last] == ' ' ) last--;
  while( last >= 0 && s[last--] != ' ' ) length++;
  return length;
}

vector<int>
No66_plusOne( vector<int>& digits )
{
  for( int idx = digits.size() - 1; idx >= 0; idx-- )
  {
    if( digits[idx] == 9 ) digits[idx] = 0; // 进位
    else
    {
      digits[idx]++; return digits;
    }   // 不进位则返回
  }

  digits.insert( digits.begin(), 1 ); // 这里肯定是首位进位或者为空的情况
  return digits;
}

string
No67_addBinary( string a, string b )
{
  // 高位补0
  while( a.length() > b.length() ) b = '0' + b;
  while( a.length() < b.length() ) a = '0' + a;

  // 进位相加
  int carry = 0;
  for( int idx = (int)a.length() - 1; idx >= 0; idx-- )
  {
    // +-'0'是为了对应ascii码
    int sum = a[idx] - '0' + b[idx] - '0' + carry;
    a[idx] = sum % 2 + '0'; // 本位数值
    carry = sum / 2;       // 进位更新
  }

  // 有溢出
  if( carry > 0 ) a = '1' + a;

  return a;
}

int No69_mySqrt( int x )
{
  int left = 0, right = x, ans = -1;
  while( left <= right )
  {
    int mid = left + ( right - left ) / 2;
    if( (long long)mid * mid <= x )
    {
      ans = mid;
      left = mid + 1;
    }
    else
    {
      right = mid - 1;
    }
  }
  return ans;
}

int No70_climbStairs( int n )
{
  if( n <= 1 )return n;
  vector<int> dp( n + 1 );
  dp[1] = 1;
  dp[2] = 2;
  for( int pos = 3; pos <= n; pos++ )
  {
    dp[pos] = dp[pos - 1] + dp[pos - 2];
  }
  return dp[n];
}

ListNode* No83_deleteDuplicates( ListNode* head )
{
  if( !head ) return head;
  ListNode* cur = head;
  while( cur->next )
  {
    if( cur->val == cur->next->val )
    {
      cur->next = cur->next->next;
    }
    else
    {
      cur = cur->next;
    }
  }
  return head;
}

void No88_merge( vector<int>& nums1, int m, vector<int>& nums2, int n )
{
  vector<int> ans;
  int pos1 = 0;
  int pos2 = 0;
  while( pos1 < m || pos2 < n )
  {
    if( pos1 == m )
    {
      ans.emplace_back( nums2[pos2++] );
    }
    else if( pos2 == n )
    {
      ans.emplace_back( nums1[pos1++] );
    }
    else if( nums1[pos1] <= nums2[pos2] )
    {
      ans.emplace_back( nums1[pos1] );
      pos1++;
    }
    else
    {
      ans.emplace_back( nums2[pos2] );
      pos2++;
    }
  }
  nums1 = ans;
}

static void No94_inorder( TreeNode* node, vector<int>& res )
{
  // 方法一 : 递归法
  if( !node ) return;
  No94_inorder( node->left, res );
  res.push_back( node->val );
  No94_inorder( node->right, res );
}

static vector<int> No94_inorder( TreeNode* node )
{
  // 方法二 : 迭代法
  vector<int> res;
  stack<TreeNode*> stk;
  while( node || !stk.empty() )
  {
    while( node )
    {
      stk.push( node );
      node = node->left;
    }
    node = stk.top();
    stk.pop();
    res.push_back( node->val );
    node = node->right;
  }
  return res;
}

vector<int>
No94_inorderTraversal( TreeNode* root )
{
  vector<int> res;
  No94_inorder( root, res );
  return res;
}

bool
No100_isSameTree( TreeNode* p, TreeNode* q )
{
  // 后续遍历，左右中
  if( !p && !q ) return true;  // 均为空即一致
  else if( !p || !q ) return false; // 一值一空为不一致，上面已判断均为空情况，这里肯定是一有值一空
  else if( p->val != q->val ) return false;
  bool left = No100_isSameTree( p->left, q->left );    // 左
  bool right = No100_isSameTree( p->right, q->right ); // 左
  return left && right;                                // 中
}

static bool
No101_isSymmetricTree( TreeNode* left, TreeNode* right )
{
  // 后续遍历，左右中
  if( !left && !right ) return true;  // 均为空即一致
  else if( !left || !right ) return false; // 一值一空为不一致，上面已判断均为空情况，这里肯定是一有值一空
  else if( left->val != right->val ) return false;
  bool outside = No101_isSymmetricTree( left->left, right->right ); // 左子树：左、 右子树：右
  bool inside = No101_isSymmetricTree( left->right, right->left );  // 左子树：右、 右子树：左
  return outside && inside; // 左子树：中、 右子树：中 （逻辑处理）
}

bool
No101_isSymmetric( TreeNode* root )
{
  return No101_isSymmetricTree( root, root );
}

int No104_maxDepth( TreeNode* root )
{
  // 方法一：深度优先法
  if( !root ) return 0;
  int leftHight = No104_maxDepth( root->left );
  int rightHight = No104_maxDepth( root->right );
  int maxHight = max( leftHight, rightHight ) + 1;
  return maxHight;

  // 以下为精简版
  //return max( No104_maxDepth( root->left ), No104_maxDepth( root->right ) ) + 1;
}

TreeNode* No108_traversal( vector<int>& nums, int left, int right )
{
  if( left > right ) return nullptr;
  int mid = ( left + right ) / 2;
  TreeNode* node = new TreeNode( nums[mid] );
  node->left = No108_traversal( nums, left, mid - 1 );
  node->right = No108_traversal( nums, mid + 1, right );
  return node;
}

TreeNode* No108_sortedArrayToBST( vector<int>& nums )
{
  return No108_traversal( nums, 0, nums.size() - 1 );
}

int No110_getHeight( TreeNode* root )
{
  if( !root ) return 0;
  int leftHeight = No110_getHeight( root->left );
  if( leftHeight == -1 ) return -1;
  int rightHeight = No110_getHeight( root->right );
  if( rightHeight == -1 ) return -1;
  if( abs( leftHeight - rightHeight ) > 1 ) return -1;
  int height = 1 + max( leftHeight, rightHeight );
  return height;
}

bool No110_isBalanced( TreeNode* root )
{
  if( !root ) return true;
  int leftHeight = No110_getHeight( root->left );
  if( leftHeight == -1 ) return false;
  int rightHeight = No110_getHeight( root->right );
  if( rightHeight == -1 ) return false;
  if( abs( leftHeight - rightHeight ) > 1 ) return false;
  return true;
}

int No111_minDepth( TreeNode* root )
{
  // 方法一：深度优先法
  if( !root ) return 0;
  int leftHight = No104_maxDepth( root->left );
  int rightHight = No104_maxDepth( root->right );
  int minHight = 0;
  // 和最大深度不同，null会返回0，要排除这种情况
  if( leftHight == 0 && rightHight != 0 ) minHight = rightHight + 1;
  else if( leftHight != 0 && rightHight == 0 ) minHight = leftHight + 1;
  else minHight = min( leftHight, rightHight ) + 1;
  return minHight;
}

bool No112_traversal( TreeNode* root, int targetSum )
{
  if( !root->left && !root->right )
  {
    if( targetSum == 0 ) return true;
    else return false;
  }
  if( root->left )
  {
    // 用到了回溯的概念，可以精简
    targetSum -= root->left->val;
    if( No112_traversal( root->left, targetSum ) ) return true;
    targetSum += root->left->val;
  }
  if( root->right )
  {
    // 精简后的结果
    if( No112_traversal( root->right, targetSum - root->right->val ) ) return true;
  }
  return false;
}

bool No112_hasPathSum( TreeNode* root, int targetSum )
{
  if( !root ) return false;
  return No112_traversal( root, targetSum - root->val );
}

vector<vector<int>>
No118_generate( int numRows )
{
  // 两步：
  // 1、先一个循环构造杨辉三角的边角值
  // 2、再利用动态方程dp[i][j] = dp[i-1][j-1]+dp[i-1][j];

  vector<vector<int>> ans( numRows );
  for( int row = 0; row < numRows; row++ )
  {
    ans[row] = vector<int>( row + 1, 0 );
    ans[row][0] = 1;
    ans[row][row] = 1;
  }

  if( numRows <= 2 ) return ans;

  for( int row = 2; row < numRows; ++row )
  {
    for( int col = 1; col < ans[row].size() - 1; col++ )
    {
      ans[row][col] = ans[row - 1][col - 1] + ans[row - 1][col];
    }
  }
  return ans;
}

vector<int>
No119_getRow( int rowIndex )
{
  // 利用组合数公式求第N行杨辉三角
  vector<int> ans;
  for( int k = 0; k <= rowIndex; k++ )
  {
    ans.push_back( Combination( rowIndex, k ) );
  }
  return ans;
}

int
No121_maxProfit( vector<int>& prices )
{
  // 动态规划法
  // dp[i][0] 表示第i天持有股票所得最多现金
  // dp[i][1] 表示第i天不持有股票所得最多现金
  int size = prices.size();
  if( size == 0 ) return 0;
  vector<vector<int>> dp( size, vector<int>( 2 ) );
  dp[0][0] = 0 - prices[0]; // 当天买进后手里现金
  dp[0][1] = 0;             // 当天买进后又卖出后手里现金
  for( int i = 1; i < size; i++ )
  {
    // 对比前一天买入和今天买入，哪个花钱少
    dp[i][0] = max( dp[i - 1][0], -prices[i] );
    // 对比之前卖出和今天卖出，哪个赚钱多
    dp[i][1] = max( dp[i - 1][1], prices[i] + dp[i - 1][0] );
  }
  return dp[size - 1][1];

#if 0
  // 贪心
  int low = INT_MAX;
  int result = 0;
  for( int i = 0; i < prices.size(); i++ )
  {
    low = min( low, prices[i] );  // 取最左最小价格
    result = max( result, prices[i] - low ); // 直接取最大区间利润
  }
  return result;
#endif

#if 0
  // 以前写的,应该是暴力
  int size = prices.size();
  if( size < 2 ) return 0;
  int maxProfit = 0;
  int buyPrices = prices[0];
  for( int i = 1; i < size; i++ )
  {
    int profit = prices[i] - buyPrices;
    if( maxProfit < profit )
    {
      maxProfit = profit;
    }
    else if( 0 > profit )
    {
      buyPrices = prices[i];
    }
  }
  return maxProfit;
#endif
}

bool No125_isPalindrome( string s )
{
  string line;
  for( const char& c : s )
  {
    if( isalnum( c ) )
    {
      line += tolower( c );
    }
  }
  string reverse( line.rbegin(), line.rend() );
  return line == reverse;
}

int No136_singleNumber( vector<int>& nums )
{
  int ans = 0;
  for( int num : nums ) ans ^= num;
  return ans;
}

bool
No141_hasCycle( ListNode* head )
{
  ListNode* faster = head;
  ListNode* slower = head;
  if( !head ) return false;
  while( faster && faster->next )
  {
    faster = faster->next->next;
    slower = slower->next;
    if( faster == slower ) return true;
  }
  return false;
}

vector<int> No144_preorderTraversal( TreeNode* root )
{
  // 二叉树前序遍历，迭代法
  stack<TreeNode*> stk;
  vector<int> res;
  stk.push( root );
  while( !stk.empty() )
  {
    TreeNode* node = stk.top();
    stk.pop();
    if( node )
    {
      res.push_back( node->val );
      stk.push( node->right );
      stk.push( node->left );
    }
    else
    {
      continue;
    }
  }
  return res;
}

void No145_traversal( TreeNode* node, vector<int>& ans )
{
  if( !node ) return;
  No145_traversal( node->left, ans );
  No145_traversal( node->right, ans );
  ans.push_back( node->val );
}

vector<int> No145_postorderTraversal( TreeNode* root )
{
  vector<int> ans;
  No145_traversal( root, ans );
  return ans;
}

ListNode* No160_getIntersectionNode( ListNode* headA, ListNode* headB )
{
  if( !headA || !headB ) return nullptr;
  ListNode* pA = headA;
  ListNode* pB = headB;
  while( pA != pB )
  {
    // 如果两个链表不相交，那最终pA = nullptr = pB，跳出循环
    pA = pA ? pA->next : headB;
    pB = pB ? pB->next : headA;
  }
  return pA;
}

string No168_convertToTitle( int columnNumber )
{
  string ans;
  while( columnNumber-- )
  {
    ans += columnNumber % 26 + 'A';
    columnNumber /= 26;
  }
  reverse( ans.begin(), ans.end() );
  return ans;
}

int No169_majorityElement( vector<int>& nums )
{
  int maxCount = 0;
  int maxNum = nums[0];
  unordered_map<int, int> numMap;
  for( int num : nums )
  {
    numMap[num]++;
    if( numMap[num] > maxCount )
    {
      maxCount = numMap[num];
      maxNum = num;
    }
  }
  return maxNum;
}

int No171_titleToNumber( string columnTitle )
{
  int num = 0;
  long count = 1;
  for( int i = columnTitle.size() - 1; i >= 0; i-- )
  {
    int temp = columnTitle[i] - 'A' + 1;
    num += temp * count;
    count *= 26;
  }
  return num;
}

uint32_t No190_reverseBits( uint32_t n )
{
  uint32_t i = 0, j = 32;
  while( j-- )
  {
    // i左移一位并补上最后一位
    i = ( i << 1 ) | ( n & 1 );
    // n右移替换最后一位
    n >>= 1;
  }
  return i;
}

int No191_hammingWeight( uint32_t n )
{
  int count = 0, i = 32;
  while( i-- )
  {
    if( ( n & 1 ) == 1 ) count++;
    n >>= 1;
  }
  return count;
}

bool No202_isHappy( int n )
{
  int next = 0;
  unordered_set<int> set;
  while( n != 1 && set.find( n ) == set.end() )
  {
    next = 0;
    set.insert( n );
    while( n > 0 )
    {
      int d = n % 10;
      n /= 10;
      next += d * d;
    }
    n = next;
  }
  return n == 1;
}

ListNode* No203_removeElements( ListNode* head, int val )
{
#if 0
  ListNode* pA = head;
  while( pA && pA->val == val )
  {
    pA = pA->next;
    head = pA;
  }
  while( pA && pA->next )
  {
    if( pA->next->val == val )
    {
      pA->next = pA->next->next;
    }
    else
    {
      pA = pA->next;
    }
  }
  return head;
#endif
  // 设置一个虚拟头结点在进行移除节点操作
  ListNode* dummy = new ListNode(val+1);
  dummy->next = head;
  ListNode* cur = dummy;
  while( cur && cur->next )
  {
    if( cur->next->val == val )
    {
      ListNode* temp = cur->next;
      cur->next = cur->next->next;
      delete temp;
    }
    else
    {
      cur = cur->next;
    }
  }
  head = dummy->next;
  delete dummy;
  return head;
}

bool No205_isIsomorphic( string s, string t )
{
  char s1, t1;
  size_t size = s.size();
  unordered_map<char, char> sMap;
  unordered_map<char, char> tMap;
  for( int pos = 0; pos < size; pos++ )
  {
    s1 = s[pos];
    t1 = t[pos];
    if( ( sMap.count( s1 ) && sMap[s1] != t1 ) ||
        ( tMap.count( t1 ) && tMap[t1] != s1 ) )
    {
      return false;
    }
    sMap[s1] = t1;
    tMap[t1] = s1;
  }

  return true;
}

ListNode* No206_reverseList( ListNode* head )
{
  ListNode* pre = nullptr;
  ListNode* cur = head;
  while( cur )
  {
    ListNode* next = cur->next;
    cur->next = pre;
    pre = cur;
    cur = next;
  }
  return pre;
}

bool No217_containsDuplicate( vector<int>& nums )
{
  unordered_set<int> set;
  for( int num : nums )
  {
    if( set.count( num ) ) return true;
    else set.insert( num );
  }
  return false;
}

bool No219_containsNearbyDuplicate( vector<int>& nums, int k )
{
  unordered_map<int, int> dictionary;
  int length = nums.size();
  for( int i = 0; i < length; i++ )
  {
    int num = nums[i];
    if( dictionary.count( num ) && i - dictionary[num] <= k )
    {
      return true;
    }
    dictionary[num] = i;
  }
  return false;
}

TreeNode* No226_traversal( TreeNode* node )
{
  if( !node ) return node;
  TreeNode* temp = node->left;    // 中，交换
  node->left = node->right;
  node->right = temp;
  No226_traversal( node->left );  // 左
  No226_traversal( node->right ); // 右
  return node;
}

TreeNode* No226_invertTree( TreeNode* root )
{
  return No226_traversal(root);
}

vector<string> No228_summaryRanges( vector<int>& nums )
{
  vector<string> ret;
  int i = 0;
  int n = nums.size();
  while( i < n )
  {
    int low = i;
    i++;
    while( i < n && nums[i] == nums[i - 1] + 1 )
    {
      i++;
    }
    int high = i - 1;
    string temp = to_string( nums[low] );
    if( low < high )
    {
      temp.append( "->" );
      temp.append( to_string( nums[high] ) );
    }
    ret.push_back( move( temp ) );
  }
  return ret;
}

bool No231_isPowerOfTwo( int n )
{
  return n > 0 ? ( n & ( n - 1 ) ) == 0 == 0 : 0;
}

bool No234_isPalindrome( ListNode* head )
{
  vector<int> lists;
  while( head )
  {
    lists.emplace_back( head->val );
    head = head->next;
  }
  for( int left = 0, right = (int)lists.size() - 1; left < right; ++left, --right )
  {
    if( lists[left] != lists[right] )
    {
      return false;
    }
  }
  return true;
}

bool No242_isAnagram( string s, string t )
{
#if 0
  // 有点邪门的方法
  sort( s.begin(), s.end() );
  sort( t.begin(), t.end() );
  return s == t;
#endif
  // 哈希数组法，记得初始化为0
  int map[26] = {0};
  for( const char& c : s ) map[c - 'a']++;
  for( const char& c : t ) map[c - 'a']--;
  for( const int i : map ) if( i != 0 ) return false;
  return true;
}

void No247_traversal( TreeNode* node, vector<int>& path, vector<string>& res )
{
  path.push_back( node->val );
  if( !node->left && !node->right ) // 中
  {
    string temp;
    for( const int val : path )
    {
      temp += ( to_string( val ) );
      temp += "->";
    }
    temp.pop_back();
    temp.pop_back();
    res.push_back( temp );
  }
  if( node->left ) // 左
  {
    No247_traversal( node->left, path, res );
    path.pop_back();
  }
  if( node->right ) // 右
  {
    No247_traversal( node->right, path, res );
    path.pop_back();
  }
}

vector<string> No247_binaryTreePaths( TreeNode* root )
{
  vector<int> path;
  vector<string> res;
  if( !root ) return res;
  No247_traversal( root, path, res );
  return res;
}

int No258_addDigits( int num )
{
  if( num == 0 ) return 0;
  if( num % 9 == 0 ) return 9;
  return num % 9;
}

bool No263_isUgly( int n )
{
  if( n <= 0 ) return false;
  int factors[] = {2, 3, 5};
  for( int factor : factors )
  {
    while( n % factor == 0 )
    {
      n /= factor;
    }
  }
  return n == 1;
}

int No268_missingNumber( vector<int>& nums )
{
  sort( nums.begin(), nums.end() );
  int size = nums.size();
  for( int i = 0; i < size; i++ )
  {
    if( nums[i] != i )
    {
      return i;
    }
  }
  return size;
}

static bool isBadVersion( int n )
{
  return n == 5;
}

int No278_firstBadVersion( int n )
{
  int left = 1, right = n;
  while( left < right )
  {
    int mid = left + ( right - left ) / 2;
    if( isBadVersion( mid ) )
    {
      right = mid;
    }
    else
    {
      left = mid + 1;
    }
  }
  return left;
}

void No283_moveZeroes( vector<int>& nums )
{
  int left = 0;
  int right = 0;
  int size = nums.size();
  while( left < size && nums[left] != 0 )left++;
  for( right = left; right < size; right++ )
  {
    if( nums[right] != 0 )
    {
      swap( nums[left], nums[right] );
      left++;
    }
  }
}

bool No290_wordPattern( string pattern, string s )
{
  vector<string> strVec;
  stringstream iss( s );
  string word;
  while( iss >> word ) strVec.push_back( word );
  if( strVec.size() != pattern.size() ) return false;

  unordered_map<char, string> m1;
  unordered_map<string, char> m2;
  int size = pattern.size();
  for( int pos = 0; pos < size; pos++ )
  {
    char c1 = pattern[pos];
    string s1 = strVec[pos];

    if( m1.find( c1 ) == m1.end() ) m1[c1] = s1;
    if( m2.find( s1 ) == m2.end() ) m2[s1] = c1;
    if( m1[c1] != s1 || m2[s1] != c1 )return false;
  }
  return true;
}

bool No292_canWinNim( int n )
{
  return n%4 != 0;
}

vector<int> No338_countBits( int n )
{
  vector<int> ans;
  for( int pos = 0; pos <= n; pos++ )
  {
    int temp = pos, count = 0;
    while( temp > 0 )
    {
      if( temp & 1 ) count++;
      temp = temp >> 1;
    }
    ans.push_back( count );
  }
  return ans;
}

bool No342_isPowerOfFour( int n )
{
  bool b1 = n > 0;
  bool b2 = ( n & ( n - 1 ) ) == 0;
  bool b3 = n % 3 == 1;  // 判断能否被3整除余1， 如果判断4整除余0的话，1会被认为是错误的
  bool b4 = b1 && b2 && b3;
  return b4;
}

void No344_reverseString( vector<char>& s )
{
  int left = 0;
  int right = s.size() - 1;
  for( ; left < right; left++, right-- )
  {
    swap( s[left], s[right] );
  }
}

string No345_reverseVowels( string s )
{
  unordered_set<char> set{'a','e','i','o','u','A','E','I','O','U'};
  int size = s.length();
  int left = 0;
  int right = s.size() - 1;
  while( left < right )
  {
    while( left < right && set.find( s[left] ) == set.end() )
    {
      left++;
    }
    while( left < right && set.find( s[right] ) == set.end() )
    {
      right--;
    }
    if( left < right )
    {
      swap( s[left], s[right] );
      left++;
      right--;
    }
  }
  return s;
}

vector<int> No349_intersection( vector<int>& nums1, vector<int>& nums2 )
{
  unordered_set<int> set( nums1.begin(), nums1.end() );
  unordered_set<int> resultSet;
  for( const int num : nums2 ) if( set.count( num ) ) resultSet.insert( num );
  vector<int> ans( resultSet.begin(), resultSet.end() );
  return ans;
}

bool No392_isSubsequence( string s, string t )
{
  // dp[i][j] 表示以下标i-1为结尾的字符串s，和以下标j-1为结尾的字符串t，相同子序列的长度为dp[i][j]。
  vector<vector<int>> dp( s.size() + 1, vector<int>( t.size() + 1, 0 ) );
  for( int i = 1; i <= s.size(); i++ )
  {
    for( int j = 1; j <= t.size(); j++ )
    {
      if( s[i - 1] == t[j - 1] ) dp[i][j] = dp[i - 1][j - 1] + 1;
      else dp[i][j] = dp[i][j - 1];
    }
  }
  if( dp[s.size()][t.size()] == s.size() ) return true;
  return false;
}

int No404_traversal( TreeNode* node, bool left )
{
  if( !node->left && !node->right )
  {
    // 是叶子节点，且为左节点时
    if( left ) return node->val;
    else return 0;
  }

  int sum = 0;
  if( node->left ) sum += No404_traversal( node->left, true );
  if( node->right ) sum += No404_traversal( node->right, false );
  return sum;
}

int No404_sumOfLeftLeaves( TreeNode* root )
{
  int sum = 0;
  if( root->left ) sum += No404_traversal( root->left, true );
  if( root->right ) sum += No404_traversal( root->right, false );
  return sum;
}

int No455_findContentChildren( vector<int>& g, vector<int>& s )
{
  // 贪心算法
  sort( g.begin(), g.end() );
  sort( s.begin(), s.end() );
  int result = 0;
  int index = s.size() - 1;
  for( int i = g.size() - 1; i >= 0; i-- )
  {
    if( index >= 0 && s[index] >= g[i] )
    {
      result++;
      index--;
    }
  }
  return result;
}

void No501_traversal( TreeNode* node, TreeNode*& pre, vector<int>& res, int& count, int& maxCount )
{
  if( !node ) return;
  // 左遍历
  No501_traversal( node->left, pre, res, count, maxCount );

  if( !pre ) count = 1;
  else if( node->val == pre->val ) count++;
  else count = 1;
  pre = node; // 更新pre

  // 中处理
  if( count == maxCount ) res.push_back( node->val );
  if( count > maxCount )
  {
    maxCount = count;
    res.clear();
    res.push_back( node->val );
  }

  // 右遍历
  No501_traversal( node->right, pre, res, count, maxCount );
}

vector<int> No501_findMode( TreeNode* root )
{
  TreeNode* pre = nullptr;
  vector<int> res;
  int count = 0;
  int maxCount = 0;
  No501_traversal( root, pre, res, count, maxCount );
  return res;
}

int No509_fib( int n )
{
  if( n <= 1 ) return n;
  vector<int> nums( n + 1 );
  nums[0] = 0;
  nums[1] = 1;
  for( int i = 2; i <= n; i++ )
    nums[i] = nums[i - 1] + nums[i - 2];
  return nums[n];
}

void No530_traversal( TreeNode* node, TreeNode*& pre, int& minDiff )
{
  if( !node ) return;
  No530_traversal( node->left, pre, minDiff );
  if( pre ) minDiff = std::min( minDiff, node->val - pre->val );
  pre = node;
  No530_traversal( node->right, pre, minDiff );
}

int No530_getMinimumDifference( TreeNode* root )
{
  TreeNode* pre = nullptr;
  int minDiff = INT_MAX;
  No530_traversal( root, pre, minDiff );
  return minDiff;
}

TreeNode* No617_mergeTrees( TreeNode* root1, TreeNode* root2 )
{
  if( !root1 ) return root2;
  if( !root2 ) return root1;

  // 重新定义新节点，不修改原有两树的结构
  TreeNode* root = new TreeNode( 0 );
  root->val = root1->val + root2->val;
  root->left = No617_mergeTrees( root1->left, root2->left );
  root->right = No617_mergeTrees( root1->right, root2->right );
  return root;
}

int No674_findLengthOfLCIS( vector<int>& nums )
{
  // dp[i]：以下标i为结尾的连续递增的子序列长度为dp[i]。
  if( nums.size() <= 1 ) return nums.size();
  int result = 1;
  vector<int> dp( nums.size(), 1 );
  for( int i = 1; i < nums.size(); i++ )
  {
    if( nums[i] > nums[i - 1] ) dp[i] = dp[i - 1] + 1;
    if( dp[i] > result ) result = dp[i];
  }
  return result;
#if 0
  // 贪心
  if( nums.size() == 0 ) return 0;
  int result = 1; // 连续子序列最少也是1
  int count = 1;
  for( int i = 1; i < nums.size(); i++ )
  {
    if( nums[i] > nums[i - 1] ) count++; // 连续记录
    else count = 1; // 不连续，count从头开始
    if( count > result ) result = count;
  }
  return result;
#endif
}

TreeNode* No700_searchBST( TreeNode* root, int val )
{
  while( root )
  {
    if( root->val > val ) root = root->left;
    else if( root->val < val ) root = root->right;
    else return root;
  }
  return nullptr;
}

int No704_search( vector<int>& nums, int target )
{
  int left = 0;
  int right = nums.size() - 1;
  while( left <= right )
  {
    int mid = ( left + right ) / 2;
    if( nums[mid] > target )
    {
      right = mid - 1;
    }
    else if( nums[mid] < target )
    {
      left = mid + 1;
    }
    else
    {
      return mid;
    }
  }
  return -1;
}

int No746_minCostClimbingStairs( vector<int>& cost )
{
  int size = cost.size();
  vector<int> dp( size + 1 );
  dp[0] = 0;
  dp[1] = 0;
  for( int i = 2; i <= size; i++ )
  {
    dp[i] = min( dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2] );
  }
  return dp[size];
}

vector<int> No977_sortedSquares( vector<int>& nums )
{
  int pos = nums.size() - 1;
  vector<int> ans( nums.size() );
  int left = 0, right = nums.size() - 1;
  while( left <= right )
  {
    if( nums[left] * nums[left] > nums[right] * nums[right] )
    {
      ans[pos] = nums[left] * nums[left];
      left++;
    }
    else
    {
      ans[pos] = nums[right] * nums[right];
      right--;
    }
    pos--;
  }

  return ans;
}

string No1047_removeDuplicates( string s )
{
  string ans( "" );
  for( const char& c : s )
  {
    if( ans.size() != 0 && ans.back() == c ) ans.pop_back();
    else ans.push_back( c );
  }
  return ans;
}
