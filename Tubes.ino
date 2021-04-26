#include <require_cpp11.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <RTClib.h>
SoftwareSerial ArduinoUno (2, 8);
RTC_DS3231 rtc;

int sensorLDR = A0;
const int sensorMin = 0;
const int sensorMax = 1024;
int sensorHujan = A2;
int Buzzer = 4;
char Days[7][12] = {"Minggu", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};
String hari;
int tgl, bulan, th, jam, menit, detik;
int relay = 6;


void setup() {
  Serial.begin(9600);
  pinMode(Buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
  Serial.begin(9600);
  ArduinoUno.begin(4800);

  //Setting Waktu
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2021, 04, 18, 15, 0, 0));
}

void loop() {
  int nilaiSensorLDR = analogRead(sensorLDR);
  int nilaiSensorHujan = analogRead(sensorHujan);
  ArduinoUno.print(nilaiSensorLDR);
  ArduinoUno.println("\n");
  int range = map(nilaiSensorHujan, sensorMin, sensorMax, 0, 2);
  Serial.print("Nilai Sensor : ");
  Serial.println(nilaiSensorLDR);
  
  //RTC
  DateTime now = rtc.now();
  hari    = Days[now.dayOfTheWeek()];
  tgl     = now.day(), DEC;
  bulan   = now.month(), DEC;
  th      = now.year(), DEC;
  jam     = now.hour(), DEC;
  menit   = now.minute(), DEC;
  detik   = now.second(), DEC;

  Serial.println(String() + hari + ", " + tgl + "-" + bulan + "-" + th);
  Serial.println(String() + jam + ":" + menit + ":" + detik);
  Serial.println();

  digitalWrite(relay, LOW);
    if (nilaiSensorLDR < 200){
      Serial.println("Terang");
    }else{
      Serial.println("Mendung");
    }

    switch(range){
      case 0:
        digitalWrite(Buzzer, HIGH);
        delay(5000);
        Serial.println("Hujan");
      case 1:
        Serial.println("Tidak Hujan");
        delay(5000);
      
    }
  
  
  delay(1000);
}
