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

}