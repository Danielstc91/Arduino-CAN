// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>

// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 10;
const int ledHIGH    = 1;
const int ledLOW     = 0;
const int buttonPin = 3;

int buttonState = 0;  
  int previousState = 0;
  int Status =0; 

MCP_CAN CAN(SPI_CS_PIN);                                    // Set CS pin

void setup()
{
    Serial.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS))              // init can bus : baudrate = 500k
    {
        Serial.println("CAN BUS Shield init fail");
        Serial.println(" Init CAN BUS Shield again");
        delay(100);
    }
    Serial.println("CAN BUS Shield init ok!");


    pinMode(buttonPin, INPUT);
}



void loop()
{   Serial.println("In loop");
  
 buttonPressed();


}





int buttonPressed(){
  
 // send data:  id = 0x70, standard frame, data len = 8, stmp: data buf
 // CAN.sendMsgBuf(id, standard frame, length, PAcketData);
  
  
  //Packet Data = 8 bits
  unsigned char PacketData[8] = {Status, 1, 2, 3, 4, 5, 6, 7};
  
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed. If it is, Change First Byte of Packet Data to 1(ON);
  if (buttonState == HIGH && previousState == LOW) {
    Status = 1;
    previousState = HIGH;
    PacketData[0] = Status;
    CAN.sendMsgBuf(0x70, 0, 8, PacketData);
  } else if (buttonState ==LOW && previousState ==HIGH) {
    Status = 0;
    previousState = LOW;
    PacketData[0] = Status;
    CAN.sendMsgBuf(0x70, 0, 8, PacketData);   
} else{
      return Status;
    }

}
/*********************************************************************************************************
  END FILE
*********************************************************************************************************/
