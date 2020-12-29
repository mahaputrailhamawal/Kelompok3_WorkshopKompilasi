
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define s0 D3
#define s1 D2
#define s2 D1

char auth[] = "rEXc4HKU6BkbQtJc_Xj1iZDfErnRU3Hq";

char ssid[] = "IndiHome";
char pass[] = "jahemerah";

int analogPin = 0;

float sensor1;
float sensor2;
float suhu[3], kelembaban[3], rule[3][3];
float defuzzy;
int out[9];

void Fuzzyfikasi() {
  
  //Suhu

  //Dingin
  if (sensor1 <= 12)
    suhu [0] = 1;
  else if (sensor1 > 12 && sensor1 < 20)
    suhu [0] = (20 - sensor1) / 8;
  else if (sensor1 >= 20)
    suhu [0] = 0;
  //Sedang
  if (sensor1 == 26)
    suhu [1] = 1;
  else if (sensor1 > 16 && sensor1 < 26)
    suhu [1] = (sensor1 - 16) / 10;
  else if (sensor1 > 26 && sensor1 < 30)
    suhu [1] = (30 - sensor1) / 4;
  else if (sensor1 <= 16 || sensor1 >= 30)
    suhu [1] = 0;
  //Panas
  if (sensor1 <= 28)
    suhu [2] = 0;
  else if (sensor1 > 28 && sensor1 < 35)
    suhu [2] = (sensor1 - 28) / 10;
  else if (sensor1 >= 35)
    suhu [2] = 1;

  //Kelembaban
  //Kering
  if (sensor2 <= 30)
    kelembaban [0] = 1;
  else if (sensor2 > 30 && sensor2 < 45)
    kelembaban [0] = (45 - sensor2) / 15;
  else if (sensor2 >= 45)
    kelembaban [0] = 0;
  //Ideal
  if (sensor2 == 55)
    kelembaban [1] = 0;
  else if (sensor2 > 40 && sensor2 < 55)
    kelembaban [1] = (sensor2 - 40) / 15;
  else if (sensor2 > 55 && sensor2 < 70)
    kelembaban [1] = (70 - sensor2) / 15;
  else if (sensor2 <=40 || sensor2 >= 70)
    kelembaban [1] = 0;
  //Lembab
  if (sensor2 <= 70)
    kelembaban [2] = 0;
  else if (sensor2 > 70 && sensor2 < 80)
    kelembaban [2] = (sensor2 - 70) / 10;
  else if (sensor2 >= 80);
    kelembaban [2] = 1;
}

float Min (float a, float b) {
  float min;
  if (a < b) min = a;
  else min = b;
  return min;
}

void Rule() {
  
  for (int i=0; i<3; i++){
    for(int j=0; j<3; j++){
      rule[j][i] = Min(suhu[j],kelembaban[i]);
    }
  }
  
  // //Rule1
  // rule[0][0] = Min(suhu[0], kelembaban[0]);
  // out[0] = 55;
  // //Rule2
  // rule[1][0] = Min(suhu[1], kelembaban[0]);
  // out[1] = 55;
  // //Rule3
  // rule[2][0] = Min(suhu[2], kelembaban[0]);
  // out[2] = 100;
  // //Rule4
  // rule[0][1] = Min(suhu[0], kelembaban[1]);
  // out[3] = 25;
  // //Rule5
  // rule[1][1] = Min(suhu[1], kelembaban[1]);
  // out[4] = 55;
  // //Rule6
  // rule[2][1] = Min(suhu[2], kelembaban[1]);
  // out[5] = 100;
  // //Rule7
  // rule[0][2] = Min(suhu[0], kelembaban[2]);
  // out[6] = 25;
  // //Rule8
  // rule[1][2] = Min(suhu[1], kelembaban[2]);
  // out[7] = 25;
  // //Rule9
  // rule[2][2] = Min(suhu[2], kelembaban[2]);
  // out[8] = 55;
}

void Defuzzyfikasi(){
  float RPM_Rendah = 25;
  float RPM_Sedang = 55;
  float RPM_Tinggi = 100;
  
  float pembilang, penyebut = 0.00;
  
  Rule();
  
  pembilang = rule[0][0]*RPM_Sedang + rule[1][0]*RPM_Sedang + rule[2][0]*RPM_Tinggi + rule[0][1]*RPM_Rendah + rule[1][1]*RPM_Sedang + rule[2][1]*RPM_Tinggi + rule[0][2]*RPM_Rendah + rule[1][2]*RPM_Rendah + rule[2][2]*RPM_Sedang;
  
  for (int i=0; i<3; i++){
    for (int j=0; j<3; j++){
      penyebut = penyebut + rule[j][i];
    }
  }
  //Serial.print("Pembilang Penyebut : "); Serial.print(pembilang); Serial.print(" ");Serial.println(penyebut);
  defuzzy = pembilang / penyebut;
 
}



void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  sensor1 = analogRead(analogPin);
  sensor1 = map(sensor1,0,1023,0,45);
  sensor2 = analogRead(analogPin);
  sensor2 = map(sensor2,0,1023,0,100);
  
  Fuzzyfikasi();
  Defuzzyfikasi();
  
  Serial.print("Suhu : ");Serial.print(sensor1);Serial.print(" , Kelembaban : ");Serial.println(sensor2);
  delay(1000);
  Serial.print("RPM AC : ");Serial.println(defuzzy);
  Blynk.virtualWrite(V5,defuzzy);
  delay(1000);
  Blynk.run();
}
