// EventQueue3.cpp
// EventQueue example : posting events to the queue
// https://os.mbed.com/docs/mbed-os/v6.9/apis/eventqueue.html

#include "mbed_events.h"

using namespace std::chrono_literals;

/************************************************************
In the example below, there are 3 types of event callbacks
1) Call the provided function immediately
2) Call the provided function once (after the specified period)
3) Call the provided function every specified period

Expected output:
    called immediately
    called every 1 second
    called in 2 second
    called every 1 second
    called every 1 second ...(repeated forever)
*************************************************************/


int main(void){
    // creates a queue with the default size
    EventQueue queue;

    // events are simple callbacks
    queue.call(printf, "called immediately\r\n");
    queue.call_in(2000ms, printf, "called in 2 seconds\r\n");
    queue.call_every(1000ms, printf, "called every 1 second\r\n");

    // events are executed by the dispatch_forever method
    queue.dispatch_forever();

    return 0;
}