//
// Created by root on 18-1-31.
////
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

#include <boost/bind.hpp>
#include <assert.h>
using namespace muduo;
using namespace muduo::net;

class ChatServer{
public:
    ChatServer(EventLoop *loop, const InetAddress& listenAddr):
            server_(loop, listenAddr, "ChatServer"),
            cc(boost::bind(&ChatServer::onStringMessage, this, _1, _2, _3 )),
            connections_(new CnList)                    //这里要改，初始化这个shared_ptr对象
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

        CnListPtr copy_connections = getConnection_();      //引用计数+1
        for(auto const &i: *copy_connections)
            //这里读是直接对列表读操作，而没有互斥量的保护，而且用的是另一个指向该内存的指针，而非原来的指针
            if(i != conn)
                cc.send(i, string);
        //然后结束了，引用-1，因为这个指针是一个栈上的对象
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
        if(!connections_.unique())                              //这里如果有读操作的话
        {
            connections_.reset(new CnList(*connections_));      //这里将connections_ 重定向到一个新开的数据区域
        }

        assert(connections_.unique());
        if(conn->connected())
            //这里两种情况，第一种 是重定向之后的副本，第二种是没有读操作，直接在互斥量保护下进行修改
            connections_->insert(conn);
        else
            connections_->erase(conn);
        //也没有必要再将修改后的拷贝回来了，因为读操作读的只是一个副本，写操作才是本身


    };
    typedef std::set<TcpConnectionPtr> CnList;
    typedef std::shared_ptr<CnList> CnListPtr;

    CnListPtr getConnection_()
    {
        std::lock_guard<std::mutex> lg(mut);
        //用互斥量获取当前的连接列表，因为在获取的时候 防止写对象对connections_对其进行重定向到另一块内存上
        return connections_;
    }
private:

    Codec cc;
    std::mutex mut;
    CnListPtr connections_;
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




