
/*

ServerNet.cpp

*/
#define _CRT_SECURE_NO_WARNINGS


#include"iostream"
#include "fstream"
#include"SocketServer.h"

using namespace std;





/*��������ʼ��*/

int ServerNet::ServerInit(const char* address, int port)

{

	int rlt = 0;



	int iErrorMsg;



	//��ʼ��WinSock

	WSAData wsaData;

	iErrorMsg = WSAStartup(MAKEWORD(1, 1), &wsaData);



	if (iErrorMsg != NO_ERROR)

	{

		//��ʼ��WinSockʧ��

		printf("server wsastartup failed with error : %d\n", iErrorMsg);



		rlt = 1;

		return rlt;

	}



	// ������������socket



	m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_sock == INVALID_SOCKET)

		// ����socket�������쳣

	{

		printf("server socket failed with error: %d\n", WSAGetLastError());

		rlt = 2;

		return rlt;

	}



	// ������Ϣ

	SOCKADDR_IN	servaddr;

	servaddr.sin_family = AF_INET;

	servaddr.sin_port = port;

	servaddr.sin_addr.s_addr = inet_addr(address);



	//��

	iErrorMsg = bind(m_sock, (SOCKADDR*)&servaddr, sizeof(servaddr));

	if (iErrorMsg < 0)

	{

		//��ʧ��

		printf("bind failed with error : %d\n", iErrorMsg);

		rlt = 3;

		return rlt;

	}

	

	return rlt;

}



void ServerNet::ServerRun(int portnum ,const char* Filepath)

{

	// ��������

	listen(m_sock, 5);

	

	SOCKADDR_IN tcpAddr;

	int len = sizeof(sockaddr);

	SOCKET newSocket;

	char buf[1000000];

	int rval;

	


	do

	{

		// ������Ϣ

		newSocket = accept(m_sock, (sockaddr*)&tcpAddr, &len);



		if (newSocket == INVALID_SOCKET)

		{

			// �ǿ���socket

			printf("invalid socket occured.\n");

		}

		else

		{

			// ���õ���socket����

			printf("new socket connect: %d\n", newSocket);

			ofstream outFile;

			char* Filename = (char*)malloc(100);

			sprintf(Filename, "%s\\Result%d.csv", Filepath, portnum);

			outFile.open(Filename, ios::out);

			free(Filename);

			// ��Ϣ����

			do

			{
				SocketPackage Sockrecv;

				//printf("process\n");

				// ��������

				memset(buf, 0, sizeof(buf));

				rval = recv(newSocket, buf, 1000000, 0);

				memcpy(&Sockrecv, buf, sizeof(SocketPackage));

				//if (Sockrecv.Res[0] && Sockrecv.Res[2047]) {
				//printf("Sockpack.CameraNum =%s ,Sockpack.Framecnt =%d ,  Sockpack.Res[0] = %f,Sockpack.Res[2047] = %f\n", Sockrecv.SerialNumber, Sockrecv.Framecnt, Sockrecv.s[1008], Sockrecv.ay[1008]);
				//}

				outFile << Sockrecv.SerialNumber << "," << Sockrecv.Framecnt;
				for (int i = 0; i < 2048; i++)
				{
					outFile << "," << Sockrecv.s[i] << "," << Sockrecv.ay[i];
				}
				outFile << endl;

				//if (rval == SOCKET_ERROR)

				//	// ���쳣ͨ��������δcloseSocket���˳�ʱ

				//{

				//	printf("recv socket error.\n");

				//	break;

				//}



				 if (rval == 0)

					// 0��ʾ�����˳�

					printf("socket %d connect end.\n", newSocket);

				//else

					// ��ʾ���յ�������

					//printf("recv msg: %s\n", buf);

			} while (rval != 0);



			// ���ڽ��յ�socket

			closesocket(newSocket);

		}

	} while (1);



	// �ر�����socket

	closesocket(m_sock);

}
