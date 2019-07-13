
// BUSY -> GPIO4, RST -> GPIO2
// DC -> GPIO0, CS -> GPIO5
// CLK -> GPIO14, DIN -> GPIO13
// GND -> GND, 3.3V -> 3.3V
#define ENABLE_GxEPD2_GFX 0

#include <GxEPD2_BW.h>
#include <Fonts/FreeMonoBold9pt7b.h>

GxEPD2_BW<GxEPD2_154, GxEPD2_154::HEIGHT> display(GxEPD2_154(/*CS=*/ 5, /*DC=*/ 0, /*RST=*/ 2, /*BUSY=*/ 4));

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println("setup");
  delay(100);
  display.init(115200);
  helloWorld();
  delay(180000);
}

void loop() {
  Serial.println("loop ...");
  blackScreen();
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  digitalWrite(BUILTIN_LED, LOW);
  delay(180000);
  helloWorld();
  digitalWrite(BUILTIN_LED, HIGH);
  delay(1000);
  digitalWrite(BUILTIN_LED, LOW);
  delay(180000);
}

const char HelloWorld[] = "Hello!!";

void blackScreen() {
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_BLACK);
  }
  while (display.nextPage()); 
}

void helloWorld()
{
  Serial.println("helloWorld");
  display.setRotation(1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(GxEPD_BLACK);
  int16_t tbx, tby; uint16_t tbw, tbh;
  display.getTextBounds(HelloWorld, 0, 0, &tbx, &tby, &tbw, &tbh);
  uint16_t x = (display.width() - tbw) / 2;
  uint16_t y = (display.height() + tbh) / 2; // y is base line!
  display.setFullWindow();
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x, y);
    display.print(HelloWorld);
  }
  while (display.nextPage());
  Serial.println("helloWorld done");
}
