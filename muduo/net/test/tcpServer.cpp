/*======================================================
    > File Name: tcpServer.cpp
    > Author: MiaoShuai
    > E-mail:  
    > Other :  
    > Created Time: 2015年11月22日 星期日 17时36分22秒
 =======================================================*/

#include <stdio.h>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/InetAddress.h>
#include <muduo/net/TcpConnection.h>
#include <muduo/base/Timestamp.h>
#include <muduo/net/Buffer.h>

//新来连接和其断开时调用
void connectionCallback(const muduo::net::TcpConnectionPtr &)
{
    printf("111\n");
}

//收到消息时调用
void messageCallback(const muduo::net::TcpConnectionPtr &,muduo::net::Buffer *,muduo::Timestamp)
{
    printf("222\n");
}
//给客户端写完成时调用
void writeCompleteCallback(const muduo::net::TcpConnectionPtr &)
{
    printf("333\n");
}



int main(int argc,char **argv)
{
    muduo::net::EventLoop loop;
    muduo::net::InetAddress listenAddr("127.0.0.1",static_cast<uint16_t>(atoi(argv[1])));
    
    muduo::net::TcpServer server(&loop,listenAddr,"tcpServer",muduo::net::TcpServer::kReusePort);  //设置为重用端口
    //设置给新连接的各种回调
    server.setConnectionCallback(connectionCallback);
    server.setMessageCallback(messageCallback);
    server.setWriteCompleteCallback(writeCompleteCallback);

    server.start();
       
    loop.loop();

    return 0;
}
