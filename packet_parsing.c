#include <stdlib.h>
#include <stdio.h>
#include <pcap.h>
#include <arpa/inet.h>
#define MAXSIZE 65535

/* Ethernet header */
struct ethheader {
  u_char  ether_dhost[6]; /* destination host address */
  u_char  ether_shost[6]; /* source host address */
  u_short ether_type;     /* protocol type (IP, ARP, RARP, etc) */
};

/* IP Header */
struct ipheader {
  unsigned char      iph_ihl:4, //IP header length
                     iph_ver:4; //IP version
  unsigned char      iph_tos; //Type of service
  unsigned short int iph_len; //IP Packet length (data + header)
  unsigned short int iph_ident; //Identification
  unsigned short int iph_flag:3, //Fragmentation flags
                     iph_offset:13; //Flags offset
  unsigned char      iph_ttl; //Time to Live
  unsigned char      iph_protocol; //Protocol type
  unsigned short int iph_chksum; //IP datagram checksum
  struct  in_addr    iph_sourceip; //Source IP address
  struct  in_addr    iph_destip;   //Destination IP address
};

/*TCP protocol*/
struct tcpheader {
    unsigned short int tcph_srcport;    // Source port
    unsigned short int tcph_destport;   // Destination port
    unsigned int       tcph_seqnum;     // Sequence Number
    unsigned int       tcph_acknum;     // Acknowledgment Number
    unsigned char      tcph_reserved:4, tcph_offset:4; // Data offset + Reserved
    unsigned char      tcph_flags;      // TCP flags (URG, ACK, PSH, RST, SYN, FIN)
    unsigned short int tcph_win;        // Window size
    unsigned short int tcph_checksum;   // Checksum
    unsigned short int tcph_urgptr;     // Urgent pointer
};

void got_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *packet)
{
    struct ethheader *eth = (struct ethheader *)packet;

    if (ntohs(eth->ether_type) == 0x0800) { // 0x0800 is IP type
        struct ipheader *ip = (struct ipheader *)(packet + sizeof(struct ethheader));

        if (ip->iph_protocol == IPPROTO_TCP) { // Check if the protocol is TCP
            struct tcpheader *tcp = (struct tcpheader *)(packet + sizeof(struct ethheader) + (ip->iph_ihl << 2));
	    
	    // Calculate the TCP data offset in bytes
	    int data_offset = (tcp->tcph_offset >> 4) * 4;

	    // Calculate the total length of the TCP packet
	    int tcp_packet_length = ntohs(ip->iph_len) - (ip->iph_ihl << 2) - data_offset;
	    
	    printf("Ethernet header, src mac: %02X:%02X:%02X:%02X:%02X:%02X\n",
    	    eth->ether_shost[0], eth->ether_shost[1], eth->ether_shost[2],
    	    eth->ether_shost[3], eth->ether_shost[4], eth->ether_shost[5]);

	    printf("Ethernet header, dst mac: %02X:%02X:%02X:%02X:%02X:%02X\n",
    	    eth->ether_dhost[0], eth->ether_dhost[1], eth->ether_dhost[2],
    	    eth->ether_dhost[3], eth->ether_dhost[4], eth->ether_dhost[5]);
            
	    printf("IP Header, src ip: %s\n", inet_ntoa(ip->iph_sourceip));
            printf("IP Header, dst ip: %s\n", inet_ntoa(ip->iph_destip));
            
	    printf("TCP Header, src port: %d\n", ntohs(tcp->tcph_srcport));
            printf("TCP Header, dst port:  %d\n", ntohs(tcp->tcph_destport));

    	    // Calculate the length of the TCP data
    	    int data_length = tcp_packet_length - data_offset;

    	    // Print the data
    	    printf("TCP Data (%d bytes):\n", data_length);
    	    for (int i = 0; i < data_length; i++) {
            	printf("%c", packet[sizeof(struct ethheader) + (ip->iph_ihl << 2) + data_offset + i]);
    	    }
    	    printf("\n\n");

            return;
        }
    }
}

int main()
{
  pcap_t *handle;
  char errbuf[PCAP_ERRBUF_SIZE];
  struct bpf_program fp;
  char filter_exp[] = "tcp";
  bpf_u_int32 net;

  // Step 1: Open live pcap session on NIC with name enp0s3
  handle = pcap_open_live("ens33", BUFSIZ, 1, 1000, errbuf);

  // Step 2: Compile filter_exp into BPF psuedo-code
  pcap_compile(handle, &fp, filter_exp, 0, net);
  if (pcap_setfilter(handle, &fp) !=0) {
      pcap_perror(handle, "Error:");
      exit(EXIT_FAILURE);
  }

  // Step 3: Capture packets
  pcap_loop(handle, -1, got_packet, NULL);

  pcap_close(handle);   //Close the handle
  return 0;
}
