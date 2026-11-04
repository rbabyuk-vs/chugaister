#include <FastLED.h>

#define LED_PIN 18
#define NUM_LEDS 25
#define WIDTH 5
#define HEIGHT 5

CRGB leds[NUM_LEDS];

// Adjust if your matrix wiring is serpentine differently.
uint16_t XY(uint8_t x, uint8_t y) {
  if (y % 2 == 0) {
    return y * WIDTH + x;
  } else {
    return y * WIDTH + (WIDTH - 1 - x);
  }
}

void clearLeds() {
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  FastLED.show();
}

void showColor(CRGB color, uint8_t brightness = 60) {
  FastLED.setBrightness(brightness);
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
}

// 1. BOOT — pixels light one by one
void bootAnimation() {
  clearLeds();
  FastLED.setBrightness(50);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::White;
    FastLED.show();
    delay(45);
  }

  delay(300);

  for (int b = 50; b >= 0; b -= 2) {
    FastLED.setBrightness(b);
    FastLED.show();
    delay(20);
  }

  clearLeds();
}

// 2. SAFE — slow white breathing
void safeBreathing(uint32_t durationMs) {
  uint32_t start = millis();

  while (millis() - start < durationMs) {
    float phase = (millis() % 3000) / 3000.0;
    float wave = (sin(phase * TWO_PI - HALF_PI) + 1.0) / 2.0;

    uint8_t brightness = 12 + wave * 55;

    FastLED.setBrightness(brightness);
    fill_solid(leds, NUM_LEDS, CRGB::White);
    FastLED.show();

    delay(20);
  }
}

// 3. WARNING — amber sweep across the matrix
void warningSweep(uint8_t cycles) {
  FastLED.setBrightness(70);

  for (uint8_t c = 0; c < cycles; c++) {
    for (uint8_t x = 0; x < WIDTH; x++) {
      fill_solid(leds, NUM_LEDS, CRGB(20, 5, 0));

      for (uint8_t y = 0; y < HEIGHT; y++) {
        leds[XY(x, y)] = CRGB(255, 100, 0);
      }

      FastLED.show();
      delay(120);
    }

    for (int x = WIDTH - 2; x > 0; x--) {
      fill_solid(leds, NUM_LEDS, CRGB(20, 5, 0));

      for (uint8_t y = 0; y < HEIGHT; y++) {
        leds[XY(x, y)] = CRGB(255, 100, 0);
      }

      FastLED.show();
      delay(120);
    }
  }

  showColor(CRGB(255, 80, 0), 35);
  delay(700);
}

// 4. ALERT — heartbeat-like red flash
void alertHeartbeat(uint8_t beats) {
  for (uint8_t i = 0; i < beats; i++) {
    showColor(CRGB::Red, 100);
    delay(120);

    showColor(CRGB::Red, 20);
    delay(120);

    showColor(CRGB::Red, 100);
    delay(180);

    showColor(CRGB::Red, 15);
    delay(700);
  }

  showColor(CRGB::Red, 45);
  delay(700);
}

// 5. OFFLINE — blue pixel searches around the perimeter
void offlineSearch(uint8_t loops) {
  const uint8_t path[][2] = {{0, 0}, {1, 0}, {2, 0}, {3, 0}, {4, 0}, {4, 1},
                             {4, 2}, {4, 3}, {4, 4}, {3, 4}, {2, 4}, {1, 4},
                             {0, 4}, {0, 3}, {0, 2}, {0, 1}};

  const uint8_t pathLength = sizeof(path) / sizeof(path[0]);

  FastLED.setBrightness(80);

  for (uint8_t loop = 0; loop < loops; loop++) {
    for (uint8_t i = 0; i < pathLength; i++) {
      fill_solid(leds, NUM_LEDS, CRGB(0, 0, 8));

      uint8_t x = path[i][0];
      uint8_t y = path[i][1];

      leds[XY(x, y)] = CRGB(0, 80, 255);

      FastLED.show();
      delay(90);
    }
  }

  showColor(CRGB(0, 30, 100), 30);
  delay(700);
}

// 6. BLUE/YELLOW wave
void ukrainianWave(uint8_t cycles) {
  FastLED.setBrightness(60);

  for (uint8_t c = 0; c < cycles; c++) {
    for (uint8_t offset = 0; offset < WIDTH + HEIGHT; offset++) {
      for (uint8_t y = 0; y < HEIGHT; y++) {
        for (uint8_t x = 0; x < WIDTH; x++) {

          uint8_t diagonal = (x + y + offset) % 6;

          if (diagonal < 3) {
            leds[XY(x, y)] = CRGB(0, 70, 255);
          } else {
            leds[XY(x, y)] = CRGB(255, 180, 0);
          }
        }
      }

      FastLED.show();
      delay(120);
    }
  }
}

// 7. Center-out pulse
void centerPulse(CRGB color, uint8_t cycles) {
  const uint8_t cx = 2;
  const uint8_t cy = 2;

  FastLED.setBrightness(70);

  for (uint8_t c = 0; c < cycles; c++) {
    for (uint8_t radius = 0; radius <= 4; radius++) {
      fill_solid(leds, NUM_LEDS, CRGB::Black);

      for (uint8_t y = 0; y < HEIGHT; y++) {
        for (uint8_t x = 0; x < WIDTH; x++) {
          uint8_t distance = abs((int)x - cx) + abs((int)y - cy);

          if (distance == radius) {
            leds[XY(x, y)] = color;
          }
        }
      }

      FastLED.show();
      delay(140);
    }
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("CHUGAISTER LED DEMO");

  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(50);

  clearLeds();
}

void loop() {
  Serial.println("BOOT");
  bootAnimation();

  Serial.println("SAFE");
  safeBreathing(5000);

  Serial.println("WARNING");
  warningSweep(3);

  Serial.println("ALERT");
  alertHeartbeat(5);

  Serial.println("OFFLINE");
  offlineSearch(3);

  Serial.println("UKRAINIAN MODE");
  ukrainianWave(3);

  Serial.println("CENTER PULSE");
  centerPulse(CRGB::White, 3);

  clearLeds();
  delay(1000);
}