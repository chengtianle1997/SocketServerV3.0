

#include"cmdline.h"
#include"thread"
#include"SocketServer.h"

//#include "string"
//#include <stdlib.h>

//using namespace std;

const char* FilePath = "C:\\CalResult";

ServerNet serverNet1;
ServerNet serverNet2;
ServerNet serverNet3;
ServerNet serverNet4;
ServerNet serverNet5;
ServerNet serverNet6;
ServerNet serverNet7;
ServerNet serverNet8;
ServerNet serverNet9;
ServerNet serverNet10;

int ServerPort = 8001;
const char* ServerAddr = "127.0.0.1";

void ServerRun1()
{
	serverNet1.ServerRun(1, FilePath);
}

void ServerRun2()
{
	serverNet2.ServerRun(2, FilePath);
}

void ServerRun3()
{
	serverNet3.ServerRun(3, FilePath);
}

void ServerRun4()
{
	serverNet4.ServerRun(4, FilePath);
}

void ServerRun5()
{
	serverNet5.ServerRun(5, FilePath);
}

void ServerRun6()
{
	serverNet6.ServerRun(6, FilePath);
}

void ServerRun7()
{
	serverNet7.ServerRun(7, FilePath);
}

void ServerRun8()
{
	serverNet8.ServerRun(8, FilePath);
}

void ServerRun9()
{
	serverNet9.ServerRun(9, FilePath);
}

void ServerRun10()
{
	serverNet10.ServerRun(10, FilePath);
}

int CreateFolder(const char* Filepath)
{
	int ret = CreateDirectory(Filepath, NULL);
	if (!ret)
	{
		printf("Create directory failed!\n");
	}
	return ret;
}

int main(int argc, char* argv[])
{
	

	cmdline::parser args;

	//ClientParam
	args.add<UINT>("serverport", 's', "ServerPort", false, 8001, cmdline::range(0, 65535));
	args.add<std::string>("ssar", '\0', "ServerAddress", false, "127.0.0.1");
	args.add<std::string>("filepath", 'p', "CSVFileSavedAddress", false, "C:\\CalResult");
	args.parse_check(argc, argv);

	//input serverport from cmdline
	if (args.exist("serverport"))
	{
		//int ServerPort;
		ServerPort = args.get<UINT>("serverport");
	}
	//input serveraddr from cmdline
	if (args.exist("ssar"))
	{
		ServerAddr = args.get<std::string>("ssar").data();
	}
	//input filepath
	if (args.exist("filepath"))
	{
		FilePath = args.get<std::string>("filepath").data();
	}

	CreateFolder(FilePath);

	printf("ServerPort:%d\n", ServerPort);

	printf("ServerAddr:%s\n", ServerAddr);



	int iRlt = serverNet1.ServerInit(ServerAddr, ServerPort);

	iRlt = serverNet2.ServerInit(ServerAddr, ServerPort + 1);
	

	iRlt = serverNet3.ServerInit(ServerAddr, ServerPort + 2);

	iRlt = serverNet4.ServerInit(ServerAddr, ServerPort + 3);

	iRlt = serverNet5.ServerInit(ServerAddr, ServerPort + 4);

	iRlt = serverNet6.ServerInit(ServerAddr, ServerPort + 5);

	iRlt = serverNet7.ServerInit(ServerAddr, ServerPort + 6);

	iRlt = serverNet8.ServerInit(ServerAddr, ServerPort + 7);

	iRlt = serverNet9.ServerInit(ServerAddr, ServerPort + 8);

	iRlt = serverNet10.ServerInit(ServerAddr, ServerPort + 9);

	if (iRlt == 0)

	{

		printf("server init successful.\n");

		std::thread th1(ServerRun1);
		//th1.detach();
		std::thread th2(ServerRun2);
		//th2.detach();
		std::thread th3(ServerRun3);
		//th3.detach();
		std::thread th4(ServerRun4);
		//th4.detach();
		std::thread th5(ServerRun5);
		//th5.detach();
		std::thread th6(ServerRun6);
		//th6.detach();
		std::thread th7(ServerRun7);
		//th7.detach();
		std::thread th8(ServerRun8);
		//th8.detach();
		std::thread th9(ServerRun9);
		//th9.detach();
		std::thread th10(ServerRun10);
		//th10.detach();


		th1.join();
		th2.join();
		th3.join();
		th4.join();
		th5.join();
		th6.join();
		th7.join();
		th8.join();
		th9.join();
		th10.join();

		//serverNet1.ServerRun();
		//serverNet2.ServerRun();

	}

	else

		printf("server init failed with error: %d\n", iRlt);

	//system("pause");

	return 0;
}
