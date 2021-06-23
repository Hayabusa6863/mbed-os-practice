#include "mbed.h"
#include "rtos.h"

#define WAIT_MICROSECOND 100
DigitalOut pin(PG_0);

int main(void){
    while(1){
        pin = !pin;
        wait_us(WAIT_MICROSECOND);
    }
    return 0;
}