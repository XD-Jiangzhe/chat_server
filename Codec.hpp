//
// Created by root on 18-1-30.
//
#ifndef CHAT_SERVER_CODEC_HPP
#define CHAT_SERVER_CODEC_HPP

#include <muduo/net/TcpServer.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/net/Buffer.h>
#include <muduo/base/Timestamp.h>
#include <muduo/base/Logging.h>

#include <functional>
#include <sys/types.h>
#include <arpa/inet.h>

using namespace muduo;
using namespace muduo::net;
class Codec
        {
        public:

            typedef std::function<void(const TcpConnectionPtr&, string& message, Timestamp  )> StringMessageCallback;
            explicit  Codec(const StringMessageCallback& cb_):cb(cb_){}

            void OnMessage(const TcpConnectionPtr&, Buffer*, Timestamp );
            void send(const TcpConnectionPtr&, string&);

        private:

            StringMessageCallback cb;
            int len_header = sizeof(int);
        };

        void Codec::OnMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp arrival)
        {
            while(buf->readableBytes() >= len_header)
            {
                const char* begin = buf->peek();
                //int be32 = *reinterpret_cast<int*>(const_cast<char*>(begin));
                int be32 = *reinterpret_cast<const int*>(begin);
                //这里要先将begin的const去掉，要么转成const int,转指针类型要用reinterpret_cast类型
                int len = ntohl(be32);
                if(len > 65536 || len <0)
                {
                    LOG_ERROR<<"Invalid length"<<len;
                    conn->shutdown();
                    //如果接收的长度是错误的， 就将该客户端关闭
                    break;
                } else
                {
                    if(buf->readableBytes()-len_header < len)
                    {
                        break;
                    } else
                    {
                        buf->retrieve(static_cast<size_t>(len_header));
                        string sendmsg(buf->retrieveAsString(static_cast<size_t>(len)));
                        cb(conn, sendmsg, arrival);
                        //这里将解码好的字符串发送给接收方
                        //LOG_INFO<<"send msg to server"<<sendmsg;
                    }
                }
            }
        }

        void  Codec::send(const TcpConnectionPtr& conn, string& sendmsg)
        {
            Buffer buf;
            int len = sendmsg.size();
            //LOG_INFO<<"sendmsg "<<sendmsg;
            int32_t  be32 = htonl(len);
            buf.append(sendmsg.data(), sendmsg.size());
            buf.prepend(&be32, sizeof(be32));       //在头部加的信息
            conn->send(&buf);
        }


#endif //CHAT_SERVER_CODEC_HPP
