#include <AsyncUDP.h>
#include <M5StickC.h>
#include "RoverC.h"
#include <WiFi.h>


int cnt = 0;
bool grab = false;
char buf = 'K';
int v = 100; // velocity

char ssid[] = "M5StickC-Controller";
char pass[] = "controller";
AsyncUDP udp; // udp instance
unsigned int port = 8888;  // local port to listen on


void moveServo(uint8_t angle) {
    int8_t angle1, angle2;
    if (angle == 0) {
        angle1 = 0;
        angle2 = 180;
    } else if (angle == 180) {
        angle1 = 180;
        angle2 = 0;
    }
        
    Wire.beginTransmission(ROVER_ADDRESS); // 0X38
    Wire.write(0X10);
    Wire.write(angle1);
    Wire.endTransmission();
    Wire.beginTransmission(ROVER_ADDRESS); // 0X38
    Wire.write(0X11);
    Wire.write(angle2);
    Wire.endTransmission();
}


void setup(){ 
    M5.begin();
    Serial.begin(115200);
    rovercInit();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    delay(100);

    moveServo(0);
    delay(2000);

    if (udp.listen(port)) {
        udp.onPacket([](AsyncUDPPacket packet) {
            buf = (char)*(packet.data());
            Serial.println(buf);
        });
    }
}

void loop() {
    if (WiFi.waitForConnectResult() != WL_CONNECTED) { 
        Serial.print(".");
    }

    M5.update();

    switch (buf) {
        case 'a':
            moveForward(v/2);
            break;
        case 'A':
            moveForward(v);
            break;
        case 'b':
            moveBack(v/2);
            break;
        case 'B':
            moveBack(v);
            break;
        case 'c':
            moveLeftForward(v/2);
            break;
        case 'C':
            moveLeftForward(v);
            break;
        case 'd':
            moveRightForward(v/2);
            break;
        case 'D':
            moveRightForward(v);
            break;
        case 'e':
            moveLeftBack(v/2);
            break;
        case 'E':
            moveLeftBack(v);
            break;
        case 'f':
            moveRightBack(v/2);
            break;
        case 'F':
            moveRightBack(v);
            break;
        case 'g':
            moveLeft(v/2);
            break;
        case 'G':
            moveLeft(v);
            break;
        case 'h':
            moveRight(v/2);
            break;
        case 'H':
            moveRight(v);
            break;
        case 'I':
            turnRight(v/2);
            break;
        case 'J':
            turnLeft(v/2);
            break;
        case 'K':
            stop();
            if (30 < cnt) {
                if (!grab) {
                    moveServo(180);
                    delay(2000);
                    grab = true;
                } else {
                    moveServo(0);
                    delay(2000);
                    grab = false;
                }
            }
            break;
        default:
            stop();
            break;
    }

    if (buf == 'K') {
        cnt++;
    } else {
        cnt = 0;
    }

    delay(100);
}

