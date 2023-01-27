#include<iostream>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
  const int BUF_SIZE = 64;
  int RetVal;
  WSADATA Wsd;
  if( WSAStartup( MAKEWORD( 2, 2 ), &Wsd ) != 0 )
  {
    cout << "初始化套接字动态库失败" << endl;
    return -1;
  }

  SOCKET ServerScoket;
  ServerScoket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( ServerScoket == INVALID_SOCKET )
  {
    cout << "创建套接字失败" << endl;
    WSACleanup();
    return -1;
  }

  SOCKADDR_IN ServerAddr;
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons( 2345 );
  ServerAddr.sin_addr.S_un.S_addr = inet_addr( "127.0.0.1" );
  RetVal = connect( ServerScoket, (SOCKADDR*)&ServerAddr, sizeof( ServerAddr ) );
  if( RetVal == SOCKET_ERROR )
  {
    cout << "链接服务器失败" << endl;
    closesocket( ServerScoket );
    WSACleanup();
    return -1;
  }

  char SendBuff[BUF_SIZE];
  char RECVBuff[BUF_SIZE];
  while( true )
  {
    ZeroMemory( SendBuff, BUF_SIZE );
    cout << "向服务器发送数据" << endl;
    cin >> SendBuff;
    RetVal = send( ServerScoket, SendBuff, strlen( SendBuff ), 0 );
    if( RetVal == SOCKET_ERROR )
    {
      cout << "发送数据失败" << endl;
      closesocket( ServerScoket );
      WSACleanup();
      return -1;
    }
    ZeroMemory( RECVBuff, BUF_SIZE );
    recv( ServerScoket, RECVBuff, BUF_SIZE, 0 );
    cout << endl << "从服务器接收数据:" << RECVBuff << endl;
  }

  closesocket( ServerScoket );
  WSACleanup();
  return 0;
}
