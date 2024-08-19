#include <stdio.h>
#include <unistd.h>
typedef enum{
    IDLE,
    CONNECT,
    ACTIVE,
    OPENSENT,
    OPENCONFIRM,
    ESTABLIS
}state;

void BGP_Finite_State_Machine(state *bgp_fsm){
    switch(*bgp_fsm){
        case IDLE:
            printf("IDLE state\n");
            *bgp_fsm = CONNECT;
            sleep(3);
            break;
        case CONNECT:
            printf("CONNECT state\n");
            *bgp_fsm = ACTIVE;
            sleep(3);
            break;
        case ACTIVE:
            printf("ACTIVE state\n");
            *bgp_fsm = OPENSENT;
            sleep(3);
            break;
        case OPENSENT:
            printf("OPENSENT state\n");
            *bgp_fsm = OPENCONFIRM;
            sleep(3);
            break;
        case OPENCONFIRM:
            printf("OPENCONFIRM state\n");
            *bgp_fsm = -1;
            sleep(3);
            break;
        default:
            printf("Unknown state\n");
            break;
    }
}
int main() {
    state bgstate = IDLE;
    for(int i=0;i<7;i++)
        BGP_Finite_State_Machine(&bgstate);
    return 0;
}
