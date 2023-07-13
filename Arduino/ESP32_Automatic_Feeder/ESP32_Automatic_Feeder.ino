/****************************************************************
  Sommerprojektgruppe 15

  Automatischer Futterspender
  - Einlesen von eines RFID Chips
  - Abfragen der Datenbank für den Namen und die Futtermenge
  - Einstellen der Futtermenge
  - Aktualisieren der Datensätze in der Datenbank
****************************************************************/

#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <SPI.h>
#include <Stepper.h>
#include <WiFi.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define RST_PIN 17
#define SS_PIN  5
MFRC522 mfrc522(SS_PIN, RST_PIN);
String cardUID;

const int stepsPerRevolution = 2048;
#define IN1 15
#define IN2 2
#define IN3 0
#define IN4 4
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);

#define button1 32
#define button2 33
#define button3 27

const char* ssid = "xxx";
const char* pass = "xxx";
WiFiClient client;

MySQL_Connection conn(&client);
IPAddress server_addr(xxx, xxx, xxx, xxx);
char user[] = "xxx";
char password[] = "xxx";
char query[128];
int KatzeID;
String Name;
int maxFutterausgabe;

void setup()
{
  Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  SPI.begin();
  mfrc522.PCD_Init();

  myStepper.setSpeed(10);

  initWiFi();

  lcd.clear();
  lcd.print("Bereit");
}

void loop() 
{
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

  queryDBkatze();

  delay(3000);

  lcd.clear();
  lcd.print("Katze: " + Name);
  delay(5000);

  lcd.clear();
  lcd.print("Ausgabe Futter");
  myStepper.step(2 * stepsPerRevolution);
  delay(5000);

  lcd.clear();
  lcd.print("Bereit");
}

void initWiFi()
{
  Serial.printf("\nConnecting to %s", ssid);

  lcd.print("Connecting to:");
  lcd.setCursor(0, 1);
  lcd.print(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }

  Serial.println("\nConnected to network");

  lcd.clear();
  lcd.print("Connected to network");
  lcd.setCursor(0, 1);
  lcd.print("network");
  delay(3000);

  Serial.print("IP address is: ");
  Serial.println(WiFi.localIP());
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());

  lcd.clear();
  lcd.print("IP address:");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
  delay(3000);
}

bool queryDBkatze()
{
  if (conn.connect(server_addr, 3306, user, password))
  {
    delay(1000);

    const char SELECT_SQL[] = "SELECT `ID`, `Name`, `maxFutterausgabe` FROM `k84947_iot`.katze WHERE `cardUID` = %s";
    sprintf(query, SELECT_SQL, cardUID.c_str());
    Serial.print("Used query: ");
    Serial.println(query);
    MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
    cur_mem->execute(query);

    column_names *cols = cur_mem->get_columns();
    Serial.print("Recieved columns: ");
    for (int f = 0; f < cols->num_fields; f++)
    {
      Serial.print(cols->fields[f]->name);
      if (f < cols->num_fields - 1)
      {
        Serial.print(" , ");
      }
    }
    Serial.println();

    row_values *row = NULL;
    do
    {
      row = cur_mem->get_next_row();
      if (row != NULL)
      {
        String KatzeIDDB = row->values[0];
        Name = row->values[1];
        String maxFutterausgabeDB = row->values[2];
        KatzeID = KatzeIDDB.toInt();
        maxFutterausgabe = maxFutterausgabeDB.toInt();
        Serial.println("Recieved values: ID: " + KatzeIDDB + "Name: " + Name + " maxFutterausgabe: " + maxFutterausgabeDB);
        Serial.println( );
        
      }
    }
    while (row != NULL);
    delete cur_mem;
    conn.close();
    return true;
  }
  else
  {
    Serial.println("Connection failed.");
    conn.close();
    return false;
  }
}

void readCard (byte *buffer, byte bufferSize)
{
  cardUID = "";
  for (byte i = 0; i < bufferSize; i++)
  {
    cardUID += buffer[i], DEC;
  }
  Serial.println("Card UID: " + cardUID);
}