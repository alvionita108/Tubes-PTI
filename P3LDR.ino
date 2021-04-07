const int LDR = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LDR,INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int intensity = analogRead(LDR);
  Serial.println(condition(intensity));
  delay(500);
}

String condition(int intensity){
  int intMapped = map(intensity, 0, 1023, 0, 3);
  if(intMapped==1) return "Gelap";
  else if(intMapped==2) return "Mendung";
  else return "Cerah";
}
