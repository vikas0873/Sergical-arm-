#include <WiFi.h>
#include <FirebaseESP32.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#define WIFI_SSID "SSID"
#define WIFI_PASSWORD "PASS"
#define API_KEY "API"
#define DATABASE_URL "URL"

#define pot1  35
#define pot2  34
#define pot3  32
#define pot4  33


FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;


void setup() {
  // initialize serial communication at 115200 bits per second:
  Serial.begin(115200);


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

void loop() {

  int analogValue3 =analogRead(pot1);
  int analogValue2 =analogRead(pot2);
  int analogValue1 =analogRead(pot3);
  int analogValue4 =analogRead(pot4);
  
  String data1= String(map(analogValue1,0,4096,100,600)) + " " + String(map(analogValue2,0,4096,100,600))+ " " + String(map(analogValue3,0,4096,100,600))+ " " + String(map(analogValue4,0,4096,100,600));


  if (Firebase.ready()){
    sendDataPrevMillis = millis();
 Firebase.setString(fbdo,"/test/int",data1);
 Serial.println(data1);  // delay in between reads for clear read from serial
}}
