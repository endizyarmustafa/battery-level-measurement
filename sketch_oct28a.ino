#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h> 

// Ekran pin tanımları
#define TFT_CS     10
#define TFT_DC     9
#define TFT_RST    8 

// Renk tanımları
#define ST7735_BLACK 0x0000
#define ST7735_WHITE 0xFFFF
#define ST7735_YELLOW 0xFFE0 

// Nesne oluşturma
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
Adafruit_INA219 ina219;

void setup() {
    Serial.begin(115200);  // Seri iletişimi başlat
    ina219.begin();        // INA219 sensörünü başlat
    tft.initR(INITR_BLACKTAB); // ST7735 ekranı başlat
    tft.fillScreen(ST7735_BLACK); // Ekranı siyah yap
    delay(500); // 0.5 saniye bekle
}

void loop() {
    float shuntVoltage = ina219.getShuntVoltage_mV(); // Şunt voltajını oku
    float busVoltage = ina219.getBusVoltage_V();       // Bus voltajını oku
    float current_mA = ina219.getCurrent_mA();         // Akımı oku
    float power_mW = busVoltage * current_mA; // Güç hesapla (mW)

    // Ekranı temizle
    tft.fillScreen(ST7735_BLACK);
    
    // Bus Voltage bilgisini ekrana yazdır
    tft.setCursor(0, 10);
    tft.setTextColor(ST7735_YELLOW);
    tft.setTextSize(1); // Yazı boyutunu ayarla
    tft.println("Bus Voltage:");
    tft.setCursor(0, 30);
    tft.setTextColor(ST7735_WHITE);
    tft.print(busVoltage, 2);
    tft.println(" V");
    
    // Shunt Voltage bilgisini ekrana yazdır
    tft.setCursor(0, 50);
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Shunt Voltage:");
    tft.setCursor(0, 70);
    tft.setTextColor(ST7735_WHITE);
    tft.print(shuntVoltage, 2);
    tft.println(" mV");
    
    // Current bilgisini ekrana yazdır
    tft.setCursor(0, 90);
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Current:");
    tft.setCursor(0, 110);
    tft.setTextColor(ST7735_WHITE);
    tft.print(current_mA, 2);
    tft.println(" mA");
    
    // Güç bilgisini ekrana yazdır
    tft.setCursor(0, 130);
    tft.setTextColor(ST7735_YELLOW);
    tft.println("Power:");
    tft.setCursor(0, 150);
    tft.setTextColor(ST7735_WHITE);
    tft.print(power_mW, 2);
    tft.println(" mW");

    delay(1000); // 1 saniye bekle
}
