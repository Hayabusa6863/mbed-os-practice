// cite from here
// https://gist.github.com/lonesometraveler/823a91ceed53f6783be1eaae97a36858

/* Advise from author */
// Execution of certain function in an ISR context is not safe. 
// For example, printf() in an interrupt context causes a Mutex error. 
// Using Mbed's EventQueue, you can defer execution of code from an interrupt context to a user context.
// More about EventQueue: https://os.mbed.com/docs/mbed-os/v5.15/tutorials/the-eventqueue-api.html

#include "mbed.h"
#include "string.h"
#include <cstdio>
#include <cstring>

EventQueue *queue = mbed_event_queue();
DigitalOut led(LED1);
UnbufferedSerial pc(USBTX, USBRX);
Ticker t;
int counter = 0;
char wtext[128];


void processInUserContext(){
    led = !led;
    // sprintf(wtext, "printing in a user context. counter = %d\r\n",counter);
    // pc.write(wtext, strlen(wtext));
    printf("printing in a user context. counter = %d\r\n",counter);
}

void ticker_callback(){
    counter++;
    queue->call(&processInUserContext);  // process in a differnt context
}

int main(){
    t.attach(&ticker_callback, 500ms);
    queue->dispatch_forever();
}