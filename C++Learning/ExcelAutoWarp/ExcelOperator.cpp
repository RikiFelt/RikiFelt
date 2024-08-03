#include <ole2.h> // OLE2 Definitions

#include "ExcelOperator.h"

using namespace std;

// AutoWrap() - Automation helper function...
HRESULT AutoWrap( int autoType, VARIANT* pvResult, IDispatch* pDisp, LPOLESTR ptName, int cArgs... )
{
  // Begin variable-argument list...
  va_list marker;
  va_start( marker, cArgs );

  if( !pDisp )
  {
    MessageBox( NULL, "NULL IDispatch passed to AutoWrap()", "Error", 0x10010 );
    _exit( 0 );
  }

  // Variables used...
  DISPPARAMS dp = {NULL, NULL, 0, 0};
  DISPID dispidNamed = DISPID_PROPERTYPUT;
  DISPID dispID;
  HRESULT hr;
  char buf[200];
  char szName[200];

  // Convert down to ANSI
  WideCharToMultiByte( CP_ACP, 0, ptName, -1, szName, 256, NULL, NULL );

  // Get DISPID for name passed...
  hr = pDisp->GetIDsOfNames( IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID );
  if( FAILED( hr ) )
  {
    // sprintf( buf, "IDispatch::GetIDsOfNames(\"%s\") failed w/err 0x%08lx", szName, hr );
    MessageBox( NULL, buf, "AutoWrap()", 0x10010 );
    _exit( 0 );
    return hr;
  }

  // Allocate memory for arguments...
  VARIANT* pArgs = new VARIANT[cArgs + 1];
  // Extract arguments...
  for( int i = 0; i < cArgs; i++ )
  {
    pArgs[i] = va_arg( marker, VARIANT );
  }

  // Build DISPPARAMS
  dp.cArgs = cArgs;
  dp.rgvarg = pArgs;

  // Handle special-case for property-puts!
  if( autoType & DISPATCH_PROPERTYPUT )
  {
    dp.cNamedArgs = 1;
    dp.rgdispidNamedArgs = &dispidNamed;
  }

  // Make the call!
  hr = pDisp->Invoke( dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL );
  if( FAILED( hr ) )
  {
    // sprintf( buf, "IDispatch::Invoke(\"%s\"=%08lx) failed w/err 0x%08lx", szName, dispID, hr );
    MessageBox( NULL, buf, "AutoWrap()", 0x10010 );
    _exit( 0 );
    return hr;
  }
  // End variable-argument section...
  va_end( marker );

  delete[] pArgs;

  return hr;
}

void ExcelOperator::New()
{
  if( pXlApp ) return;
  else Initialize();

  // Call Workbooks.Add() to get a new workbook...
  pXlBook = ExecuteGet( pXlBooks, L"Add" );

  // Get ActiveSheet object
  pXlSheet = ExecuteGet( pXlApp, L"ActiveSheet" );
}

void ExcelOperator::Open( LPCWSTR filename )
{
  if( pXlApp ) return;
  else Initialize();

  // Open Book
  pXlBook = ExecuteGet( pXlBooks, L"Open", filename );

  // Get ActiveSheet object
  pXlSheet = ExecuteGet( pXlApp, L"ActiveSheet" );
}

void ExcelOperator::Fill()
{
  // Get Range object for the Range A1:O15...
  IDispatch* pXlRange = ExecuteGet( pXlSheet, L"Range", L"A1:O15" );

  if( pXlRange )
  {
    // Create a 15x15 safearray of variants...
    VARIANT arr;
    arr.vt = VT_ARRAY | VT_VARIANT;
    {
      SAFEARRAYBOUND sab[2];
      sab[0].lLbound = 1; sab[0].cElements = 15;
      sab[1].lLbound = 1; sab[1].cElements = 15;
      arr.parray = SafeArrayCreate( VT_VARIANT, 2, sab );
    }

    // Fill safearray with some values...
    for( int i = 1; i <= 15; i++ )
    {
      for( int j = 1; j <= 15; j++ )
      {
        // Create entry value for (i,j)
        VARIANT tmp;
        tmp.vt = VT_I4;
        tmp.lVal = i * j;
        // Add to safearray...
        long indices[] = {i,j};
        SafeArrayPutElement( arr.parray, indices, (void*)&tmp );
      }
    }

    // Set range with our safearray...
    WCHAR func[] = {L"Value"};
    AutoWrap( DISPATCH_PROPERTYPUT, NULL, pXlRange, func, 1, arr );
    VariantClear( &arr );
    if( pXlRange ) pXlRange->Release();
  }
}

void ExcelOperator::Save()
{
  // Save Book, Not work!
  ExecutePut( pXlBook, L"Saved", 1 );
}

void ExcelOperator::SaveAs( LPCWSTR filename )
{
  ExecuteMethod( pXlSheet, L"SaveAs", filename );
}

void ExcelOperator::Quit()
{
  ExecuteMethod( pXlApp, L"Quit" );

  Uninitialize();
}

int ExcelOperator::Initialize()
{
  // Initialize COM for this thread...
  CoInitialize( NULL );

  // Get CLSID for our server...
  CLSID clsid;
  HRESULT hr = CLSIDFromProgID( L"Excel.Application", &clsid );

  if( FAILED( hr ) )
  {

    ::MessageBox( NULL, "CLSIDFromProgID() failed", "Error", 0x10010 );
    return -1;
  }

  // Start server and get IDispatch...
  hr = CoCreateInstance( clsid, NULL, CLSCTX_LOCAL_SERVER, IID_IDispatch, (void**)&pXlApp );
  if( FAILED( hr ) )
  {
    ::MessageBox( NULL, "Excel not registered properly", "Error", 0x10010 );
    return -2;
  }

  // Make it visible (i.e. app.visible = 1)
  ExecutePut( pXlApp, L"Visible", 1 );

  // Get Workbooks collection
  pXlBooks = ExecuteGet( pXlApp, L"Workbooks" );

  return 0;
}

void ExcelOperator::Uninitialize()
{
  // Release references...
  if( pXlSheet ) pXlSheet->Release();
  if( pXlBook ) pXlBook->Release();
  if( pXlBooks ) pXlBooks->Release();
  if( pXlApp ) pXlApp->Release();

  // Uninitialize COM for this thread...
  CoUninitialize();
}

IDispatch* ExcelOperator::ExecuteGet( IDispatch* parent, LPCWSTR func )
{
  return Execute( DISPATCH_PROPERTYGET, parent, func, nullptr, nullptr );
}

IDispatch* ExcelOperator::ExecuteGet( IDispatch* parent, LPCWSTR func, long vt_i4 )
{
  return Execute( DISPATCH_PROPERTYGET, parent, func, &vt_i4, nullptr );
}

IDispatch* ExcelOperator::ExecuteGet( IDispatch* parent, LPCWSTR func, LPCWSTR vt_bstr )
{
  return Execute( DISPATCH_PROPERTYGET, parent, func, nullptr, vt_bstr );
}

void ExcelOperator::ExecutePut( IDispatch* parent, LPCWSTR func, long vt_i4 )
{
  Execute( DISPATCH_PROPERTYPUT, parent, func, &vt_i4, nullptr );
}

void ExcelOperator::ExecuteMethod( IDispatch* parent, LPCWSTR func )
{
  Execute( DISPATCH_METHOD, parent, func, nullptr, nullptr );
}

void ExcelOperator::ExecuteMethod( IDispatch* parent, LPCWSTR func, LPCWSTR vt_bstr )
{
  Execute( DISPATCH_METHOD, parent, func, nullptr, vt_bstr );
}

IDispatch* ExcelOperator::Execute( int method, IDispatch* parent, LPCWSTR func, long* vt_i4, LPCWSTR vt_bstr )
{
  IDispatch* child = nullptr;
  if( parent )
  {
    VARIANT result;
    VariantInit( &result );

    if( vt_i4 )
    {
      VARIANT param;
      param.vt = VT_I4;
      param.lVal = *vt_i4;
      AutoWrap( method, &result, parent, (LPWSTR)func, 1, param );
    }
    else if( vt_bstr )
    {
      VARIANT param;
      param.vt = VT_BSTR;
      param.bstrVal = ::SysAllocString( vt_bstr );
      AutoWrap( method, &result, parent, (LPWSTR)func, 1, param );
    }
    else
    {
      AutoWrap( method, &result, parent, (LPWSTR)func, 0 );
    }

    child = result.pdispVal;
  }
  return child;;
}
