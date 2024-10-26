#include <stdio.h>
#include <string.h>
#define MAX_LINK 3
#define MAX_LAOD 5
typedef struct link_s{
    int id;
    int load;
}Link;
typedef struct packet_s{
    char sip[16];
    char dip[16];
    char smac[18];
    char dmac[18];
    int sport;
    int dport;
    int svlan;
    int cvlan;
}Packet;
unsigned long int ip_to_num(char *ip){
    unsigned int octet;
    unsigned int num=0;
    char *p = ip;
    while(*p){
        if( sscanf(p,"%u",&octet) != 1) break;
        num = (num << 8) + octet;
        p = strchr(p, '.');
        if(!p) break;
        p++;
    }
    return num;
}
unsigned long int mac_to_num(char *mac){
    unsigned int hex;
    unsigned int num=0;
    char *p=mac;
    while(*p){
        if( sscanf(p,"%02x",&hex) != 1) break;
        num = (num << 8) + hex;
        p = strchr(p, ':');
        if(!p) break;
        p++;
    }
    return num;
}

int hashfunction(Packet p){
    unsigned long sip = ip_to_num(p.sip);
    unsigned long dip = ip_to_num(p.dip);
    unsigned long smac = mac_to_num(p.smac);
    unsigned long dmac = mac_to_num(p.dmac);
    int sport = p.sport;
    int dport = p.dport;
    int svlan = p.svlan;
    int cvlan = p.cvlan;
    unsigned long num = (sip^dip^smac^dmac^sport^dport^svlan^cvlan);
    return num%MAX_LINK;
}
int adoptive_hashing(Link link[], Packet packet){
    int index = hashfunction(packet);
    if( link[index].load > MAX_LAOD){
        for(int i=0;i<MAX_LINK;i++){
            if(link[i].load < MAX_LAOD )
                index  = i;
                break;
        }
    }
    return index;
}
void simulate_traffic(Link link[], Packet packet[], int num_packet){
    for(int i=0;i<num_packet;i++){
        Packet p = packet[i];
        int selected_link = adoptive_hashing(link, p);
        link[selected_link].load++;
        printf("SIP %s packet assigned to link %d and its current load is %d\n",
                p.sip, link[selected_link].id, link[selected_link].load);
    }
}
int main()
{
    Link link[MAX_LINK];
    for(int i=0;i<MAX_LINK;i++){
        link[i].id=i;
        link[i].load=0;
    }
    Packet packet[]={
        {"192.168.1.1", "192.168.1.10", "00:11:22:33:44:55", "00:11:22:33:44:66", 1000, 2000, 100, 10},
        {"192.168.1.2", "192.168.1.20", "00:11:22:33:44:77", "00:11:22:33:44:88", 1500, 2500, 200, 25},
        {"192.168.1.3", "192.168.1.30", "00:11:22:33:44:99", "00:11:22:33:44:AA", 2000, 3000, 300, 32},
        {"192.168.1.4", "192.168.1.40", "00:11:22:33:44:BB", "00:11:22:33:44:CC", 2500, 3500, 400, 45},
        {"192.168.1.5", "192.168.1.50", "00:11:22:33:44:DD", "00:11:22:33:44:EE", 3000, 4000, 100, 56},
        {"192.168.1.6", "192.168.1.60", "00:11:22:33:44:FF", "00:11:22:33:44:00", 3500, 4500, 200, 78},
        {"192.168.1.7", "192.168.1.70", "00:11:22:33:44:11", "00:11:22:33:44:22", 4000, 5000, 300, 90},
        {"192.168.1.8", "192.168.1.80", "00:11:22:33:44:33", "00:11:22:33:44:44", 4500, 5500, 400, 101},
        {"192.168.1.9", "192.168.1.90", "00:11:22:33:44:55", "00:11:22:33:44:66", 5000, 6000, 100, 111},
        {"192.168.1.10", "192.168.1.100", "00:11:22:33:44:77", "00:11:22:33:44:88", 5500, 6500, 200, 123}
    };
    int num_packet = sizeof(packet)/sizeof(packet[0]);
    simulate_traffic(link, packet, num_packet);
    printf("\nFinal load distribution:\n");
    for (int i = 0; i < MAX_LINK; i++) {
        printf("Link %d: %d packets\n", link[i].id, link[i].load);
    }
    return 0;
}