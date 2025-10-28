#include <SPI.h>
#include <mcp2515.h>

struct can_frame canMesaj;
MCP2515 mcp2515(10); 

void setup() {
  Serial.begin(9600);
  SPI.begin();

  mcp2515.reset();
  mcp2515.setBitrate(CAN_500KBPS, MCP_8MHZ);
  mcp2515.setNormalMode();

  Serial.println("CAN Alıcı Başlatıldı!");
}

void loop() {
  if (mcp2515.readMessage(&canMesaj) == MCP2515::ERROR_OK) {
    Serial.print("Gelen mesaj: ");
    for (uint8_t i = 0; i < canMesaj.can_dlc; i++) {
      Serial.print((char)canMesaj.data[i]); 
    }
    Serial.println();

  }
}