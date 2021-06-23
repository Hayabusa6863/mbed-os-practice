// EventQueue2.cpp
// Shared event example: deferring from interrupt context
// https://os.mbed.com/docs/mbed-os/v6.9/apis/eventqueue.html

#include "mbed.h"
#include "mbed_events.h"

DigitalOut led1(LED1);
InterruptIn sw(USER_BUTTON);

void rise_handler(void){
    // Toggle LED
    led1 = !led1;
}

void fall_handler(void){
    printf("fall_handler in context %p\n", ThisThread::get_id());
    // Toggle LED
    led1 = !led1;
}

int main(void){
    // Request the share queue
    EventQueue *queue = mbed_event_queue();
    printf("Starting in context %p\r\n", ThisThread::get_id());

    // The 'rise' handler will execute in IRQ context
    sw.rise(rise_handler);

    // The 'fall' handler will execute in the context of the shared queue thread
    sw.fall(queue->event(fall_handler));

    return 0;
}