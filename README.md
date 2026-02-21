# Szenzormodalitások - Arduino bevezetés
- https://www.tinkercad.com/joinclass/FBXMSJFMM

## Mikrokontrollerek VS számítógépek 

### Embedded Linux
Linkek, anyagok:
https://www.windriver.com/solutions/learning/embedded-linux

## Arduino
Linkek, anyagok:
- https://docs.arduino.cc/arduino-cloud/guides/editor

### `Hello world`
https://www.tinkercad.com/things/4O3nPQPU3fB-console-hello-world
```C++
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
### Hello world - blinking led
https://www.tinkercad.com/things/40oyIzZqLwF-arduino-hello-world
```C++
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

## ESP32
Linkek, anyagok:

## Micropython
Linkek, anyagok:
- https://roboticcoding.com/is-micropython-better-than-arduino/
- https://docs.pycom.io/docnotes/examples/
- https://randomnerdtutorials.com/projects-esp32-esp8266-micropython/

### Arduino vs. MicroPython

| Feature        | Arduino (C++)                         | MicroPython                            |
|----------------|---------------------------------------|----------------------------------------|
| **Execution**  | Compiled (Native Machine Code)        | Interpreted (Bytecode)                 |
| **Speed**      | Blazing Fast (Real-time)              | Slower (High-level overhead)           |
| **Ease of Use**| Moderate (C++ syntax)                 | High (Pythonic syntax)                 |
| **Memory Usage** | Very Efficient                      | Heavy (Requires more RAM)              |
| **Debugging**  | Compile, Upload, Repeat               | Live via REPL (Instant)                |
| **Best For**   | Hardcore Robotics & Low-power systems | IoT, Rapid Prototyping, AI             |

### Hardware Compatibility: Which Boards Play Nice With MicroPython and Arduino?
- Arduino Uno (Atmega328P): ❌ No MicroPython (Not enough RAM).
- ESP32: ✅ Excellent for both. This is the “sweet spot” for MicroPython.
- Raspberry Pi Pico: ✅ Built for MicroPython, but has great Arduino support too.
- STM32 Series: ✅ Strong support for both.

## Haladóknak
### `External Interrupt`
![](https://cdn.sparkfun.com/assets/home_page_posts/2/6/0/8/2018-02-06_-_External_Interrupts_cr.png)

Level Up Your Arduino Code: External Interrupts: https://www.youtube.com/watch?v=J61_PKyWjxU
  
### ESP Home
Linkek, anyagok:
- https://www.home-assistant.io/
- https://esphome.io/guides/getting_started_hassio/

### micro ROS
Linkek, anyagok:
- https://micro.ros.org/
- https://www.hackster.io/514301/micro-ros-on-esp32-using-arduino-ide-1360ca
- https://discourse.openrobotics.org/t/micro-ros-esp32-cam/18827
- https://robofoundry.medium.com/building-cheapest-ros2-robot-using-esp32-part-3-simulation-ff00b2e06681
  
### alacsony szintű programozás
Linkek, anyagok:
- https://sam-mundayhall.medium.com/advanced-arduino-programming-led-blink-part-1-ccaaabfcefe2

### beágyazott AI
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
