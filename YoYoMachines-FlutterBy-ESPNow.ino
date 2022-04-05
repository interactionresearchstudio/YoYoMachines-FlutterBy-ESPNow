#include <esp_now.h>
#include <esp_wifi.h>
#include <WiFi.h>

#define SENS_3 26
#define SENS_1 25

#define LED_BUILTIN 2
#define LED_BUILTIN_ON HIGH
int BUTTON_BUILTIN =  0;

#include <AceButton.h>
using namespace ace_button;

typedef struct command_struct {
  byte cmd;
  byte option;
  byte isIncreasing;
};

//PIR variables
int PIR_sensitivity;
#define PIR_PIN 14
#define FAN_PIN 13
#define FANRUNTIME 10000
int fan_on_time = 10;
long currFanRunTime;
bool isFanRunning = false;
long prevPirCheckMillis;
#define PIRCHECKINTERVAL 50
bool hasSentPIR = false;
#define PIRSENDINTERVAL 3000
long prevPirOnMillis = 0;

/// Led Settings ///
bool isBlinking = false;
bool readyToBlink = false;
unsigned long blinkTime;
int blinkDuration = 200;

//Button Settings
AceButton buttonBuiltIn(BUTTON_BUILTIN);

void handleButtonEvent(AceButton*, uint8_t, uint8_t);
int longButtonPressDelay = 5000;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  setupPins();
  fan_on_time = checkSensLength();

  initEspNow();
}

void loop() {
  pirHandler();
  fanHandler();
  ledHandler();
  buttonBuiltIn.check();
}
