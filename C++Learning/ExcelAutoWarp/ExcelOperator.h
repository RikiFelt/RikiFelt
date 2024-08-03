#pragma once

#include <wtypes.h> // LPCWSTR

struct IDispatch;

class ExcelOperator
{
public:
  ExcelOperator() = default;
  ~ExcelOperator() = default;

public:
  void New();

  void Open( LPCWSTR filename );

  void Fill();

  void Save();

  void SaveAs( LPCWSTR filename );

  void Quit();

private:
  int Initialize();

  void Uninitialize();

private:
  IDispatch* ExecuteGet( IDispatch* parent, LPCWSTR func );

  IDispatch* ExecuteGet( IDispatch* parent, LPCWSTR func, long vt_i4 );

  IDispatch* ExecuteGet( IDispatch* parent, LPCWSTR func, LPCWSTR vt_bstr );

  void ExecutePut( IDispatch* parent, LPCWSTR func, long vt_i4 );

  void ExecuteMethod( IDispatch* parent, LPCWSTR func );

  void ExecuteMethod( IDispatch* parent, LPCWSTR func, LPCWSTR vt_bstr );

  IDispatch* Execute( int method, IDispatch* parent, LPCWSTR func, long* vt_i4, LPCWSTR vt_bstr );

private:
  IDispatch* pXlApp = nullptr;
  IDispatch* pXlBooks = nullptr;
  IDispatch* pXlBook = nullptr;
  IDispatch* pXlSheet = nullptr;
};

