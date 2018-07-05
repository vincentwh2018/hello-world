#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>

int send_sip_msg (char *msg)
{
   int sockfd = -1;
   struct sockaddr_in sockaddr;

   memset (&sockaddr, 0, sizeof (struct sockaddr_in));
   sockaddr.sin_family = AF_INET;
   sockaddr.sin_port = htons (5060);
   sockaddr.sin_addr.s_addr = inet_addr("192.168.10.118");

   sockfd = socket (sockaddr.sin_family, SOCK_DGRAM, 0);
   if (sockfd < 0)
   {
      printf ("create socket error\n");
      return -1;
   }
   if (connect(sockfd, (struct sockaddr *) &sockaddr,
	sizeof (struct sockaddr_in)) < 0)
   {
      printf ("connect error\n");
      close (sockfd);
      return -1;
   }

   int ret = write (sockfd, msg, strlen (msg));
   if (ret != strlen(msg))
   {
	printf ("send %d\n bytes..\n");
   }

   close(sockfd);
   return 1;
}



int main()
{
#if 0
char sipmsg[] = "INVITE sip:3001@192.168.10.161;transport=udp;user=phone SIP/2.0\r\n\
Via: SIP/2.0/UDP 192.168.10.85:5060;branch=z9hG4bK11295343100000000274.\r\n\
From: <sip:1022@192.168.10.161;user=phone>;tag=44bcc1a8-1c4b6-d95e4a70\r\n\
To: <sip:3001@192.168.10.161;user=phone>\r\n\
Call-ID: 44BCC1A8-00000040@ynzc1pcu-255\r\n\
CSeq: 1 INVITE\r\n\
Accept: application/sdp,application/isup,multipart/mixed,application/vnd.siemens.key-event,application/vnd.siemens.surpass\r\n\
Contact: <sip:1022@192.168.10.161:5060;transport=udp>\r\n\
MIME-Version: 1.0\r\n\
Supported: timer\r\n\
Supported: 100rel\r\n\
Max-Forwards: 70\r\n\
P-Asserted-Identity: <sip:1022@192.168.10.161:5060;user=phone>\r\n\
Allow: ACK,INFO,BYE,CANCEL,INVITE,OPTIONS,NOTIFY,PRACK,UPDATE\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 1085\r\n\
\r\n\
v=0\r\n\
o=hiQ9200/CN0/106/012/044 1065420060618131032 1779171372 IN IP4 192.168.10.85\r\n\
s=Phone Call via hiQ9200 SIPCA\r\n\
c=IN IP4 193.158.156.83\r\n\
t=0 0\r\n\
m=audio 39064 RTP/AVP 8 0 4 18 102 2 96 100\r\n\
a=rtpmap:8 PCMA/8000\r\n\
a=fmtp:8 vad=no\r\n\
a=rtpmap:0 PCMU/8000\r\n\
a=fmtp:0 vad=no\r\n\
a=rtpmap:4 G723/8000\r\n\
a=fmtp:4 annexa=no\r\n\
a=rtpmap:18 G729/8000\r\n\
a=fmtp:18 annexb=no\r\n\
a=rtpmap:102 G726-32/8000\r\n\
a=fmtp:102 vad=no\r\n\
a=rtpmap:2 G726-32/8000\r\n\
a=fmtp:2 vad=no\r\n\
a=rtpmap:96 G726-24/8000\r\n\
a=fmtp:96 vad=no\r\n\
a=rtpmap:100 telephone-event/8000\r\n\
a=fmtp:100 0-15\r\n\
a=sqn: 0\r\n\
a=cdsc: 1 audio RTP/AVP 8 0 4 18 102 2 96 100\r\n\
a=cpar: a=rtpmap:8 PCMA/8000\r\n\
a=cpar: a=fmtp:8 vad=no\r\n\
a=cpar: a=rtpmap:0 PCMU/8000\r\n\
a=cpar: a=fmtp:0 vad=no\r\n\
a=cpar: a=rtpmap:4 G723/8000\r\n\
a=cpar: a=fmtp:4 annexa=no\r\n\
a=cpar: a=rtpmap:18 G729/8000\r\n\
a=cpar: a=fmtp:18 annexb=no\r\n\
a=cpar: a=rtpmap:102 G726-32/8000\r\n\
a=cpar: a=fmtp:102 vad=no\r\n\
a=cpar: a=rtpmap:2 G726-32/8000\r\n\
a=cpar: a=fmtp:2 vad=no\r\n\
a=cpar: a=rtpmap:96 G726-24/8000\r\n\
a=cpar: a=fmtp:96 vad=no\r\n\
a=cpar: a=rtpmap:100 telephone-event/8000\r\n\
a=cpar: a=fmtp:100 0-15\r\n\
a=sendrecv\r\n\
m=video 16544 RTP/AVP 115 34\r\n\
a=fmtp:115 QCIF=1 CIF=1 MAXBR=1960\r\n\
a=fmtp:34 QCIF=1 CIF=1 MAXBR=1960\r\n\
a=rtpmap:115 H263-1998/90000\r\n\
a=rtpmap:34 H263/90000\r\n\
a=sendrecv\r\n\
a=x-rtp-session-id:54A9E6606A6242998EC1DD55CD158121\r\n";
#endif

#if 0
char sipmsg[] = "INVITE sip:3001@192.168.10.161:5060 SIP/2.0\r\n\
Via: SIP/2.0/UDP 192.168.10.120:5060;branch=z9hG4bK00d4qc102ghgga8l53c1.1\r\n\
From: <sip:4001@192.168.10.161>;tag=SD7rede01-0082-00001019-0063\r\n\
To: <sip:3001@192.168.10.161>\r\n\
Call-ID: SD7rede01-c7510d20aeed55581177b92d9e1bd107-h24fmi3\r\n\
CSeq: 1 INVITE\r\n\
Max-Forwards: 25\r\n\
Contact: <sip:4001@192.168.10.161:5060;transport=udp>\r\n\
Proxy-Require: privacy\r\n\
Allow: INVITE,REGISTER,ACK,OPTIONS,BYE,INFO,REFER,NOTIFY,SUBSCRIBE,MESSAGE,CANCEL,PRACK,UPDATE\r\n\
Supported: timer\r\n\
P-Charging-Vector: icid-value=65053NeNB8ktNrH8zxd1176297207@vpsle11a\r\n\
P-DCS-Billing-Info: 461cdef6000146f8@81.144.103.4\r\n\
P-Presented-Identity: <anonymous@anonymous.invalid>\r\n\
Session-Expires: 900\r\n\
Min-SE: 450\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 486\r\n\
\r\n\
v=0\r\n\
o=- 2 2 IN IP4 194.102.31.71\r\n\
s=<BT Softphone 1.5>\r\n\
c=IN IP4 194.102.31.71\r\n\
t=0 0\r\n\
m=audio 16542 RTP/AVP 96 18 0 101\r\n\
a=fmtp:101 0-15\r\n\
a=rtpmap:96 AMR-WB/16000\r\n\
a=rtpmap:101 telephone-event/8000\r\n\
a=sendrecv\r\n\
a=x-rtp-session-id:2C35E69C867E4791B9B5FA4EB020DD61\r\n\
m=video 16544 RTP/AVP 115 34\r\n\
a=fmtp:115 QCIF=1 CIF=1 MAXBR=1960\r\n\
a=fmtp:34 QCIF=1 CIF=1 MAXBR=1960\r\n\
a=rtpmap:115 H263-1998/90000\r\n\
a=rtpmap:34 H263/90000\r\n\
a=sendrecv\r\n\
a=x-rtp-session-id:54A9E6606A6242998EC1DD55CD158121\r\n\
Route: 192.168.10.161\r\n";
#endif


#if 0
char sipmsg[] = "INVITE sip:3001@192.168.10.161:5060 SIP/2.0\r\n\
Via: SIP/2.0/UDP 192.168.10.161:5060;branch=z9hG4bKdvl7e630503gfbs9s4s1.1\r\n\
From: <sip:4001@192.168.10.161>;tag=SD7rede01-0082-00001019-0063\r\n\
To: <sip:3001@192.168.10.161>\r\n\
Call-ID: SDu4m0801-43bf6d545a297e73de1dbba460eaa5a1-h24fmi0\r\n\
CSeq: 1 INVITE\r\n\
Max-Forwards: 25\r\n\
Contact: <sip:194.102.31.75:5060;transport=udp>\r\n\
Allow: INVITE,REGISTER,ACK,OPTIONS,BYE,INFO,REFER,NOTIFY,SUBSCRIBE,MESSAGE,CANCEL,PRACK,UPDATE\r\n\
Supported: timer\r\n\
P-Charging-Vector: icid-value=2587RSTzNHCjNHnrEtN1176714789@vpsle11a\r\n\
P-DCS-Billing-Info: 46233e2500000516@81.144.103.4\r\n\
P-Presented-Identity: <anonymous@anonymous.invalid>\r\n\
Session-Expires: 900\r\n\
Min-SE: 450\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 236\r\n\
\r\n\
v=0\r\n\
o=- 2 2 IN IP4 194.102.31.75\r\n\
s=<BT Softphone 1.5>\r\n\
c=IN IP4 194.102.31.75\r\n\
t=0 0\r\n\
m=audio 14240 RTP/AVP 8 0 101\r\n\
a=fmtp:101 0-15\r\n\
a=rtpmap:101 telephone-event/8000\r\n\
a=sendrecv\r\n\
a=x-rtp-session-id:1DB6A94F3C864E379C7E659058E090E0\r\n";
#endif

#if 0
char sipmsg[] = "INVITE sip:3001@192.168.10.161:5060 SIP/2.0\r\n\
Via: SIP/2.0/UDP 192.168.10.161:5060;branch=z9hG4bKcr617j302g9gcbk9k001.1\r\n\
From: <sip:4001@192.168.10.161;user=phone>;tag=SDt7lve01-0082-00002dbe-0d8b\r\n\
To: <sip:3001@192.168.10.161:5060>\r\n\
Call-ID: SDt7lve01-5cad9cecae02a349edfdc6b7eb05cd60-h24fmi0\r\n\
CSeq: 1 INVITE\r\n\
Max-Forwards: 24\r\n\
Contact: <sip:4001@182.168.10.161:5060;transport=udp>\r\n\
Accept: application/dtmf-relay,x-application/dtmf-relay,application/sdp\r\n\
Allow: INVITE,REGISTER,ACK,OPTIONS,BYE,INFO,REFER,NOTIFY,SUBSCRIBE,MESSAGE,CANCEL,PRACK,UPDATE\r\n\
Supported: timer,replaces,100rel\r\n\
P-Charging-Vector: icid-value=8970uLUJLYVm3vsCYpF1176476268@vpsle11a\r\n\
P-Asserted-Identity: <sip:+445600704104@btsip.bt.com;user=phone>\r\n\
P-DCS-Billing-Info: 461f9a6b00017ad2@81.144.103.4\r\n\
Session-Expires: 900\r\n\
Min-SE: 450\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 207\r\n\
\r\n\
v=0\r\n\
o=BTHH 946702338 946702338 IN IP4 194.102.31.75\r\n\
s=-\r\n\
c=IN IP4 194.102.31.75\r\n\
t=0 0\r\n\
m=audio 14100 RTP/AVP 18 8 0 101\r\n\
a=rtpmap:101 telephone-event/8000\r\n\
a=ptime:20\r\n\
a=SilenceSupp:off\r\n\
a=fmtp:101 0-15\r\n";
#endif

#if 0
char sipmsg[] = "INVITE sip:3001@192.168.10.161:5060 SIP/2.0\r\n\
Via: SIP/2.0/UDP 192.168.10.161:5060;branch=z9hG4bKcr617j302g9gcbk9k001.1\r\n\
From: \"NULL\"<sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk;user=phone>;tag=SDt7lve01-0082-00002dbe-0d8b\r\n\
To: \"3001\" <sip:3001@192.168.10.161:5060>\r\n\
Call-ID: SDt7lve01-5cad9cecae02a349edfdc6b7eb05cd60-h24fmi0\r\n\
CSeq: 1 INVITE\r\n\
Max-Forwards: 24\r\n\
Contact: <sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk:5060;transport=udp>\r\n\
Accept: application/dtmf-relay,x-application/dtmf-relay,application/sdp\r\n\
Allow: INVITE,REGISTER,ACK,OPTIONS,BYE,INFO,REFER,NOTIFY,SUBSCRIBE,MESSAGE,CANCEL,PRACK,UPDATE\r\n\
Supported: timer,replaces,100rel\r\n\
P-Charging-Vector: icid-value=8970uLUJLYVm3vsCYpF1176476268@vpsle11a\r\n\
P-Asserted-Identity: <sip:4005@btsip.bt.com;user=phone>\r\n\
P-DCS-Billing-Info: 461f9a6b00017ad2@81.144.103.4\r\n\
Session-Expires: 900\r\n\
Min-SE: 450\r\n\
Content-Type: application/sdp\r\n\
Content-Length: 203\r\n\
\r\n\
v=0\r\n\
o=BTHH 946702338 946702338 IN IP4 194.102.31.75\r\n\
s=-\r\n\
c=IN IP4 194.102.31.75\r\n\
t=0 0\r\n\
m=audio 14100 RTP/AVP 20 101\r\n\
a=rtpmap:101 telephone-event/8000\r\n\
a=ptime:20\r\n\
a=SilenceSupp:off\r\n\
a=fmtp:101 0-15\r\n";
#endif

char sipmsg[]="INVITE sip:3001@192.168.10.161:5060 SIP/2.0\r\n\
Via: SIP/2.0/UDP  sia-tdcbtsCA146.ipt.ip.tele.dk:5060;branch=z9hG4bK_11461552360444447057\r\n\
From: \"NULL\"<sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk;user=phone>;tag=1_1146_f155236_5f44\r\n\
To: <sip:3001@192.168.10.161;user=phone>\r\n\
Call-ID: 1257411435@sia-tdcbtsCA146.ipt.ip.tele.dk\r\n\
CSeq: 1       INVITE\r\n\
Max-Forwards: 70\r\n\
Supported: 100rel,timer\r\n\
Contact: <sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk:5060;transport=udp>\r\n\
Allow: INVITE,ACK,BYE,CANCEL,OPTIONS,REGISTER,INFO,PRACK,SUBSCRIBE,NOTIFY,REFER,UPDATE\r\n\
Min-SE: 900..Session-Expires: 1800;refresher=uac\r\n\
Alert-Info: <file://Bellcore-dr1>\r\n\
User-Agent: BTS10200/900-04.05.01.V24 (SIA)\r\n\
Content-Length:    288\r\n\
Content-Type: application/sdp\r\n\
\r\n\
v=0\r\n\
o=- 3592102 0 IN IP4 194.239.116.12\r\n\
s=Cisco SDP 0\r\n\
c=IN IP4 194.239.116.12\r\n\
t=0 0\r\n\
m=audio 18832 RTP/AVP 8 18 100\r\n\
a=rtpmap:100 X-NSE/8000\r\n\
a=fmtp:100 200-202\r\n\
a=sqn:0\r\n\
a=cdsc:1 audio RTP/AVP 100\r\n\
a=cpar:a=rtpmap:100 X-NSE/8000\r\n\
a=cpar:a=fmtp:100 200-202\r\n\
a=cdsc:2 image udptl t38\r\n";

   //printf("sip msg: \n%s\n", sipmsg);
   send_sip_msg(sipmsg);
   return 0;
}

/*
To: <sip:44641122@sia-tdcbtsCA146.ipt.ip.tele.dk;user=phone>

Contact: <sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk:5060;transport=udp>

From: "NULL"<sip:20153316@sia-tdcbtsCA146.ipt.ip.tele.dk;user=phone>
*/
