#include "mbed.h"

// F303K8
PinName can_rx_pin = PA_11;
PinName can_tx_pin = PA_12;

const int can_baudrate = 1000000;
const int data_length = 8;

char counter = 0;

Ticker ticker;
CAN can(can_rx_pin, can_tx_pin, can_baudrate);  // CAN通信の設定
DigitalOut led(LED1);   // デバッグ用LED


int main(void){
    CANMessage msg;
    msg.id = 1;
    msg.len = data_length;
    msg.data[0] = 0x00;
    msg.data[1] = 0x11;
    msg.data[2] = 0x22;
    msg.data[3] = 0x33;
    msg.data[4] = 0x44;
    msg.data[5] = 0x55;
    msg.data[6] = 0x66;
    msg.data[7] = 0x77;

    while(1){
        can.write(msg);
        led = !led;
        osDelay(500);   // while文が500msで回るように調節
    }

    return 0;
}
