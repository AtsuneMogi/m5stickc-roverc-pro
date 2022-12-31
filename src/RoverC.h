#ifndef _ROVERC_H_
#define _ROVERC_H_

#include <M5StickC.h>

#define ROVER_ADDRESS 0X38


void rovercInit(void); //sda: 0, scl: 26
void sendIic(uint8_t registerNum, uint8_t speed);
void moveForward(int8_t speed);
void moveBack(int8_t speed);
void moveLeft(int8_t speed);
void moveRight(int8_t speed);
void moveLeftForward(int8_t speed);
void moveRightForward(int8_t speed);
void moveLeftBack(int8_t speed);
void moveRightBack(int8_t speed);
void turnLeft(int8_t speed);
void turnRight(int8_t speed);
void stop();

#endif