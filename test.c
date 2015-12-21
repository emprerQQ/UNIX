
#include "unp.h"

int
main (int argc, char **argv)
{
	int 	sockfd, n;
	char 	recvline[MAXLINE+1];
	struct sockaddr_in servaddr;
	
	if (argc != 2)
		err_quit("usage: a.out <IPaddress>");

	if ((sockfd = socket(AF_INET, SOCK_STREAM,0)) <0)
//socket函数创建网际(AF_INET)字节流（SOCK_STREAM）套接口，它是TCP套接口的特色名字，该函数返回一个小整数描述字，用它来标识套接口
		err_sys("socket error");

	bzero(&servaddr, sizeof(servaddr));  
//bzero将整个结构清零
	servaddr.sin_family = AF_INET;           //地址族
	servaddr.sin_port = htons(13);
//htons(主机到网络短整数)变换二进制端口号的字节序
	if (inet_pton(AF_INET,argv[1],&servaddr.sin_addr) <= 0)
		err_quit("inet_pton error for % s",argv[1]);
//inet_pton(表达式到数值)

	if (connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) <0)
		err_sys("connect error");
//connect函数跟由它的第二个参数指定的套接口地址结构对应的服务器

	while ( (n = read(sockfd, recvline, MAXLINE)) >0)
	{
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
		err_sys("fputs error");
	}
	if (n<0)
		err_sys("read error");
	exit(0);

}
