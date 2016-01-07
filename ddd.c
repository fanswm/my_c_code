#include <winsock2.h>
#include <stdio.h> //printf����Ҫ�õ�ͷ�ļ�

#pragma comment(lib,"ws2_32.lib")

void Help(); //������������
int main(int argc, char* argv[])
{
	//��������
	WORD wVersion = MAKEWORD(2,0); //socket�İ汾
	WSADATA wsaData;
	//sockaddr_in�ṹ
	struct sockaddr_in sin;
	int iFromPort; //��ʼ�˿�
	int iToPort; //�����˿�
	int iNowPort; //����ɨ��Ķ˿�
	char* cHost; //Ҫɨ�������
	SOCKET s; //���洴��socketʱ�ķ���ֵ
	int iOpenPort; //���Ŷ˿ڸ���
	
	iOpenPort = 0;
	//����������²�������4��������portscan.exe��������ʾ��ȷ���÷�
	if(argc != 4)
	{
		Help(); //��������
		return -1;
	}
	
	//�����û������Ҫɨ�����ʼ�˿ںͽ����˿�
	//�����û��������char�ͣ�����Ҫ��ת��int��
	iFromPort = atoi(argv[2]);
	iToPort = atoi(argv[3]);
	cHost = argv[1];
	
	//���û�����Ķ˿ڽ����ж�
	if(iFromPort > iToPort || iFromPort < 0 || iFromPort >65535 || iToPort <0 || iToPort >65535)
	{
		printf("��ʼ�˿ڲ��ܴ��ڽ����˿ڣ��ҷ�ΧΪ��1-65535!\n");
		return 0;
	}
	
	if (WSAStartup(wVersion , &wsaData))
	{
		printf("��ʼ��ʧ�ܣ�");
		return -1;
	}
	
	printf("======= ��ʼɨ�� =======\n");
	//ѭ������˿ڣ����ж϶˿��Ƿ񿪷�
	for(iNowPort = iFromPort; iNowPort <= iToPort; iNowPort++)
	{
		s = socket(AF_INET,SOCK_STREAM,0);
		if(s == INVALID_SOCKET)
		{
			printf("����socket()ʧ�ܣ�\n");
			WSACleanup();  
		}

		//���ṹ��Ա��ֵ
		sin.sin_family = AF_INET;
		sin.sin_port = htons(iNowPort);
		sin.sin_addr.S_un.S_addr = inet_addr(cHost);

		//��������
		if(connect(s,(struct sockaddr*)&sin,sizeof(sin)) == SOCKET_ERROR)
		{
			printf("%s -> %d:δ����\n",cHost,iNowPort);  
			closesocket(s);
		}
		else
		{
			printf("%s -> %d:����\n",cHost,iNowPort);
			iOpenPort ++;
			closesocket(s);
		}  
	}
	
	printf("======= ɨ���� =======\n");
	printf("������%s ɨ�赽%d���˿ڿ���",cHost,iOpenPort);
	
	//�ر�socket
	closesocket(s);
	WSACleanup();
	return 0;
}
//����Ϊ������������
void Help()
{
	printf("\nPortScan V1.0 by:������ȥҪ��\n");
	printf("Usage:\n");
	printf("  PortScan.exe <TargetIP> <BeginPort> <EndPort>\n");
	printf("Example:\n");
	printf("  PortScan.exe 127.0.0.1 135 445\n");  
}
