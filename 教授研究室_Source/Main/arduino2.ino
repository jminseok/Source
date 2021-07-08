#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"
#include <Adafruit_GPS.h>

#define mySerial Serial

Adafruit_GPS GPS(&mySerial);

#define GPSECHO  true
const int buzzer = A3; //buzzer to arduino pin A3
const int read = A2; //Sensor A2 pin to Arduino pin A2
int value;          //Variable to store the incomming data
//segments
int a = 0;
int b = 1;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
//decimal point
int p = 9;
//digits
int d3 = 10;
int d2 = 11;
int d1 = 12;
//other
long n = 0;
int x = 100;
int del = 45;

boolean usingInterrupt = false;
void useInterrupt(boolean); // Func prototype keeps Arduino 0023 happy

#ifdef __AVR__
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();

#ifdef UDR0
  if (GPSECHO)
    if (c) UDR0 = c;  
#endif
}

uint32_t timer = millis();

Adafruit_BicolorMatrix matrix = Adafruit_BicolorMatrix();

void setup() {
  Serial.begin(9600);
  Serial.println("8x8 LED Matrix Test");
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  matrix.begin(0x70);  // pass in the address
     
  Serial.begin(115200);
  Serial.println("Adafruit GPS library basic test!");
// 여기서부터 gps
  GPS.begin(9600);
  mySerial.begin(9600);
  
  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);
  

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   

  GPS.sendCommand(PGCMD_ANTENNA);

#ifdef __arm__
  usingInterrupt = false;  //NOTE - we don't want to use interrupts on the Due
#else
  useInterrupt(true);
#endif

  delay(1000);
  // Ask for firmware version
  mySerial.println(PMTK_Q_RELEASE);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(p, OUTPUT);
}
void pickDigit(int x)
{
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  //digitalWrite(d4, LOW);
  
  switch(x)
  {
    case 1: digitalWrite(d1, HIGH); break;
    case 2: digitalWrite(d2, HIGH); break;
    case 3: digitalWrite(d3, HIGH); break;
    //default: digitalWrite(d4, HIGH); break;
  }
}

static const uint8_t PROGMEM
  wait_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00000000 },
  start_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00000001 },
  goldtime1_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00000001 },
  goldtime2_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00000011 },
  goldtime3_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00000111 },
  goldtime4_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00001111 },
  goldtime5_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00011111 },
  goldtime6_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B00111111 },
  goldtime7_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B01111111 },
  goldtime8_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B00000000,    B11111111 },
    goldtime9_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B00000000,    B10000000,    B11111111 },
    goldtime10_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B00000000,    B10000000,    B10000000,    B11111111 },
    goldtime11_bmp[] =
  { B00000000,    B00000000,    B00000000,    B00000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime12_bmp[] =
  { B00000000,    B00000000,    B00000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime13_bmp[] =
  { B00000000,    B00000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime14_bmp[] =
  { B00000000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime15_bmp[] =
  { B10000000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime16_bmp[] =
  { B11000000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime17_bmp[] =
  { B11100000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime18_bmp[] =
  { B11110000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime19_bmp[] =
  { B11111000,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime20_bmp[] =
  { B11111100,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime21_bmp[] =
  { B11111110,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime22_bmp[] =
  { B11111111,    B10000000,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime23_bmp[] =
  { B11111111,    B10000001,    B10000000,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime24_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000000,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime25_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000000,    B10000000,    B10000000,    B11111111 },
    goldtime26_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000000,    B10000000,    B11111111 },
    goldtime27_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10000000,    B11111111 },
    goldtime28_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10000001,    B11111111 },
    goldtime29_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10000011,    B11111111 },
    goldtime30_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10000111,    B11111111 },
    goldtime31_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10001111,    B11111111 },
    goldtime32_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10001111,    B11111111 },
    goldtime33_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10011111,    B11111111 },
    goldtime34_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B10111111,    B11111111 },
    goldtime35_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B10000001,    B11111111,    B11111111 },
    goldtime36_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B10000001,    B11000001,    B11111111,    B11111111 },
    goldtime37_bmp[] =
  { B11111111,    B10000001,    B10000001,    B10000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime38_bmp[] =
  { B11111111,    B10000001,    B10000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime39_bmp[] =
  { B11111111,    B10000001,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime40_bmp[] =
  { B11111111,    B11000001,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime41_bmp[] =
  { B11111111,    B11100001,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime42_bmp[] =
  { B11111111,    B11110001,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime43_bmp[] =
  { B11111111,    B11111001,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime44_bmp[] =
  { B11111111,    B11111101,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime45_bmp[] =
  { B11111111,    B11111111,    B11000001,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime46_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000001,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime47_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000001,    B11000001,    B11111111,    B11111111 },
    goldtime48_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11000001,    B11111111,    B11111111 },
    goldtime49_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11000011,    B11111111,    B11111111 },
    goldtime50_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11000111,    B11111111,    B11111111 },
    goldtime51_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11001111,    B11111111,    B11111111 },
    goldtime52_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11011111,    B11111111,    B11111111 },
    goldtime53_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11000011,    B11111111,    B11111111,    B11111111 },
    goldtime54_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11000011,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime55_bmp[] =
  { B11111111,    B11111111,    B11000011,    B11100011,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime56_bmp[] =
  { B11111111,    B11111111,    B11100011,    B11100011,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime57_bmp[] =
  { B11111111,    B11111111,    B11110011,    B11100011,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime58_bmp[] =
  { B11111111,    B11111111,    B11111011,    B11100011,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime59_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11100111,
    B11100011,    B11111111,    B11111111,    B11111111 },
    goldtime60_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11100111,
    B11100111,    B11111111,    B11111111,    B11111111 },
    goldtime61_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11100111,
    B11101111,    B11111111,    B11111111,    B11111111 },
    goldtime62_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11100111,
    B11111111,    B11111111,    B11111111,    B11111111 },
    goldtime63_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11110111,
    B11111111,    B11111111,    B11111111,    B11111111 },
    goldtime64_bmp[] =
  { B11111111,    B11111111,    B11111111,    B11111111,
    B11111111,    B11111111,    B11111111,    B11111111 };

void pickNumber(int x)
{
  switch(x)
  {
    default: zero(); break;
    case 1: one(); break;
    case 2: two(); break;
    case 3: three(); break;
    case 4: four(); break;
    case 5: five(); break;
    case 6: six(); break;
    case 7: seven(); break;
    case 8: eight(); break;
    case 9: nine(); break;
  }
}

void dispDec(int x)
{
  digitalWrite(p, LOW);
}

void clearLEDs()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
  digitalWrite(p, HIGH);
}

void zero()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, HIGH);
}

void one()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void two()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, HIGH);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void three()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
}

void four()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void five()
{
  digitalWrite(a, LOW);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void six()
{
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void seven()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, HIGH);
}

void eight()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void nine()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}
void playthejaket()
{
   Serial.println("Water level: Danger!");   
   tone(buzzer, 1000); // Send 1KHz sound signal...
   delay(1000);        // ...for 1 sec
   noTone(buzzer);     // Stop sound...
   delay(1000);        // ...for 1sec
   if (! usingInterrupt) {
      char c = GPS.read();
   if (GPSECHO)
      if (c) Serial.print(c);
   }
   if (GPS.newNMEAreceived()){
      if (!GPS.parse(GPS.lastNMEA())) 
          return; 
   }
  
   if (timer > millis())  timer = millis();
  
   if (millis() - timer > 2000) { 
       timer = millis(); // reset the timer
   
     Serial.print("\nTime: ");
     Serial.print(GPS.hour, DEC); Serial.print(':');
     Serial.print(GPS.minute, DEC); Serial.print(':');
     Serial.print(GPS.seconds, DEC); Serial.print('.');
     Serial.println(GPS.milliseconds);
     Serial.print("Date: ");
     Serial.print(GPS.day, DEC); Serial.print('/');
     Serial.print(GPS.month, DEC); Serial.print("/20");
     Serial.println(GPS.year, DEC);
     Serial.print("Fix: "); Serial.print((int)GPS.fix);
     Serial.print(" quality: "); Serial.println((int)GPS.fixquality); 
       if (GPS.fix) {
         Serial.print("Location: ");
         Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
          Serial.print(", "); 
          Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      
          Serial.print("Speed (knots): "); Serial.println(GPS.speed);
          Serial.print("Angle: "); Serial.println(GPS.angle);
          Serial.print("Altitude: "); Serial.println(GPS.altitude);
          Serial.print("Satellites: "); Serial.println((int)GPS.satellites);
        }
    }
  clearLEDs();
  pickDigit(1);
  dispDec(1);
  pickNumber((n/x/1000)%10);
  delayMicroseconds(del);
  clearLEDs();
  pickDigit(2);
  pickNumber((n/x/100)%10);
  delayMicroseconds(del);
  clearLEDs();
  pickDigit(3);
  pickNumber((n/x/10)%10);
  delayMicroseconds(del);
  n++;
}

void loop() {
  value = analogRead(read); //Read data from analog pin and store it to value variable
    if (value<=400){ 
    Serial.println("Water level: Safe!"); 
    matrix.clear();
    matrix.drawBitmap(0, 0, wait_bmp, 8, 8, LED_RED);
    matrix.writeDisplay();
  delay(1000);
  }
  else if (value>400){ 
   // 첫 시작
  matrix.clear();
  matrix.drawBitmap(0, 0, start_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
    
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime1_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);
  
   playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime2_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime3_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime4_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime5_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);
  
  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime6_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime7_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);
  
  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime8_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime9_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime10_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime11_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime12_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime13_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime14_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime15_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime16_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime17_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime18_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

 playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime19_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime20_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime21_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime22_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime23_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);
  
  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime24_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime25_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime26_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime27_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime28_bmp, 8, 8, LED_GREEN);
  matrix.writeDisplay();
  delay(1000);

 playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime29_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime30_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

 playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime31_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime32_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime33_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime34_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime35_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime36_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime37_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime38_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime39_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime40_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime41_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime42_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime43_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime44_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime45_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime46_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime47_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime48_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime49_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime50_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime51_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime52_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime53_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime54_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime55_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime56_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime57_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime58_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime59_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime60_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(1000);

  playthejaket();
  
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime61_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime61_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime61_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime61_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime62_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime62_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime62_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime62_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime63_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime63_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime63_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime63_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();

  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime64_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime64_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime64_bmp, 8, 8, LED_YELLOW);
  matrix.writeDisplay();
  delay(250);
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime64_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  delay(250);
  playthejaket();
 
  while(goldtime64_bmp){
  matrix.clear();
  matrix.drawBitmap(0, 0, goldtime64_bmp, 8, 8, LED_RED);
  matrix.writeDisplay();
  playthejaket();
  }
  
  matrix.setTextWrap(false);
  }
  delay(5000);
}

void useInterrupt(boolean v) {
  if (v) {
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}
#endif //#ifdef__AVR__

