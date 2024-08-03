//#include <windows.h>
#include <shlobj.h> // SHGetSetFolderCustomSettings
//#include <shlwapi.h>
//#include <iostream>

bool SetFolderIcon( LPCWSTR folderPath, LPCWSTR iconPath )
{
  SHFOLDERCUSTOMSETTINGS fcs = {0};
  fcs.dwSize = sizeof( SHFOLDERCUSTOMSETTINGS );
  fcs.dwMask = FCSM_ICONFILE;
  fcs.pszIconFile = (LPWSTR)iconPath;
  fcs.cchIconFile = 0;
  fcs.iIconIndex = 0;
  HRESULT hr = SHGetSetFolderCustomSettings( &fcs, folderPath, FCS_FORCEWRITE );
  if( FAILED( hr ) )
  {
    return false;
  }
  return true;
}

int main()
{
  LPCWSTR folderPath = L"D:\\a";
  LPCWSTR iconPath = L"D:\\a\\a.ico";
  SetFolderIcon( folderPath, iconPath );

  return 0;
}
