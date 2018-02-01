//
// Created by root on 18-1-31.
////
// Created by root on 18-1-30.
//
#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/EventLoop.h>
#include "Codec.hpp"
#include <set>
#include <iostream>
#include <mutex>
#include <memory>
#include <functional>
#include <muduo/base/ThreadLocalSingleton.h>


#include <assert.h>
using namespace muduo;
using namespace muduo::net;
using namespace std::placeholders;
class ChatServer {
public:
    typedef std::set<TcpConnectionPtr> CnList;
    typedef ThreadLocalSingleton<CnList> LocalConnections;

    ChatServer(EventLoop *loop, const InetAddress& listenaddr):
            server_(loop, listenaddr, "chat_server"),
            cc(std::bind(&ChatServer::onStringMessage, this, std::placeholders::_1,std::placeholders::_2,std::placeholders::_3))
    {
        server_.setMessageCallback(std::bind(&Codec::OnMessage, &cc, _1 ,_2, _3));
        server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));
    }
    void setthreadnum(int numthreads)
    {
        server_.setThreadNum(numthreads);
    }

    void start()
    {
        server_.setThreadInitCallback(std::bind(&ChatServer::threadInit, this, _1));    //这里初始化每个io线程，即将 io线程放到一个 io线程列表中
        server_.start();
    }

private:
    void onStringMessage(const TcpConnectionPtr& conn, const string& message, Timestamp arrival)
    {
        EventLoop::Functor f = std::bind(&ChatServer::distribute, this, message);
        std::lock_guard<std::mutex> lg(mut);
        for(auto const& i : loops)
            i->queueInLoop(f);          //这里将 分发 消息放到 eventloop 中去，让每个io线程按照自己的 connections 列表来进行分发
    }

    void onConnection(const TcpConnectionPtr& conn)
    //这里设计的时候是这样的，就是 分开多个io线程之后，连接在io主线程中被分给底下的多个io线程的时候才会调用
    //底下io线程的connectEstablished 函数会回调 connectioncallback 这里就 添加到了底下io线程中的 connections 列表中
    //这个列表是 线程独有的，每个线程中都有这个 列表。但是每个线程都不一样
    {
        if(conn->connected())
            LocalConnections::instance().insert(conn);          //这里将每个conn放到一个自己io线程的连接列表中
        else
            LocalConnections::instance().erase(conn);
    }

    void distribute(string& msg)
    {
        for(auto const &i : LocalConnections::instance())
        {
            cc.send(i, msg);
        }
        LOG_INFO<<"distribute out";
    }

    void threadInit(EventLoop* loop)
    {
        LocalConnections::instance();   //这里初始化 这个cnlist 对象，即new 一个新的对象
        std::lock_guard<std::mutex> lg(mut);
        loops.insert(loop);
        //将初始化的当前的 loop 放到loops列表中
    }
    std::mutex mut;
    std::set<EventLoop*> loops;

    TcpServer server_;
    Codec cc;

};
int main()
{
    EventLoop loop;
    InetAddress serveraddr(2018);

    ChatServer chatserver(&loop, serveraddr);
    chatserver.setthreadnum(10);

    chatserver.start();
    loop.loop();
    return 0;
}

