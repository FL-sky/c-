#include <event2/event.h>
#include<event2/thread.h>
#include<event2/listener.h>
#ifdef _WIN32
#include <signal.h>
#endif
#include <iostream>

using namespace std;

#define SPORT 5001

void listen_cb(struct evconnlistener *ev, evutil_socket_t s, struct sockaddr *addr, int socklen, void *arg) {
	cout << "listen_cb" << endl;
}


int main()
{
#ifdef _WIN32
	//��ʼ��socket��
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	//���Թܵ��źţ��������ݸ��ѹرյ�socket
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

	//��������������
	event_config *conf = event_config_new();

	//��ʾ֧�ֵ�����ģʽ
	const char **methods = event_get_supported_methods();
	cout << "supported_methods:" << endl;
	for (int i = 0; methods[i] != NULL; i++)
	{
		cout << methods[i] << endl; ///windowsֻ��win32
	}

	// ��������
	// ������ EV_FEATURE_FDS �����������޷����ã���windows�� EV_FEATURE_FDS ��Ч

	// event_config_require_features(conf, EV_FEATURE_ET | EV_FEATURE_FDS);
	// event_config_require_features(conf, EV_FEATURE_FDS); // ��֧��epoll

	//��������ģ�ͣ�ʹ��select
	event_config_avoid_method(conf, "epoll");
	event_config_avoid_method(conf, "poll");

	//windows��֧��IOCP���̳߳أ�
#ifdef _WIN32
	event_config_set_flag(conf, EVENT_BASE_FLAG_STARTUP_IOCP);
	//��ʼ��iocp���߳�
	evthread_use_windows_threads();
	//����CPU����
	SYSTEM_INFO	 si;
	GetSystemInfo(&si);
	event_config_set_num_cpus_hint(conf, si.dwNumberOfProcessors);

#endif

	//��ʼ������libevent������
	event_base *base = event_base_new_with_config(conf);
	event_config_free(conf);
	if (!base)
	{
		cerr << "event_base_new_with_config failed!" << endl;
		base = event_base_new();
		if (!base)
		{
			cerr << "event_base_new failed!" << endl;
			return 0;
		}
	}
	else
	{
		//��ȡ��ǰ����ģ��
		cout << "current method is " << event_base_get_method(base) << endl;

		//ȷ�������Ƿ���Ч
		int f = event_base_get_features(base);
		if (f & EV_FEATURE_ET)
			cout << "EV_FEATURE_ET events are supported." << endl;
		else
			cout << "EV_FEATURE_ET events are not supported." << endl;

		if (f & EV_FEATURE_O1)
			cout << "EV_FEATURE_O1 events are supported." << endl;
		else
			cout << "EV_FEATURE_O1 events are not supported." << endl;

		if (f & EV_FEATURE_FDS)
			cout << "EV_FEATURE_FDS events are supported." << endl;
		else
			cout << "EV_FEATURE_FDS events are not supported." << endl;

		if (f & EV_FEATURE_EARLY_CLOSE)
			cout << "EV_FEATURE_EARLY_CLOSE events are supported." << endl;
		else
			cout << "EV_FEATURE_EARLY_CLOSE events are not supported." << endl;
		//cout << "event_base_new_with_config success!" << endl;

		sockaddr_in sin;
		memset(&sin, 0, sizeof(sin));
		sin.sin_family = AF_INET;
		sin.sin_port = htons(SPORT);

		evconnlistener *ev = evconnlistener_new_bind(base, listen_cb, base, 10, LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
			(sockaddr*)&sin, sizeof(sin));
		event_base_dispatch(base);
		evconnlistener_free(ev);
	}
	event_base_free(base);

	return 0;
}