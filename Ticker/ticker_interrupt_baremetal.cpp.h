
#include "mbed.h"
#include <cstring>

// UnbufferedSerial pc(USBTX, USBRX);
DigitalOut led(LED1);
Ticker t;
int counter = 0;

char wtext[128];

void ticker_callback(){
    led = !led;
    counter++;
    printf("counter: %d\r\n", counter);   // cause error (Not allowed in ISR context)
    
}

int main(){
    t.attach(&ticker_callback, 500ms);

    while(1){

    }   
    return 0; 
}