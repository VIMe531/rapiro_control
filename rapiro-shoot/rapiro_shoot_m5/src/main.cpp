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
#include <ESP32Servo.h>

#define OUTPUT_GAIN 80

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "************";
char pass[] = "************";

// BlynkTimer timer;
AudioGeneratorWAV *wav;
AudioFileSourceSD *file;
AudioOutputI2S *out;

// servo instance
Servo servo;

// wavファイルを再生する関数
void playWAV(char*);

// PWM Configuration
int PWM_PIN = 2;
int minUs = 500;  // 0
int maxUs = 2400; // 180

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // 停止
  Serial2.print("#M0");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Stop");
}

BLYNK_WRITE(V1)
{
  // 前進
  Serial2.print("#M1");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Forward");

  playWAV("/voice/lets-take-a-walk.wav");
  M5.Lcd.println("Playing WAV done");
}

BLYNK_WRITE(V2)
{
  // 後退
  Serial2.print("#M2");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Backward");
}


BLYNK_WRITE(V3)
{
  // 右旋回
  Serial2.print("#M3");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Turn Right");
  
  playWAV("/voice/yoisho.wav");
  M5.Lcd.println("Playing WAV done");
}

BLYNK_WRITE(V4)
{
  // 左旋回
  Serial2.print("#M4");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Turn Left");
  
  playWAV("/voice/yoisho.wav");
  M5.Lcd.println("Playing WAV done");
}

BLYNK_WRITE(V5)
{
  // 銃を構える
  Serial2.print("#M5");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Hold a gun");

  playWAV("/voice/thanks-for-watching.wav");
  M5.Lcd.println("Playing WAV done");
}

BLYNK_WRITE(V6)
{
  // 銃を下ろす
  Serial2.print("#M6");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.println("Put down a gun");

  playWAV("/voice/thanks-for-watching.wav");
  M5.Lcd.println("Playing WAV done");
}

BLYNK_WRITE(V7)
{
  //銃を右に
  Serial2.print("#M7");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);

  playWAV("/voice/hello.wav");
  M5.Lcd.println("Wave left hand");
}

BLYNK_WRITE(V8)
{
  // 銃を左に
  Serial2.print("#M8");
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);

  playWAV("/voice/hello.wav");
  M5.Lcd.println("Strech right hand");
}

BLYNK_WRITE(V9)
{
  // 射撃
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(2,10);

  playWAV("/voice/hello.wav");
  M5.Lcd.println("Playing wav done");
  delay(1000);

  servo.write(90);
  delay(10);
  M5.Lcd.println("Shooting done");
  delay(1000);
  servo.write(0);
  delay(10);
}

/*
// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
}
*/

void playWAV(char* filename){
  file = new AudioFileSourceSD(filename);
  out = new AudioOutputI2S(0, 1); // Output to builtInDAC
  out->SetOutputModeMono(true);
  out->SetGain(1.0);
  wav = new AudioGeneratorWAV();
  wav->begin(file, out);
  while(wav->isRunning()) {
    if (!wav->loop()) wav->stop();
   }
}

void setup()
{
  M5.begin(); // serial baudrate is defined as 115200 bps
  Serial2.begin(57600);
  M5.Power.begin();
  
  M5.Lcd.begin();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(2,10);
  M5.Lcd.fillScreen(BLACK);

  servo.setPeriodHertz(50);
  servo.attach(PWM_PIN,minUs,maxUs);

  WiFi.begin(ssid,pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    M5.Lcd.print(".");
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("Wifi Connected!");

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
//  timer.setInterval(1000L, myTimerEvent);

}

void loop()
{
  Blynk.run();
//  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}