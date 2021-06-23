#include "mbed.h"

# define CAN_ID     1


// F303K8
PinName can_rx_pin = PA_11;
PinName can_tx_pin = PA_12;

/*
// F446RE
PinName can_rx_pin = PB_8;
PinName can_tx_pin = PB_9;
*/
const int can_baudrate = 1000000;
const int data_length = 8;

DigitalOut led(LED1);   // 確認用LED
CAN can(can_rx_pin, can_tx_pin, can_baudrate);
CANMessage rxMsg;
EventQueue eventQueue(32 * EVENTS_EVENT_SIZE);

void onCanReceived(void){
    if(can.read(rxMsg)){
        printf("Message received: ");
        for(int i=0; i<rxMsg.len; i++){
            printf("%d, ", rxMsg.data[i]);
        }
        printf("\r\n");
    }
}



int main(void){
    led = 0;    // LEDをOFF
    can.attach(eventQueue.event(callback(onCanReceived)));

    while(1){
        led = !led;
        ThisThread::sleep_for(200ms);  // while文が1000msで回るように調節
    }
    return 0;
}
