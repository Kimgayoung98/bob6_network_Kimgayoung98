#include<stdio.h>
#include "pcap.h"
#include <WinSock2.h>

typedef struct Ethernet_Header//이더넷 헤더 구조체
{
	u_char des[6];//수신자 MAC 주소
	u_char src[6];//송신자 MAC 주소
	short int ptype;//뒤에 나올 패킷의 프로토콜 종류(예:ARP/IP/RARP)
					//IP 헤더가 오는 경우 : 0x0800
}Ethernet_Header;//부를 이름 선언(별명)

typedef struct ipaddress
{
	u_char ip1;
	u_char ip2;
	u_char ip3;
	u_char ip4;
}ip;

//IP 프로토콜의 헤더를 저장할 구조체 정의
typedef struct IPHeader
{
	u_char HeaderLength : 4;//헤더 길이 *4
	u_char Version : 4;//IP v4 or IPv6
	u_short TotalLength;//헤더 길이 + 데이터 길이/
	u_short FlagOffset;//플래그 + 프래그먼트 오프셋

	ip SenderAddress;
	ip DestinationAddress;

}IPHeader;

void main()
{
	pcap_if_t *allDevice; //찾아낸 디바이스를 LinkedList로 묶고, 그 중 첫 번째 오브젝트를 담을 변수 생성
	pcap_if_t *device; //Linked List의 다음 오브젝트를 담을 공간
	char errorMSG[256]; //에러 메시지를 담을 변수 생성
	char counter = 0;

	pcap_t *pickedDev; //사용할 디바이스를 저장하는 변수

					   //1. 장치 검색 (찾아낸 디바이스를 LinkedList로 묶음)
	if ((pcap_findalldevs(&allDevice, errorMSG)) == -1)//변수 생성시에는 1 포인터지만, pcap_findallDevice에 쓰는건 더블 포인트이므로 주소로 주어야 함.
	{											   //pcap_if_t는 int형태를 반환하며, -1이 나올 경우, 디바이스를 찾지 못했을 경우이다.
		printf("장치 검색 오류");
	}
	//2. 장치 출력
	int count = 0;
	for (device = allDevice; device != NULL; device = device->next)
		//dev에 allDevice의 첫 시작 주소를 넣으며, dev의 값이 NULL(끝)일 경우 종료, dev는 매 for마다 다음 주소값으로 전환
	{
		printf("%d 번 네트워크\n", count);
		printf("어댑터 정보 : %s\n", device->name);
		printf("어댑터 설명 : %s\n", device->description);
		count = count + 1;
	}
}