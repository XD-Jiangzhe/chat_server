//
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
#include <boost/bind.hpp>

using namespace muduo;
using namespace muduo::net;

class ChatServer{
public:
    ChatServer(EventLoop *loop, const InetAddress& listenAddr):
                server_(loop, listenAddr, "ChatServer"),
                cc(boost::bind(&ChatServer::onStringMessage, this, _1, _2, _3 ))
    {
        server_.setConnectionCallback(boost::bind(&ChatServer::onConnection,this, _1 ));        //这里是将server的回调设置为chatserver的回调
        server_.setMessageCallback(boost::bind(&ChatServer::onMessage, this, _1, _2, _3));            //一有数据就回调codec的解码函数
    }

    void setiothreadnum(int threadnum)
    {
        server_.setThreadNum(threadnum);
    }

    void start()
    {
        server_.start();
    }

    void onStringMessage(const TcpConnectionPtr& conn, string &string, Timestamp arrival)
    {
        LOG_INFO<<"send string"<<string;
        std::lock_guard<std::mutex> lg(mut);
        for(auto const& i: connections_)
            if(i != conn)
                cc.send(i, string);
        //向中间层发送数据，然后进行编码再发送给客户端,然后每个conn发送string
    }

    void onMessage(const TcpConnectionPtr& conn, Buffer *buffer, Timestamp arrival)
    {
        cc.OnMessage(conn, buffer, arrival);
        //这里将数据发送给cc进行解码，然后cc内部调用onStringMessage 将解码好的再发送回去？
    };

    void onConnection(const TcpConnectionPtr& conn)
    {
        std::lock_guard<std::mutex> lg(mut);
        if(conn->connected())
        {
            connections_.insert(conn);
            std::cout<<connections_.size()<<std::endl;
        }
        else
            connections_.erase(conn);

    };
private:

    Codec cc;
    std::mutex mut;
    std::set<TcpConnectionPtr> connections_;
    TcpServer server_;
};

int main()
{
    EventLoop loop;
    ChatServer chatserver(&loop, InetAddress(2018));
    chatserver.setiothreadnum(10);
    chatserver.start();
    loop.loop();
    return 0;
}
