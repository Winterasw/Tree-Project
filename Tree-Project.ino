#include <Arduino.h>
#include <TridentTD_LineNotify.h>
#define BLYNK_TEMPLATE_ID "TMPL65caLrBaC"
#define BLYNK_TEMPLATE_NAME "Tree"
#define BLYNK_AUTH_TOKEN "ruGoHbbqNxhG2F6Frt7m0rB2h8evbp83"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Asaiwn_2.4G";
char pass[] = "0909287745";

BlynkTimer timer;
String LINE_TOKEN = "c3SJZeSqSV3XLFUZHnjAtKA9oXuPBrR9uVoDQJjAZ3p";   //Line Token

int moisture = 0;
BLYNK_CONNECTED() {
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent() {
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, millis() / 1000);
}

void setup() {

  // Init USB serial port for debugging
  Serial.begin(115200);
  Serial.println(LINE.getVersion());
  LINE.setToken(LINE_TOKEN);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

  pinMode(V33, OUTPUT);  // 3v3 Temp
  pinMode(A0, INPUT);    //moisture
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  LINE.notify("Starting ...");

  
  
}

void loop() {

  delay(100);
  Blynk.run();
  timer.run();

      moisture = map(analogRead(A0), 0, 1024, 0, 100);  // Read "A1" moisture pin

    Serial.print(moisture);
    Blynk.virtualWrite(V1, moisture);  // V1 = Humidity

    if (moisture < 40) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println(" | Humidity < 40");
      LINE.notify("ความชื้นน้อยกว่า 40% โปรดรดน้ำด้วยคร้าบ!!!");
      Blynk.virtualWrite(V2, 1);// blynk alert

    } else if (moisture > 60) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println(" | Humidity > 60");
      LINE.notify("ความชื้นมากกว่า 60% แล้วคร้าบ!!!");
      Blynk.virtualWrite(V2, 1); // blynk alert

    } else {
      Serial.println(" | Humidity normal");
      digitalWrite(LED_BUILTIN, HIGH);
    }
    delay(3000);
}

