#include <Wire.h>
#include "SSD1306Wire.h"
#include "MAX30105.h"
#include "spo2_algorithm.h"
#include "heartRate.h"
#include <Adafruit_BMP085.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include<U8g2lib.h>
#include "OneButton.h"
#include <ArduinoJson.h>
#include <EEPROM.h>

#include "images.h"
#include "fontovi.h"
/////////////////////////Batarya/////////////////////////
int nVoltageRaw;
float fVoltage;
int btry, perc;
float fVoltageMatrix[102][2] = {
  {4.20,  100}, {4.19,  99}, {4.18,  98}, {4.17,  97}, {4.16,  96},
  {4.15, 95}, {4.14, 94}, {4.13, 93}, {4.12, 92}, {4.11, 91},
  {4.10, 90}, {4.09, 89}, {4.08, 88}, {4.07, 87}, {4.06, 86},
  {4.05, 85}, {4.04, 84}, {4.03, 83}, {4.02, 82}, {4.01, 81},
  {4.00, 80}, {3.99, 79}, {3.98, 78}, {3.97, 77}, {3.96, 76},
  {3.95, 75}, {3.94, 74}, {3.93, 73}, {3.92, 72}, {3.91, 71},
  {3.90, 70}, {3.89, 69}, {3.88, 68}, {3.87, 67}, {3.86, 66},
  {3.85, 65}, {3.84, 64}, {3.83, 63}, {3.82, 62}, {3.81, 61},
  {3.80, 60}, {3.79, 59}, {3.78, 58}, {3.77, 57}, {3.76, 56},
  {3.75, 55}, {3.74, 54}, {3.73, 53}, {3.72, 52}, {3.71, 51},
  {3.70, 50}, {3.69, 49}, {3.68, 48}, {3.67, 47}, {3.66, 46},
  {3.65, 45}, {3.64, 44}, {3.63, 43}, {3.62, 42}, {3.61, 41},
  {3.60, 40}, {3.59, 39}, {3.58, 38}, {3.57, 37}, {3.56, 36},
  {3.55, 35}, {3.54, 34}, {3.53, 33}, {3.52, 32}, {3.51, 31},
  {3.50, 30}, {3.49, 29}, {3.48, 28}, {3.47, 27}, {3.46, 26},
  {3.45, 25}, {3.44, 24}, {3.43, 23}, {3.42, 22}, {3.41, 21},
  {3.40, 20}, {3.39, 19}, {3.38, 18}, {3.37, 17}, {3.36, 16},
  {3.35, 15}, {3.34, 14}, {3.33, 13}, {3.32, 12}, {3.31, 11},
  {3.30, 10}, {3.29, 9}, {3.28, 8}, {3.27, 7}, {3.26, 6},
  {3.25, 5}, {3.24, 4}, {3.23, 3}, {3.22, 2}, {3.21, 1},
  {3.20, 0},
  {0, 0}
};
void batarya() {
  nVoltageRaw = analogRead(A0);
  fVoltage = (float)nVoltageRaw * 0.0050925207756233000;
  /* Serial.print("fVoltage:");
    Serial.println(fVoltage);*/
  for (btry = 100; btry >= 0; btry--) {
    if (fVoltageMatrix[btry][0] >= fVoltage) {
      perc = fVoltageMatrix[btry + 1][1];
      break;
    }
  }
  /*  Serial.print("perc:");
    Serial.println(perc);*/
}
/////////////////////////Batarya/////////////////////////
/////////////////////////Star wars /////////////////////////
int metx = 0;
int mety = 0;
int postoji = 0;
int nep = 8;
int smjer1 = 0;
int go = 0;
int rx = 95;
int ry = 0;
int rx2 = 95;
int ry2 = 0;
int rx3 = 95;
int ry3 = 0;
int bodovi = 0;
int brzina = 3;
int bkugle = 1;
int najmanja = 600;
int najveca = 1200;
int promjer = 10;
int rx4 = 95;
int ry4 = 0;
int zivoti = 5;
int poc1 = 0;
int ispaljeno = 0;
int nivo = 1;
int centar = 95;
unsigned long pocetno = 0;
unsigned long odabrano = 0;
unsigned long trenutno1 = 0;
unsigned long nivovrije = 0;
int poz = 30;
/////////////////////////Star Wars/////////////////////////
/////////////////////////nota/////////////////////////
#define do_ 261
#define re 294
#define mi 329
#define fa 349
#define sol 392
#define la 440
#define si 493
#define DO_ 523
int ind5 = 0;
bool melodi;
int mx33[] = {40, 40, 40, 40, 40, 40, 40, 40, 40};
int my33[] = {1, 8, 15, 22, 29, 36, 43, 50};
int my34[] = {1, 10, 20, 30, 40, 50, 60};
int sarki[] = {mi, mi, fa, sol, sol, fa, mi, re, do_, do_, re, mi, mi, re, re, mi, mi, fa, sol, sol, fa, mi, re, do_, do_, re, mi, re, do_, do_, re, re, mi, do_, re, mi, fa, mi, do_, re, mi, fa, mi, re, do_ , re, sol, mi, mi, mi, fa, sol, sol, fa, mi, re, do_, do_, re, mi, re, do_, do_};
int tokyo[] = {mi, mi, mi, mi, mi, fa, la, mi, mi, mi, fa, la, mi, mi, mi, fa, la, mi, mi, mi, fa, la, mi, mi, mi, fa, la, si, si, re, do_, si, re, do_, si, re, do_, si, la, la, re, do_, si, re, do_, si, re, do_, si, la, la, mi, fa, la, mi, mi, fa, la, mi, mi, mi, fa, la, mi, mi};
int izmir[] = {re, la, la, la, la, la, la, si, la, sol, si, la, la, re, re, do_, si, la, sol, la, sol, fa, mi, fa, la, fa, la, la, sol, fa, mi, re, fa, mi, re, DO_, re};
int mehter[] = {re, la, la, la, sol, la, si, do_, la, si, la, sol, la, sol, fa, si, la, sol, sol, la, sol, sol, la, sol, fa, mi, re, sol, sol, fa, sol, mi, DO_, re, mi, fa, mi, re};
int sarki1[] = {mi, sol, sol, re, mi, sol, re, do_, sol, do_, re, mi, sol, mi, sol, sol, re, mi, sol, re, do_, sol, do_, re, mi, sol, mi, sol, sol, re, mi, sol, re, do_, sol, do_, re, mi, sol};
/////////////////////////nota /////////////////////////
/////////////////////////notlar/////////////////////////
String not1 = "Robotics";
String not2 = "Project";
String not3 = "abc";
String not4 = "123";
String not5 = "Arduino";
String ekrannot = "RProject";
int ind8 = 0;
int mx22[] = {0, 20, 40, 60, 80, 100};
int my22[] = {50, 50, 50, 50, 50, 50};
bool notdur;
String webPagenot = "";
String webStatnot = "";
/////////////////////////notlar/////////////////////////
/////////////////////////oto ekran/////////////////////////
int sayac1 = 0;
bool otoekran;
/////////////////////////oto ekran/////////////////////////
/////////////////////////uyku/////////////////////////
int sayac = 0;
int uyku = 0;
bool uyku1 = 0;
int uykudk = 0;
int uykusaat = 0;
int uykuger = 0;
int uykugeres = 0;
int uykudkes = 0;
int uykusaates = 0;
/////////////////////////uyku bitti/////////////////////////
/////////////////////////Adım sayar/////////////////////////
float vector;
float vectorprevious;
float totalvector;
int Steps = 0;
int accelX, accelY, accelZ;
unsigned long eskiZaman = 0;
unsigned long yeniZaman;
bool ad ;
/////////////////////////Adım sayar bitti/////////////////////////
/////////////////////////Gyro/////////////////////////
const int MPU_addr = 0x69;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;

int minVal = 265;
int maxVal = 402;

float k;//x
float l;//y
float n;//y

int anglee = 0;
int axiss = 0;
/////////////////////////Gyro bitti/////////////////////////
/////////////////////////analog saat/////////////////////////
int screenW = 128;
int screenH = 64;
//int clockCenterX = screenW / 2;
int clockCenterX = 79;
//int clockCenterY = ((screenH - 16) / 2) + 16; // top yellow part is 16 px height
int clockCenterY = 34; // top yellow part is 16 px height
int clockRadius = 30;
int16_t satx ;
int16_t saty ;

// utility function for digital clock display: prints leading 0
String twoDigits(int digits) {
  if (digits < 10) {
    String i = '0' + String(digits);
    return i;
  }
  else {
    return String(digits);
  }
}
/////////////////////////analog saat bitti/////////////////////////
/////////////////////////Oyunların Değişkenleri/////////////////////////
int x, y, radius = 3;
int xSpeed, ySpeed;

// Players
float userX = 0, userY = 30;
float comX = 126, comY = 30;
float userSpeed = 1.23, comSpeed = 1.23;
int rallyCount = 0, maxRally = 10; // add difficulty

// GUI
int border = 9;
int maxHeight = 63, maxWidth = 127; // screen size
int padHeight = 10, padWidth = 2;
int gameHeight = maxHeight - border, gameWidth = maxWidth - padWidth;
int userScore = 0, comScore = 0, maxScore = 7;
String displayScore = "";

// Display object
U8G2_SSD1306_128X64_NONAME_1_HW_I2C oled(U8G2_R0, U8X8_PIN_NONE);

#define DEMO_DURATION 3000
typedef void (*Demo)(void);

float zidx[4];
int prazan[4];
int razmak = 32;
int sirinaProlaza = 30;

int score = 0;
int stis = 0;
float fx = 30.00;
float fy = 22.00;
int smjer = 0;
unsigned long trenutno = 0;

int igra = 0;
int frame = 0;
int sviraj = 0;
unsigned long ton = 0;
/////////////////////////Oyunların Değişkenleri Bitti/////////////////////////
/////////////////////////İnternet Ayarları/////////////////////////
String yourssid     = "DELETE";
String  yourpassword = "3HD50mnhc-esgjs8472hf";
String ssid = "NodeMCU";  // Enter SSID here
String password = "Astra2013";  //Enter Password here

const long utcOffsetInSeconds = 10800;
//const long utcOffsetInSeconds = 3600;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "tr.pool.ntp.org", utcOffsetInSeconds);
IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

bool LED1status = LOW;
bool LED2status = LOW;

ESP8266WebServer server(80);

String webPagewifi = "";
String webStatwifi = "";
String webPage = "";
String webStat = "";
String webFooter = "";
/////////////////////////İnternet Ayarları Bitti/////////////////////////
/////////////////////////Ledler,Butonlar,Menü ve Değişkenleri,Ekran/////////////////////////
SSD1306Wire  display(0x3c, D1, D2);
#define DS3231_I2C_ADDRESS 0x68
// D1 -> SDA
// D2 -> SCL

OneButton button(D5, true);
OneButton button1(D3, true);

int upButton = D3;
int downButton = D4;
int selectButton = D5;
int menu = 1;

int parlak = 250;

int led = D7;
int led1 = D8;
int led2 = D0;
int buzzer = D6;

int indled = 0;
int mxled[] = {0, 50, 100};
int myled[] = {50, 50, 50};

int deg = 0;
int a = 0;
int b = 0;
int ab = 0;
int saat = 1 ;
int suiz = 1;
int oturmaiz = 1;
/////////////////////////Ledler,Butonlar,Menü ve Değişkenleri,Ekran bitti/////////////////////////
/////////////////////////Tema/////////////////////////
int te = 0;
int ind2 = 0;
int mx2[] = {0, 0, 0, 0, 60, 0, 60};
int my2[] = { 10, 20, 30, 40, 40, 50, 50};
int stil = 1;
int still = 1;
int dark = 1;
/////////////////////////Tema bitti/////////////////////////
/////////////////////////Alarm/////////////////////////
int saatbass = 0;
int saatbass1 = 0;
int saatbass2 = 0;
int saatbass3 = 0;
int al = 0;
int ind1 = 0;
int mx1[] = {0, 0, 0, 0};
int my1[] = {20, 30, 40, 50};
int alsa1 = 0;
int alsa2 = 0;
int alsa3 = 0;
int al2 = 0;
int almu1 = 0;
int almu2 = 0;
int almu3 = 0;
int albas = 0;
int alarm1 = 0;
int alarm2 = 0;
int alarm3 = 0;
int saatbas = 1;
/////////////////////////Alarm bitti/////////////////////////
/////////////////////////Hesap Makinesi/////////////////////////
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
int ind = 0;
//int pres = 0;
int stis1 = 0;
int poc = 0;
String line = "";
String num1 = "";
String num2 = "";
int operacija = 0;
int changeNumber = 0;
float n1 = 0.0000;
float n2 = 0.0000;
float res = 0.0000;
char buttons[] = {'0', '.', '=', '/', '1', '2', '3', '+', '4', '5', '6', '-', '7', '8', '9', '*', 'C'};
int mx[] = {2, 20, 32, 42, 2, 20, 32, 42, 2, 20, 32, 42, 2, 20, 32, 42, 62};
int my[] = {45, 45, 45, 45, 30, 30, 30, 30, 15, 15, 15, 15, 0, 0, 0, 0, 0};
/////////////////////////Hesap Makinesi/////////////////////////
/////////////////////////bmp180/////////////////////////
float t;
float p;
float m;
String strTemp;
String strPasc;
String strMetr;
char Pasc[6];
char Temp[6];
char Metr[6];
Adafruit_BMP085 bmp;
/////////////////////////bmp180/////////////////////////
/////////////////////////max30102/////////////////////////
const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;
String strBPM;
char BPM[6];

MAX30105 particleSensor;

#define MAX_BRIGHTNESS 255
uint32_t irBuffer[100]; //infrared LED sensor data
uint32_t redBuffer[100];  //red LED sensor data

int32_t bufferLength; //data length
int32_t spo2; //SPO2 value
int8_t validSPO2; //indicator to show if the SPO2 calculation is valid
int32_t heartRate; //heart rate value
int8_t validHeartRate; //indicator to show if the heart rate calculation is valid
/////////////////////////max30102/////////////////////////
/////////////////////////kronometre ve zamanlayıcı değişkenler/////////////////////////
int counter = 0;
int counter1 = 0;
int krodk = 0;
int krosn = 0;
int krosa = 0;
int timer123 = 0;
int mx55[] = {0, 40, 80};
int ind75 = 0;
unsigned long eskiZaman22 = 0;
unsigned long yeniZaman22;
unsigned long eskiZaman11 = 0;
unsigned long yeniZaman11;
int but = 0;
bool kro1;
int ses = 1;
int suizbass = 0;
int otbass = 0;
/////////////////////////kronometre ve zamanlayıcı değişkenler/////////////////////////
/////////////////////////Hava Durumu/////////////////////////
String APIKEY = "41ce9a5426a41cb7b4852d3091ac49c4";
String CityID = "323786";
WiFiClient client;
char servername[] = "api.openweathermap.org";
String result;
String weatherDescription = "";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;
float Sunrise;
float Sunset;
float Speed;
float Temp_min;
float Temp_max;
float Visibility;
float Wind_angle;
int f = 0;
int hav = 0;
/////////////////////////Hava Durumu bitti/////////////////////////
/////////////////////////açılış ekranı/////////////////////////
void drawCircle(void) {
  //  display.drawProgressBar(0, 32, 120, 10, progress);
  display.clear();
  display.drawXbm(34, 14, WiFi_Logo_width, WiFi_Logo_height, WiFi_Logo_bits);
  display.setFont(ArialMT_Plain_10);
  display.setColor(WHITE);
  display.display();
  delay(2000);
  alsa1 = EEPROM.read(1);
  Serial.println(alsa1);
  Serial.println("1. okundu");
  delay(100);
  alsa2 = EEPROM.read(2);
  Serial.println(alsa2);
  Serial.println("2. okundu");
  delay(100);
  alsa3 = EEPROM.read(3);
  Serial.println(alsa3);
  Serial.println("3. okundu");
  delay(100);
  almu1 = EEPROM.read(4);
  Serial.println(almu1);
  Serial.println("4. okundu");
  delay(100);
  almu2 = EEPROM.read(5);
  Serial.println(almu2);
  Serial.println("5. okundu");
  delay(100);
  almu3 = EEPROM.read(6);
  Serial.println(almu3);
  Serial.println("6. okundu");
  delay(100);
  alarm1 = EEPROM.read(7);
  Serial.println(alarm1);
  Serial.println("7. okundu");
  delay(100);
  alarm2 = EEPROM.read(8);
  Serial.println(alarm2);
  Serial.println("8. okundu");
  delay(100);
  alarm3 = EEPROM.read(9);
  Serial.println(alarm3);
  Serial.println("9. okundu");
  delay(100);
  saatbas = EEPROM.read(10);
  Serial.println(saatbas);
  Serial.println("10. okundu");
  delay(100);
  display.clear();
  for (int16_t i = 0; i < display.getHeight(); i += 2) {
    display.drawCircle(display.getWidth() / 2, display.getHeight() / 2, i);
    display.display();
    delay(10);
  }
  saat = EEPROM.read(11);
  Serial.println(saat);
  Serial.println("11. okundu");
  delay(100);
  stil = EEPROM.read(12);
  Serial.println(stil);
  Serial.println("12. okundu");
  delay(100);
  still = EEPROM.read(13);
  Serial.println(still);
  Serial.println("13. okundu");
  delay(100);
  dark = EEPROM.read(14);
  Serial.println(dark);
  Serial.println("14. okundu");
  delay(100);
  ses = EEPROM.read(15);
  Serial.println(ses);
  Serial.println("15. okundu");
  delay(100);
  parlak = EEPROM.read(20);
  Serial.println(parlak);
  Serial.println("20. okundu");
  delay(100);
  /* Steps = EEPROM.read(25);
    Serial.println(Steps);
    delay(100);*/
  uykudkes = EEPROM.read(26);
  Serial.println(uykudkes);
  Serial.println("26. okundu");
  delay(100);
  uykusaates = EEPROM.read(27);
  Serial.println(uykusaates);
  Serial.println("27. okundu");
  delay(100);
  /* suiz = EEPROM.read(15);
    Serial.println(suiz);
    delay(100);
    oturmaiz = EEPROM.read(16);
    Serial.println(oturmaiz);
    delay(100);*/
  delay(300);
  display.clear();
  display.setBrightness(parlak);
  // This will draw the part of the circel in quadrant 1
  // Quadrants are numberd like this:
  //   0010 | 0001
  //  ------|-----
  //   0100 | 1000
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000001);
  display.drawString(20, 52, "Robotics Project");
  display.display();
  delay(400);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000011);
  display.drawString(20, 52, "Robotics Project");
  display.display();
  delay(400);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00000111);
  display.drawString(20, 52, "Robotics Project");
  display.display();
  delay(400);
  display.drawCircleQuads(display.getWidth() / 2, display.getHeight() / 2, display.getHeight() / 4, 0b00001111);
  display.drawString(20, 52, "Robotics Project");
  display.display();
  delay(400);
  display.clear();
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 26, "Robotics Project");
  display.setFont(ArialMT_Plain_10);
  display.display();
  delay(400);
}
/////////////////////////açılış ekranı/////////////////////////
byte decToBcd(byte val)
{
  return ( (val / 10 * 16) + (val % 10) );
}

// Convert binary coded decimal to decimal numbers
byte bcdToDec(byte val)
{
  return ( (val / 16 * 10) + (val % 16) );
}
/////////////////////////saat yazma/////////////////////////
// Set the time
void setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
{
  // sets time and date data to DS3231
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set next input to start at the seconds register
  Wire.write(decToBcd(second)); // set seconds
  Wire.write(decToBcd(minute)); // set minutes
  Wire.write(decToBcd(hour)); // set hours
  Wire.write(decToBcd(dayOfWeek)); // set day of week (1=Sunday, 7=Saturday)
  Wire.write(decToBcd(dayOfMonth)); // set date (1 to 31)
  Wire.write(decToBcd(month)); // set month
  Wire.write(decToBcd(year)); // set year (0 to 99)
  Wire.endTransmission();
}
void readDS3231time(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
{
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0); // set DS3231 register pointer to 00h
  Wire.endTransmission();

  // request seven bytes of data from DS3231 starting from register 00h
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  *second = bcdToDec(Wire.read() & 0x7f);
  *minute = bcdToDec(Wire.read());
  *hour = bcdToDec(Wire.read() & 0x3f);
  *dayOfWeek = bcdToDec(Wire.read());
  *dayOfMonth = bcdToDec(Wire.read());
  *month = bcdToDec(Wire.read());
  *year = bcdToDec(Wire.read());
}
/////////////////////////saat yazma bitti/////////////////////////
void setup() {
  Wire.begin(D1, D2);
  Serial.begin(115200);
  Serial.println("Açıldı...");
  delay(100);
  kro1 = false;
  ad = true;
  uyku1 = false;
  otoekran = false;
  notdur = false;
  melodi = false;
  if (!display.init()) //Use default I2C port, 400kHz speed
  {
    Serial.println("SSD1306 was not found. Please check wiring/power. ");
    while (1);
  }
  // display.init();
  Serial.println("ekran açıldı...");
  delay(100);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.println("Gyro açıldı...");
  delay(100);
  display.setContrast(255);
  for (int i = 0; i < 4; i++)
  {
    zidx[i] = 128 + ((i + 1) * razmak);
    {
      prazan[i] = random(8, 32);
    }
  }
  display.flipScreenVertically();
  display.clear();
  EEPROM.begin(512);
  pinMode(led, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  drawCircle();
  delay(100);
  digitalWrite(led, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(buzzer, LOW);
  Serial.println("Initializing...");
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(selectButton, INPUT_PULLUP);
  button.attachClick(myClick);
  button.attachDoubleClick(myDouble);
  button1.attachClick(myClick1);
  button1.attachDoubleClick(myDouble1);
  //setDS3231time(30, 29, 12, 3, 14, 11, 16);
  // setDS3231time(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  oledConfig();
  // Initialize ball position and speed
  x = random(50, 70);
  y = random(border + radius + 5, 63 - 5);
  xSpeed = 1;
  ySpeed = 1;
  updateMenu();
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  if (!bmp.begin())
  {
    Serial.println("Could not find BMP180 or BMP085 sensor at 0x77");
    while (1);
  }
}

void loop() {
  /////////////////////////oto ekran/////////////////////////
  if (otoekran == true) {
    display.clear();
    display.display();
    display.displayOff();
    ad = true;
    WiFi.mode(WIFI_OFF);
    deg = 0;
    if (!digitalRead(selectButton)) {
      display.displayOn();
      display.setBrightness(parlak);
      WiFi.mode(WIFI_OFF);
      deg = 1;
      a = 0;
      b = 0;
      suizbass = 151;
      sayac = 0;
      sayac1 = 0;
      uyku = false;
      display.setFont(ArialMT_Plain_10);
      particleSensor.setup(0); //Configure sensor with default settings
      ses1();
      delay(100);
      digitalWrite(led, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzer, LOW);
      while (!digitalRead(downButton));
    }
  }
  /////////////////////////oto ekran bitti/////////////////////////
  /////////////////////////menü gezinme/////////////////////////
  if (otoekran == false) {
    if (ab == 0) {
      if (!digitalRead(downButton)) {
        WiFi.mode(WIFI_OFF);
        menu++;
        updateMenu();
        deg = 0;
        a = 0;
        b = 0;
        sayac = 0;
        sayac1 = 0;
        otoekran = false;
        uyku = false;
        display.setFont(ArialMT_Plain_10);
        particleSensor.setup(0); //Configure sensor with default settings
        ses1();
        delay(100);
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        digitalWrite(buzzer, LOW);
        while (!digitalRead(downButton));
      }
    }
  }
  if (a == 0) {
    if (!digitalRead(upButton)) {
      menu--;
      updateMenu();
      ses1();
      sayac1 = 0;
      otoekran = false;
      delay(100);
      digitalWrite(led, HIGH);
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzer, LOW);
      while (!digitalRead(upButton));
    }
    if (!digitalRead(selectButton)) {
      executeAction();
      sayac1 = 0;
      otoekran = false;
      delay(300);
      while (!digitalRead(selectButton));
    }
  }
  /////////////////////////menü gezinme/////////////////////////
  /////////////////////////saat ekranı/////////////////////////
  if (deg  == 1) {
    batarya();
    byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
    // retrieve data from DS3231
    readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
    if (saat == 0) {
      display.clear();
      stilb();
      display.setFont(ArialMT_Plain_24);
      display.drawString(30, 20, String(hour, DEC));
      display.drawString(57, 20, ":");
      display.drawString(62, 20, String(minute, DEC));
      display.setFont(ArialMT_Plain_10);
      display.drawString(78, 0, String(dayOfMonth, DEC));
      display.drawString(92, 0, "/");
      display.drawString(95, 0, String(month, DEC));
      display.drawString(107, 0, "/");
      display.drawString(110, 0, String(year, DEC));
      display.drawString(20, 0, String(ekrannot));
      display.drawString(100, 50, "Menu");
      display.drawString(50, 50, "Kapa");
      display.drawString(3, 50, "Ses");
      if (ses == 1) { //eğer ki ses açıksa
        display.drawString(0, 0, "on");
      }
      if (ses == 0) { //eğerki ses kapalı ise
        display.drawString(0, 0, "off");
      }
      if (alarm1 == 1 || alarm2 == 1 || alarm3 == 1 ) {
        display.drawString(2, 15, "al");
      }
      else {

      }
      display.drawString(100, 15, "%");
      display.drawString(110, 15, String(perc));
      display.drawString(2, 25, String(Steps));
      display.display();
      /* Serial.print(second, DEC);
        Serial.print(" ");
        Serial.print(dayOfMonth, DEC);
        Serial.print("/");
        Serial.print(month, DEC);
        Serial.print("/");
        Serial.print(year, DEC);
        Serial.print(" Day of week: ");
        switch (dayOfWeek) {
         case 1:
           Serial.println("Sunday");
           break;
         case 2:
           Serial.println("Monday");
           break;
         case 3:
           Serial.println("Tuesday");
           break;
         case 4:
           Serial.println("Wednesday");
           break;
         case 5:
           Serial.println("Thursday");
           break;
         case 6:
           Serial.println("Friday");
           break;
         case 7:
           Serial.println("Saturday");
           break;
         default:
           Serial.println(dayOfWeek);
        }*/
    }
    if (saat == 1) {
      display.clear();
      display.drawCircle(clockCenterX + satx, clockCenterY + saty, 2);
      //
      //hour ticks
      for ( int z = 0; z < 360; z = z + 30 ) {
        //Begin at 0° and stop at 360°
        float angle = z ;
        angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
        int x2 = ( clockCenterX + ( sin(angle) * clockRadius ) );
        int y2 = ( clockCenterY - ( cos(angle) * clockRadius ) );
        int x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 8 ) ) ) );
        int y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 8 ) ) ) );
        display.drawLine( x2 + satx , y2 + saty , x3 + satx , y3 + saty);
      }

      // display second hand
      float angle = second * 6 ;
      angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
      int x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 5 ) ) ) );
      int y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 5 ) ) ) );
      display.drawLine( clockCenterX + satx , clockCenterY + saty , x3 + satx , y3 + saty);
      //
      // display minute hand
      angle = minute * 6 ;
      angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
      x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 4 ) ) ) );
      y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 4 ) ) ) );
      display.drawLine( clockCenterX + satx , clockCenterY + saty , x3 + satx , y3 + saty);
      //
      // display hour hand
      angle = hour * 30 + int( ( minute / 12 ) * 6 )   ;
      angle = ( angle / 57.29577951 ) ; //Convert degrees to radians
      x3 = ( clockCenterX + ( sin(angle) * ( clockRadius - ( clockRadius / 2 ) ) ) );
      y3 = ( clockCenterY - ( cos(angle) * ( clockRadius - ( clockRadius / 2 ) ) ) );
      display.drawLine( clockCenterX + satx , clockCenterY + saty , x3 + satx , y3 + saty);
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 50, String(month, DEC));
      display.drawString(14, 50, "/");
      display.drawString(20, 50, String(dayOfMonth, DEC));
      display.drawString(0, 0, String(hour, DEC));
      display.drawString(14, 0, ":");
      display.drawString(20, 0, String(minute, DEC));
      display.drawString(0, 10, "%");
      display.drawString(10, 10, String(perc));
      display.drawString(0, 20, String(Steps));
      // display.drawString(10, 0, String(ekrannot));
      display.drawLine(30, 0, 25, 124);
      if (ses == 0) { //eğerki ses kapalı ise
        display.drawString(0, 30, "off");
      }
      if (ses == 1) { //eğer ki ses açıksa
        display.drawString(0, 30, "on");
      }
      if (alarm1 == 1 || alarm2 == 1 || alarm3 == 1 ) {
        display.drawString(0, 40, "al");
      }
      else {

      }
      display.display();
    }
    if (saat == 2) {
      display.clear();
      display.setFont(Syncopate_Bold_30);
      display.drawString(10, 0, String(hour, DEC));
      display.drawString(55, 0, ":");
      display.drawString(60, 0, String(minute, DEC));
      display.setFont(ArialMT_Plain_10);
      display.drawString(84, 50, String(dayOfMonth, DEC));
      display.drawString(96, 50, "/");
      display.drawString(100, 50, String(month, DEC));
      display.drawString(112, 50, "/");
      display.drawString(116, 50, String(year, DEC));
      display.drawString(50, 30, "%");
      display.drawString(60, 30, String(perc));
      display.drawString(50, 40, String(Steps));
      display.drawString(0, 50, String(ekrannot));
      display.drawLine(0, 40, 128, 40);
      display.drawLine(84, 0, 84, 64);
      if (ses == 0) { //eğerki ses kapalı ise
        display.drawString(110, 30, "off");
      }
      if (ses == 1) { //eğer ki ses açıksa
        display.drawString(110, 30, "on");
      }
      if (alarm1 == 1 || alarm2 == 1 || alarm3 == 1 ) {
        display.drawString(0, 30, "al");
      }
      else {

      }
      display.display();
    }
    if (!digitalRead(selectButton)) { //yukarı butonuna basılırsa
      otoekran = true;
      delay(300);
      while (!digitalRead(selectButton));
    }
    if (!digitalRead(upButton)) { //yukarı butonuna basılırsa
      if (ses == 1) {
        ses = 0;
      }
      else if (ses == 0) {
        ses = 1;
      }
      le();  //ledi aç kapat
      EEPROM.write(15, ses);
      EEPROM.commit();
      delay(300);
      while (!digitalRead(upButton));
    }
  }
  /////////////////////////saat ekranı/////////////////////////
  /////////////////////////bmp180/////////////////////////
  if (deg == 2) {
    t = bmp.readTemperature();
    p = bmp.readPressure();
    m = bmp.readAltitude(101500);
    strTemp = String(t);
    strPasc = String(p);
    strMetr = String(m);
    strTemp.toCharArray(Temp, 5);
    strPasc.toCharArray(Pasc, 5);
    strMetr.toCharArray(Metr, 5);
    display.clear();
    stila();
    display.drawString(0, 0, "Sicaklik:");
    display.drawString(45, 0, (Temp));
    display.drawString(0, 15, "Basinç:");
    display.drawString(45, 15, (Pasc));
    display.drawString(0, 30, "Feet:");
    display.drawString(45, 30, (Metr));
    display.display();
  }
  /////////////////////////bmp180/////////////////////////
  /////////////////////////BPM/////////////////////////
  if (deg  == 3) {
    particleSensor.setup(); //Configure sensor with default settings
    particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
    particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED
    long irValue = particleSensor.getIR();
    if (irValue < 5000) {
      display.clear();
      stila();
      display.drawString(10, 50, "Parmaginizi Yerlestiriniz");
      display.display();
      beatAvg = 0;
    }
    if (irValue > 5000) {
      if (checkForBeat(irValue) == true)
      {
        //We sensed a beat!
        long delta = millis() - lastBeat;
        lastBeat = millis();

        beatsPerMinute = 60 / (delta / 1000.0);

        if (beatsPerMinute < 255 && beatsPerMinute > 20)
        {
          rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
          rateSpot %= RATE_SIZE; //Wrap variable

          //Take average of readings
          beatAvg = 0;
          for (byte x = 0 ; x < RATE_SIZE ; x++)
            beatAvg += rates[x];
          beatAvg /= RATE_SIZE;
        }
      }
      display.clear();
      stila();
      strBPM = String(beatAvg);
      strBPM.toCharArray(BPM, 5);
      display.setFont(ArialMT_Plain_10);
      display.setFont(ArialMT_Plain_24);
      display.drawString(0, 0, "Nabiz:");
      display.drawString(80, 0, (BPM));
      display.setFont(ArialMT_Plain_10);
      display.drawString(20, 50, "Okumaya Başlandı");
      display.display();//Deactivate the buzzer to have the effect of a "bip"
    }
  }
  /////////////////////////BPM/////////////////////////
  /////////////////////////Spo2/////////////////////////
  if (deg == 4) {
    bufferLength = 100;
    for (byte i = 0 ; i < bufferLength ; i++)
    {
      redBuffer[i] = particleSensor.getRed();
      irBuffer[i] = particleSensor.getIR();
      particleSensor.nextSample(); //We're finished with this sample so move to next sample
      display.clear();
      stila();
      display.drawString(0, 20, "redBuffer:");
      display.drawString(60, 20, String(redBuffer[i], DEC));
      display.drawString(0, 40, "irBuffer:");
      display.drawString(60, 40, String(irBuffer[i], DEC));
      display.display();
      if (!digitalRead(downButton)) {
        menu++;
        updateMenu();
        deg = 0;
        a = 0;
        b = 0;
        i = 101;
        while (!digitalRead(downButton));
      }
    }
    if (deg == 4) {
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
      for (byte i = 25; i < 100; i++)
      {
        redBuffer[i - 25] = redBuffer[i];
        irBuffer[i - 25] = irBuffer[i];
        if (!digitalRead(downButton)) {
          menu++;
          updateMenu();
          deg = 0;
          a = 0;
          b = 0;
          i = 101;
          while (!digitalRead(downButton));
        }
      }
    }
    if (deg == 4) {
      for (byte i = 75; i < 100; i++)
      {
        redBuffer[i] = particleSensor.getRed();
        irBuffer[i] = particleSensor.getIR();
        particleSensor.nextSample();
        display.clear();
        stila();
        display.drawString(0, 0, "Spo2:");
        display.drawString(60, 0, String(spo2, DEC));
        display.drawString(0, 20, "redBuffer:");
        display.drawString(60, 20, String(redBuffer[i], DEC));
        display.drawString(0, 40, "irBuffer:");
        display.drawString(60, 40, String(irBuffer[i], DEC));
        display.display();
        if (!digitalRead(downButton)) {
          menu++;
          updateMenu();
          deg = 0;
          a = 0;
          b = 0;
          i = 101;
          while (!digitalRead(downButton));
        }
      }
      maxim_heart_rate_and_oxygen_saturation(irBuffer, bufferLength, redBuffer, &spo2, &validSPO2, &heartRate, &validHeartRate);
    }
  }
  /////////////////////////Spo2 bitti/////////////////////////
  /////////////////////////Kronometre/////////////////////////
  if (deg  == 5) {//kronometre açık ise kodları getir
    if (kro1 == false) {
      display.clear();
      stila();
      display.drawString(0, 0, "BAS...");
      display.drawString(0, 30, "Zaman:");
      display.drawString(50, 30, String(counter1));
      display.display();
      if (!digitalRead(selectButton)) {
        kro1 = true;
        delay(100);
        while (!digitalRead(selectButton));
      }
    }
    if (kro1 == true) {
      display.clear();
      stila();
      display.drawString(0, 0, "Saniye:");
      display.drawString(40, 0, String(counter));
      display.display();
      counter ++;
      yeniZaman11 = millis();
      if (yeniZaman11 - eskiZaman11 > 1000) {
        eskiZaman11 = yeniZaman11;
        counter ++;
      }
      if (!digitalRead(selectButton)) {
        kro1 = false;
        counter1 = counter;
        counter = 0;
        delay(100);
        while (!digitalRead(selectButton));
      }
    }
  }
  /////////////////////////kronometre bitti/////////////////////////
  /////////////////////////Notlar/////////////////////////
  if (deg == 6) {
    button.tick();
    button1.tick();
    display.clear();
    display.drawString(5, 0, not1);
    display.drawString(5, 10, not2);
    display.drawString(5, 20, not3);
    display.drawString(5, 30, not4);
    display.drawString(5, 40, not5);
    display.drawString(5, 50, "1");
    display.drawString(25, 50, "2");
    display.drawString(45, 50, "3");
    display.drawString(65, 50, "4");
    display.drawString(85, 50, "5");
    display.drawString(105 , 50, "Not");
    display.drawRect(mx22[ind8], my22[ind8], 5, 10);
    display.display();
  }
  if (notdur == true) {
    deg = 0;
    WiFi.softAP(ssid, password);
    /*Serial.print(ssid);
      Serial.print(password);*/
    WiFi.softAPConfig(local_ip, gateway, subnet);
    display.clear();
    stila();
    display.drawString(0, 0, "Wifi ağı oluşturuluyor.");
    delay(100);
    display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
    delay(100);
    display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
    delay(100);
    display.clear();
    stila();
    display.drawString(0, 0, "Wifi ağı oluştururldu..");
    display.drawString(0, 20, "Kontrol Etkin.");
    display.display();
    delay(100);
    /*  server.on("/", handle_OnConnect);
      server.on("/led1on", handle_led1on);
      server.on("/led1off", handle_led1off);
      server.on("/led2on", handle_led2on);
      server.on("/led2off", handle_led2off);*/
    server.onNotFound(handle_NotFound);
    server.on("/", handleNotPage); //aynı sayfaya dönecek
    server.on("/set", handleSetCommandNot);        // parametreleri koda set ön eki ile göndereceğiz.
    server.handleClient();
    server.begin(); //sunucuyu başlattı
    // Serial.println("HTTP server started");
  }
  /////////////////////////Notlar bitti/////////////////////////
  /////////////////////////Hesap Makinesi /////////////////////////
  if (deg == 7) {
    button.tick();
    button1.tick();
    display.clear();
    stila();
    int poz = 4;
    int pozx = 1;
    for (int i = 0; i < 16; i++)
    {
      if (i % 4 == 0) {
        poz = poz - 1;
        pozx = 1;
      }
      display.setFont(ArialMT_Plain_16);
      display.drawString(0 + (pozx * 7), (poz * 14) + 0, String(buttons[i]));
      // display.drawRect(0, 0, 64, 15);
      pozx = pozx + 2;
      // poz = poz + 1;
    }
    display.drawString(60, 0, "C");
    display.drawRect(mx[ind], my[ind], 17, 15);
    display.drawString(65, 20, String(line));
    display.display();
  }
  /////////////////////////Hesap Makinesi /////////////////////////
  /////////////////////////Zamanlayıcı/////////////////////////
  if (deg == 8) {
    if (timer123 == 0) {
      button.tick();
      button1.tick();
      display.clear();
      display.drawString(0, 0, "SA");
      display.drawString(40, 0, "DK");
      display.drawString(80, 0, "SN");
      display.drawString(0, 20, String(krosa));
      display.drawString(40, 20, String(krodk));
      display.drawString(80, 20, String(krosn));
      display.drawRect(mx55[ind75], 60, 40, 30);
      display.display();
    }
    else if (timer123 == 1) {
      button.tick();
      button1.tick();
      display.clear();
      display.drawString(0, 0, "SA");
      display.drawString(40, 0, "DK");
      display.drawString(80, 0, "SN");
      display.drawString(0, 20, String(krosa));
      display.drawString(40, 20, String(krodk));
      display.drawString(80, 20, String(krosn));
      display.display();
      yeniZaman22 = millis();
      if (yeniZaman22 - eskiZaman22 > 1000) {
        eskiZaman22 = yeniZaman22;
        if (krosn != 0) {
          krosn--;
          if (krodk != 0) {
            if (krosn == 0) {
              krosn = 60;
              krodk--;
            }
          }
          if (krosa != 0) {
            if (krodk == 0) {
              krodk = 60;
              krosa--;
            }
          }
        }
        if (krosn == 0) {
          if (krodk != 0) {
            krodk = krodk - 1;
            krosn  = 60;
          }
          if (krodk == 0) {
            if (krosa != 0) {
              krodk = krodk - 1;
              krosn  = 60;
            }
          }
        }
        if (krosa == 0 && krodk == 0 && krosn == 0) {
          timer123 = 2;
        }
      }
    }
    else if (timer123 == 2) {
      button.tick();
      button1.tick();
      display.clear();
      display.drawString(0, 0, "SÜRE DOLDU!");
      display.drawString(0, 20, String(krosa));
      display.drawString(40, 20, String(krodk));
      display.drawString(80, 20, String(krosn));
      display.display();
    }
    else if (timer123 == 3) {
      button.tick();
      button1.tick();
      display.clear();
      display.drawString(0, 0, "DURAKLATILDI!");
      display.drawString(0, 20, String(krosa));
      display.drawString(40, 20, String(krodk));
      display.drawString(80, 20, String(krosn));
      display.display();
    }
    /*int krodk = 0;
      int krodk1 = 0;
      int krosn = 0;
      int krosn1 = 0;
      int krosa = 0;
      int krosa1 = 0;
      unsigned long eskiZaman22 = 0;
      unsigned long yeniZaman22;
      int timer123 =0;*/
  }
  /////////////////////////Zamanlayıcı bitti/////////////////////////
  /////////////////////////Adım sayar /////////////////////////
  if (ad == true) {
    stepp();
  }
  if (deg == 9) {
    display.clear();
    stila();
    display.drawString(30, 0, "Adim Sayar");
    display.drawString(0, 30, "Adim:");
    display.drawString(50, 30, String(Steps));
    display.display();
    if (!digitalRead(selectButton)) {
      Steps = 0;
      display.drawString(0, 50, "Veri sifirlandi");
      /* EEPROM.write(25, 0);
        EEPROM.commit();*/
      delay(2000);
      while (!digitalRead(selectButton));
    }
    display.display();
  }
  /////////////////////////Adım sayar bitti/////////////////////////
  /////////////////////////Uyku Takip/////////////////////////
  if (deg == 10) {
    uykuger = uyku / 2;
    display.clear();
    stila();
    display.drawString(30, 0, "Uyku Takip");
    display.drawString(50, 10, "Yeni");
    display.drawString(80, 10, "Eski");
    display.drawString(0, 20, "Uyku Sn:");
    display.drawString(50, 20, String(uykuger));
    display.drawString(80, 20, String(uykugeres));
    display.drawString(0, 30, "Uyku Dk:");
    display.drawString(50, 30, String(uykudk));
    display.drawString(80, 30, String(uykudkes));
    display.drawString(0, 40, "Uyku Sa:");
    display.drawString(50, 40, String(uykusaat));
    display.drawString(80, 40, String(uykusaates));
    display.display();
  }
  /////////////////////////Uyku Takip bitti/////////////////////////
  /////////////////////////Gyro /////////////////////////
  if (deg == 11) {
    /*  Wire.beginTransmission(MPU_addr);
      Wire.write(0x3B);
      Wire.endTransmission(false);
      Wire.requestFrom(MPU_addr, 14, true);
      AcX = Wire.read() << 8 | Wire.read();
      AcY = Wire.read() << 8 | Wire.read();
      AcZ = Wire.read() << 8 | Wire.read();
      int xAng = map(AcX, minVal, maxVal, -90, 90);
      int yAng = map(AcY, minVal, maxVal, -90, 90);
      int zAng = map(AcZ, minVal, maxVal, -90, 90);

      k = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
      l = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
      n = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);

      Serial.print("AngleX= ");
      Serial.println(k);

      Serial.print("AngleY= ");
      Serial.println(l);

      Serial.print("AngleZ= ");
      Serial.println(n);
      Serial.println("-----------------------------------------");*/
    /*   Wire.beginTransmission(MPU_addr);
       Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
       Wire.endTransmission(false);
       Wire.requestFrom(MPU_addr, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
       AcX = Wire.read() << 8 | Wire.read(); // X-axis value
       AcY = Wire.read() << 8 | Wire.read(); // Y-axis value
       AcZ = Wire.read() << 8 | Wire.read(); // Z-axis value*/
    button.tick();
    display.clear();
    if ( axiss == 0) {
      anglee = atan(-1 * accelX / sqrt(pow(accelY, 2) + pow(accelZ, 2))) * 180 / PI;
      display.setFont(ArialMT_Plain_16);
      display.drawString(30, 20, "X'e göre");
    }
    if (axiss == 1) {
      anglee = atan(-1 * accelY / sqrt(pow(accelX, 2) + pow(accelZ, 2))) * 180 / PI;
      display.setFont(ArialMT_Plain_16);
      display.drawString(30, 20, "Y'e göre");
    }
    stila();
    display.setFont(ArialMT_Plain_24);
    display.drawString(45, 0, String(abs(anglee)) );
    display.setFont(ArialMT_Plain_10);
    display.display();
    delay(200);
    if (!digitalRead(selectButton)) {
      axiss = axiss + 1;
      if (axiss == 2) {
        axiss = 0;
      }
      delay(250);
      while (!digitalRead(selectButton));
    }
  }
  /////////////////////////Gyro bitti /////////////////////////
  /////////////////////////Hava durumu/////////////////////////
  if (deg == 12) {
    if (f == 0) {
      WiFi.begin(yourssid, yourpassword);
      while (WiFi.status() != WL_CONNECTED)
      {
        display.clear();
        stila();
        display.drawString(0, 0, "Aga baglanılıyor...");
        display.display();
        Serial.print(".");
        delay(500);
      }
      Serial.println("Connected");
      f = 1;
      delay(1000);
      getWeatherData();
    }
    if (hav == 1) {
      display.clear();
      stila();
      display.drawString(0, 0, "Sıcaklık:");
      display.drawString(40, 0, String(Temperature));
      display.drawString(0, 15, "Nem:");
      display.drawString(40, 15, String(Humidity));
      display.drawString(0, 30, "Rüzgar Hızı:");
      display.drawString(70, 30, String(Speed));
      display.drawString(0, 45, "Görünürlük:");
      display.drawString(80, 45, String(Visibility));
      display.display();
    }
    if (hav == 0) {
      display.clear();
      stila();
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 50, String(weatherLocation));
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 0, String(weatherDescription));
      display.setFont(ArialMT_Plain_10);
      display.display();
    }
    /*  weatherDescription = description;
      weatherLocation = location;
      Country = country;
      Temperature = temperature;
      Humidity = humidity;
      Pressure = pressure;
      Sunrise = sunrise;
      Sunset = sunset;
      Speed = speed;
      Temp_min = temp_min;
      Temp_max = temp_max;
      Visibility = visibility;
      Wind_angle = wind_angle;*/
    if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
      hav = hav + 1;  //değişkeni yani basma sayısını bir arttır
      if (hav == 2) {
        hav = 0;
      }
      delay(100);  //bekle
      while (!digitalRead(selectButton));
    }
  }
  /////////////////////////Hava durumu bitti/////////////////////////
  /////////////////////////İzleme/////////////////////////
  if (deg == 13) {
    display.clear();
    stila();
    display.drawString(0, 00, "Su Izleme:");
    display.drawString(0, 40, "Oturma Hatirlaticisi:");
    if (suiz == 0) {
      display.drawString(40, 10, "Acik");
    }
    else if (suiz == 1) {
      display.drawString(40, 10, "Kapali");
    }
    if (oturmaiz == 0) {
      display.drawString(40, 50, "Acik");
    }
    else if (oturmaiz == 1) {
      display.drawString(40, 50, "Kapali");
    }
    display.display();
    if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
      if (suiz == 0) {
        suiz = 1;
        EEPROM.write(15, suiz);
        EEPROM.commit();
        delay(100);
      }
      else if (suiz == 1) {
        suiz = 0;
        EEPROM.write(15, suiz);
        EEPROM.commit();
        delay(100);
      }
      delay(100);  //bekle
      while (!digitalRead(selectButton));
    }
    if (!digitalRead(upButton)) {  //seç düğmesine basarsa
      if (oturmaiz == 0) {
        oturmaiz = 1;
        EEPROM.write(16, oturmaiz);
        EEPROM.commit();
        delay(100);
      }
      else if (oturmaiz == 1) {
        oturmaiz = 0;
        EEPROM.write(16, oturmaiz);
        EEPROM.commit();
        delay(100);
      }
      delay(100);  //bekle
      while (!digitalRead(upButton));
    }
  }
  /////////////////////////İzleme bitti/////////////////////////
  /////////////////////////press game/////////////////////////
  if (deg  == 14) {
    if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
      but = but + 1;  //değişkeni yani basma sayısını bir arttır
      delay(100);  //bekle
      while (!digitalRead(selectButton));
    }
    display.clear();
    stila();
    display.drawString(30, 0, ">Press Game<");
    display.drawString(0, 30, "BAS...");
    if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
      but = but + 1;  //değişkeni yani basma sayısını bir arttır
      delay(100);  //bekle
      while (!digitalRead(selectButton));
    }
    display.drawString(0, 50, String(but));
    display.display();
    if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
      but = but + 1;  //değişkeni yani basma sayısını bir arttır
      delay(100);  //bekle
      while (!digitalRead(selectButton));
    }
  }
  /////////////////////////press game bitti/////////////////////////
  /////////////////////////flappy bird/////////////////////////
  if (deg == 15) {
    display.clear();
    if (igra == 0)
    {
      display.setFont(ArialMT_Plain_16);
      display.drawString(0, 4, "Flappy ");
      display.drawXbm(0, 0, 128, 64, pozadina);
      display.drawXbm(20, 32, 14, 9, ptica);
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 44, "press to start");
      if (digitalRead(D5) == 0)
        igra = 1;
    }
    if (igra == 1)
    {
      display.setFont(ArialMT_Plain_10);
      display.drawString(3, 0, String(score));
      if (digitalRead(D3) == 0)
      {
        if (stis == 0)
        {
          trenutno = millis();
          smjer = 1;
          sviraj = 1;
          stis = 1;
          ton = millis();
        }
      } else {
        stis = 0;
      }
      for (int j = 0; j < 4; j++) {
        display.setColor(WHITE);
        display.fillRect(zidx[j], 0, 6, 64);
        display.setColor(BLACK);
        display.fillRect(zidx[j], prazan[j], 6, sirinaProlaza);
      }
      display.setColor(WHITE);
      //  display.fillCircle(fx, fy, 4); // igrac
      display.drawXbm(fx, fy, 14, 9, ptica);
      for (int j = 0; j < 4; j++)
      {
        zidx[j] = zidx[j] - 0.01;
        if (zidx[j] < -7) {
          score = score + 1;
          digitalWrite(D7, 1);
          prazan[j] = random(8, 32);
          zidx[j] = 128;
        }
      }
      if ((trenutno + 185) < millis())
        smjer = 0;
      if ((ton + 40) < millis())
        sviraj = 0;
      if (smjer == 0)
        fy = fy + 0.01;
      else
        fy = fy - 0.03;
      if (sviraj == 1)
        digitalWrite(D7, 1);
      else
        digitalWrite(D7, 0);
      if (fy > 63 || fy < 0) {
        igra = 0;
        fy = 22;
        score = 0;
        digitalWrite(D7, 1);
        delay(500);
        digitalWrite(D7, 0);
        for (int i = 0; i < 4; i++)
        {
          zidx[i] = 128 + ((i + 1) * razmak);
          {
            prazan[i] = random(4, 30);
          }
        }
      }
      for (int m = 0; m < 4; m++)
        if (zidx[m] <= fx + 7 && fx + 7 <= zidx[m] + 6)
        {
          if (fy < prazan[m] || fy + 8 > prazan[m] + sirinaProlaza) {
            igra = 0;
            fy = 22;
            score = 0;
            digitalWrite(D7, 1);
            delay(500);
            digitalWrite(D7, 0);
            for (int i = 0; i < 4; i++)
            {
              zidx[i] = 128 + ((i + 1) * razmak);
              {
                prazan[i] = random(8, 32);
              }
            }
          }
        }
      display.drawRect(0, 0, 128, 64);
    }
    display.display();
  }
  /////////////////////////flappy bird bitti/////////////////////////
  /////////////////////////pong game/////////////////////////
  if (deg == 16) {
    move();
    displa();
  }
  /////////////////////////pong game bitti/////////////////////////
  /////////////////////////Notalar/////////////////////////
  if (deg == 17) {
    /* for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
       tone(buzzer, sarki[g]);
       delay(350);
      }
      noTone(buzzer);*/
    button.tick();
    button1.tick();
    display.clear();
    display.drawString(0, 1, "do");
    display.drawString(0, 8, "re");
    display.drawString(0, 15, "mi");
    display.drawString(0, 22, "fa");
    display.drawString(0, 29, "sol");
    display.drawString(0, 36, "la");
    display.drawString(0, 43, "si");
    display.drawString(0, 50, "do");

    display.drawString(60, 0, "Sarki 1");
    display.drawString(60, 10, "Sarki 2");
    display.drawString(60, 20, "Sarki 3");
    display.drawString(60, 30, "Sarki 4");
    display.drawString(60, 40, "Sarki 5");
    display.drawString(60, 50, "Sarki 6");
    if (melodi == true) {
      display.drawRect(mx33[ind5], my34[ind5], 5, 10);
      display.drawRect(60, 60, 30, 30);
    }
    if (melodi == false) {
      display.drawRect(mx33[ind5], my33[ind5], 5, 10);
      display.drawRect(0, 60, 30, 30);
    }
    display.display();
  }
  /////////////////////////Notalar/////////////////////////
  /////////////////////////Star Wars/////////////////////////
  if (deg == 18) {
    if (go == 0) {
      display.clear();
      display.setPixel(50, 30);
      display.setPixel(30, 17);
      display.setPixel(60, 18);
      display.setPixel(55, 16);
      display.setPixel(25, 43);
      display.setPixel(100, 43);
      display.setPixel(117, 52);
      display.setPixel(14, 49);
      display.setPixel(24, 24);
      display.setPixel(78, 36);
      display.setPixel(80, 57);
      display.setPixel(107, 11);
      display.setPixel(150, 11);
      display.setPixel(5, 5);
      display.setPixel(8, 7);
      display.setPixel(70, 12);
      display.setPixel(10, 56);
      display.setPixel(75, 25);
      if (poc1 == 0) {
        pocetno = millis();
        odabrano = random(400, 1200);
        poc1 = 1;
      }
      trenutno1 = millis();
      if ((trenutno1 - nivovrije) > 50000)
      {
        nivovrije = trenutno1;
        nivo = nivo + 1;
        brzina = brzina + 1;
        if ( nivo % 2 == 0 )
        {
          bkugle = bkugle + 1;
          promjer = promjer - 1;
        }
        najmanja = najmanja - 50;
        najveca = najveca - 50;
      }
      if ((odabrano + pocetno) < trenutno1)
      {
        poc1 = 0;
        ispaljeno = ispaljeno + 1;
        if (ispaljeno == 1)
        { rx = 95;
          ry = nep;
        }
        if (ispaljeno == 2) {
          rx2 = 95;
          ry2 = nep;
        }
        if (ispaljeno == 3)
        {
          rx3 = 95;
          ry3 = nep;
        }
        if (ispaljeno == 4) {
          rx4 = 95;
          ry4 = nep;
        }
      }
      if (ispaljeno > 0)
      {
        display.drawCircle( rx, ry, 2);
        rx = rx - brzina;
      }
      if (ispaljeno > 1)
      {
        display.drawCircle( rx2, ry2, 1);
        rx2 = rx2 - brzina;
      }
      if (ispaljeno > 2)
      {
        display.drawCircle( rx3, ry3, 4);
        rx3 = rx3 - brzina;
      }
      if (ispaljeno > 3)
      {
        display.drawCircle( rx4, ry4, 2);
        rx4 = rx4 - brzina;
      }
      if (digitalRead(D3) == 0 && poz >= 2) {
        poz = poz - 2;
      }
      if (digitalRead(D4) == 0 && poz <= 46) {
        poz = poz + 2;
      }
      if (digitalRead(D5) == 0 && postoji == 0)
      {
        postoji = 1;
        metx = 6;
        mety = poz + 8;
      }
      if (postoji == 1)
      {
        metx = metx + 8 ;
        display.drawLine(metx, mety, metx + 4, mety);
      }
      display.drawFastImage(4, poz, 16, 16, dioda16);
      display.fillCircle(centar, nep, promjer);
      display.fillCircle(centar + 2, nep + 3, promjer / 3);
      display.drawString(33, 54, "score:");
      display.drawString(68, 54, String(bodovi));
      display.drawString(33, 0, "lives:");
      display.drawString(68, 0, String(zivoti));
      display.drawString(110, 0, "L");
      display.drawString(122, 0, String(nivo));
      display.drawString(108, 54, String(trenutno / 1000));
      display.display();
      if (metx > 128)postoji = 0;
      if (smjer1 == 0) {
        nep = nep + bkugle;
      }
      else
      {
        nep = nep - bkugle;
      }
      if (nep >= (64 - promjer))
        smjer1 = 1;
      if (nep <= promjer)
        smjer1 = 0;
      if (mety >= nep - promjer && mety <= nep + promjer)
        if (metx > (centar - promjer) && metx < (centar + promjer))
        {
          metx = -20;
          bodovi = bodovi + 1;
          postoji = 0;
        }
      int pozicija = poz + 8;
      if (ry >= pozicija - 8 && ry <= pozicija + 8)
        if (rx < 12 && rx > 4)
        {
          rx = 95;
          ry = -50;
          zivoti = zivoti - 1;
        }
      if (ry2 >= pozicija - 8 && ry2 <= pozicija + 8)
        if (rx2 < 12 && rx2 > 4)
        {
          rx2 = -50;
          ry2 = -50;
          zivoti = zivoti - 1;
        }
      if (ry3 >= pozicija - 8 && ry3 <= pozicija + 8)
        if (rx3 < 12 && rx3 > 4)
        {
          rx3 = -50;
          ry3 = -50;
          zivoti = zivoti - 1;
        }
      if (ry4 >= pozicija - 8 && ry4 <= pozicija + 8)
        if (rx4 < 12 && rx4 > 4)
        {
          rx4 = 200;
          ry4 = -50;
          ispaljeno = 0;
          zivoti = zivoti - 1;
        }
      if (rx4 < 1) {
        ispaljeno = 0;
        rx4 = 200;
      }

      if (zivoti == 0)
        go = 1;
    }
    if (go == 1)
    {
      if (zivoti == 0) {
        zivoti = 5;
      }
      display.clear();
      display.drawString(7, 10, "GAME OVER");
      display.drawString(7, 30, "score:");
      display.drawString(44, 30, String(bodovi));
      display.drawString(7, 40, "level");
      display.drawString(122, 0, String(nivo));
      display.drawString(7, 50, "time(s):");
      display.drawString(60, 50, String(trenutno / 1000));
      display.display();
      if (digitalRead(D5) == 0)
      {
        metx = 0;
        mety = 0;
        postoji = 0;
        nep = 8;
        smjer1 = 0;
        go = 0;
        rx = 95;
        ry = 0;
        rx2 = 95;
        ry2 = 0;
        rx3 = 95;
        ry3 = 0;
        bodovi = 0;
        brzina = 3;
        bkugle = 1;
        najmanja = 600;
        najveca = 1200;
        promjer = 12;
        rx4 = 95;
        ry4 = 0;
        zivoti = 5;
        poc1 = 0;
        ispaljeno = 0;
        nivo = 1;
        pocetno = 0;
        odabrano = 0;
        trenutno1 = 0;
        nivovrije = 0;
      }
      if (digitalRead(D3) == 0)
      {
        go = 0;
        metx = 0;
        mety = 0;
        postoji = 0;
        nep = 8;
        smjer1 = 0;
        go = 0;
        rx = 95;
        ry = 0;
        rx2 = 95;
        ry2 = 0;
        rx3 = 95;
        ry3 = 0;
        bodovi = 0;
        brzina = 3;
        bkugle = 1;
        najmanja = 600;
        najveca = 1200;
        promjer = 12;
        rx4 = 95;
        ry4 = 0;
        zivoti = 5;
        poc1 = 0;
        ispaljeno = 0;
        nivo = 1;
        pocetno = 0;
        odabrano = 0;
        trenutno1 = 0;
        nivovrije = 0;
        WiFi.mode(WIFI_OFF);
        menu++;
        updateMenu();
        deg = 0;
        a = 0;
        b = 0;
        ab = 0;
        sayac = 0;
        sayac1 = 0;
        otoekran = false;
        uyku = false;
        display.setFont(ArialMT_Plain_10);
        particleSensor.setup(0); //Configure sensor with default settings
        ses1();
        delay(100);
        digitalWrite(led, LOW);
        digitalWrite(buzzer, LOW);
      }
    }
  }
  /////////////////////////Star Wars bitti/////////////////////////
  /////////////////////////fener/////////////////////////
  if ( deg == 19) {
    button.tick();
    button1.tick();
    display.clear();
    stila();
    display.drawString(0, 20, "R");
    display.drawString(50, 20, "G");
    display.drawString(100, 20, "B");
    display.drawRect(mxled[indled], myled[indled], 5, 10);
    display.display();
  }
  /////////////////////////fener bitti/////////////////////////
  /////////////////////////uzaktan kontrol/////////////////////////
  if (deg == 20) {
    WiFi.softAP(ssid, password);
    WiFi.softAPConfig(local_ip, gateway, subnet);
    display.clear();
    stila();
    display.drawString(0, 0, "Wifi ağı oluşturuluyor.");
    delay(100);
    display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
    delay(100);
    display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
    delay(100);
    display.clear();
    stila();
    display.drawString(0, 0, "Wifi ağı oluştururldu..");
    display.drawString(0, 20, "Kontrol Etkin.");
    display.display();
    delay(100);
    server.on("/", handle_OnConnect);
    server.on("/led1on", handle_led1on);
    server.on("/led1off", handle_led1off);
    server.on("/led2on", handle_led2on);
    server.on("/led2off", handle_led2off);
    server.handleClient();
    server.begin(); //sunucuyu başlattı
    Serial.println("HTTP server started");
    if (LED1status)
    {
      digitalWrite(led, HIGH);
    }
    else
    {
      digitalWrite(led, LOW);
    }

    if (LED2status)
    {
      digitalWrite(buzzer, HIGH);
    }
    else
    {
      digitalWrite(buzzer, LOW);
    }
  }
  /////////////////////////uzaktan kontrol bitti/////////////////////////
  /////////////////////////Alarm/////////////////////////
  if (deg == 21) {
    if (al == 0) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(0, 0, "Alarmlar:");
      display.drawString(10, 20, "Alarm 1");
      display.drawString(10, 30, "Alarm 2");
      display.drawString(10, 40, "Alarm 3");
      display.drawString(10, 50, "Saat Basi");
      display.drawRect(mx1[ind1], my1[ind1], 5, 10);
      display.display();
    }
    if (al == 1) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(0, 0, "Alarm 1");
      display.setFont(ArialMT_Plain_24);
      display.drawString(20, 30, String(alsa1));
      display.drawString(50, 30, ":");
      display.drawString(60, 30, String(almu1));
      display.display();
      display.setFont(ArialMT_Plain_10);
      if (alarm1 == 1) {
        display.drawString(80, 0, "ACIK");
        display.display();
      }
      if (alarm1 == 0) {
        display.drawString(80, 0, "KAPALİ");
        display.display();
      }
    }
    if (al == 2) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(0, 0, "Alarm 2");
      display.setFont(ArialMT_Plain_24);
      display.drawString(20, 30, String(alsa2));
      display.drawString(50, 30, ":");
      display.drawString(60, 30, String(almu2));
      display.display();
      display.setFont(ArialMT_Plain_10);
      if (alarm2 == 1) {
        display.drawString(80, 0, "ACIK");
        display.display();
      }
      if (alarm2 == 0) {
        display.drawString(80, 0, "KAPALİ");
        display.display();
      }
    }
    if (al == 3) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(0, 0, "Alarm 3");
      display.setFont(ArialMT_Plain_24);
      display.drawString(20, 30, String(alsa3));
      display.drawString(50, 30, ":");
      display.drawString(60, 30, String(almu3));
      display.display();
      display.setFont(ArialMT_Plain_10);
      if (alarm3 == 1) {
        display.drawString(80, 0, "ACIK");
        display.display();
      }
      if (alarm3 == 0) {
        display.drawString(80, 0, "KAPALİ");
        display.display();
      }
    }
    if (al == 4) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(0, 0, "Saat Basi");
      display.setFont(ArialMT_Plain_24);
      display.drawString(20, 20, "60");
      display.setFont(ArialMT_Plain_10);
      display.drawString(0, 50, "Dakikada Bir");
      display.display();
      display.setFont(ArialMT_Plain_10);
      if (saatbas == 1) {
        display.drawString(80, 0, "ACIK");
        display.display();
      }
      if (saatbas == 0) {
        display.drawString(80, 0, "KAPALİ");
        display.display();
      }
    }
  }
  /////////////////////////Alarm Bitti/////////////////////////
  /////////////////////////ayarlar/////////////////////////
  if ( deg == 22) {
    if (te == 0) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(5, 10, "Tema");
      display.drawString(5, 20, "Saat Stili");
      display.drawString(5, 30, "Çevre Çizgisi");
      display.drawString(5, 40, "Saat1");
      display.drawString(70, 40, "Saat2");
      display.drawString(5, 50, "Wifi");
      display.drawString(70, 50, "Parliklik");
      display.drawRect(mx2[ind2], my2[ind2], 5, 10);
      display.display();
    }
    if (te == 1) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(5, 5, "Tema");
      if (dark == 1) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Açik");
      }
      if (dark == 0) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Kapalı");
      }
      display.setFont(ArialMT_Plain_10);
      display.display();
    }
    if (te == 2) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(5, 5, "Saat Stili");
      if (saat == 0) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Digital");
      }
      if (saat == 1) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Analog");
      }
      if (saat == 2) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Digital2");
      }
      display.setFont(ArialMT_Plain_10);
      display.display();
    }
    if (te == 3) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(5, 5, "Çevre Çizgisi");
      if (stil == 1) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Açik");
      }
      if (stil == 0) {
        display.setFont(ArialMT_Plain_24);
        display.drawString(30, 20, "Kapalı");
      }
      display.display();
      display.setFont(ArialMT_Plain_10);
    }
    if (te == 4) {
      WiFi.begin(yourssid, yourpassword);
      while ( WiFi.status() != WL_CONNECTED ) {
        display.clear();
        stila();
        display.drawString(0, 0, " Wifi agina baglaniyor.");
        display.drawString(5, 20, "bekleyiniz...");
        display.display();
        Serial.print ( "." );
        delay ( 500 );
      }
      timeClient.begin();
      display.clear();
      stila();
      display.drawString(0, 0, " Wifi agına baglandi.");
      display.drawString(0, 20, "(tr.pool.ntp.org)");
      display.drawString(0, 30, "'den veri alindi");
      display.display();
      timeClient.update();
      delay(250);
      Serial.print(timeClient.getHours());
      Serial.print(":");
      Serial.print(timeClient.getMinutes());
      Serial.print(":");
      Serial.println(timeClient.getSeconds());
      //  Serial.println(timeClient.getFormattedTime());
      unsigned long epochTime = timeClient.getEpochTime();
      String formattedTime = timeClient.getFormattedTime();
      byte currentHour = timeClient.getHours();
      byte currentMinute = timeClient.getMinutes();
      byte currentSecond = timeClient.getSeconds();
      byte weekDay = timeClient.getDay();
      //Get a time structure
      struct tm *ptm = gmtime ((time_t *)&epochTime);
      byte monthDay = ptm->tm_mday;
      byte currentMonth = ptm->tm_mon + 1;
      byte currentYear = ptm->tm_year + 1852;
      //String currentDate = String(currentYear) + "-" + String(currentMonth) + "-" + String(monthDay);
      //(byte *second, byte *minute, byte *hour, byte *dayOfWeek, byte *dayOfMonth, byte *month, byte *year)
      setDS3231time(currentSecond, currentMinute, currentHour, weekDay, monthDay, currentMonth, currentYear);
      Serial.print(weekDay);
      deg = 1;
      delay(1000);
    }
    if (te == 5) {
      WiFi.softAP(ssid, password);
      WiFi.softAPConfig(local_ip, gateway, subnet);
      display.clear();
      stila();
      display.drawString(0, 0, "Wifi ağı oluşturuluyor.");
      delay(100);
      display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
      delay(100);
      display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
      delay(100);
      display.clear();
      stila();
      display.drawString(0, 0, "Wifi ağı oluştururldu..");
      display.drawString(0, 20, "Kontrol Etkin.");
      display.display();
      delay(100);
      /*  server.on("/", handle_OnConnect);
        server.on("/led1on", handle_led1on);
        server.on("/led1off", handle_led1off);
        server.on("/led2on", handle_led2on);
        server.on("/led2off", handle_led2off);*/
      server.onNotFound(handle_NotFound);
      server.on("/", handleMainPage); //aynı sayfaya dönecek
      server.on("/set", handleSetCommand);        // parametreleri koda set ön eki ile göndereceğiz.
      server.handleClient();
      server.begin(); //sunucuyu başlattı
      Serial.println("HTTP server started");
    }
    if (te == 6) {
      WiFi.softAP(ssid, password);
      Serial.print(ssid);
      Serial.print(password);
      WiFi.softAPConfig(local_ip, gateway, subnet);
      display.clear();
      stila();
      display.drawString(0, 0, "Wifi ağı oluşturuluyor.");
      delay(100);
      display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
      delay(100);
      display.drawString(0, 0, "Wifi ağı oluşturuluyor..");
      delay(100);
      display.clear();
      stila();
      display.drawString(0, 0, "Wifi ağı oluştururldu..");
      display.drawString(0, 20, "Kontrol Etkin.");
      display.display();
      delay(100);
      /*  server.on("/", handle_OnConnect);
        server.on("/led1on", handle_led1on);
        server.on("/led1off", handle_led1off);
        server.on("/led2on", handle_led2on);
        server.on("/led2off", handle_led2off);*/
      server.onNotFound(handle_NotFound);
      server.on("/", handleWifiPage); //aynı sayfaya dönecek
      server.on("/set", handleSetCommandWifi);        // parametreleri koda set ön eki ile göndereceğiz.
      server.handleClient();
      server.begin(); //sunucuyu başlattı
      Serial.println("HTTP server started");
    }
    if (te == 7) {
      button.tick();
      button1.tick();
      display.clear();
      stila();
      display.drawString(5, 5, "Parlaklık");
      display.setFont(ArialMT_Plain_24);
      display.drawString(30, 20, String(parlak));
      display.setFont(ArialMT_Plain_10);
      display.display();
    }
  }
  /////////////////////////ayarlar bitti/////////////////////////
  /////////////////////////Alarm/////////////////////////
  byte second, minute, hour, dayOfWeek, dayOfMonth, month, year;
  readDS3231time(&second, &minute, &hour, &dayOfWeek, &dayOfMonth, &month, &year);
  if (alarm1 == 1) {
    if (saatbass1 < 150) {
      if (hour == alsa1 && minute == almu1) {  //dakika altmışa kalansız bölünürse
        saatbass = 1;
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        deg = 0;
        otoekran = false;
        delay (200);
        display.clear();
        stila();
        display.setFont(ArialMT_Plain_24);
        display.drawString(20, 20, "ALARM!");
        display.setFont(ArialMT_Plain_10);
        display.drawString(40, 115, "Secmeye Bas");
        display.display();
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        saatbass1 = saatbass1 + 1;
        otoekran = false;
        if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
          saatbass1 = 151;
          deg = 1;
          delay(100);  //bekle
          while (!digitalRead(selectButton));
        }
      }
    }
    if (hour != alsa1 && minute != almu1) {
      saatbass1 = 0;
    }
  }
  if (alarm2 == 1) {
    if (saatbass2 < 150) {
      if (hour == alsa2 && minute == almu2) {  //dakika altmışa kalansız bölünürse
        saatbass = 1;
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        deg = 0;
        otoekran = false;
        delay (200);
        display.clear();
        stila();
        display.setFont(ArialMT_Plain_24);
        display.drawString(20, 20, "ALARM!");
        display.setFont(ArialMT_Plain_10);
        display.drawString(40, 115, "Secmeye Bas");
        display.display();
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        saatbass2 = saatbass2 + 1;
        otoekran = false;
        if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
          saatbass2 = 151;
          deg = 1;
          delay(100);  //bekle
          while (!digitalRead(selectButton));
        }
      }
    }
    if (hour == alsa2 && minute != almu2) {
      saatbass2 = 0;
    }
  }
  if (alarm3 == 1) {
    if (saatbass3 < 150) {
      if (hour == alsa3 && minute == almu3) {  //dakika altmışa kalansız bölünürse
        saatbass = 1;
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        deg = 0;
        otoekran = false;
        delay (200);
        display.clear();
        stila();
        display.setFont(ArialMT_Plain_24);
        display.drawString(20, 20, "ALARM!");
        display.setFont(ArialMT_Plain_10);
        display.drawString(40, 115, "Secmeye Bas");
        display.display();
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        saatbass3 = saatbass3 + 1;
        if (!digitalRead(selectButton)) {  //seç düğmesine basarsa
          saatbass3 = 151;
          deg = 1;
          delay(100);  //bekle
          while (!digitalRead(selectButton));
        }
      }
    }
    if (hour == alsa3 && minute != almu3) {
      saatbass3 = 0;
    }
  }
  else if (suiz == 0) {
    if (suizbass == 0) {
      if (minute == 0) {
        otoekran = false;
        deg = 0;
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        delay (300);
        display.clear();
        stila();
        display.setFont(ArialMT_Plain_24);
        display.drawString(20, 20, "SU IC!");
        display.setFont(ArialMT_Plain_10);
        display.drawString(40, 115, "Secmeye Bas");
        display.display();
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        suizbass = suizbass + 1;
      }
    }
    if (minute != 0) {
      suizbass = 0;
    }
  }
  else if (oturmaiz == 0) {
    if (Steps % 2000 == 0 && Steps != 0) {
      if (otbass == 0) {  //dakika altmışa kalansız bölünürse
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        otoekran = false;
        deg = 0;
        delay (300);
        display.clear();
        stila();
        display.setFont(ArialMT_Plain_24);
        display.drawString(20, 20, "Biraz Dinlen!");
        display.setFont(ArialMT_Plain_10);
        display.drawString(40, 115, String(Steps));
        display.display();
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        otbass = otbass + 1;
      }
    }
    if (Steps % 2000 != 0) {
      otbass = 0;
    }
  }
  if (saatbas == true) {
    if (saatbass == 0) {
      if (minute == 0) {  //dakika altmışa kalansız bölünürse
        ses1();   //ses açma kapma komuduna göre ses ya çalar ya da çalmaz
        delay (300);
        Serial.print("Saat başı");
        digitalWrite(buzzer, LOW);    //ses çalmaz
        digitalWrite(led, HIGH);
        digitalWrite(led1, HIGH);
        digitalWrite(led2, HIGH);
        saatbass = 1;
      }
    }
    if (minute != 0) {
      saatbass = 0;
    }
  }
  /////////////////////////Alarmlar bitti/////////////////////////
}
/////////////////////////menü sekmeleri/////////////////////////
void updateMenu() {
  switch (menu) {
    case 0:
      menu = 1;
      break;
    case 1:
      display.setColor(WHITE);
      deg = 1;
      ad = true;
      break;
    case 2:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, ">Sicaklik<");
      display.drawString(0, 20, "  Kalp Basinci");
      display.drawString(0, 40, "  Spo2 Hesaplama");
      display.display();
      ad = true;
      break;
    case 3:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Sicaklik");
      display.drawString(0, 20, ">Kalp Basinci<");
      display.drawString(0, 40, "  Spo2 Hesaplama");
      display.display();
      ad = true;
      break;
    case 4:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Sicaklik");
      display.drawString(0, 20, "  Kalp Basinci");
      display.drawString(0, 40, ">Spo2 Hesaplama<");
      display.display();
      ad = true;
      break;
    case 5:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, ">Kronometre<");
      display.drawString(0, 20, "  Notlar");
      display.drawString(0, 40, "  Hesap Makinesi");
      display.display();
      ad = true;
      break;
    case 6:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Kronometre");
      display.drawString(0, 20, ">Notlar<");
      display.drawString(0, 40, "  Hesap Makinesi");
      display.display();
      ad = true;
      break;
    case 7:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Kronometre");
      display.drawString(0, 20, "  Notlar");
      display.drawString(0, 40, ">Hesap Makinesi<");
      display.display();
      ad = true;
      break;
    case 8:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, ">Zamanlayıcı<");
      display.drawString(0, 20, "  Adım Sayar");
      display.drawString(0, 40, " Uyku Takip");
      display.display();
      ad = true;
      break;
    case 9:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, "  Zamanlayıcı");
      display.drawString(0, 20, ">Adım Sayar<");
      display.drawString(0, 40, " Uyku Takip");
      display.display();
      ad = true;
      break;
    case 10:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, "  Zamanlayıcı");
      display.drawString(0, 20, "  Adım Sayar");
      display.drawString(0, 40, ">Uyku Takip<");
      display.display();
      ad = true;
      break;
    case 11:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, ">Gyro<");
      display.drawString(0, 20, "  Hava Durumu");
      display.drawString(0, 40, "  Izleme");
      display.display();
      ad = true;
      break;
    case 12:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, "  Gyro");
      display.drawString(0, 20, ">Hava Durumu<");
      display.drawString(0, 40, "  Izleme");
      display.display();
      ad = true;
      break;
    case 13:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, "  Gyro");
      display.drawString(0, 20, "  Hava Durumu");
      display.drawString(0, 40, ">Izleme<");
      display.display();
      ad = true;
      break;
    case 14:
      display.clear();
      tema();
      display.setFont(ArialMT_Plain_10);
      stila();
      display.drawString(0, 0, ">Press Game<");
      display.drawString(0, 20, "  Flappy Bird");
      display.drawString(0, 40, "  Ping Pong");
      display.display();
      ad = true;
      break;
    case 15:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Press Game");
      display.drawString(0, 20, ">Flappy Bird<");
      display.drawString(0, 40, "  Ping Pong");
      display.display();
      ad = true;
      break;
    case 16:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Press Game");
      display.drawString(0, 20, "  Flappy Bird");
      display.drawString(0, 40, ">Ping Pong<");
      display.display();
      ad = true;
      break;
    case 17:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, ">Notalar<");
      display.drawString(0, 20, "  Star Wars");
      display.drawString(0, 40, "  Fener");
      display.display();
      ad = true;
      break;
    case 18:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Notalar");
      display.drawString(0, 20, ">Star Wars<");
      display.drawString(0, 40, "  Fener");
      display.display();
      ad = true;
      break;
    case 19:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Notalar");
      display.drawString(0, 20, "  Star Wars");
      display.drawString(0, 40, ">Fener<");
      display.display();
      ad = true;
      break;
    case 20:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, ">Uzaktan Kontrol<");
      display.drawString(0, 20, "  Alarm");
      display.drawString(0, 40, "  Ayarlar");
      display.display();
      ad = true;
      break;
    case 21:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Uzaktan Kontrol");
      display.drawString(0, 20, ">Alarm<");
      display.drawString(0, 40, "  Ayarlar");
      display.display();
      ad = true;
      break;
    case 22:
      display.clear();
      tema();
      stila();
      display.drawString(0, 0, "  Uzaktan Kontrol");
      display.drawString(0, 20, "  Alarm");
      display.drawString(0, 40, ">Ayarlar<");
      display.display();
      ad = true;
      break;
    case 23:
      menu = 1;
      break;
  }
}
/////////////////////////menü sekmeleri bitti/////////////////////////
/////////////////////////menü içerikleri/////////////////////////
void executeAction() {
  switch (menu) {
    /*   case 1:
         action1();
         break;*/
    case 2:
      action2();
      break;
    case 3:
      action3();
      break;
    case 4 :
      action4();
      break;
    case 5:
      action5();
      break;
    case 6:
      action6();
      break;
    case 7:
      action7();
      break;
    case 8:
      action8();
      break;
    case 9:
      action9();
      break;
    case 10:
      action10();
      break;
    case 11:
      action11();
      break;
    case 12:
      action12();
      break;
    case 13:
      action13();
      break;
    case 14:
      action14();
      break;
    case 15:
      action15();
      break;
    case 16:
      action16();
      break;
    case 17:
      action17();
      break;
    case 18:
      action18();
      break;
    case 19:
      action19();
      break;
    case 20:
      action20();
      break;
    case 21:
      action21();
      break;
    case 22:
      action22();
      break;
  }
}
/*void action1() {
  // saat = true;
  }*/
void action2() {
  deg = 2;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action3() {
  deg = 3;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action4() {
  deg = 4;
  a = 1;
  display.setColor(WHITE);
  ad = false;
  byte ledBrightness = 60; //Options: 0=Off to 255=50mA
  byte sampleAverage = 4; //Options: 1, 2, 4, 8, 16, 32
  byte ledMode = 3; //Options: 1 = Red only, 2 = Red + IR, 3 = Red + IR + Green
  byte sampleRate = 100; //Options: 50, 100, 200, 400, 800, 1000, 1600, 3200
  int pulseWidth = 411; //Options: 69, 118, 215, 411
  int adcRange = 4096; //Options: 2048, 4096, 8192, 16384
  particleSensor.setup(ledBrightness, sampleAverage, ledMode, sampleRate, pulseWidth, adcRange); //Configure sensor with these settings
}
void action5() {
  deg = 5;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action6() {
  deg = 6;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action7() {
  deg = 7;
  a = 1;
  ind = 0;
  //int pres = 0;
  stis1 = 0;
  poc = 0;
  line = "";
  num1 = "";
  num2 = "";
  operacija = 0;
  changeNumber = 0;
  n1 = 0.0000;
  n2 = 0.0000;
  res = 0.0000;
  display.setColor(WHITE);
  ad = false;
}
void action8() {
  deg = 8;
  a = 1;
  display.setColor(WHITE);
  ad = false;
  timer123 = 0;
}
void action9() {
  deg = 9;
  a = 1;
  display.setColor(WHITE);
  ad = true;
}
void action10() {
  deg = 10;
  a = 1;
  display.setColor(WHITE);
  ad = true;
}
void action11() {
  deg = 11;
  a = 1;
  display.setColor(WHITE);
  ad = true;
}
void action12() {
  deg = 12;
  a = 1;
  display.setColor(WHITE);
  ad = false;
  f = 0;
}
void action13() {
  deg = 13;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action14() {
  deg = 14;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action15() {
  deg = 15;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action16() {
  deg = 16;
  a = 1;
  display.setColor(WHITE);
  display.clear();
  ad = false;
}
void action17() {
  deg = 17;
  a = 1;
  ind5 = 0;
  display.setColor(WHITE);
  ad = false;
}
void action18() {
  a = 1;
  display.setColor(WHITE);
  ad = false;
  display.clear();
  display.drawXbm(6, 11, 48, 48, storm);
  //display.drawFastImage(6, 11, storm, 48, 48, 1);
  display.drawString(65, 14, "xWing");
  display.drawString(65, 17, "vs");
  display.drawString(0, 0, "Esp8266");
  display.drawString(65, 39, "Death");
  display.drawString(65, 14, "star");
  display.display();
  delay(3000);
  deg = 18;
  ab = 1;
}
void action19() {
  deg = 19;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action20() {
  deg = 20;
  a = 1;
  display.setColor(WHITE);
  ad = false;
}
void action21() {
  deg = 21;
  a = 1;
  al = 0;
  ind1 = 0;
  display.setColor(WHITE);
  ad = false;
}
void action22() {
  deg = 22;
  a = 1;
  te = 0;
  ind2 = 0;
  display.setColor(WHITE);
  ad = false;
}
/////////////////////////menü içerikleri bitti/////////////////////////
/////////////////////////ses modları/////////////////////////
void ses1() {  //ses komudumuz
  if ( ses == 0) {  //ses kapalı ise
    digitalWrite(buzzer, LOW);  //buzzer çalmasın
    digitalWrite(led, HIGH);
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
  }
  if (ses == 1) {  //ses açık ise
    digitalWrite(buzzer, HIGH);   //buzzer çalsın
    digitalWrite(led, LOW);      //led yansın
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
  }
}
void le () {
  digitalWrite(led, LOW);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  delay(300);
  digitalWrite(led, HIGH);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
}
/////////////////////////temalar/////////////////////////
void stila() {
  if ( stil == 0) {

  }
  if (stil == 1) {
    display.drawRect(0, 0, 128, 64);
    /*  display.setCursor(40, 50);
      display.print("ARSAL");   //menü dekoru*/
  }
}
void stilb() {
  if ( still == 0) {

  }
  if (still == 1) {
    display.drawRect(0, 15, 128, 64);
    display.drawRect(0, 50, 128, 64);
  }
}
void tema() {
  if ( dark == 0) {
    display.setColor(WHITE);
  }
  if (dark == 1) {
    display.setColor(WHITE);
    display.fillRect(0, 0, 128, 64);
    display.setColor(BLACK);
    display.display();
  }
}
/////////////////////////saat değiştirme kodları/////////////////////////
void handleMainPage() {

  webPage = "<html xmlns=\"http://www.w3.org/1999/xhtml\"><head>";
  webPage += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />";
  webPage += "<title>ledsaat_server</title></head><body><p><font size=\"16\">NodemcuWatch Saat Ayar Sayfası</font></p>";
  webPage += "<p>&nbsp;</p><form id=\"form1\" name=\"form1\" method=\"get\" action=\"/set\">";

  // saat saniye
  webPage += "<p>Saniye:<label><input name=\"saniye\" type=\"text\" id=\"saniye\" maxlength=\"2\" /></label></p>";
  // saat dakika
  webPage += "<p>Dakika<label><input name=\"dakika\" type=\"text\" id=\"dakika\" maxlength=\"2\" /></label></p>";
  // saat saat
  webPage += "<p>Saat:<label><input name=\"saat\" type=\"text\" id=\"saat\" maxlength=\"2\" /></label></p>";
  // saat haftanın günü
  webPage += "<p>Haftaın Günü:<label><input name=\"gün\" type=\"text\" id=\"gün\" maxlength=\"2\" /></label></p>";
  // saat ayıngünü
  webPage += "<p>Ayın Günü:<label><input name=\"aygün\" type=\"text\" id=\"aygün\" maxlength=\"2\" /></label></p>";
  // saat ay
  webPage += "<p>Ay:<label><input name=\"ay\" type=\"text\" id=\"ay\" maxlength=\"2\" /></label></p>";
  // saat yıl
  webPage += "<p>Yıl:<label><input name=\"yıl\" type=\"text\" id=\"yıl\" maxlength=\"2\" /></label></p>";
  //Hava durumu ıd
  webPage += "<p>Konum ID::<label><input name=\"ıd\" type=\"text\" id=\"ıd\" maxlength=\"6\" /></label></p>";


  //radio butonlar
  /* webPage += "<p><label><input type=\"radio\" name=\"setalarm\" value=\"1\" id=\"setalarm_0\"" + acik + "/>";
    webPage += "Alarm-1 Açık</label><br /><label><input type=\"radio\" name=\"setalarm\" value=\"0\" id=\"setalarm_1\"" + kapali + " />";
    webPage += "Alarm-1 Kapalı</label> <br /> </p>";*/
  //submit butonu
  webPage += "<p><input type=\"submit\" name=\"button\" id=\"button\" value=\"Onay\" />";
  webPage += "</p><p><label></label></p></form><p>&nbsp;</p><p>&nbsp;</p>";
  webPage += "</body></html>";

  webStat = "<p style=\"font-size: 90%; color: #FF8000;\">RSSI: ";
  webStat += WiFi.RSSI();
  webStat += "<br/>";
  webStat += "Uptime [min]: ";
  webStat += millis() / (1000 * 60);
  webStat += "</p>";
  server.send(200, "text/html", webPage + webStat);
  Serial.println("Web sayfası isteği");
}
//sayfadan gelen değişkenlerin alınıp kodun içinde kullanılması için kullandığımız fonksiyon
void handleSetCommand() {
  String response = "";
  if (server.args() == 0) { //hiç argüman gelmemişse
    response = "Parametre Yok";
    Serial.println("Parametre Yok");
  }
  else { //veri gelmişse
    byte second;
    byte minute;
    byte hour;
    byte dayOfWeek;
    byte dayOfMonth;
    byte month;
    byte year;
    if (server.argName(0) == "saniye") { //alarmduration isimli gelen veriyi al ve Integer'a çevirip programdaki değişkeni güncelle.
      second = server.arg("saniye").toInt();
      Serial.println(second);
    }
    if (server.argName(1) == "dakika") {
      minute = (byte)server.arg("dakika").toInt();
      Serial.println(minute);
    }
    if (server.argName(2) == "saat") {
      hour = (byte)server.arg("saat").toInt();
      Serial.println(hour);
    }
    if (server.argName(3) == "gün") {
      dayOfWeek = (byte)server.arg("gün").toInt();
      Serial.println(dayOfWeek);
    }
    if (server.argName(4) == "aygün") {
      dayOfMonth = (byte)server.arg("aygün").toInt();
      Serial.println(dayOfMonth);
    }
    if (server.argName(5) == "ay") {
      month = server.arg("ay").toInt();
      Serial.println(month);
    }
    if (server.argName(6) == "yıl") {
      year = server.arg("yıl").toInt();
      Serial.println(year);
      delay(100);
    }
    if (server.argName(7) == "ıd") {
      CityID = server.arg("yıl").toInt();
      Serial.println(year);
      delay(100);
      //response = "Senkron süresi güncellendi:";
      //response += alarmduration;
    }
    response = "<html><head><meta http-equiv=\"refresh\" content=\"2; url=/\"></head><body>Ayarlar Guncellendi. Bekleyin ana sayfaya yonlendiriliyorsunuz.</body></html>";
    setDS3231time( second, minute, hour, dayOfWeek, dayOfMonth, month, year);
    deg = 1;
    //String CityID = "323786";
    // setDS3231time(30, 29, 12, 3, 14, 11, 16);
    server.send(200, "text/html", response);          //HTTP cevaplarını sunucuya gönderiyor.
    Serial.print("Change request: ");
    Serial.println(response);
  }
}
/////////////////////////saat değiştirme kodları/////////////////////////
/////////////////////////wifi değiştirme kodları/////////////////////////
void handleWifiPage() {

  webPagewifi = "<html xmlns=\"http://www.w3.org/1999/xhtml\"><head>";
  webPagewifi += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />";
  webPagewifi += "<title>ledsaat_server</title></head><body><p><font size=\"16\">NodemcuWatch Wifi Ayar Sayfası</font></p>";
  webPagewifi += "<p>&nbsp;</p><form id=\"form1\" name=\"form1\" method=\"get\" action=\"/set\">";

  // ssid
  webPagewifi += "<p>Ad:<label><input name=\"ssid\" type=\"text\" id=\"ssid\" maxlength=\"10\" /></label></p>";
  // pswd
  webPagewifi += "<p>Sifre<label><input name=\"pswd\" type=\"text\" id=\"pswd\" maxlength=\"10\" /></label></p>";
  /* // ssid1
    webPagewifi += "<p>Cihazin Adı:<label><input name=\"ssd1\" type=\"text\" id=\"ssd1\" maxlength=\"10\" /></label></p>";
    //pswd1
    webPagewifi += "<p>Cihazin Sifresi:<label><input name=\"pswd1\" type=\"text\" id=\"pswd1\" maxlength=\"10\" /></label></p>";*/

  //submit butonu
  webPagewifi += "<p><input type=\"submit\" name=\"button\" id=\"button\" value=\"Onay\" />";
  webPagewifi += "</p><p><label></label></p></form><p>&nbsp;</p><p>&nbsp;</p>";
  webPagewifi += "</body></html>";

  webStatwifi = "<p style=\"font-size: 90%; color: #FF8000;\">RSSI: ";
  webStatwifi += WiFi.RSSI();
  webStatwifi += "<br/>";
  webStatwifi += "Uptime [min]: ";
  webStatwifi += millis() / (1000 * 60);
  webStatwifi += "</p>";
  server.send(200, "text/html", webPagewifi + webStatwifi);
  Serial.println("Web sayfası isteği");
}
//sayfadan gelen değişkenlerin alınıp kodun içinde kullanılması için kullandığımız fonksiyon
void handleSetCommandWifi() {
  String response = "";
  if (server.args() == 0) { //hiç argüman gelmemişse
    response = "Parametre Yok";
    Serial.println("Parametre Yok");
  }
  else { //veri gelmişse
    if (server.argName(0) == "ssid") { //alarmduration isimli gelen veriyi al ve Integer'a çevirip programdaki değişkeni güncelle.
      yourssid = server.arg("ssid").c_str();
      Serial.println(yourssid);
    }
    if (server.argName(1) == "pswd") {
      yourpassword  = server.arg("pswd").c_str();
      Serial.println(yourpassword);
    }
    /*   if (server.argName(2) == "ssid1") {
         ssid = server.arg("ssid1").c_str();
         Serial.println(ssid);
       }
       if (server.argName(3) == "pswd1") {
         password = server.arg("pswd1").c_str();
         Serial.println( password);
         delay(100);
       }*/
    response = "<html><head><meta http-equiv=\"refresh\" content=\"2; url=/\"></head><body>Ayarlar Guncellendi.Sayfayı Kapatabilirsiniz</body></html>";
    delay(500);
    deg = 1;
    server.send(200, "text/html", response);          //HTTP cevaplarını sunucuya gönderiyor.
    Serial.print("Change request: ");
    Serial.println(response);
    WiFi.mode(WIFI_OFF);
  }
}
/////////////////////////wifi değiştirme kodları/////////////////////////
/////////////////////////Notlar/////////////////////////
void handleNotPage() {

  webPagenot = "<html xmlns=\"http://www.w3.org/1999/xhtml\"><head>";
  webPagenot += "<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />";
  webPagenot += "<title>ledsaat_server</title></head><body><p><font size=\"16\">NodemcuWatch Notlar Ayar Sayfası</font></p>";
  webPagenot += "<p>&nbsp;</p><form id=\"form1\" name=\"form1\" method=\"get\" action=\"/set\">";

  // not
  webPagenot += "<p>Not:<label><input name=\"nott\" type=\"text\" id=\"nott\" maxlength=\"10\" /></label></p>";

  //submit butonu
  webPagenot += "<p><input type=\"submit\" name=\"button\" id=\"button\" value=\"Onay\" />";
  webPagenot += "</p><p><label></label></p></form><p>&nbsp;</p><p>&nbsp;</p>";
  webPagenot += "</body></html>";

  webStatnot = "<p style=\"font-size: 90%; color: #FF8000;\">RSSI: ";
  webStatnot += WiFi.RSSI();
  webStatnot += "<br/>";
  webStatnot += "Uptime [min]: ";
  webStatnot += millis() / (1000 * 60);
  webStatnot += "</p>";
  server.send(200, "text/html", webPagenot + webStatnot);
  Serial.println("Web sayfası isteği");
}
//sayfadan gelen değişkenlerin alınıp kodun içinde kullanılması için kullandığımız fonksiyon
void handleSetCommandNot() {
  String response = "";
  if (server.args() == 0) { //hiç argüman gelmemişse
    response = "Parametre Yok";
    Serial.println("Parametre Yok");
  }
  else { //veri gelmişse
    if (server.argName(0) == "nott") {
      if (ind8 == 0) {
        not1 = "";
        not1 = server.arg("nott").c_str();
        Serial.println(not1);
        delay(100);
      }
      if (ind8 == 1) {
        not2 = "";
        not2 =  server.arg("nott").c_str();
        Serial.println(not2);
        delay(100);
      }
      if (ind8 == 2) {
        not3 = "";
        not3 =  server.arg("nott").c_str();
        Serial.println(not3);
        delay(100);
      }
      if (ind8 == 3) {
        not4 = "";
        not4 =  server.arg("nott").c_str();
        Serial.println(not4);
        delay(100);
      }
      if (ind8 == 4) {
        not5 = "";
        not5 = server.arg("nott").c_str();
        Serial.println(not5);
        delay(100);
      }
      if (ind8 == 5) {
        ekrannot = "";
        ekrannot = server.arg("nott").c_str();
        Serial.println(ekrannot);
        delay(100);
      }
      response = "<html><head><meta http-equiv=\"refresh\" content=\"2; url=/\"></head><body>Ayarlar Guncellendi.Sayfayı Kapatabilirsiniz</body></html>";
      delay(500);
      deg = 1;
      notdur = false;
      server.send(200, "text/html", response);          //HTTP cevaplarını sunucuya gönderiyor.
      Serial.print("Change request: ");
      Serial.println(response);
    }
  }
}
/////////////////////////Notlar/////////////////////////
/////////////////////////uzaktan konrol kodları/////////////////////////
void handle_OnConnect() {
  LED1status = LOW;
  LED2status = LOW;
  Serial.println("GPIO7 Status: OFF | GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status, LED2status));
}
void handle_led1on() {
  LED1status = HIGH;
  Serial.println("GPIO7 Status: ON");
  server.send(200, "text/html", SendHTML(true, LED2status));
}

void handle_led1off() {
  LED1status = LOW;
  Serial.println("GPIO7 Status: OFF");
  server.send(200, "text/html", SendHTML(false, LED2status));
}

void handle_led2on() {
  LED2status = HIGH;
  Serial.println("GPIO6 Status: ON");
  server.send(200, "text/html", SendHTML(LED1status, true));
}

void handle_led2off() {
  LED2status = LOW;
  Serial.println("GPIO6 Status: OFF");
  server.send(200, "text/html", SendHTML(LED1status, false));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
String SendHTML(uint8_t led1stat, uint8_t led2stat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>LED Control</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr += ".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr += ".button-on {background-color: #1abc9c;}\n";
  ptr += ".button-on:active {background-color: #16a085;}\n";
  ptr += ".button-off {background-color: #34495e;}\n";
  ptr += ".button-off:active {background-color: #2c3e50;}\n";
  ptr += "p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<h1>ESP8266 Web Server</h1>\n";
  ptr += "<h3>Using Access Point(AP) Mode</h3>\n";
  ptr += "<h1>Robotics Projects Turkey</h1>\n";
  if (led1stat)
  {
    ptr += "<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";
  }
  if (led2stat)
  {
    ptr += "<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";
  }
  else
  {
    ptr += "<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";
  }
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
/////////////////////////uzaktan kontrol kodları/////////////////////////
/////////////////////////oyun kodu/////////////////////////
void oledConfig() {
  oled.begin();
  oled.setFont(u8g2_font_6x10_tf);
  oled.setFontRefHeightExtendedText();
  oled.setDrawColor(1);
  oled.setFontPosTop();
  oled.setFontDirection(0);
}
void move() {
  // If the ball has reached a boundary, change direction
  if (x + radius > gameWidth || x - radius < padWidth)
    xSpeed = -xSpeed;
  if (y + radius >= maxHeight || y - radius <= border)
    ySpeed = -ySpeed;
  // Move the ball to its new position
  x += xSpeed;
  y += ySpeed;
  // Move the user's pad
  if (digitalRead(selectButton) == LOW) {
    userY += userSpeed;
    if (userY >= gameHeight) userY = 53; // don't let pad go off playing area
  } else if (digitalRead(upButton) == LOW) {
    userY -= userSpeed;
    if (userY <= border) userY = border;
  }
  // Move the com's pad; simple AI
  if (xSpeed) {
    if (ySpeed > 0) comY += comSpeed; // if the ball is going down, move the pad down
    else comY -= comSpeed;       // and viceversa.
    if (comY >= gameHeight) comY = gameHeight; // don't let pad go off playing area
    if (comY <= border) comY = border;
  }
  // Check if com scored
  if ((x - radius) <= (userX + 1)) {
    if (!(y + radius >= userY && y - radius <= userY + padHeight)) {
      comScore++; // golazo
      delay(1000);
      x = random(50, 70);
      y = random(border + radius + 5, 63 - 5);
    } else {
      rallyCount++;
    }
    if (rallyCount > maxRally) {
      rallyCount = 0;
      xSpeed = xSpeed > 0 ? xSpeed + 1 : xSpeed - 1;
      ySpeed = ySpeed > 0 ? ySpeed + 1 : ySpeed - 1;
    }
    if (xSpeed > 2 || ySpeed > 2) {
      xSpeed = 2;
      ySpeed = 2;
    } else if (xSpeed < -2 || ySpeed < -2) {
      xSpeed = -2;
      ySpeed = -2;
    }
  }
  // Check if user scored
  if ((comX - 1) <= (x + radius)) {
    if (!(y + radius >= comY && y - radius <= comY + padHeight)) {
      userScore++; // Messi <3
      delay(1000);
      x = random(50, 70);
      y = random(border + radius + 5, 63 - 5);
    }
  }
  // Update score
  displayScore = "ACROBOTIC u: " + String(userScore) + " | c: " + String(comScore);
}
void displa() {
  oled.firstPage();
  do {
    oled.drawCircle(x, y, radius);
    oled.drawStr(0, 0, displayScore.c_str());
    oled.drawLine(0, border, 127, border);
    oled.drawBox(userX, userY, padWidth, padHeight);
    oled.drawBox(comX, comY, padWidth, padHeight);
  } while (oled.nextPage());
  // Game Over message
  if (userScore >= maxScore || comScore >= maxScore) {
    oled.firstPage();
    do {
      const char* msg = userScore >= maxScore ? "YOU WON :)" : "YOU LOST :(";
      oled.drawStr(15, 5, msg);
      oled.drawStr(30, 30, "Press any Key to");
      oled.drawStr(30, 55, "start over");
    } while (oled.nextPage());
    // Wait until a key is pressed
    while (1) {
      if (!(digitalRead(upButton) && digitalRead(downButton))) {
        break;
      }
      delay(20);
    }
    x = random(50, 70);
    y = random(border + radius + 5, maxHeight - 5);
    userScore = 0;
    comScore = 0;
    // Mercy rule
    if (comScore >= maxScore) {
      xSpeed = 1;
      ySpeed = 1;
      rallyCount = 0;
    }
  }
}
/////////////////////////oyun kodu bitti/////////////////////////
/////////////////////////Hesap Makeinesi/////////////////////////
void myClick()
{
  if (deg == 6) {
    notdur = true;
  }
  if (deg == 7) {
    ind++;
    if (ind > 16)
      ind = 0;
  }
  if (deg == 8) {
    if (timer123 == 0) {
      if (ind75 == 0) {
        krosa = krosa + 1;
        if (krosa == 24) {
          krosa = 0;
        }
      }
      else if (ind75 == 1) {
        krodk = krodk + 1;
        if (krodk == 60) {
          krodk = 0;
        }
      }
      else if (ind75 == 2) {
        krosn = krosn + 1;
        if (krosn == 60) {
          krosn = 0;
        }
      }
    }
    else if (timer123 == 1) {
      timer123 = 0;
    }
    else if (timer123 == 3) {
      timer123 = 0;
    }
  }
  if (deg == 17) {
    if (melodi == false) {
      if (ind5 == 0) {
        tone(buzzer, do_);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 1) {
        tone(buzzer, re);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 2) {
        tone(buzzer, mi);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 3) {
        tone(buzzer, fa);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 4) {
        tone(buzzer, sol);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 5) {
        tone(buzzer, la);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 6) {
        tone(buzzer, si);
        delay(100);
        noTone(buzzer);
      }
      if (ind5 == 7) {
        tone(buzzer, DO_);
        delay(100);
        noTone(buzzer);
      }
    }
    if (melodi == true) {
      if (ind5 == 0) {
        for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
          tone(buzzer, sarki[g]);
          delay(500);
        }
        noTone(buzzer);
      }
      if (ind5 == 1) {
        for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
          tone(buzzer, tokyo[g]);
          delay(500);
        }
        noTone(buzzer);
      }
      if (ind5 == 2) {
        for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
          tone(buzzer, izmir[g]);
          delay(500);
        }
        noTone(buzzer);
      }
      if (ind5 == 3) {
        for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
          tone(buzzer, mehter[g]);
          delay(500);
        }
        noTone(buzzer);
      }
      if (ind5 == 4) {
        for (int g = 0; g < sizeof(sarki) / sizeof(int); g++) {
          tone(buzzer, sarki1[g]);
          delay(500);
        }
        noTone(buzzer);
      }
      if (ind5 == 1) {
        for (int g = 0; g < 25; g++) {
          digitalWrite(buzzer, HIGH);
          delay(250);
          digitalWrite(buzzer, LOW);
        }
        noTone(buzzer);
      }
    }
  }
  if (deg == 19) {
    if (indled == 0) {
      digitalWrite(led, LOW);
    }
    if (indled == 1) {
      digitalWrite(led1, LOW);
    }
    if (indled == 2) {
      digitalWrite(led2, LOW);
    }
  }
  if (deg == 21) {
    if (al == 0) {
      ind1++;
      if (ind1 > 3) {
        ind1 = 0;
      }
    }
    if (al == 1) {
      almu1 = almu1 + 1;
      if (almu1 == 60) {
        almu1 = 0;
      }
      EEPROM.write(4, almu1);
      EEPROM.commit();
      delay(100);
    }
    if (al == 2) {
      almu2 = almu2 + 1;
      if (almu2 == 60) {
        almu2 = 0;
      }
      EEPROM.write(5, almu2);
      EEPROM.commit();
      delay(100);
    }
    if (al == 3) {
      almu3 = almu3 + 1;
      if (almu3 == 60) {
        almu3 = 0;
      }
      EEPROM.write(6, almu3);
      EEPROM.commit();
      delay(100);
    }
  }
  if (deg == 22) {
    if (te == 0) {
      ind2++;
      if (ind2 > 6)
        ind2 = 0;
    }
    if (te == 1) {
      if (dark == 1) {
        dark = 0;
      }
      else if (dark == 0) {
        dark = 1;
      }
      EEPROM.write(14, dark);
      EEPROM.commit();
      delay(100);
    }
    if (te == 2) {
      saat = saat + 1;
      if (saat == 3) {
        saat == 0;
      }
      EEPROM.write(11, saat);
      EEPROM.commit();
      delay(100);
    }
    if (te == 3) {
      if (stil == 0) {
        stil = 1;
      }
      else if (stil == 0) {
        stil = 1;
      }
      EEPROM.write(12, stil);
      EEPROM.commit();
      delay(100);
    }
    if (te == 7) {
      if (parlak != 250) {
        parlak = parlak + 10;
        display.setBrightness(parlak);
        EEPROM.write(20, parlak);
        EEPROM.commit();
        delay(100);
      }
    }
  }
}
void myDouble()
{
  if (deg == 7) {
    if (buttons[ind] == 'C')
    {
      int pres = 0;
      int stis1 = 0;
      int poc = 0;
      String line = "";
      String num1 = "";
      String num2 = "";
      int operacija = 0;
    } else {
      if (buttons[ind] == '=')
      {
        calculate();
      } else {
        line = line + buttons[ind];
      }
    }
    ind = 0;
  }
  if (deg == 8) {
    if (timer123 == 0) {
      timer123 = 1;
    }
  }
  if (deg == 19) {
    indled = indled + 1;
    if (indled == 3) {
      indled = 0;
    }
  }
  if (deg == 21) {
    if (al == 1) {
      if (alarm1 == 1) {
        alarm1 = 0;
      }
      else if (alarm1 == 0) {
        alarm1 = 1;
      }
      EEPROM.write(7, alarm1);
      EEPROM.commit();
      delay(100);
    }
    if (al == 2) {
      if (alarm2 == 1) {
        alarm2 = 0;
      }
      else if (alarm2 == 0) {
        alarm2 = 1;
      }
      EEPROM.write(8, alarm2);
      EEPROM.commit();
      delay(100);
    }
    if (al == 3) {
      if (alarm3 == 1) {
        alarm3 = 0;
      }
      else if (alarm3 == 0) {
        alarm3 = 1;
      }
      EEPROM.write(9, alarm3);
      EEPROM.commit();
      delay(100);
    }
    if (al == 4) {
      if (saatbas == 1) {
        saatbas = 0;
      }
      else if (saatbas == 0) {
        saatbas = 1;
      }
      EEPROM.write(10, saatbas);
      EEPROM.commit();
      delay(100);
    }
  }
  if (deg == 22) {
    if (te > 0) {
      te = 0;
      ind2 = 0;
    }
  }
}
void myDouble1()
{
  if (deg == 7) {
    calculate();
  }
  if (deg == 8) {
    if (timer123 == 0) {
      ind75 = ind75 + 1;
      if (ind75 == 3) {
        ind75 = 0;
      }
    }
    else if (timer123 == 1) {

    }
  }
  if (deg == 17) {
    if (melodi == true) {
      melodi = false;
    }
    else if (melodi == false) {
      melodi = true;
    }
  }
  if (deg == 19) {
    indled = indled + 1;
    if (indled == 3) {
      indled = 0;
    }
  }
}
void myClick1()
{
  if (deg == 6) {
    ind8 = ind8 + 1;
    if (ind8 == 6) {
      ind8 = 1;
    }
  }
  if (deg == 7) {
    ind = ind + 4;
    if (ind > 16)
      ind = 0;
  }
  if (deg == 8) {
    if (timer123 == 0) {
      if (krosa != 0) {
        if (ind75 == 0) {
          krosa = krosa - 1;
        }
      }
      if (krodk != 0) {
        if (ind75 == 1) {
          krodk = krodk - 1;
        }
      }
      if (krosn != 0) {
        if (ind75 == 2) {
          krosn = krosn - 1;
        }
      }
    }
    else if (timer123 == 1) {
      timer123 = 3;
    }
    else if (timer123 == 2) {
      timer123 = 0;
    }
    else if (timer123 == 3) {
      timer123 = 1;
    }
  }
  if (deg == 17) {
    ind5 = ind5 + 1;
    if (melodi == false) {
      if (ind5 == 9) {
        ind5 = 0;
      }
    }
    if (melodi == true) {
      if (ind5 == 6) {
        ind5 = 0;
      }
    }
  }
  if (deg == 19) {
    if (indled == 0) {
      digitalWrite(led, HIGH);
    }
    if (indled == 1) {
      digitalWrite(led1, HIGH);
    }
    if (indled == 2) {
      digitalWrite(led2, HIGH);
    }
  }
  if (deg == 21) {
    if (al == 0) {
      al = ind1 + 1;
    }
    if (al == 1) {
      alsa1 = alsa1 + 1;
      if (alsa1 == 24) {
        alsa1 = 0;
      }
      EEPROM.write(1, alsa1);
      EEPROM.commit();
      delay(100);
    }
    if (al == 2) {
      alsa2 = alsa2 + 1;
      if (alsa2 == 24) {
        alsa2 = 0;
      }
      EEPROM.write(2, alsa2);
      EEPROM.commit();
      delay(100);
    }
    if (al == 3) {
      alsa3 = alsa3 + 1;
      if (alsa3 == 24) {
        alsa3 = 0;
      }
      EEPROM.write(3, alsa3);
      EEPROM.commit();
      delay(100);
    }
  }
  if (deg == 22) {
    if (te == 0) {
      te = ind2 + 1;
    }
    if (te == 3) {
      stil = false;
    }
    if (te == 7) {
      if (parlak != 20) {
        parlak = parlak - 10;
        display.setBrightness(parlak);
        EEPROM.write(20, parlak);
        EEPROM.commit();
        delay(100);
      }
    }
  }
}
void calculate()
{
  int duz = line.length();
  for (int i = 0; i < duz; i++)
  {
    if (line.charAt(i) == '+') {
      changeNumber = 1;
      operacija = 1;
    }
    if (line.charAt(i) == '-') {
      changeNumber = 1;
      operacija = 2;
    }
    if (line.charAt(i) == '*') {
      changeNumber = 1;
      operacija = 3;
    }
    if (line.charAt(i) == '/') {
      changeNumber = 1;
      operacija = 4;
    }
    if (changeNumber == 0)
    {
      char slovo = line.charAt(i);
      num1 = num1 + slovo;
    }
    if (changeNumber == 2) {
      char slovo = line.charAt(i);
      num2 = num2 + slovo;
    }
    if (changeNumber == 1)
      changeNumber = 2;
  }
  n1 = num1.toFloat();
  n2 = num2.toFloat();

  if (operacija == 1) {
    res = n1 + n2;
  }
  if (operacija == 2) {
    res = n1 - n2;
  }
  if (operacija == 3) {
    res = n1 * n2;
  }
  if (operacija == 4) {
    res = n1 / n2;
  }
  Serial.println(n1); Serial.println(n2);
  Serial.println(n1 / n2);
  line = "";
  int tenths = res / 10;
  float remain = res - (tenths * 10);
  line = (String)res;
  changeNumber = 0;
  num1 = "";
  num2 = "";
  operacija = 0;
}
/////////////////////////Hesap Makinesi Bitti/////////////////////////
/////////////////////////uyku ve adım/////////////////////////
void stepp ()
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr, 14, true);
  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
  int xAng = map(accelX, minVal, maxVal, -90, 90);
  int yAng = map(accelY, minVal, maxVal, -90, 90);
  int zAng = map(accelZ, minVal, maxVal, -90, 90);

  k = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
  l = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
  n = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI);
  yeniZaman = millis();
  if (yeniZaman - eskiZaman > 500) {
    vector = sqrt( (k * k) + (l * l) + (n * n) );
    totalvector = vector - vectorprevious;
    if (totalvector > 10) {
      Steps++;
      /* EEPROM.write(25, Steps);
        EEPROM.commit();
        delay(25);*/
    }
    if (totalvector > 20) {
      uykugeres = uyku / 2;
      uykudkes = uykudk;
      uykusaates = uykusaat;
    }
    if (totalvector > 15) {
      uykugeres = uyku / 2;
      uykudkes = uykudk;
      uykusaates = uykusaat;
      EEPROM.write(26, uykudkes);
      EEPROM.commit();
      delay(100);
      EEPROM.write(27, uykusaates);
      EEPROM.commit();
      delay(100);
      sayac = 0;
      uyku = false;
      uyku = 0;
      uykudk = 0;
      uykusaat = 0;
      uykuger = 0;
    }
    if (totalvector < 7) {
      sayac = sayac + 1;
    }
    if (sayac == 1200) {
      uyku1 = true;
    }
    if (uyku1 == true) {
      uyku = uyku + 1;
      if (uyku == 120) {
        uykudk = uykudk + 1;
        uyku = 0;
      }
      if (uykudk == 60) {
        uykusaat = uykusaat + 1;
        uykudk = 0;
      }
    }
    sayac1 = sayac1 + 1;
    if (sayac1 == 120) {
      otoekran = true;
    }
    vectorprevious = vector;
    eskiZaman = yeniZaman;
  }
  ///Serial.println(Steps);
  //Serial.println(totalvector);
}
/////////////////////////uyku ve adım bitti/////////////////////////
/////////////////////////hava durumu /////////////////////////
void getWeatherData()                                //client function to send/receive GET request data.
{
  if (client.connect(servername, 80))
  {
    client.println("GET /data/2.5/weather?id=" + CityID + "&units=metric&APPID=" + APIKEY);
    client.println("Host: api.openweathermap.org");
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  }
  else {
    Serial.println("connection failed");        //error message if no client connect
    Serial.println();
  }
  while (client.connected() && !client.available())
    delay(1);                                          //waits for data
  while (client.connected() || client.available())
  { //connected or data available
    char c = client.read();                     //gets byte from ethernet buffer
    result = result + c;
  }
  client.stop();                                      //stop client
  result.replace('[', ' ');
  result.replace(']', ' ');
  Serial.println(result);
  char jsonArray [result.length() + 1];
  result.toCharArray(jsonArray, sizeof(jsonArray));
  jsonArray[result.length() + 1] = '\0';
  StaticJsonBuffer<1024> json_buf;
  JsonObject &root = json_buf.parseObject(jsonArray);

  if (!root.success())
  {
    Serial.println("parseObject() failed");
  }
  String location = root["name"];
  String country = root["sys"]["country"];
  float temperature = root["main"]["temp"];
  float humidity = root["main"]["humidity"];
  String weather = root["weather"]["main"];
  String description = root["weather"]["description"];
  float pressure = root["main"]["pressure"];
  float sunrise = root["sys"]["sunrise"];
  float sunset = root["sys"]["sunset"];
  float temp_min = root["main"]["temp_min"];
  float temp_max = root["main"]["temp_max"];
  float speed = root["wind"]["speed"];
  float visibility = root["visibility"];
  float wind_angle = root["wind"]["deg"];
  weatherDescription = description;
  weatherLocation = location;
  Country = country;
  Temperature = temperature;
  Humidity = humidity;
  Pressure = pressure;
  Sunrise = sunrise;
  Sunset = sunset;
  Speed = speed;
  Temp_min = temp_min;
  Temp_max = temp_max;
  Visibility = visibility;
  Wind_angle = wind_angle;
  delay(1000);
}
/////////////////////////hava durumu bitti/////////////////////////
