#pragma once
/*

ServerNet.h

����ˣ�����Socket����������Ķ˿ںź͵�ַ���󶨵�Socket��ʹ��Listen�򿪼�����

Ȼ�󲻶���Acceptȥ�鿴�Ƿ������ӣ�����У�����Socket����ͨ��Recv��ȡ��Ϣ�����ݣ�

ͨ����ɺ����CloseSocket�ر������ӦAccept����Socket�����������Ҫ�ȴ��κοͻ������ӣ���ô��CloseSocket�رյ������Socket

*/





#include<stdio.h>

#include<windows.h>

#include "fstream"

using namespace std;



#pragma comment(lib, "Ws2_32.lib")

typedef struct {

	unsigned char SerialNumber[64];
	int Framecnt;
	float s[2048];
	float ay[2048];

}SocketPackage;



class ServerNet

{

private:

	SOCKET m_sock;



public:

	//  ��ʼ��������

	int ServerInit(const char* address, int port);



	// ��������

	void ServerRun(int portnum ,const char* Filepath);

};

