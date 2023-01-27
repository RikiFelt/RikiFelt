#include<iostream>
#include "winsock2.h"
#pragma comment(lib,"ws2_32.lib")

using namespace std;

int main()
{
  int RetVal;
  WORD SocketVersion = MAKEWORD( 2, 2 );
  WSADATA wsd;
  if( WSAStartup( SocketVersion, &wsd ) != 0 )
  {
    cout << "绑定Socket库失败" << endl;
  }

  SOCKET ServerSocket;
  ServerSocket = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
  if( ServerSocket == INVALID_SOCKET )
  {
    cout << "创建服务器套接字失败" << endl;
    WSACleanup();
    return -1;
  }

  SOCKADDR_IN ServerAddr;
  ServerAddr.sin_family = AF_INET;
  ServerAddr.sin_port = htons( 2345 );
  ServerAddr.sin_addr.S_un.S_addr = INADDR_ANY;
  RetVal = bind( ServerSocket, (SOCKADDR*)&ServerAddr, sizeof( SOCKADDR_IN ) );
  if( RetVal == SOCKET_ERROR )
  {
    cout << "套接字绑定失败" << endl;
    closesocket( ServerSocket );
    WSACleanup();
    return -1;
  }

  RetVal = listen( ServerSocket, 2 );
  if( RetVal == SOCKET_ERROR )
  {
    cout << "套接字监听失败" << endl;
    closesocket( ServerSocket );
    WSACleanup();
    return -1;
  }

  SOCKET ClientSocket;
  SOCKADDR_IN ClientAddr;
  int ClientAddrLen = sizeof( ClientAddr );
  ClientSocket = accept( ServerSocket, (SOCKADDR*)&ClientAddr, &ClientAddrLen );
  if( ClientSocket == INVALID_SOCKET )
  {
    cout << "接收客户端请求失败" << endl;
    closesocket( ServerSocket );
    WSACleanup();
    return -1;
  }

  char ReceiveBuff[BUFSIZ];
  char SendBuff[BUFSIZ];
  while( true )
  {
    ZeroMemory( ReceiveBuff, BUFSIZ );
    RetVal = recv( ClientSocket, ReceiveBuff, BUFSIZ, 0 );
    if( RetVal == SOCKET_ERROR )
    {
      cout << "接收数据失败" << endl;
      closesocket( ServerSocket );
      closesocket( ClientSocket );
      WSACleanup();
      return -1;
    }

    cout << "接收自客户端数据：" << ReceiveBuff << endl;
    cout << "向客户端发送数据：";
    cin >> SendBuff;
    send( ClientSocket, SendBuff, strlen( SendBuff ), 0 );
  }

  closesocket( ServerSocket );
  closesocket( ClientSocket );
  WSACleanup();
  return 0;
}