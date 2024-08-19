#include <stdio.h>

int main() {
    int val = 0x1234;
    char *byte = (char *)&val;
    if(*byte == 0x01){
        printf("Big endian %x\n", *byte);
    }else{
        printf("Little endian %x\n", *byte);
    }
    return 0;
}
