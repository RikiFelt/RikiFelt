#include "ExcelOperator.h"

int main( int, int )
{
  ExcelOperator ope;
  ope.New();
  // ope.Open( L"D:\\a.xlsx" );
  ope.Fill();
  // ope.Save(); // Not Work!
  ope.SaveAs( L"D:\\b.xlsx" );
  ope.Quit();

  return 0;
}