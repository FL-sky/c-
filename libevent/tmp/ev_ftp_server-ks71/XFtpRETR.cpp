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
		Close();///�ƺ�û��close�ͻᳬʱ����ʧ��
		return;
	}
	cout << "[" << len << "]" << flush;
	Send(buf, len);
}

void XFtpRETR::Event(struct bufferevent* bev, short what) {
	//����Է�����ϵ������߻��������п����ղ���BEV_EVENT_EOF����
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT" << endl;

		Close();
	}
	else if (what & BEV_EVENT_CONNECTED) {
		cout << "XFtpRETR BEV_EVENT_CONNECTED" << endl;
	}
}

//����Э��
void XFtpRETR::Parse(std::string type, std::string msg) {
	//�ļ���
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
		//��������ͨ��
		ConnectPORT();

		//���Ϳ�ʼ�����ļ���ָ��
		ResCMD("150 File OK\r\n");

		////����д���¼�
		bufferevent_trigger(bev, EV_WRITE, 0);
	}
	else {
		//string msg = "";
		ResCMD("450 file open failed!\r\n");
		//����д���¼�

	}

}