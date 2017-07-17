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
	pcap_if_t *allDevice; //ã�Ƴ� ����̽��� LinkedList�� ����, �� �� ù ��° ������Ʈ�� ���� ���� ����
	pcap_if_t *device; //Linked List�� ���� ������Ʈ�� ���� ����
	char errorMSG[256]; //���� �޽����� ���� ���� ����
	char counter = 0;

	pcap_t *pickedDev; //����� ����̽��� �����ϴ� ����

					   //1. ��ġ �˻� (ã�Ƴ� ����̽��� LinkedList�� ����)
	if ((pcap_findalldevs(&allDevice, errorMSG)) == -1)//���� �����ÿ��� 1 ����������, pcap_findallDevice�� ���°� ���� ����Ʈ�̹Ƿ� �ּҷ� �־�� ��.
	{											   //pcap_if_t�� int���¸� ��ȯ�ϸ�, -1�� ���� ���, ����̽��� ã�� ������ ����̴�.
		printf("��ġ �˻� ����");
	}
	//2. ��ġ ���
	int count = 0;
	for (device = allDevice; device != NULL; device = device->next)
		//dev�� allDevice�� ù ���� �ּҸ� ������, dev�� ���� NULL(��)�� ��� ����, dev�� �� for���� ���� �ּҰ����� ��ȯ
	{
		printf("%d �� ��Ʈ��ũ\n", count);
		printf("����� ���� : %s\n", device->name);
		printf("����� ���� : %s\n", device->description);
		count = count + 1;
	}
}