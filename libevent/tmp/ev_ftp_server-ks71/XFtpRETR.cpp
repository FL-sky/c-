#include "XFtpRETR.h"
#include<string>
#include<iostream>
#include<event2/bufferevent.h>
#include<event2/event.h>
//#include<io.h>
using namespace std;


void XFtpRETR::Write(struct bufferevent* bev) {
	if (!fp) {
		return;
	}
	int len = fread(buf, 1, sizeof(buf), fp);
	if (len <= 0) {
		//fclose(fp);
		//fp = 0;
		ResCMD("226 Transfer complete\r\n");
		Close();///似乎没有close就会超时下载失败
		return;
	}
	cout << "[" << len << "]" << flush;
	Send(buf, len);
}

void XFtpRETR::Event(struct bufferevent* bev, short what) {
	//如果对方网络断掉，或者机器死机有可能收不到BEV_EVENT_EOF数据
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT" << endl;

		Close();
	}
	else if (what & BEV_EVENT_CONNECTED) {
		cout << "XFtpRETR BEV_EVENT_CONNECTED" << endl;
	}
}

//解析协议
void XFtpRETR::Parse(std::string type, std::string msg) {
	//文件名
	int pos = msg.rfind(" ") + 1;
	string filename = msg.substr(pos, msg.size() - pos - 2);
	string path = cmdTask->rootDir;
	path += cmdTask->curDir;
	char ch = cmdTask->curDir[cmdTask->curDir.length() - 1];
	if (ch != '/' && ch != '\\') {
		path += "/";
	}
	path += filename;
	fp = fopen(path.c_str(), "rb");
	if (fp) {
		//连接数据通道
		ConnectPORT();

		//发送开始下载文件的指令
		ResCMD("150 File OK\r\n");

		////触发写入事件
		bufferevent_trigger(bev, EV_WRITE, 0);
	}
	else {
		//string msg = "";
		ResCMD("450 file open failed!\r\n");
		//激活写入事件

	}

}