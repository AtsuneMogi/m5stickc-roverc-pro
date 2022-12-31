#include <AsyncUDP.h>
#include <M5StickC.h>
#include "RoverC.h"
#include <WiFi.h>


int cnt = 0;
bool grab = false;
char buf[1];
int v = 100; // velocity

char ssid[] = "M5StickC-Controller";
char pass[] = "controller";
AsyncUDP udp; // udp instance
unsigned int port = 8888;  // local port to listen on


void moveServo(uint8_t angle) {
    Wire.beginTransmission(ROVER_ADDRESS); // 0X38
    Wire.write(0X10);
    Wire.write((int8_t)angle);
    Wire.endTransmission();
}


void setup(){ 
    M5.begin();
    Serial.begin(115200);
    rovercInit();

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    delay(100);

    Serial.print("Connecting...");
    while (WiFi.waitForConnectResult() != WL_CONNECTED) { 
        Serial.print(".");
        delay(500);
    }
    Serial.println("");

    moveServo(0);
    delay(2000);

    if (udp.listen(port)) {
        udp.onPacket([](AsyncUDPPacket packet) {
            buf[0]= (char)*(packet.data());
            Serial.println(buf[0]);
        });
    }
}

void loop() {
    M5.update();

    switch (buf[0]) {
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

    if (buf[0] == 'K') {
        cnt++;
    } else {
        cnt = 0;
    }

    delay(100);
}
