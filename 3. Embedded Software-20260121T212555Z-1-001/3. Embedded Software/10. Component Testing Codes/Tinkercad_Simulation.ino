#include <Adafruit_NeoPixel.h>

#define PIN 8   // input pin Neopixel is attached to

#define NUMPIXELS 8 // number of neopixels in strip

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 100; // timing delay in milliseconds

int redColor = 0;
int greenColor = 0;
int blueColor = 0;
int intensity = 0;

void setup(){
    pixels.begin();
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(3, OUTPUT);
    Serial.begin(9600);
}


void loop(){
  //motor control
    //int vol = analogRead(A1);
    float intensity = 255*(255.0/1024.0);//vol
    analogWrite(18, intensity);

    Serial.println(intensity);
    //int vol2 = analogRead(A3);
    //float intensity2 = 255*(255.0/1024.0); //vol
    analogWrite(19, intensity2);
   
  //  Serial.println(intensity2);
       //Serial.println(intensity);
  
  // AIR PUMP CONTROLL BASED ON TIME
  
 // for (int i = 0; i < 256; i++) {
  //  analogWrite(3, i);
  //  analogWrite(3, i);
  //  delay(200);
      //  i+=10;
  //}
  
  
  //led control
  //  int voltage = analogRead(A0);
  //  float brightness = voltage * (255.0 / 1023.0);
   // pixels.setBrightness(brightness);
    //Serial.println(voltage);
   // for(int i= 0;i<= 7;i++)
   // {
   //   pixels.setPixelColor(i, pixels.Color(138, 43, 226));
   // }
  
      
      
      
    /*  
    pixels.setPixelColor(0, pixels.Color(138, 43, 226));
    pixels.setPixelColor(1, pixels.Color(138, 43, 226));
    pixels.setPixelColor(2, pixels.Color(138, 43, 226));
    pixels.setPixelColor(3, pixels.Color(138, 43, 226));
    pixels.setPixelColor(4, pixels.Color(165, 100, 75));
    pixels.setPixelColor(5, pixels.Color(138, 43, 226));
    pixels.setPixelColor(6, pixels.Color(255, 0, 0));
    pixels.setPixelColor(7, pixels.Color(255, 0, 0));
    */
    //pixels.show();



}
