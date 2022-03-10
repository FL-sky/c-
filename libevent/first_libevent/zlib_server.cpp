#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <string.h>
#ifndef _WIN32
#include <signal.h>
#endif
#include <iostream>
using namespace std;
#define SPORT 5001

bufferevent_filter_result filter_in(
    evbuffer* src, evbuffer* dst, ev_ssize_t dst_limit,
    bufferevent_flush_mode mode, void* ctx)
{
    //1 ���տͻ��˷��͵��ļ���
    char data[1024] = { 0 };
    int len = evbuffer_remove(src, data, sizeof(data) - 1);

    cout << "server recv: " << data << endl;
    evbuffer_add(dst, data, len);

    return BEV_OK;
}

bufferevent_filter_result filter_out(
    evbuffer* src, evbuffer* dst, ev_ssize_t dst_limit,
    bufferevent_flush_mode mode, void* ctx)
{
    return BEV_OK;
}

void read_cb(bufferevent* bev, void* ctx)
{
    //2 �ظ�OK
    bufferevent_write(bev, "OK", 2);
}

void event_cb(bufferevent* bev, short what, void* ctx)
{
}

void listen_cb(struct evconnlistener* e, evutil_socket_t s, struct sockaddr* a, int socklen, void* arg)
{
    cout << "listen_cb" << endl;
    event_base* base = (event_base*)arg;
    //1����һ��bufferevent ����ͨ��
    bufferevent* bev = bufferevent_socket_new(base, s, BEV_OPT_CLOSE_ON_FREE);

    //2��ӹ��� ����������ص�
    bufferevent* bev_filter = bufferevent_filter_new(bev,
        filter_in,
        0,
        BEV_OPT_CLOSE_ON_FREE,
        0,
        0
    );

    ///3���ûص� ��ȡ�¼����������ӶϿ�)
    bufferevent_setcb(bev_filter, read_cb, 0, event_cb, 0);
    bufferevent_enable(bev_filter, EV_READ | EV_WRITE);
}
void Server(event_base* base)
{
    cout << "begin Server" << endl;
    //�����˿�
    //socket ,bind,listen ���¼�
    sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(SPORT);

    evconnlistener* ev = evconnlistener_new_bind(base,
        listen_cb,
        base,
        LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE,
        10,
        (sockaddr*)&sin,
        sizeof(sin));

    /*if (ev)
        evconnlistener_free(ev);*/
}
