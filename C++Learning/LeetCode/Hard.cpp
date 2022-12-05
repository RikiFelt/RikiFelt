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
