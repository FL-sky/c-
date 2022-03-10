#include "XFtpLIST.h"
#include<string>
#include<iostream>
#include<event2/bufferevent.h>
#include<event2/event.h>
#include<io.h>
using namespace std;

void XFtpLIST::Write(struct bufferevent* bev) {
	// 4. 发送完成 回应226
	ResCMD("226 Transfer complete\r\n");
	// 5. 关闭连接
	Close();

}
void XFtpLIST::Event(struct bufferevent* bev, short what) {
	//如果对方网络断掉，或者机器死机有可能收不到BEV_EVENT_EOF数据
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT" << endl;

		Close();
		//bufferevent_free(bev);
		//this->bev = 0;
		////delete this; 只有当客户端被清理的时候，ta会被同步清理
	}
	else if (what & BEV_EVENT_CONNECTED) {
		cout << "XFtpLIST BEV_EVENT_CONNECTED" << endl;
	}
}

//解析协议
void XFtpLIST::Parse(std::string type, std::string msg) {
	string resmsg = "";
	if (type == "PWD") {
		//257 "/" is current directory.
		resmsg = "257 \"";
		resmsg += cmdTask->curDir;
		resmsg += "\" is current dir.\r\n";
 		ResCMD(resmsg);
	}
	else if (type == "LIST") {
		/*	
		*	1. 连接数据通道
		*	2. 150回应
		*	3. 发送目录数据通道
		*	4. 发送完成 回应226
		*	5. 关闭连接
		*/
		//命令通道回复消息 使用数据通道发送目录
		//-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n
		// 
		// 1. 连接数据通道
		ConnectPORT();
		// 2. 150回应
		ResCMD("150 Here comes the directory listing. \r\n");

		//string listdata = "-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n";
		// 3. 发送目录数据通道
		string listdata = GetListData(cmdTask->rootDir + cmdTask->curDir);
		//curDir;

		Send(listdata);

	}
}

std::string  XFtpLIST::GetListData(std::string path) {
	//string listdata = "-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n";
	string data = "";
	//存储文件信息
	_finddata_t file;
	//目录上下文
	path += "/*.*";
	intptr_t dir = _findfirst(path.c_str(), &file);
	if (dir < 0) {
		return data;
	}
	do {
		string tmp = "";
		//是否是目录 去掉 . ..
		if (file.attrib & _A_SUBDIR) {
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
				continue;
			}
			tmp = "drwxrwxrwx 1 root group ";
		}
		else {
			tmp = "-rwxrwxrwx 1 root group ";
		}
		//文件大小
		char buf[1024];
		sprintf(buf, "%u ", file.size);
		tmp += buf;

		//日期时间
		strftime(buf, sizeof(buf) - 1, "%b %d %H:%M ", localtime(&file.time_write));
		tmp += buf;
		tmp += file.name;
		tmp += "\r\n";

		data += tmp;


	} while (_findnext(dir, &file) == 0);

	return data;
}