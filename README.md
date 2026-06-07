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

Notes:
- `upload_speed` is 460800 — this board's serial chip fails at 921600.
- The display is an ST7735 **BLACKTAB** variant (`-DST7735_BLACKTAB` in
  `platformio.ini`). If a different module shows shifted pixels or wrong
  colors, try `GREENTAB`, `GREENTAB2/3`, or `REDTAB` instead.
- The onboard BOOT button (GPIO0) triggers the sequence too, so no external
  button is needed for testing.

## Asset pipeline

Pixel art and fonts are converted to C headers at dev time (no filesystem
upload needed). Requires Python 3 with Pillow (`pip3 install pillow`).

Convert a PNG to an RGB565 image header (must match display size, 128x160):

```
python3 scripts/png_to_rgb565.py assets/cake-1.png include/cake_frame_1.h cake_frame_1
```

Convert a TTF to an Adafruit GFX font header (TFT_eSPI FreeFont, 1-bit,
no anti-aliasing — suited to pixel fonts):

```
python3 scripts/ttf_to_gfx.py assets/rainyhearts.ttf include/rainyhearts_font.h 16
```

After regenerating headers, rebuild and flash with `pio run -t upload`.

Images draw with `tft.pushImage(...)` — `tft.setSwapBytes(true)` is required
because the generated arrays are big-endian RGB565. Text draws over the image
with a transparent background (set only a foreground color).

## Project layout

```
src/             firmware source
include/         generated image/font headers + project headers
lib/             local libraries
assets/          source art (PNG) and fonts (TTF)
scripts/         asset conversion scripts (PNG -> RGB565, TTF -> GFX font)
data/            files for SPIFFS / LittleFS (sprites, etc.)
docs/            wiring diagrams, PCB notes
```
