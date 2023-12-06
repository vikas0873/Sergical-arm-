#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASSWORD"
#define API_KEY "APIkey"
#define DATABASE_URL "URL"

Adafruit_PWMServoDriver myServo = Adafruit_PWMServoDriver();

#define SERVOMIN 0
#define SERVOMAX 400

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;

uint8_t servonum0 = 0;
uint8_t servonum1 = 1;
uint8_t servonum2 = 2;
uint8_t servonum3 = 3;
uint8_t servonum4 = 4;

//uint8_t numberOfServos = 6;
String t;

int h=0;
int j=0;
void setup() {
  Serial.begin(115200);
  myServo.begin();
  myServo.setPWMFreq(60);
  delay(10);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Firebase.begin(DATABASE_URL, API_KEY);
  Firebase.setDoubleDigits(5);
}


void seperatedata()
{
String a[100];
for(int i=0; i < t.length();i++)
{
if(t[i] != ' ')
   a[h].concat(t[i]);
else
   h++;
   
}
int s1=a[0].toInt();
int s2=a[1].toInt();
int s3=a[2].toInt();
int s4=a[3].toInt();
while(j <= h){
Serial.println(a[j]);
Serial.println(" ");
j++;
}
    myServo.setPWM(servonum0, 0, s1);
    myServo.setPWM(servonum1, 0, s2);
    myServo.setPWM(servonum2, 0, s3);
    myServo.setPWM(servonum3, 0, s4);
}

void loop() {
j=0;
h=0;
if(Firebase.ready())
    {
    Firebase.getString(fbdo,"/test/int");
t=fbdo.stringData();
    }
Serial.println(" ");
seperatedata();
  
//  for (uint16_t pulselen = SERVOMIN; pulselen < SERVOMAX; pulselen++){
//    myServo.setPWM(servonum0, 0, pulselen);
//    myServo.setPWM(servonum1, 0, pulselen);
//    myServo.setPWM(servonum2, 0, pulselen);
//   
//  }
//  delay(500);
//  for (uint16_t pulselen = SERVOMAX; pulselen > SERVOMIN; pulselen--){
//    myServo.setPWM(servonum0, 0, pulselen);
//    myServo.setPWM(servonum1, 0, pulselen);
//    myServo.setPWM(servonum2, 0, pulselen);
//    
//  }
}
