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

  Serial.println("CAN Verici Başlatıldı!");
}

void loop() {
  const char *mesaj = "Merhaba";
  uint8_t len = strlen(mesaj);

  canMesaj.can_id  = 0x100; 
  canMesaj.can_dlc = len;   

  for (uint8_t i = 0; i < len && i < 8; i++) {
    canMesaj.data[i] = mesaj[i];
  }

  if (mcp2515.sendMessage(&canMesaj) == MCP2515::ERROR_OK) {
    Serial.println("Mesaj gönderildi: Merhaba");
  } else {
    Serial.println("Gönderim hatası!");
  }

  delay(1000);
}
