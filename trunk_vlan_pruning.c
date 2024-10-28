#include<stdio.h>
#include<stdbool.h>
#define MAXVLAN 4096
void print_active_trunk_valns(bool trunk_vlans[], int size){
    printf("active vlans");
    for(int i=1;i<size;i++){
        if(trunk_vlans[i]){
            printf(" %d",i);
        }
    }
}
void prune_trunk_vlans(bool trunk_vlans[], bool allowed_valns[], int size){
    for(int i=1;i<size;i++){
        if(!allowed_valns[i])
            trunk_vlans[i]=false;
    }
}
int main(){
    bool trunk_vlans[MAXVLAN]={false};
    bool allowed_valns[MAXVLAN]={false};
    trunk_vlans[10]=true;
    trunk_vlans[20]=true;
    trunk_vlans[30]=true;
    
    allowed_valns[10]=true;
    allowed_valns[20]=true;
    
    print_active_trunk_valns(trunk_vlans, MAXVLAN);
    prune_trunk_vlans(trunk_vlans, allowed_valns, MAXVLAN);
    printf("\nactive vlans post prune\n");
    print_active_trunk_valns(trunk_vlans, MAXVLAN);
    return 0;
}