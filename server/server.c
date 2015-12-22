/*********************************************************************
UNIX网络编程，一个简单的时间获取服务器程序
***********************************************************************/
#include <unp.h>
#include <time.h>
int
main(int argc,char **argv)
{
	
	int	listenfd,connfd;
	struct sockaddr_in servaddr;
	char	buff[MAXLINE];
	time_t	ticks;
	
	listenfd = Socket(AF_INET, SOCK_STREAM, 0); //创建TCP套接口 
	bzero(&servaddr, sizeof(servaddr)); //清除结构体
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);  /*daytime server*/
	Bind(listenfd, (SA*) &servaddr, sizeof(servaddr));//捆绑服务器众所周知的端口到套接口
	Listen(listenfd, LISTENQ) ;//把套接口变换成监听套接口
	
	for(; ;)
	{
		connfd = Accept(listenfd, (SA*)NULL,NULL);　//接受客户连接，服务器进程调用accept函数后处于休眠状态，等待单个客户端连接的到达和对内核对它的接受，三路握手建立连接，握手完毕返回值为已连接描述字，该描述字用于与新近连接的客户通信
		ticks = time(NULL);//time返回当前的时间和日期
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));//ctime把整数值变换成直观可读的时间格式．
		Write(connfd,buff,strlen(buff));
		
		Close(connfd);//终止连接
	}
	

}
