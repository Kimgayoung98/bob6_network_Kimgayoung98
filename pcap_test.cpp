#include<stdio.h>
#include "pcap.h"
#include <WinSock2.h>

void packet_handler(u_char *param, const struct pcap_pkthdr *h, const u_char *data);

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
	//3. ��Ʈ��ũ ī�带 �����ϰ� ���õ� ����̽��� ������ ��Ŷ �����ϱ�
	printf("��Ŷ�� ������ ��Ʈ��ũ�� ���� �ϼ��� : ");
	device = allDevice;//ī�带 �������� �ʰ� �׳� ù ��° ī��� ��������.

	int choice;
	scanf_s("%d", &choice);
	for (count = 0; count < choice; count++)
	{
		device = device->next;
	}

	//��Ʈ��ũ ��ġ�� ����, ������ ��Ŷ ���� �����Ѵ�.
	pickedDev = pcap_open_live(device->name, 65536, 0, 1000, errorMSG);
	//��ī���� �̸�, ������ ��Ŷ ũ��(�ִ� 65536), ���ι̽�ť����(��Ŷ ���� ���) ����, ��Ŷ ��� �ð�, ���� ������ ������ ����)

	//4. ��ī�� ����Ʈ ������ ������ �޸𸮸� ����ش�.
	pcap_freealldevs(allDevice);

	//5. ������ ��Ʈ��ũ ī�忡�� ��Ŷ�� ���� ĸ�� �� �Լ��� ����� ĸ�ĸ� �����Ѵ�.
	pcap_loop(pickedDev, 0, packet_handler, NULL);
}

//�Ʒ����� ����� �� �ֵ�����Ŷ �ڵ鷯�� �����.
void packet_handler(u_char *param, const struct pcap_pkthdr *h, const u_char *data)
//���� = �Ķ����, ��Ŷ ���, ��Ŷ ������(������ MAC �ּ� �κ� ����)
{
#define IPHEADER 0x0800
	//�ҽ� ���� �� �������� ���� ����� ���ڷ� �ٲ۴�.

	Ethernet_Header *EH = (Ethernet_Header *)data;//data �ּҿ� ����� 14byte �����Ͱ� ����ü Ethernet_Header ���·� EH�� ����ȴ�.
	short int type = ntohs(EH->ptype);
	//EH->ptype�� �� ����� ������ ���ϹǷ�,
	//�̸� ��Ʋ ����� �������� ��ȯ(ntohs �Լ�)�Ͽ� type�� �����Ѵ�.
	printf("���� ��Ŷ : %04x\n", EH->ptype);
}
