#pragma warning(disable:4996)

#include<stdio.h>
#include<string.h>
#include<WinSock2.h>
#include<io.h>
#pragma comment(lib, "ws2_32.lib")

void error_die(const char* str) {
	printf("[hint]%s failed:%d", str, WSAGetLastError()); 
	exit(-1);
}

void initSocket() {
	//参数1:指定socket版本使用最新的2.2版本即可//参数2:是一个穿出参数
	WORD version = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (0 != WSAStartup(version, &wsadata)) {
		error_die("WSAStartup");
	}
}

SOCKET listenClient() {
	//2, 创建socket 相当于买手机, 买了手机有没有电话号码?没有, 怎么办?
	//参数1:指定ip协议 ipv4->AF_INET  ipv6->AF_INET6
	// 参数2:数据传输格式常用的有两种流式传输数据报传输
	//参数3:传输协议 TCP UDP
	SOCKET serfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serfd == INVALID_SOCKET)
	{
		error_die("socket");
	}

	//3, 绑定ip地址和端口号―没有电话号码, 就买电话卡, 插入手机, 手机就可以打电话了
	//参数1:指定的socket	手机
	//参数2:IP地址和端口号	电话号码 有两个结构体
	//参数3:				手机号码长度
	struct sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;//必须和创建socket的时候一样
								 //大端存储和小端存储htons把本地字节序转为网络字节序
	serAddr.sin_port = htons(80);
	//[O-65536) 0-1024是系统保留端口号, 咱们
	char sip[] = "192.168.1.41";
	//serAddr.sin_addr.S_un.S_addr = INADDR_ANY;//绑定本机任意Ip地址
	serAddr.sin_addr.S_un.S_addr = inet_addr(sip);
	if (SOCKET_ERROR == bind(serfd, (struct sockaddr*)&serAddr, sizeof(serAddr))) {
		error_die("bind");
	}

	//4, 监听等电话
	listen(serfd, 10);

	return serfd;
}

void sendHtml(SOCKET clifd, const char* filePath) {
	FILE* pr = fopen(filePath, "r");

	if (pr == NULL) {
		error_die("fopen");
	}
	char data[1024] = "";
	do {
		fgets(data, 1024, pr);//只读一次, 要读完需要使用循环
		send(clifd, data, strlen(data), 0);
	} while (!feof(pr));

	fclose(pr);
}
void notFind(SOCKET clifd) {
	/*
1,发送404错误
HTTP/1.0 404 NOT FOUND
2,加点图片
*/
	char sendBuf[1024];
	sprintf(sendBuf, "HTTP/1.0 404 NOT FOUND\r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);
	sprintf(sendBuf, "Content-type:text/html \r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);
	sprintf(sendBuf, "\r\n");
	send(clifd, sendBuf, strlen(sendBuf), 0);
	sprintf(sendBuf, "<html><body><h1>大家好, 我是顽石老师, 非常高兴和大家一起学习</h1></body></html>");
	send(clifd, sendBuf, strlen(sendBuf), 0);

}

void accept_request(SOCKET clifd) {
	//从clifd接受数据
	char recvBuf[1024] = "";
	if (recv(clifd, recvBuf, sizeof(recvBuf), 0) <= 0)
		error_die("recv offline");
	printf("recvBuf : %s \n", recvBuf);

	//给客户端发送网页
	char fstr[][128] = { "mengzhuye.html","dongfangcaifu.html","tencent.html","youku.html" };
	char filePath[128] = "htmlFiles/";//随机选择一个网页发送
	int tl = strlen(filePath);
	int rd = rand() % 4;
	strcpy(filePath + tl, fstr[rd]);
		//判断文件是否存在fopen以只读的方式打开, 看能否打开成功
	if (access(filePath, 0) == 0)//0 代表判断文件是否存在如过存在返回0否则返回-1
	{
		//发送网页
		sendHtml(clifd,  filePath);
	}
	else {
		//发送404 not find 错误
		notFind(clifd);
	}

}

int main() {

	//1, 初始化网络库wsa
	//windows socket ansyc->windows异步套接字
	initSocket();
	
	SOCKET serfd = listenClient();

	printf("欢迎使用maye的http服务器\n");
	//5, 接受链接来电话了, 就可以接听了,可以获取来电的电话号码和地址
	struct sockaddr_in cliAddr;
	int len = sizeof(cliAddr);
	int cnt = 0;
	while (1) {
		SOCKET clifd = accept(serfd, (struct sockaddr*)&cliAddr, &len); ///阻塞的
		if (clifd == INVALID_SOCKET)
		{
			error_die("accept");
		}

		printf("have a new connect...%d\n", ++cnt);
		//6, 处理链接请求
	//直接给客户端发送文本
		//char sendData[1024] = "<html><body><h1>大家好, 我是顽石老师, 非常高兴和大家一起学习</h1></body></html>";
		//send(clifd, sendData, strlen(sendData), 0);
		accept_request(clifd);

		closesocket(clifd);
	}
	//7, 关闭连接, 清理网络库
	
	closesocket(serfd);//关闭连接关闭通话
	WSACleanup();



	return 0;
}