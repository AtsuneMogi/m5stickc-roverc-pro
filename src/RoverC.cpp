#include "RoverC.h"


void rovercInit(void) { // sda: 0, scl: 26
    Wire.begin(0,26,(unsigned int)100);
}


void sendIic(uint8_t registerNum, uint8_t speed) {
    Wire.beginTransmission(ROVER_ADDRESS); // 0X38
    Wire.write(registerNum);
    Wire.write(speed); // send byte data to queue
    Wire.endTransmission();
}


void moveForward(int8_t speed) {
    sendIic(0x00, speed ); // fl
    sendIic(0x01, speed ); // fr
    sendIic(0x02, speed ); // bl
    sendIic(0x03, speed ); // br
}


void moveBack(int8_t speed) {
    sendIic(0x00, (-1) * speed);
    sendIic(0x01, (-1) * speed);
    sendIic(0x02, (-1) * speed);
    sendIic(0x03, (-1) * speed);
}


void moveLeftForward(int8_t speed) {
    sendIic(0x00, 0);
    sendIic(0x01, speed);
    sendIic(0x02, speed);
    sendIic(0x03, 0); 
}


void moveRightForward(int8_t speed) {
    sendIic(0x00, speed);
    sendIic(0x01, 0);
    sendIic(0x02, 0);
    sendIic(0x03, speed); 
}


void moveLeftBack(int8_t speed) {
    sendIic(0x00, (-1) * speed);
    sendIic(0x01, 0);
    sendIic(0x02, 0);
    sendIic(0x03, (-1) * speed);
}


void moveRightBack(int8_t speed) {
    sendIic(0x00, 0);
    sendIic(0x01, (-1) * speed);
    sendIic(0x02, (-1) * speed);
    sendIic(0x03, 0);
}


void moveLeft(int8_t speed) {
    sendIic(0x00, (-1) * speed);
    sendIic(0x01, speed );
    sendIic(0x02, speed );
    sendIic(0x03, (-1) * speed);
}


void moveRight(int8_t speed) {
    sendIic(0x00, speed);
    sendIic(0x01, (-1) * speed);
    sendIic(0x02, (-1) * speed);
    sendIic(0x03, speed);
}


void turnLeft(int8_t speed) {
    sendIic(0x00, speed );
    sendIic(0x01, (-1) * speed );
    sendIic(0x02, speed );
    sendIic(0x03, (-1) * speed );
}


void turnRight(int8_t speed) {
    sendIic(0x00, (-1) * speed );
    sendIic(0x01, speed );
    sendIic(0x02, (-1) * speed );
    sendIic(0x03, speed );
}


void stop() {
    sendIic(0x00, 0);
    sendIic(0x01, 0);
    sendIic(0x02, 0);
    sendIic(0x03, 0);
}

