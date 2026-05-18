# happy-birthday-esp32

An interactive birthday-themed embedded electronics project built around an
ESP32. A small SPI TFT display shows animated "happy birthday" graphics and
pixel-style visuals, WS2812B RGB LEDs add sparkle effects, a passive piezo
buzzer plays the happy birthday melody, and a push button triggers the
animation and sound sequence.

The project is first prototyped on a breadboard, then converted into a
custom-designed PCB in EasyEDA — a themed carrier board for the ESP32 dev
board and connected modules with decorative silkscreen artwork.

## Features
- ESP32-based control system
- 1.8" SPI TFT color display (ST7735, 128 x 160)
- WS2812B addressable RGB LEDs
- Passive buzzer for melody playback
- Tactile push-button interaction
- Custom PCB layout and artwork
- USB powered

## Hardware

| Component       | ESP32 pin | Notes                              |
|-----------------|-----------|------------------------------------|
| TFT CS          | GPIO5     | SPI chip select                    |
| TFT DC          | GPIO16    | data/command                       |
| TFT RST         | GPIO17    |                                    |
| TFT SCK         | GPIO18    | hardware SPI clock                 |
| TFT MOSI        | GPIO23    | hardware SPI MOSI                  |
| TFT VCC         | 3V3       | 3.3V logic                         |
| TFT BLK / LED   | 3V3       | backlight                          |
| WS2812B DIN     | GPIO13    | 330 ohm series resistor optional   |
| WS2812B VCC     | VIN (5V)  | USB-derived 5V                     |
| Buzzer +        | GPIO25    | passive piezo                      |
| Button          | GPIO14    | to GND, INPUT_PULLUP               |

All grounds tied together.

## Build

PlatformIO:

```
pio run                 # build
pio run -t upload       # flash
pio device monitor      # open serial
```

## Project layout

```
src/             firmware source
include/         project-wide headers
lib/             local libraries
data/            files for SPIFFS / LittleFS (sprites, etc.)
docs/            wiring diagrams, PCB notes
```
