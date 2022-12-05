#include "Base.h"
#include "Easy.h"
#include "Normal.h"
#include "Hard.h"

int main()
{
  int nTest = 0;
  bool bRet = false;
  string tempStr( "" );
  vector<int> tempNums;
  vector<vector<int>> tempDoubleIntVector;

  tempNums = {3,2,4};
  No1_twoSum_2( tempNums, 6 );

  ListNode list1 = ListNode( 5 );
  ListNode list2 = ListNode( 5 );
  No2_addTwoNumbers( &list1, &list2 );

  nTest = No3_lengthOfLongestSubstring( "abcdefg" );
  nTest = No3_lengthOfLongestSubstring( "aaaaaa" );
  nTest = No3_lengthOfLongestSubstring( "pwwkew" );
  nTest = No3_lengthOfLongestSubstring( "aabcdef" );
  nTest = No3_lengthOfLongestSubstring( "cdd" );
  nTest = No3_lengthOfLongestSubstring( "afbcdaefgbijklnmopq" );
  nTest = No3_lengthOfLongestSubstring( "abba" );

  bRet = No9_isPalindrome( 123 );
  nTest = No13_romanToInt( "III" );

  tempNums = { 3,0,-2,-1,1,2 };
  tempNums = { -1,0,1,2,-1,-4 };
  tempNums = { -1,0,1,0 };
  tempNums = { 0,0,0 };
  tempNums = { -2,0,1,1,2 };
  tempDoubleIntVector = No15_threeSum( tempNums );
  PrintDoubleIntVector( tempDoubleIntVector );

  tempNums = {1,1,1,1};
  No16_threeSumClosest( tempNums ,-100);

  bRet = No20_isValid( "()[]{} [ ]a{b}" );

  No22_generateParenthesis( 2 );

  vector<int> nums = { 0,0,1,1,1,2,2,3,3,4 };
  nTest = No26_removeDuplicates( nums );

  nTest = No28_strStr( "hello", "ll" );
  nTest = No28_strStr( "aaaaa", "bba" );
  nTest = No28_strStr( "aaa", "aaa" );
  nTest = No28_strStr( "mississippi", "issip" );


  nums = {1,3,5,6};
  nTest = No35_searchInsert( nums, 6 );

  tempStr = No5_longestPalindrome( "" );
  tempStr = No5_longestPalindrome( "a" );
  tempStr = No5_longestPalindrome( "aa" );
  tempStr = No5_longestPalindrome( "aaaa" );
  tempStr = No5_longestPalindrome( "ac" );
  tempStr = No5_longestPalindrome( "babad" );
  tempStr = No5_longestPalindrome( "cbbd" );
  tempStr = No5_longestPalindrome( "cbbbbbaaad" );

  tempStr = No6_convert( "AB", 2 );

  tempStr = No38_countAndSay( 7 );

  nums = { 2, 3, 1,1,4 };
  nums = { 1, 1,1,1 };
  nums = {1, 2,1,1,1};
  nums = {10,9,8,7,6,5,4,3,2,1,1,0};
  //nTest = No45_jump( nums );

  nums = { 2, -1, 2 };
  nTest = No53_maxSubArray( nums );

  tempStr = "luffy is still joyboy  ";
  No_58_lengthOfLastWord( tempStr );

  nTest = No62_uniquePaths( 3, 2 );
  nTest = No62_uniquePaths( 3, 1 );
  nTest = No62_uniquePaths( 7, 3 );
  nTest = No62_uniquePaths( 1, 1 );
  nTest = No62_uniquePaths( 10, 10 );
  nTest = No62_uniquePaths( 19, 13 );

  tempNums = { 9,9,9 };
  tempNums = No66_plusOne( tempNums );
  PrintIntVector( tempNums );

  tempStr = No67_addBinary( "11", "1" );

  vector<int> prices = { 7,1,5,3,6,4,6 };
  nTest = No121_maxProfit( prices );
  nTest = No122_maxProfit( prices );

  No205_isIsomorphic( "badc", "baba");

  auto strVecor =  No17_letterCombinations( "23" );
  PrintStrVector( strVecor );
}

// プログラムの実行: Ctrl + F5 または [デバッグ] > [デバッグなしで開始] メニュー
// プログラムのデバッグ: F5 または [デバッグ] > [デバッグの開始] メニュー

// 作業を開始するためのヒント: 
//    1. ソリューション エクスプローラー ウィンドウを使用してファイルを追加/管理します 
//   2. チーム エクスプローラー ウィンドウを使用してソース管理に接続します
//   3. 出力ウィンドウを使用して、ビルド出力とその他のメッセージを表示します
//   4. エラー一覧ウィンドウを使用してエラーを表示します
//   5. [プロジェクト] > [新しい項目の追加] と移動して新しいコード ファイルを作成するか、[プロジェクト] > [既存の項目の追加] と移動して既存のコード ファイルをプロジェクトに追加します
//   6. 後ほどこのプロジェクトを再び開く場合、[ファイル] > [開く] > [プロジェクト] と移動して .sln ファイルを選択します
