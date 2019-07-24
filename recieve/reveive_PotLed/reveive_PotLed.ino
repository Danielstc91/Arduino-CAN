// demo: CAN-BUS Shield, receive data with check mode
// send data coming to fast, such as less than 10ms, you can use this way
// loovee, 2014-6-13

#include <SPI.h>
#include "mcp_can.h"

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int LED        = 3;
boolean ledON        = false;
unsigned char buf[8];

byte potValue = 0;

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);
    pinMode(LED,OUTPUT);

    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println("Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");
}


void loop()
{

readCanMessage();
ledOutput(potValue);

  
}



void readCanMessage(){
    unsigned char len = 0;

  if(CAN_MSGAVAIL == CAN.checkReceive())            // check if data coming
    {
        CAN.readMsgBuf(&len, buf);    // read data,  len: data length, buf: data buf

        unsigned long canId = CAN.getCanId();
        Serial.println("-----------------------------");
        Serial.print("get data from ID: 0x");
        Serial.println(canId, HEX);

        for(int i = 0; i<len; i++)    // print the data
        {
            Serial.print(buf[i]);
            Serial.print("\t");                  
    }
      //debug
    Serial.println("message completed");
      Serial.print("potValue : " );
      Serial.println(potValue);
    Serial.print("ledOn? : ");
    Serial.println(ledON);
    Serial.print("buf1 = :");
    Serial.println(buf[1]);
    }
    updateStatus(buf);
}

 






byte updateStatus (unsigned char *buf){

  potValue = buf[1];
  if(ledON && buf[0] == 0)
            {
                //Debug
                //Serial.print("buf[1] = ");
                //Serial.println(buf[1]);
                ledON = false;
            }
    else if(!ledON &&buf[0] == 1)
            {
                //Debug
                //Serial.print("buf[1] = ");
                //Serial.println(buf[1]);
                
                //update value and led status
                ledON = true;
            }
       else {
         ledOutput(potValue);
       }
       
}



void ledOutput(int potV){
  analogWrite(LED, potV);

}


//END FILE
