#include "Easy.h"

vector<int>
No1_twoSum(vector<int>& nums, int target)
{
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
    if (0 != resultVector.size())
    {
      break;
    }
  }
  return resultVector;
}

vector<int>
No1_twoSum_2(vector<int>& nums, int target)
{
  // 哈希表法
  vector<int> resultVector;
  unordered_map<int,int> umap;
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
No7_reverse(int x)
{
  int ans = 0;
  while( x != 0 )
  {
    if( (ans > INT_MAX / 10 ) || // 判断是否将要发生越界
        (ans < INT_MIN / 10 ) )
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
No9_isPalindrome(int x)
{
  if (x != 0 && x % 10 <= 0) return false;

  int reverseX = 0;
  while (x > reverseX) // 和上面思路1的循环不同，这里只循环到整数的一半
  {
    reverseX = reverseX * 10 + x % 10;
    x /= 10;
  }

  // 判断是否为回文数
  return x == reverseX || x == reverseX / 10; // 原整数位数为奇数的情况下需要除以10
}

int
No13_romanToInt(string s)
{
  //初始化哈希表
  map<char,int> romanNumMap =
  { {'I',1}, {'V',5}, {'X',10}, {'L',50}, {'C',100}, {'D', 500}, {'M', 1000} };

  int ans = 0;
  int len = s.length();
  for( int i = 0; i < len; i++ )
  {
    int romanNum = romanNumMap[s[i]];
    if( romanNum < romanNumMap[s[i+1]] )
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
No20_isValid(string s)
{
  // 定义哈希表，左括号大于0，右括号小于0
  map<char,int> bracketsMap =
    { {'(',1}, {')',-1},
      {'{',2}, {'}',-2},
      {'[',3}, {']',-3} };
  
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
    else{} // 空字符串，或者未定义的字符根据题干的意思，应该是要无视掉
  }

  return stackInt.size() == 1;
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
  int length = 0;
  for( int index = 0; index < nums.size(); index++ )
  {
    if( nums[index] != val ) nums[length++] = nums[index];
  }
  return length;
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

int
No53_maxSubArray( vector<int>& nums )
{
  int pre = 0, maxAns = nums[0];
  for( const auto& x : nums )
  {
    pre = max( pre + x, x );
    maxAns = max( maxAns, pre );
  }
  return maxAns;
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
    else{ digits[idx]++; return digits; }   // 不进位则返回
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
    carry  = sum / 2;       // 进位更新
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
      vector<int> dp(n+1);
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
      while(cur->next )
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
        if( pos1 == m)
        {
          ans.emplace_back( nums2[pos2++] );
        }
        else if( pos2 == n)
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

static void
Inorder( TreeNode* root, vector<int>& res )
{
  // 方法一 : 递归法
  if( !root ) return;
  Inorder( root->left, res );
  res.push_back( root->val );
  Inorder( root->right, res );
}

static vector<int>
Inorder( TreeNode* root )
{
  // 方法二 : 迭代法
  vector<int> res;
  stack<TreeNode*> stk;
  while( root || !stk.empty() )
  {
    while( root )
    {
      stk.push( root );
      root = root->left;
    }
    root = stk.top();
    stk.pop();
    res.push_back( root->val );
    root = root->right;
  }
  return res;
}

vector<int>
No94_inorderTraversal( TreeNode* root )
{
  vector<int> res;
  Inorder( root, res );
  return res;
}

bool
No100_isSameTree( TreeNode* p, TreeNode* q )
{
  if( !p && !q ) return true;
  if( !p || !q ) return false;
  return( p->val == q->val &&
          No100_isSameTree( p->left, q->left ) &&
          No100_isSameTree( p->right, q->right ) );
}

static bool
_IsSymmetricTree( TreeNode* p, TreeNode* q )
{
  if( !p && !q ) return true;
  if( !p || !q ) return false;
  return( p->val == q->val &&
          _IsSymmetricTree( p->left, q->right ) &&
          _IsSymmetricTree( p->right, q->left ) );
}

bool
No101_isSymmetric( TreeNode* root )
{
  return _IsSymmetricTree( root, root );
}

int No104_maxDepth( TreeNode* root )
{
  // 方法一：深度优先法
  if( !root ) return 0;
  return max( No104_maxDepth( root->left ), No104_maxDepth( root->right ) ) + 1;
}

vector<vector<int>>
No118_generate( int numRows )
{
// 两步：
// 1、先一个循环构造杨辉三角的边角值
// 2、再利用动态方程dp[i][j] = dp[i-1][j-1]+dp[i-1][j];

  vector<vector<int>> ans( numRows );
  for (int row = 0; row < numRows; row++ )
  {
    ans[row] = vector<int>(row + 1, 0);
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
}

int
No122_maxProfit( vector<int>& prices )
{
  int size = prices.size();
  if( size < 2 ) return 0;
  int maxProfit = 0;

  // 看答案的，累加连续上升区间即可，即每天都判断是否可交易,不考虑手续费可还行
  for( int i = 1; i < size; i++ )
  {
    int profit = prices[i] - prices[i-1];
    if( 0 < profit ) maxProfit += profit;
  }

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
#endif
  return maxProfit;
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
No141_hasCycle( ListNode *head )
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

ListNode* No160_getIntersectionNode( ListNode* headA, ListNode* headB )
{
      if( !headA || !headB ) return nullptr;
      ListNode* pA = headA;
      ListNode* pB = headB;
      while( pA != pB )
      {
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

vector<string> No228_summaryRanges( vector<int>& nums )
{
        vector<string> ret;
        int i = 0;
        int n = nums.size();
        while (i < n) {
            int low = i;
            i++;
            while (i < n && nums[i] == nums[i - 1] + 1) {
                i++;
            }
            int high = i - 1;
            string temp = to_string(nums[low]);
            if (low < high) {
                temp.append("->");
                temp.append(to_string(nums[high]));
            }
            ret.push_back(move(temp));
        }
        return ret;
}


