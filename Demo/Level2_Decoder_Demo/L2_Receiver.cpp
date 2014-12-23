#include "L2_Receiver.h"

L2_Receiver::L2_Receiver(Level2_Decoder_Demo* owner)
{
	m_owner=owner;
	m_ip="127.0.0.1";
	m_port=6000;
}

L2_Receiver::~L2_Receiver()
{
#ifdef _WIN32
	WSACleanup();
	closesocket(inet_sock);
#else
	close(inet_sock);
#endif
	delete []m_ip;
	
}

int L2_Receiver::Init()
{
#ifdef _WIN32
	WORD wVersionRequested;  
	WSADATA wsaData;  
	int err;  
		// 启动socket api   
	wVersionRequested = MAKEWORD( 2, 2 );  
	err = WSAStartup( wVersionRequested, &wsaData );  
	if ( err != 0 )  
	{  
		return -1;  
	}  
	if ( LOBYTE( wsaData.wVersion ) != 2 ||  
		HIBYTE( wsaData.wVersion ) != 2 )  
	{  
		WSACleanup( );  
		return -1;   
	}  
	

#else

#endif

	return 0;
}

int L2_Receiver::Connect(int port,char *ip)
{
	if (Init()!=0)
	{
		return -1;
	}

	if (port!=0 && ip!="")
	{
		m_port = port;
		m_ip=ip;
	}
	// 创建socket   
	inet_sock = socket(AF_INET, SOCK_STREAM, 0);  
	if(inet_sock <= 0)  
	{   
		return -1;  
	}  
	sin.sin_family = AF_INET;  
	sin.sin_port = htons(m_port);  
	sin.sin_addr.s_addr = inet_addr(m_ip);  

	//建立和服务器的连接
	if(connect(inet_sock,(sockaddr*)&sin,sizeof(sin))<0)
	{
		printf("建立连接失败！");
		return -1;
	}
	return 0;
}
int L2_Receiver::Start()
{
	char *buffer=new char[BUFFER_SIZE];
	memset(buffer,0,BUFFER_SIZE);
	while(1)
	{
		int length ;
		if((length=recv(inet_sock,buffer,BUFFER_SIZE,0)) < 0)
		{
			printf("接收数据失败\n");
			return -1;
		}
		else
		{
			//printf("%s\n",buffer);
			Level2_Decoder_Demo::L2_Data_Tag data;
			data.buff=new char[length];
			memcpy(data.buff,buffer,length);
			data.lenth=length;
			m_owner->Push(data);
		}
		memset(buffer,0,BUFFER_SIZE);
	}
	delete [] buffer;
	return 0;
}

