#include <LedControl.h>             // Library for LED control with MAX72XX
#include <Bounce2.h>                // Library for Bounce of switches
LedControl lc = LedControl(7, 8, 9, 1);  // LedControl(int dataPin, int clkPin, int csPin, int numDevices)

int k, lastTime, diffTime;
int milhar, centena, dezena, unidade;
int milhar1, centena1, dezena1, unidade1;

int pinStartStop = 4;          // Start-Stop Pin
int pinLap = 3;                // Lap Time Pin

bool statusSwitch1 = false;

Bounce SW1 = Bounce();         // Define Bounce to read StartStop switch
Bounce SW2 = Bounce();         // Define Bounce to read Lap switch


void setup() {

  pinMode (pinStartStop, INPUT_PULLUP);
  pinMode (pinLap, INPUT_PULLUP);

  // After setting up the button, setup the Bounce instance
  SW1.attach(pinStartStop);   // Sets the pin (Internal Pull-Up)and matches the internal state to that of the pin
  SW1.interval(3);            // Sets the debounce time in milliseconds
  SW2.attach(pinLap);
  SW2.interval(3);

  lc.shutdown(0, false);      // The MAX72XX is in power-saving mode on startup, we have to do a wakeup call
  lc.setIntensity(0, 5);      // Set the brightness of display between 0 and 15
  lc.clearDisplay(0);         // Clear the display

  lc.setDigit(0, 7, 0, false);
  lc.setDigit(0, 6, 0, false);
  lc.setDigit(0, 5, 0, true);
  lc.setDigit(0, 4, 0, false);

  lc.setDigit(0, 3, 0, false);
  lc.setDigit(0, 2, 0, false);
  lc.setDigit(0, 1, 0, true);
  lc.setDigit(0, 0, 0, false);

}


void loop() {

  lastTime = 0;
  diffTime = 0;

  for (k = 0; k <= 9999; k++) {


    SW1.update();

    if (SW1.fell()) {
      statusSwitch1 = !statusSwitch1;
    }

    if (statusSwitch1 == true) {

      milhar = k / 1000;
      centena = (k - milhar * 1000) / 100;
      dezena = (k - milhar * 1000 - centena * 100) / 10;
      unidade = k % 10;

      lc.setDigit(0, 7, milhar, false);
      lc.setDigit(0, 6, centena, false);
      lc.setDigit(0, 5, dezena, true);
      lc.setDigit(0, 4, unidade, false);
    }
    else {
      k = k - 1;
    }


    SW2.update();

    if (SW2.fell()) {

      diffTime = k - lastTime;
      lastTime = k;

      milhar1 = diffTime / 1000;
      centena1 = (diffTime - milhar1 * 1000) / 100;
      dezena1 = (diffTime - milhar1 * 1000 - centena1 * 100) / 10;
      unidade1 = diffTime % 10;

      lc.setDigit(0, 3, milhar1, false);
      lc.setDigit(0, 2, centena1, false);
      lc.setDigit(0, 1, dezena1, true);
      lc.setDigit(0, 0, unidade1, false);

    }

    delay(99);

  }

}
