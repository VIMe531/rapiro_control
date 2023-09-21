/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "************"
#define BLYNK_TEMPLATE_NAME "************"
#define BLYNK_AUTH_TOKEN "************"

// include files
#include <M5Stack.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <AudioGeneratorWAV.h>
#include <AudioFileSourceSD.h>
#include <AudioOutputI2S.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "************";
char pass[] = "************";

AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2S *out;

// declare functions
void playWAV(char*);

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0){

  Serial2.print("#M0");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Stop");

}

BLYNK_WRITE(V1){

  Serial2.print("#M1");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Forward");

  playWAV("/voice/lets-take-a-walk.wav");
  M5.Lcd.println("Playing WAV done");

}

BLYNK_WRITE(V2){

  Serial2.print("#M2");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Backward");

}

BLYNK_WRITE(V3){

  Serial2.print("#M3");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Turn right");
  
  playWAV("/voice/yoisho.wav");
  M5.Lcd.println("Playing WAV done");

}

BLYNK_WRITE(V4){

  Serial2.print("#M4");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Turn Left");
  
  playWAV("/voice/yoisho.wav");
  M5.Lcd.println("Playing WAV done");

}

BLYNK_WRITE(V5){

  Serial2.print("#M5");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Wave hands");

  playWAV("/voice/thanks-for-watching.wav");
  M5.Lcd.println("Playing WAV done");

}

BLYNK_WRITE(V6){

  Serial2.print("#M6");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Wave right hand");
  
  playWAV("/voice/hello.wav");
  M5.Lcd.println("Playing WAV done");

}

BLYNK_WRITE(V7){

  Serial2.print("#M7");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Grip hands");

}

BLYNK_WRITE(V8){

  Serial2.print("#M8");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Wave left hand");

}

BLYNK_WRITE(V9){

  Serial2.print("#M9");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Strech right hand");

}

void playWAV(char* filename){

  file = new AudioFileSourceSD(filename);
  out = new AudioOutputI2S(0, 1);
  out->SetOutputModeMono(true);
  out->SetGain(1.0);
  wav = new AudioGeneratorWAV();
  
  wav->begin(file, out);
  while(wav->isRunning()){
    if(!wav->loop())  wav->stop();
  }

}

void setup(){
  
  M5.begin(); // serial baudrate is defined as 115200 bps
  Serial2.begin(57600);
  M5.Power.begin();
  M5.Lcd.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.fillScreen(BLACK);

  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    M5.Lcd.print(".");
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("Wifi Connected!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

}

void loop(){
  
  Blynk.run();

}