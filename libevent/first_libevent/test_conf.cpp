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
	//初始化socket库
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
#else
	//忽略管道信号，发送数据给已关闭的socket
	if (signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		return 1;
#endif

	//创建配置上下文
	event_config *conf = event_config_new();

	//显示支持的网络模式
	const char **methods = event_get_supported_methods();
	cout << "supported_methods:" << endl;
	for (int i = 0; methods[i] != NULL; i++)
	{
		cout << methods[i] << endl; ///windows只有win32
	}

	// 设置特征
	// 设置了 EV_FEATURE_FDS 其他特征就无法设置，在windows中 EV_FEATURE_FDS 无效

	// event_config_require_features(conf, EV_FEATURE_ET | EV_FEATURE_FDS);
	// event_config_require_features(conf, EV_FEATURE_FDS); // 不支持epoll

	//设置网络模型，使用select
	event_config_avoid_method(conf, "epoll");
	event_config_avoid_method(conf, "poll");

	//windows中支持IOCP（线程池）
#ifdef _WIN32
	event_config_set_flag(conf, EVENT_BASE_FLAG_STARTUP_IOCP);
	//初始化iocp的线程
	evthread_use_windows_threads();
	//设置CPU数量
	SYSTEM_INFO	 si;
	GetSystemInfo(&si);
	event_config_set_num_cpus_hint(conf, si.dwNumberOfProcessors);

#endif

	//初始化配置libevent上下文
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
		//获取当前网络模型
		cout << "current method is " << event_base_get_method(base) << endl;

		//确认特征是否生效
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