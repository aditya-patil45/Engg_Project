#define BLYNK_TEMPLATE_ID "TMPL3rKv1VYTW"
#define BLYNK_TEMPLATE_NAME "Pothole detection Robot 186"
#define BLYNK_AUTH_TOKEN "MOtOIE848X-npHvjP9ju5MEDKEhpN-Ow"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>
Servo servo;
//Motor PINs
#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
#define ENB D5
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
int Speed;
char auth[] = "MOtOIE848X-npHvjP9ju5MEDKEhpN-Ow"; //Enter your Blynk application auth
token
char ssid[] = "PotholeDetection"; //Enter your WIFI name
char pass[] = "1234567890"; //Enter your WIFI passowrd
const int trigPin = 12;
const int echoPin = 13;
//D6
//D7
//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_TO_INCH 0.393701
long duration;
float distanceCm;
float distanceInch;
void setup() {
Serial.begin(9600);
pinMode(ENA, OUTPUT);
pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
pinMode(ENB, OUTPUT);
Blynk.begin(auth, ssid, pass);
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
servo.attach(15); //D8
servo.write(0);
delay(2000);
}
BLYNK_WRITE(V0) {
forward = param.asInt();
}
BLYNK_WRITE(V1) {
backward = param.asInt();
}
BLYNK_WRITE(V2) {
right = param.asInt();
}
BLYNK_WRITE(V3) {
left = param.asInt();
}
BLYNK_WRITE(V4) {
Speed = param.asInt();
}
void smartcar() {
if (forward == 1) {
carforward();
Serial.println("carforward");
} else if (backward == 1) {
carbackward();
Serial.println("carbackward");
} else if (left == 1) {
    carturnleft();
Serial.println("carfleft");
} else if (right == 1) {
carturnright();
Serial.println("carright");
} else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
carStop();
Serial.println("carstop");
}
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculate the distance
distanceCm = duration * SOUND_VELOCITY/2;
// Convert to inches
distanceInch = distanceCm * CM_TO_INCH;
// Prints the distance on the Serial Monitor
Serial.print("Distance (cm): ");
Serial.println(distanceCm);
Serial.print("Distance (inch): ");
Serial.println(distanceInch);
if(distanceCm >= 8){
Serial.println(" pothole");
servo.write(0);
//chk
delay(5000);
servo.write(90);
//chk
// delay(2000);
}
Blynk.run();
smartcar();
}
void carforward() {
analogWrite(ENA, Speed);
analogWrite(ENB, Speed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void carbackward() {
analogWrite(ENA, Speed);
analogWrite(ENB, Speed);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void carturnleft() {
analogWrite(ENA, Speed);
analogWrite(ENB, Speed);
digitalWrite(IN1, HIGH);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, HIGH);
}
void carturnright() {
analogWrite(ENA, Speed);
analogWrite(ENB, Speed);
digitalWrite(IN1, LOW);
digitalWrite(IN2, HIGH);
digitalWrite(IN3, HIGH);
digitalWrite(IN4, LOW);
}
void carStop() {
digitalWrite(IN1, LOW);
digitalWrite(IN2, LOW);
digitalWrite(IN3, LOW);
digitalWrite(IN4, LOW);
}