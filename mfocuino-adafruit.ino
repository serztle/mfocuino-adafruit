/**
 * Copyright (C) 2011 Christophe Duvernois <christophe.duvernois@gmail.com>
 * Copyright (C) 2014 serztle <serztle@googlemail.com>
 *
 * This is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

/**
 * Arduino driver code to allow libnfc to drive the nfc shield with the uart driver
 *
 * Modified by serztle to work with Adafruit NFC-Shield 
 */

#include <Wire.h>
#include <Adafruit_NFCShield_I2C.h>

#define DEBUG (0)
#define IRQ   (2)
#define RESET (3)  // Not connected by default on the NFC Shield

Adafruit_NFCShield_I2C nfc(IRQ, RESET);

uint8_t buffer[32];

void setup(void) {
    Serial.begin(921600);
    Serial.flush();
#if DEBUG
    Serial.println("Looking for PN532...");
#endif
    nfc.begin();
#if DEBUG
    uint32_t versiondata = nfc.getFirmwareVersion();
    if (! versiondata) {
        Serial.print("Didn't find PN53x board");
        while (1);
    }
    Serial.println("PN53x board found");
#endif
}

void loop(void) {

    int b = Serial.available();
    if (b >= 5) {
        Serial.readBytes((char*)buffer, 5);
        if(buffer[0] == PN532_WAKEUP) {
#if DEBUG
            Serial.println("Wakeup case");
#endif
            //ignore wakeup from libnfc
            Serial.readBytes((char*)buffer+5, 11);
            
        } else {
#if DEBUG                   
            Serial.println("Normal case");
#endif
            uint8_t len = buffer[3] + 2;

            uint8_t br = len;
            uint8_t* bufptr = buffer+5;
            while(br){
                if(Serial.available()){
                    *bufptr++ = Serial.read();
                    --br;
                }
            }

            //send raw command to pn532
            nfc.sendRawCommandCheckAck(buffer, len+5);
            //read pn532 answer
            nfc.readRawCommandAnswer();
        }
    }
}
