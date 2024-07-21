#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial
#define BUZZER_PIN 2  //Digital Pin 4
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire, -1);
char auth[] = "TuKr5SLU6z2R_VOJTkTlO4hYfm-c-YxU";
const char *ssid = "aady.ide";
const char *password = "malamahitnahi";
int check = 0;          // Digital Pin 3
int value = 0;
const long utcOffsetInSeconds = 19800;
BlynkTimer timer;
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(115200);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(check, INPUT);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  Blynk.begin(auth, ssid, password);
  timeClient.update();
}
void buzzer()  // buzzer beep
{
  
value=digitalRead(check);
switch (value)
{
  case 0:  // if lid is close
      digitalWrite(BUZZER_PIN, HIGH);
      delay(500);
      digitalWrite(BUZZER_PIN, LOW);
      delay(500);
      break;
  case 1:  // if lid is open
      digitalWrite(BUZZER_PIN, LOW);
      break;


}
}
void disp()  //oled display commands
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Please");
  display.setCursor(0, 14);
  display.print("take the  medicine!! ");
  display.display();
  dig();
}
void dig()
{
  Blynk.virtualWrite(V8, timeClient.getFormattedTime());
}
void loop() {
  Blynk.run();
  timer.run(); // Check the sensor status
  dig(); 
Blynk.virtualWrite(V7,"  "); 
display.clearDisplay();
display.setTextSize(2);
display.setTextColor(WHITE);
display.setCursor(0, 0);
display.print(timeClient.getFormattedTime());
display.display();
int h = timeClient.getHours();
int m = timeClient.getMinutes();
int s = timeClient.getSeconds();

if (h == 11 && m == 20 && s == 00)  //first medicine
{
  for (s = 00; s <= 9; s++) {

    Blynk.virtualWrite(V7, "Time for medicine!!");
    buzzer();
    disp();
  }
} else if (h == 9 && m == 11 && s == 00)  //second medicine
{
  for (s = 00; s <= 9; s++) {
    Blynk.virtualWrite(V7, "Time for medicine!!");
    buzzer();
    disp();
  }
} else if (h == 22 && m == 20 && s == 00)  //third medicine
{
  for (s = 00; s <= 9; s++) {
    Blynk.virtualWrite(V7, "Time for medicine!!");
    buzzer();
    disp();
  }
}
delay(1000);
}
