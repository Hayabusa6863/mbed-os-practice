// The comment from author
/*
Example of an interrupt which passes its job as a thread using signals. 
"With an RTOS application it is best to design the interrupt service code as a thread within the RTOS and assign it a high priority. 
While it is possible to run C code in an interrupt service routine (ISR), 
this is not desirable within an RTOS if the interrupt code is going to run for more than a short period of time. 
This delays the timer tick and disrupts the RTOS kernel. " - “The Designers Guide to the Cortex-M ProcessorFamily” by Trevor Martin
*/

// mbed-osで割り込み処理を行うとエラーが出ていたが
// この方法だと正常に動作した．
// CAN通信やその他割り込みでも正常に動作するか？

#include "mbed.h"

InterruptIn button(BUTTON1);

Thread ISRthread(osPriorityAboveNormal);
osThreadId ISRthreadId;

DigitalOut myled(LED1);
DigitalOut myled3(LED3);

void newInput(){
    osSignalSet(ISRthreadId, 0x01);
}

void ISR_thread(){
    ISRthreadId = osThreadGetId();

    for(;;){
        osSignalWait(0x01, osWaitForever);
        myled3 = !myled3;
    }
}


int main(void){
    ISRthread.start(callback(ISR_thread));
    button.rise(&newInput);     // interrupt to catch input

    while(1){
        myled = 1;
        osDelay(1000);
        myled = 0;
        osDelay(1000);
    }
}