#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid = "ESP_AP";
// APS name
const char *password = ""; 
// APS password

void setup() {
  // Connect with internal clock
  Wire.begin(12, 14); // SDA connected to D6 (GPIO 12), SCL connected to D5 (GPIO 14)
  // Change wiring to liking

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with the I2C address 0x3C

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Setting up ESP8266 as accespoint
  WiFi.softAP(ssid, password);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Scanning...");
  display.display();
}

void loop() {
  int realAPs = WiFi.scanNetworks();
  int fakeAPs = 5; // Assuming 5 fake APs are created
  int connectedDevices = WiFi.softAPgetStationNum();

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Real APs: ");
  display.setCursor(0, 10);
  display.println(realAPs);

  display.setCursor(0, 20);
  display.println("Fake APs: ");
  display.setCursor(0, 30);
  display.println(fakeAPs);

  display.setCursor(0, 40);
  display.println("Connected: ");
  display.setCursor(0, 50);
  display.println(connectedDevices);

  // Spinning ball animation
  static const char symbols[] = {'|', '||', '||||', '||||'};
  static int symbol = 0;
  display.setCursor(110, 0);
  display.print(symbols[symbol]);
  symbol = (symbol + 1) & 0x03;

  display.display();

  delay(5000); // Deep Refresh timer
}
