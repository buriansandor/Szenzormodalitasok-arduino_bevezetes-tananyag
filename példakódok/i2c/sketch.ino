#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C* lcd = nullptr;  // Pointer az LCD-hez
byte lcdAddress = 0;               // Tárolni fogjuk a talált címet

void setup() {
  Serial.begin(115200);

  Serial.println();
  Serial.println("I2C scanner. Scanning ...");

  Wire.begin();
  
  // Először megkeressük az I2C eszközt
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found address: ");
      Serial.print(i, DEC);
      Serial.print(" (0x");
      Serial.print(i, HEX);
      Serial.println(")");
      
      // Ha még nem találtunk LCD címet, ezt használjuk
      if (lcdAddress == 0) {
        lcdAddress = i;
        Serial.print("Using this address for LCD: 0x");
        Serial.println(lcdAddress, HEX);
      }
      
      delay(1);  
    }            
  }
  
  // Ha találtunk címet, inicializáljuk az LCD-t
  if (lcdAddress != 0) {
    lcd = new LiquidCrystal_I2C(lcdAddress, 16, 2);
    lcd->init();
    lcd->clear();
    lcd->backlight();
    lcd->setCursor(2, 0);
    lcd->print("Hello world!");
    lcd->setCursor(2, 1);
    lcd->print("LCD I2C demo");
    
    Serial.println("LCD initialized successfully!");
  } else {
    Serial.println("No I2C device found!");
  }
  delay(1); 
}  

void loop() {
  if (lcd != nullptr) {
    lcd->clear();
    lcd->setCursor(2,0);
    lcd->print("My address:");
    lcd->setCursor(2,1);
    lcd-> print(lcdAddress);
  }
}