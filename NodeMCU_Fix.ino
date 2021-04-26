#define BLYNK_PRINT Serial
#include <SoftwareSerial.h>
#include <BlynkSimpleEsp8266.h>
#include <ESP8266WiFi.h>
BlynkTimer timer;

// ================= CONNECT TO WIFI ================
char auth[] = "9BzOfh-PUcR4TSZNZawfoXJb6EaTLg2V";
char ssid[] = "Redmi";
char pass[] = "testtest";
int LDR;

SoftwareSerial NodeMCU(D1, D2);

void mendung () {
  while (NodeMCU.available() > 0) {
    LDR = NodeMCU.parseInt();
    if (NodeMCU.read() == '\n') {
      Serial.println(LDR);
      if(LDR>200){
      Blynk.notify("Cuaca Sedang Mendung, Angkat Segera Pakaian Dari Jemuran Anda");  
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  NodeMCU.begin(4800);
  Blynk.begin(auth, ssid, pass);
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  timer.setInterval(400L, mendung);
}

void loop() {
  Blynk.run();
  timer.run();
}
