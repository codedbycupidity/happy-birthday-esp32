#include <Arduino.h>
#include <TFT_eSPI.h>
#include <FastLED.h>

constexpr uint8_t PIN_BUTTON = 14;
constexpr uint8_t PIN_BUZZER = 25;
constexpr uint8_t PIN_LED_DATA = 13;

constexpr uint8_t NUM_LEDS = 8;
CRGB leds[NUM_LEDS];

TFT_eSPI tft = TFT_eSPI();

struct Note { uint16_t freq; uint16_t ms; };
const Note melody[] = {
    {294, 250}, {294, 250}, {330, 500}, {294, 500}, {392, 500}, {370, 1000},
    {294, 250}, {294, 250}, {330, 500}, {294, 500}, {440, 500}, {392, 1000},
    {294, 250}, {294, 250}, {587, 500}, {494, 500}, {392, 500}, {370, 500}, {330, 1000},
    {523, 250}, {523, 250}, {494, 500}, {392, 500}, {440, 500}, {392, 1000},
};
constexpr size_t MELODY_LEN = sizeof(melody) / sizeof(melody[0]);

void playMelody() {
    for (size_t i = 0; i < MELODY_LEN; i++) {
        if (melody[i].freq > 0) {
            tone(PIN_BUZZER, melody[i].freq, melody[i].ms);
        }
        delay(melody[i].ms);
        noTone(PIN_BUZZER);
        delay(30);
    }
}

void sparkle() {
    for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CHSV(random8(), 200, 255);
    }
    FastLED.show();
}

void showTitle() {
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_PINK, TFT_BLACK);
    tft.setTextDatum(MC_DATUM);
    tft.drawString("Happy", 64, 60, 4);
    tft.drawString("Birthday!", 64, 100, 4);
}

void setup() {
    Serial.begin(115200);

    pinMode(PIN_BUTTON, INPUT_PULLUP);
    pinMode(PIN_BUZZER, OUTPUT);

    FastLED.addLeds<WS2812B, PIN_LED_DATA, GRB>(leds, NUM_LEDS);
    FastLED.setBrightness(60);
    FastLED.clear(true);

    tft.init();
    tft.setRotation(0);
    showTitle();
}

void loop() {
    static bool lastButton = HIGH;
    bool now = digitalRead(PIN_BUTTON);

    if (lastButton == HIGH && now == LOW) {
        delay(20);
        showTitle();
        for (int i = 0; i < 5; i++) { sparkle(); delay(120); }
        playMelody();
        FastLED.clear(true);
    }
    lastButton = now;
}
