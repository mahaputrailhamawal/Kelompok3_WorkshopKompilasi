//sesuikan posisi pin select
#define s0 D3
#define s1 D2
#define s2 D1
 
//gunakan A0 sebagai input
int analogPin = 0;
 
//variabel untuk menyimpan nilai input
int nilaiInput = 0;
 
void setup() {
  //jadikan pin select sebagai output
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
 
  //aktifkan komunikasi serial
  Serial.begin(9600);
}
 
void loop() {
  inputMultiplekser(0);
  nilaiInput = analogRead(analogPin);
  Serial.print(nilaiInput);
  Serial.print(" ");
   
  inputMultiplekser(1);
  nilaiInput = analogRead(analogPin);
  Serial.println(nilaiInput);
  delay(500);
}
 
 
void inputMultiplekser(int y){
  if (y==0){
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
  else if (y==1){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
  else if (y==2){
    digitalWrite(s0,LOW);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else if (y==3){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,LOW);
  }
  else if (y==4){
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
  }
  else if (y==5){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,LOW);
    digitalWrite(s2,HIGH);
  }
  else if (y==6){
    digitalWrite(s0,LOW);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
  }
  else if (y==7){
    digitalWrite(s0,HIGH);
    digitalWrite(s1,HIGH);
    digitalWrite(s2,HIGH);
  }
  //jika input bukan 0-7, maka jadikan y0
  else {
    digitalWrite(s0,LOW);
    digitalWrite(s1,LOW);
    digitalWrite(s2,LOW);
  }
}
