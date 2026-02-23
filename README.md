<center>
  <h1>Szenzormodalitások - Arduino</h1>
  <i>2/24/2026</i>
</center>

**Tartalom:**
- [Bevezetés](#bevezetés)
- [Arduino](#arduino)
- [ESP32](#esp32)
- [Micropython](#micropython)
- [Haladóknak](#haladóknak)

# Bevezetés
- Thinkercad példák egyben: https://www.tinkercad.com/joinclass/FBXMSJFMM
- Tananyag NotebookLM formában: 

## Mikrokontrollerek VS számítógépek 
| Aspektus | Mikrokontroller | Számítógép |
|----------|-----------------|-----------|
| **Cél** | Specifikus feladat végrehajtása | Általános célú számítástechnika |
| **Feldolgozási sebesség** | Alacsonyabb (MHz-GHz) | Magasabb (GHz) |
| **Memória** | Korlátozott (KB-MB) | Nagy (GB) |
| **Energiafogyasztás** | Nagyon alacsony | Magas |
| **Operációs rendszer** | Nincs vagy valós idejű OS | Windows, Linux, macOS |
| **Alkalmazás** | Beágyazott rendszerek, szenzor vezérlés | Általános számítástechnika |
| **Komplexitás** | Egyszerű | Összetett |

### Firmware vs. Szoftver
| Aspektus | Firmware | Szoftver |
|----------|----------|----------|
| **Definíció** | Alacsony szintű kód, közvetlenül a hardverhez kapcsolódik | Magas szintű alkalmazások és programok |
| **Tárolás** | ROM, Flash memória | RAM, merevlemez, SSD |
| **Módosíthatóság** | Ritkán módosítható, speciális eszközöket igényel | Könnyen módosítható, frissíthető |
| **Függőség** | Erősen kötött az adott hardverhez | Hardvertől viszonylag független |
| **Futási környezet** | Közvetlenül a processzor által futtatott | Operációs rendszer vagy interpreter által futtatott |
| **Frissítés** | Ritka, szükség esetén programozóval | Gyakori, logikai frissítések |
| **Mikrokontrollerek** | Mikrokontrollereken közvetlenül fut | Mikrokontrollerek esetén tipikusan nem használatos |

### Beágyazott rendszerek komplexitásban
[![Beágyazott rendszerek típusai felhaszálási terület szerint](https://docs.madmachine.io/assets/images/embedded_category-04e8db73ce513b0ec6ce329c9fa2f62f.png)](https://docs.madmachine.io/blog/A%20brief%20introduction%20about%20Swift%20in%20embedded%20development)


- https://witekio.com/blog/software-foundation-bare-metal-linux/
- https://forums.freertos.org/t/why-are-more-embedded-systems-moving-from-bare-metal-to-rtos-os-linux-freertos/23234

| Követelmény | Bare Metal | RTOS | Embedded Linux |
|---|---|---|---|
| Egyetlen feladat, ultra alacsony energiafogyasztás | ✅ Erősen optimalizált és minimális | ⚠️ Kis terhelés | ❌ Általában felesleges |
| Valós idejű válaszidő <1ms | ✅ Determinisztikus, ha jól tervezed | ✅ Hard real-time-hoz tervezve | ✅⚠️ Hangolással elérhető, nem feltétlenül igényel PREEMPT_RT |
| Több párhuzamos feladat | ⚠️ Lehetséges manuális ütemezéssel, de nem minden chipen | ✅ Preemptív multitasking | ✅ Teljes multitasking és IPC |
| Internet / Ethernet kapcsolat | ✅ Lehetséges lwIP vagy vendor stack-kel | ✅ Gyakran beépített vagy vendor által támogatott | ✅ Teljes hálózati verem |
| OTA frissítések, biztonsági rétegek | ✅ Bootloader és flash menedzsmenttel | ✅ Zephyr vagy AWS FreeRTOS ökoszisztémákban | ✅ Kiforrott eszközök és infrastruktúra |
| TLS / Biztonság | ✅ mbedTLS, wolfSSL, stb.-vel | ✅ Általában támogatott SDK-kban | ✅ Szabványos a legtöbb disztribúcióban |
| GUI / Multimédia | ✅ LVGL, TouchGFX támogatott | ✅ Hasonló könyvtárak támogatottak | ✅ Teljes felhasználói felület keretrendszerek |
| Memóriavédelem, sandboxing | ⚠️ Ha MPU elérhető | ⚠️ MPU támogatástól és használattól függ | ✅ Teljes MMU alapú izolálás |


### "Bare Metal"
> Nincs operációs rendszer. A kódod közvetlenül a hardveren fut.

- Arduino
- STM32
- Raspberry Pi Pico

### RTOS
> Van egy pici "ütemező" szoftver (pl. FreeRTOS), de még mindig nagyon közel vagy a hardverhez.

- ESP32
- Raspberry Pi Pico (ha telepítjük az RTOS-t)

### Embedded Linux
> Egy teljes értékű, de speciálisan megvágott operációs rendszer (kernel, driverek, fájlrendszer) általában 32 vagy 64 bites processzorral.

- rPI
- ARM Cortex-A

-----------
-----------

## Arduino
Linkek, anyagok:
- https://docs.arduino.cc/arduino-cloud/guides/editor

### Arduino program szerkezete
Az Arduino kód három fő részből áll: Globális változók; `setup()`; `loop()`;

<details>
  <summary><b>Példa kód a szerkezethez</b></summary>
  <br>

  ```Arduino
  // Globális változók
  int myPin = 13;
  int counter = 0;
  
  // egyszer fut le induláskor
  void setup()
  {
    pinMode(myPin, OUTPUT); //pinkiosztás
    Serial.begin(9600); //baud rate
  }
  
  // végtelenül ismétlődik
  void loop()
  {
    digitalWrite(myPin, HIGH);
    delay(500);
    digitalWrite(myPin, LOW);
    delay(500);
    counter++;
    Serial.println(counter);
  }
  ```
</details>



### `Hello world`
Konzolos hello world. 

Futtatható példakód: https://www.tinkercad.com/things/4O3nPQPU3fB-console-hello-world

<details>
  <summary><b>Példa kód a használathoz</b></summary>
  <br>

  ```Arduino
  int forLimit = 100;
  
  void setup()
  {
    Serial.begin(9600);
  }
  
  void loop()
  {
    Serial.println("Hello world");
    Serial.println("-----------");
    Serial.println("For example");
    for (int idx = 0; idx < forLimit; idx++)
    {
      Serial.print(idx);
    }
    delay(1000);
  }
  ```
</details>

### Hello world - blinking led
Az igazi hello world a beágyazott rendszerekben.

Futtatható példakód: https://www.tinkercad.com/things/40oyIzZqLwF-arduino-hello-world

<details>
  <summary><b>Példa kód a használathoz</b></summary>
  <br>

  ```Arduino
  void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
  }

  void loop()
  {
    digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(1000); // Wait for 1000 millisecond(s)
    digitalWrite(LED_BUILTIN, LOW); // turn the LED off by making the voltage LOW
    delay(1000); // Wait for 1000 millisecond(s)
  }
  ```
</details>

### Szenzorok
#### Analóg
Potméter kiolvasás

Futtatható példakód: https://www.tinkercad.com/things/g6zVFmgtLIQ-potmeter-analog-kiolvasas-demo

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino  
  int sensorValue = 0;

  void setup()
  {
    pinMode(A0, INPUT);
    Serial.begin(9600);
  }

  void loop()
  {
    // read the input on analog pin 0:
    sensorValue = analogRead(A0);
    // print out the value you read:
    Serial.println(sensorValue);
    delay(10); // Delay a little bit to improve simulation performance
  }
  ```
</details>

#### Digitális
Gomb kiolvasás

Futtatható példakód: https://www.tinkercad.com/things/baUvI938DFO-digitalis-kiolvasas-pelda 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino      
  int buttonState = 0;

  void setup()
  {
    pinMode(2, INPUT);
    Serial.begin(9600);
  }

  void loop()
  {
    buttonState = digitalRead(2);   // read the input pin
    Serial.println(buttonState);    // print out the state of the button
    delay(10);                      // Delay a little bit to improve simulation performance
  }
  ```
</details>


### Aktivátorok
Servo motor példa

Futtatható példakód: https://www.tinkercad.com/things/lSDT3gfnnwo-servo-motor-demo

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino  
  #include <Servo.h>

  int pos = 0;

  Servo servo_9;

  void setup()
  {
    servo_9.attach(9, 500, 2500);
  }

  void loop()
  {
    // sweep the servo from 0 to 180 degrees in steps
    // of 1 degrees
    for (pos = 0; pos <= 180; pos += 1) {
      // tell servo to go to position in variable 'pos'
      servo_9.write(pos);
      // wait 15 ms for servo to reach the position
      delay(15); // Wait for 15 millisecond(s)
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      // tell servo to go to position in variable 'pos'
      servo_9.write(pos);
      // wait 15 ms for servo to reach the position
      delay(15); // Wait for 15 millisecond(s)
    }
  }
  ```
</details>

## ESP32

### Hello world

Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino
  void setup()
  {
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.begin(9600);
  }

  void loop()
  {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.println("LED is ON");
    delay(1000);
    
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("LED is OFF");
    delay(1000);
  }
  ```
</details>

### Szenzorok, aktivátorok

Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino  
  ```
</details>


### WiFi - internet

Futtatható példakód: https://wokwi.com/projects/305569599398609473

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino
  
  #include "WiFi.h"

  void setup() {
    Serial.begin(115200);
    Serial.println("Initializing WiFi...");
    WiFi.mode(WIFI_STA);
    Serial.println("Setup done!");
  }

  void loop() {
    Serial.println("Scanning...");

    // WiFi.scanNetworks will return the number of networks found
    int n = WiFi.scanNetworks();
    Serial.println("Scan done!");
    if (n == 0) {
      Serial.println("No networks found.");
    } else {
      Serial.println();
      Serial.print(n);
      Serial.println(" networks found");
      for (int i = 0; i < n; ++i) {
        // Print SSID and RSSI for each network found
        Serial.print(i + 1);
        Serial.print(": ");
        Serial.print(WiFi.SSID(i));
        Serial.print(" (");
        Serial.print(WiFi.RSSI(i));
        Serial.print(")");
        Serial.println((WiFi.encryptionType(i) == WIFI_AUTH_OPEN) ? " " : "*");
        delay(10);
      }
    }
    Serial.println("");

    // Wait a bit before scanning again
    delay(5000);
  }  
  ```
</details>

### I2C
> Az **I2C (Inter-Integrated Circuit)** egy szinkron, soros kommunikációs protokoll, amelyet mikrovezérlők és perifériák közötti adatcserére használnak.
> 
> ***Alapvető tulajdonságok***
>
> ![](https://media.geeksforgeeks.org/wp-content/uploads/20201230010225/gfg1-300x243.png)
>
> - **Szinkron kommunikáció**: Órajel (SCL) és adatvonal (SDA) használata
> - **Kétirányú**: Mester-szolga architektúra
> - **Alacsony sebesség**: Tipikusan 100 kHz vagy 400 kHz
> - **Egyszerű hálózat**: Mindössze 2 vonal szükséges
>
> ***Fizikai kapcsolat***
>
> - **SCL (Serial Clock)**: Órajel vonal
> - **SDA (Serial Data)**: Adatvonal
> - **Pull-up ellenállások**: Szükségesek (tipikusan 4,7 kΩ)
> 
> ***Kommunikációs folyamat:***
> 1. **START feltétel**: Mester kezdeményezi
> 2. **Címzés**: 7 vagy 10 bites eszközcím
> 3. **Írási/Olvasási bit**: Kommunikáció iránya
> 4. **Adatátvitel**: 8 bites adat blokkokkal
> 5. **STOP feltétel**: Kommunikáció befejezése
> 
> ***Arduino implementáció***
> - **`Wire` könyvtár** használata
> - Egyszerű funkciók: `begin()`, `write()`, `read()`
>
> **Előnyei**
> - ✓ Csekély eszköziszám (2 vonal)
> - ✓ Több eszköz támogatása egy buszon
> - ✓ Közepes sebesség
> - ✓ Költséghatékony

Linkek: 
- https://www.geeksforgeeks.org/computer-organization-architecture/i2c-communication-protocol/


Futtatható példakód: 

<details>
  <summary><b>Arduino Példa kód</b></summary>
  <br>
  
  https://wokwi.com/projects/385160860919417857

  ```Arduino
  #include <Wire.h> 
  #include <LiquidCrystal_I2C.h>
  // Set the LCD address to 0x27 for a 16 chars and 2 line display
  LiquidCrystal_I2C lcd(0x27, 16, 2);

  void setup()
  {
    // initialize the LCD
    lcd.begin(16,2);
    lcd.print("Hello (^__^)");
          lcd.setCursor(0, 1);
          lcd.print("ThaiEasyElec");
  }

  void loop()
  {
    // Do nothing here...
  }
  ```
</details>

<details>
  <summary><b>ESP32 Példa kód</b></summary>
  <br>

  https://wokwi.com/projects/456759131929063425

  ```Arduino
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>

  LiquidCrystal_I2C* lcd = nullptr;  // Pointer az LCD-hez
  byte lcdAddress = 0;               // Tárolni fogjuk a talált címet

  void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    // Megkeressük az I2C eszközt
    for (byte i = 8; i < 120; i++) {
      Wire.beginTransmission(i);
      if (Wire.endTransmission() == 0) {
        Serial.print("Found address: ");
        Serial.print(i, DEC);
        Serial.print(" (0x");
        Serial.print(i, HEX);
        Serial.println(")");
        
        if (lcdAddress == 0) {
          lcdAddress = i;
          Serial.print("Using this address for LCD: 0x");
          Serial.println(lcdAddress, HEX);
        } 
      }            
    } 
  }  

  void loop() {
    if (lcd != nullptr) {
      lcd->clear();
      lcd->setCursor(2,0)
      lcd->print("My address:")
      lcd->setCursor(2,1)
      lcd-> print(lcdAddress)
    }
  }
  ```
</details>


### Többszálúsítás - szemafor kezelés

> ***Ismétlés:***
>
> A többszálúsítás (multithreading) az ESP32-ben a FreeRTOS operációs rendszeren keresztül valósul meg. Lehetővé teszi, hogy több feladat párhuzamosan fusson, még akkor is, ha csak egy vagy két processzormag van. Ez különösen hasznos, ha egy mikrokontroller több független műveletet kell kezelje egyszerre (pl. szenzor olvasása, adatok küldése, LED vezérlés).
>
> **Semafor (Semaphore)** olyan szinkronizációs primitív, amely megakadályozza a versengést (race condition) megosztott erőforrások eléréséhez. Amikor több feladat ugyanazt az adatot szeretné módosítani, a szemafor biztosítja, hogy csak egy feladat férjen hozzá egyszerre. Az `xSemaphoreTake()` lefoglalja a szemafort, az `xSemaphoreGive()` felszabadítja.
>
> **Gyakorlatban:** Ha egy feladat szenzor adatokat olvas, egy másik pedig soros porton küldi, a szemafor védi az `sensorData` közös változót az inkonzisztencia ellen.


Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino
  #include <freertos/FreeRTOS.h>
  #include <freertos/task.h>
  #include <freertos/semphr.h>

  SemaphoreHandle_t xMutex;
  int sharedCounter = 0;

  void task1(void *pvParameters) {
    while(1) {
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        sharedCounter++;
        Serial.print("Task 1 - Counter: ");
        Serial.println(sharedCounter);
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

  void task2(void *pvParameters) {
    while(1) {
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        sharedCounter += 2;
        Serial.print("Task 2 - Counter: ");
        Serial.println(sharedCounter);
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }

  void setup() {
    Serial.begin(115200);
    xMutex = xSemaphoreCreateMutex();
    
    xTaskCreatePinnedToCore(task1, "Task1", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(task2, "Task2", 2048, NULL, 1, NULL, 1);
  }

  void loop() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  ```
</details>

### Többszálúsítás - szenzor és kommunikáció kezelés

Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino
  #include <freertos/FreeRTOS.h>
  #include <freertos/task.h>
  #include <freertos/semphr.h>

  SemaphoreHandle_t xMutex;
  int sensorData = 0;

  void sensorTask(void *pvParameters) {
    while(1) {
      int rawValue = analogRead(A0);
      
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        sensorData = rawValue;
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }

  void communicationTask(void *pvParameters) {
    while(1) {
      if (xSemaphoreTake(xMutex, portMAX_DELAY)) {
        Serial.print("Sensor value: ");
        Serial.println(sensorData);
        xSemaphoreGive(xMutex);
      }
      vTaskDelay(500 / portTICK_PERIOD_MS);
    }
  }

  void setup() {
    Serial.begin(115200);
    pinMode(A0, INPUT);
    xMutex = xSemaphoreCreateMutex();
    
    xTaskCreatePinnedToCore(sensorTask, "SensorTask", 2048, NULL, 1, NULL, 0);
    xTaskCreatePinnedToCore(communicationTask, "CommTask", 2048, NULL, 1, NULL, 1);
  }

  void loop() {
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  ```

</details>

Linkek, anyagok:

### Többszálúsítás - szenzor és aktivátor kezelés

Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino
  
  ```

</details>

Linkek, anyagok:


## Micropython
Linkek, anyagok:
- https://roboticcoding.com/is-micropython-better-than-arduino/
- https://docs.pycom.io/docnotes/examples/
- https://randomnerdtutorials.com/projects-esp32-esp8266-micropython/

| Funkció        | Arduino (C++)                         | MicroPython                            |
|----------------|---------------------------------------|----------------------------------------|
| **Végrehajtás**  | Fordított (Natív gépi kód)        | Értelmezett (Bájtokód)                 |
| **Sebesség**      | Villámgyors (Valós idejű)              | Lassabb (Magas szintű terhelés)           |
| **Könnyű használat**| Közepes (C++ szintaxis)                 | Magas (Pythonic szintaxis)                 |
| **Memóriahasználat** | Nagyon hatékony                      | Nagyobb (Több RAM szükséges)              |
| **Hibakeresés**  | Fordítás, feltöltés, ismétlés               | Élő REPL-en keresztül (Azonnali)                |
| **Legjobb a következőhöz**   | Komoly robotika és alacsony fogyasztású rendszerek | IoT, gyors prototípusok, MI             |

### Hardver kompatibilitás: Mely táblák működnek a MicroPython-nal és Arduino-val?
- Arduino Uno (Atmega328P): ❌ Nincs MicroPython támogatás (Nem elég RAM).
- ESP32: ✅ Kiváló mindkettőhöz. Ez a "ideális pont" a MicroPython-hoz.
- Raspberry Pi Pico: ✅ A MicroPython-hoz készült, de jó Arduino támogatásai is vannak.
- STM32 sorozat: ✅ Erős támogatás mindkettőhöz.


### Hello world - szenzor - aktivátor péla

Futtatható példakód: 

<details>
  <summary><b>Példa kód</b></summary>
  <br>

  ```Arduino  
  ```
</details>

## Haladóknak
### `External Interrupt`
![](https://cdn.sparkfun.com/assets/home_page_posts/2/6/0/8/2018-02-06_-_External_Interrupts_cr.png)

Level Up Your Arduino Code: External Interrupts: https://www.youtube.com/watch?v=J61_PKyWjxU
  
### ESP Home
Linkek, anyagok:
- https://www.home-assistant.io/
- https://esphome.io/guides/getting_started_hassio/

### Micro ROS
Linkek, anyagok:
- https://micro.ros.org/
- https://www.hackster.io/514301/micro-ros-on-esp32-using-arduino-ide-1360ca
- https://discourse.openrobotics.org/t/micro-ros-esp32-cam/18827
- https://robofoundry.medium.com/building-cheapest-ros2-robot-using-esp32-part-3-simulation-ff00b2e06681
  
### Alacsony szintű programozás
Linkek, anyagok:
- https://sam-mundayhall.medium.com/advanced-arduino-programming-led-blink-part-1-ccaaabfcefe2

### Beágyazott AI
Linkek, anyagok:
- Tiny ML: https://www.datacamp.com/blog/what-is-tinyml-tiny-machine-learning
- Edge AI - Edge Impulse: https://www.edgeimpulse.com/edge-impulse-for-students#take-course

## Izgalmas projektek
### DOOM
Linkek, anyagok:
- https://esp32.com/viewtopic.php?t=2338
- https://hackaday.io/project/192783/instructions

Próbáld ki: 
- https://wokwi.com/projects/398699683506946049

### Mikrokontroller vezérelt drón
#### ESP FLY
Linkek, anyagok:
- https://www.youtube.com/watch?v=V_mZsiZcy7s
- https://forum.seeedstudio.com/t/build-the-smallest-esp32-drone-you-can-fly-with-your-phone-esp-fly/294670
- https://www.elektormagazine.com/labs/esp-fly-the-smallest-esp32-drone-you-can-build
  
#### ESP Drone
Linkek, anyagok:
- https://github.com/espressif/esp-drone
- https://docs.espressif.com/projects/espressif-esp-drone/en/latest/gettingstarted.html