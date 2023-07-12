#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN 17
#define SS_PIN  5

MFRC522 mfrc522(SS_PIN, RST_PIN);

String carduid;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    delay(50);
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    delay(50);
    return;
  }
  readCard(mfrc522.uid.uidByte, mfrc522.uid.size);
}

void readCard (byte *buffer, byte bufferSize)
{
  carduid = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    carduid += buffer[i], DEC;
  }
  Serial.println("Card UID: " + carduid);
}