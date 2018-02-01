//
// Created by root on 18-1-30.
//
#include <muduo/net/TcpClient.h>
#include <muduo/net/TcpConnection.h>
#include "Codec.hpp"
#include <muduo/net/EventLoopThread.h>

#include <mutex>
#include <boost/bind.hpp>
#include <functional>

#include <unistd.h>
#include <stdio.h>
#include <iostream>
using namespace muduo;
using namespace muduo::net;

namespace muduo
{
    namespace net
    {
        class chat_client
        {
        public:
            chat_client(EventLoop *loop, const InetAddress &addr):
                    tcl_(loop, addr, "ChatClient"),
                    cc(std::bind(&chat_client::onStringMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3))
            {
                tcl_.setConnectionCallback(std::bind(&chat_client::onConnection, this, std::placeholders::_1));
                tcl_.setMessageCallback(std::bind(&Codec::OnMessage, &cc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
                //取数据的时候直接触发中间codec的消息到来事件，来判断是否已经收到了一条完整的请求
                //连接建立的时候将连接放到 connection_列表中
            }
            void onStringMessage(const TcpConnectionPtr &conn, string &string, Timestamp arrival)
            {
                std::cout<<string<<std::endl;
                //这里直接回显，收到了已经解析好的数据
            }

            void onConnection(const TcpConnectionPtr &conn)
            {
                std::lock_guard<std::mutex> lg(mut);
                if(conn->connected())       //这里需要保护conn,因为主线程也要向conn发送未编码的数据
                    connection_ = conn;
                else
                    connection_.reset();
            }

            void write(string s)
            {
                std::lock_guard<std::mutex> lg(mut);        //这个接口是给其他线程的，所以有多个线程可以访问该数据成员，要加锁
                cc.send(connection_, s);
            }

            void connect()
            {
                tcl_.connect();
            }

            void disconnect()
            {
                tcl_.disconnect();
            }
        private:
            std::mutex mut;
            TcpConnectionPtr connection_;
            TcpClient tcl_;
            Codec cc;

        };
    }
}
using namespace muduo;
using namespace muduo::net;

int main()
{
    EventLoopThread loopthread;
    chat_client cct(loopthread.startLoop(), InetAddress(2018));     //这里创建了一个chat_client 对象，在一个新开的线程中运行
    cct.connect();

    std::string line;
    while(std::getline(std::cin, line))               //主线程中收集信息
    {
        cct.write(string(line.begin(), line.end()));
    }

    cct.disconnect();
    return 0;
}