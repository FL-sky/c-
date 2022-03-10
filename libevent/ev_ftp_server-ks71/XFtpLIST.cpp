#include "XFtpLIST.h"
#include<string>
#include<iostream>
#include<event2/bufferevent.h>
#include<event2/event.h>
#ifdef _WIN32
#include<io.h>
#endif
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
	else if (type == "CWD") {//切换目录
		//取出命令中的路径
		//CWD test\r\n
		int pos = msg.rfind(" ") + 1;
		//去掉结尾的\r\n
		int sb = 0;
		if (msg[msg.length() - 1] == '\n') {
			++sb;
			if (msg[msg.length() - 2] == '\r')
				++sb;
		}
		string path = msg.substr(pos, msg.size() - pos - sb);

		if (path[0] == '/') {//绝对路径//这句是干嘛的
			cmdTask->curDir = path;
		}
		else {
			if (cmdTask->curDir[cmdTask->curDir.size() - 1] != '/') {
				cmdTask->curDir += "/";
			}
			cmdTask->curDir += path + "/";
			// /test/
		}

		
		ResCMD("250 Directory success changed.\r\n");
	} 
	else if (type == "CDUP") {//回到上层目录

		/**
		* /Debug/test_ser.A3C61E95.tlog 
		* /Debug
		* /Debug/
		*/ 

		string path = cmdTask->curDir;
		//统一去掉结尾的 /
		if (path[path.size() - 1] == '/') {//size 和 length 无区别
			path = path.substr(0, path.size() - 1);
		}
		/** 变成这样了
		* /Debug/test_ser.A3C61E95.tlog
		* /Debug
		*/

		int pos = path.rfind("/");
		path = path.substr(0, pos);
		cmdTask->curDir = path;
		ResCMD("250 Directory success changed.\r\n");//此句不可少
	}
}

std::string  XFtpLIST::GetListData(std::string path) {
	//string listdata = "-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n";
	string data = "";

#ifdef _WIN32
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
#else
	string cmd = "ls -l ";
	cmd += path;
	FILE* f = fopen(cmd.c_str(), "r");
	if (!f) {
		return data;
	}
	for (;;) {
		int len = fread(buf, 1, sizeof(buf) - 1, fp);
		if (len <= 0) {
			break;
		}
		buf[len] = '\0';
	}

#endif
	return data;
}