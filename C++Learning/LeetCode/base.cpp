#include "Base.h"

// 组合数公式C( N, K )
int Combination( int N, int k )
{
  long res = 1;
  for( int i = 1; i <= k; i++ )
      res = res * ( N - k + i ) / i;
  return (int)res;
}

void
PrintStrVector( const vector<string>& strVector )
{
  for( const string& str : strVector )
  {
    cout << str << endl;
  }
}

void
PrintIntVector( const vector<int>& intVector )
{
  for( const int& temp : intVector )
  {
    cout << temp << "\t";
  }
  cout << endl;
}

void
PrintDoubleIntVector( const vector<vector<int>>& doubleIntVector )
{
  for( const vector<int>& intVector : doubleIntVector )
  {
    PrintIntVector( intVector );
  }
}