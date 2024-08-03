#pragma once

struct IDispatch;

class ExcelOperator
{
public:
  ExcelOperator() = default;
  ~ExcelOperator() = default;

public:
  void New();

  void Open( const wchar_t* filename );

  void Fill();

  void Save();

  void SaveAs( const wchar_t* filename );

  void Quit();

private:
  int Initialize();

  void Uninitialize();

private:
  IDispatch* ExecuteGet( IDispatch* parent, const wchar_t* funcname );

  IDispatch* ExecuteGet( IDispatch* parent, const wchar_t* funcname, long vt_i4 );

  IDispatch* ExecuteGet( IDispatch* parent, const wchar_t* funcname, const wchar_t* vt_bstr );

  void ExecutePut( IDispatch* parent, const wchar_t* funcname, long vt_i4 );

  void ExecuteMethod( IDispatch* parent, const wchar_t* funcname );

  void ExecuteMethod( IDispatch* parent, const wchar_t* funcname, const wchar_t* vt_bstr );

  IDispatch* Execute( int method, IDispatch* parent, const wchar_t* funcname, long* vt_i4, const wchar_t* vt_bstr );

private:
  IDispatch* pXlApp = nullptr;
  IDispatch* pXlBooks = nullptr;
  IDispatch* pXlBook = nullptr;
  IDispatch* pXlSheet = nullptr;
};

