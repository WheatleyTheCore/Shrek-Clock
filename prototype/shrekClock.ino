#include <NTPClient.h>
// change next line to use with another board/shield
#include <WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid     = "C4";
const char *password = "g0jxh061kf";

WiFiUDP ntpUDP;

// By default 'pool.ntp.org' is used with 60 seconds update interval and
// no offset
NTPClient timeClient(ntpUDP, "time.google.com", -(4 * 3600));

// You can specify the time server pool and the offset, (in seconds)
// additionally you can specify the update interval (in milliseconds).
// NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", 3600, 60000);

float timeToShreks(int hours, int minutes, int seconds);

void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();

  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  timeClient.update();

  String timeInShreks = String(timeToShreks(timeClient.getHours(), timeClient.getMinutes(), timeClient.getSeconds()));
  display.clearDisplay();

  display.setTextSize(3);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(20, 10);

  display.println(timeInShreks);
  display.display();

  Serial.println(timeInShreks);

  delay(1000);
}

float timeToShreks(int hours, int minutes, int seconds) {
  /*
  The shrek movie is 95 minutes. We are going to use this as our unit of time.
  Every 95 minute period will be 1 shrek.
  There are 15.158 shreks per day.
  */

  //first, we convert our time to only minutes
  float timeInMins = (hours * 60) + minutes + (seconds/60);

  //now we scale that to the time of the first shrek movie 
  float timeInShreks = timeInMins / 95;

  return timeInShreks;
}
