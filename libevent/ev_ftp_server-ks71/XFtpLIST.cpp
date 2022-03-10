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
	// 4. ������� ��Ӧ226
	ResCMD("226 Transfer complete\r\n");
	// 5. �ر�����
	Close();

}
void XFtpLIST::Event(struct bufferevent* bev, short what) {
	//����Է�����ϵ������߻��������п����ղ���BEV_EVENT_EOF����
	if (what & (BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT))
	{
		cout << "BEV_EVENT_EOF | BEV_EVENT_ERROR | EV_TIMEOUT" << endl;

		Close();
		//bufferevent_free(bev);
		//this->bev = 0;
		////delete this; ֻ�е��ͻ��˱������ʱ��ta�ᱻͬ������
	}
	else if (what & BEV_EVENT_CONNECTED) {
		cout << "XFtpLIST BEV_EVENT_CONNECTED" << endl;
	}
}

//����Э��
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
		*	1. ��������ͨ��
		*	2. 150��Ӧ
		*	3. ����Ŀ¼����ͨ��
		*	4. ������� ��Ӧ226
		*	5. �ر�����
		*/
		//����ͨ���ظ���Ϣ ʹ������ͨ������Ŀ¼
		//-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n
		// 
		// 1. ��������ͨ��
		ConnectPORT();
		// 2. 150��Ӧ
		ResCMD("150 Here comes the directory listing. \r\n");

		//string listdata = "-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n";
		// 3. ����Ŀ¼����ͨ��
		string listdata = GetListData(cmdTask->rootDir + cmdTask->curDir);
		//curDir;

		Send(listdata);

	}
	else if (type == "CWD") {//�л�Ŀ¼
		//ȡ�������е�·��
		//CWD test\r\n
		int pos = msg.rfind(" ") + 1;
		//ȥ����β��\r\n
		int sb = 0;
		if (msg[msg.length() - 1] == '\n') {
			++sb;
			if (msg[msg.length() - 2] == '\r')
				++sb;
		}
		string path = msg.substr(pos, msg.size() - pos - sb);

		if (path[0] == '/') {//����·��//����Ǹ����
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
	else if (type == "CDUP") {//�ص��ϲ�Ŀ¼

		/**
		* /Debug/test_ser.A3C61E95.tlog 
		* /Debug
		* /Debug/
		*/ 

		string path = cmdTask->curDir;
		//ͳһȥ����β�� /
		if (path[path.size() - 1] == '/') {//size �� length ������
			path = path.substr(0, path.size() - 1);
		}
		/** ���������
		* /Debug/test_ser.A3C61E95.tlog
		* /Debug
		*/

		int pos = path.rfind("/");
		path = path.substr(0, pos);
		cmdTask->curDir = path;
		ResCMD("250 Directory success changed.\r\n");//�˾䲻����
	}
}

std::string  XFtpLIST::GetListData(std::string path) {
	//string listdata = "-rwxrwxrwx 1 root group 64463 Mar 14 09:53 101.jpg\r\n";
	string data = "";

#ifdef _WIN32
	//�洢�ļ���Ϣ
	_finddata_t file;
	//Ŀ¼������
	path += "/*.*";
	intptr_t dir = _findfirst(path.c_str(), &file);
	if (dir < 0) {
		return data;
	}
	do {
		string tmp = "";
		//�Ƿ���Ŀ¼ ȥ�� . ..
		if (file.attrib & _A_SUBDIR) {
			if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0) {
				continue;
			}
			tmp = "drwxrwxrwx 1 root group ";
		}
		else {
			tmp = "-rwxrwxrwx 1 root group ";
		}
		//�ļ���С
		char buf[1024];
		sprintf(buf, "%u ", file.size);
		tmp += buf;

		//����ʱ��
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