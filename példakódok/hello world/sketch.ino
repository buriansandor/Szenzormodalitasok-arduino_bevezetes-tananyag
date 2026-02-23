#define LED_PIN 2

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);
}

void loop()
{
  digitalWrite(LED_PIN, HIGH);
  Serial.println("LED is ON");
  delay(1000);
  
  digitalWrite(LED_PIN, LOW);
  Serial.println("LED is OFF");
  delay(1000);
}