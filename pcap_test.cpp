#include<stdio.h>
#include "pcap.h"
#include <WinSock2.h>

typedef struct Ethernet_Header//�̴��� ��� ����ü
{
	u_char des[6];//������ MAC �ּ�
	u_char src[6];//�۽��� MAC �ּ�
	short int ptype;//�ڿ� ���� ��Ŷ�� �������� ����(��:ARP/IP/RARP)
					//IP ����� ���� ��� : 0x0800
}Ethernet_Header;//�θ� �̸� ����(����)

typedef struct ipaddress
{
	u_char ip1;
	u_char ip2;
	u_char ip3;
	u_char ip4;
}ip;

//IP ���������� ����� ������ ����ü ����
typedef struct IPHeader
{
	u_char HeaderLength : 4;//��� ���� *4
	u_char Version : 4;//IP v4 or IPv6
	u_short TotalLength;//��� ���� + ������ ����/
	u_short FlagOffset;//�÷��� + �����׸�Ʈ ������

	ip SenderAddress;
	ip DestinationAddress;

}IPHeader;

void main()
{

}