void setupButtons() {
  pinMode(CATEGORY_BUTTON_PIN, INPUT_PULLUP);
  resetButtons();
  pinMode(WPS_LED_PIN, OUTPUT);
}

void resetButtons() {
  storageCategory = 0;
  cookedCategory = 2;
  foodCategory = 4;
  //////Serial.println("RESETTING BUTTONS");
  analogWrite(RR, 0xd5);
  analogWrite(GG, 0xb6);
  analogWrite(BB, 0x4d);
  analogWrite(R, 0x3e);
  analogWrite(G, 0xb4);
  analogWrite(B, 0xaf);
  analogWrite(RRR, 0x3e);
  analogWrite(GGG, 0xb4);
  analogWrite(BBB, 0xaf);
}

void checkButtons() {
  short buttonPress = analogRead(CATEGORY_BUTTON_PIN);
  if (buttonPress < 42) {
    foodCategory = 4;
    analogWrite(RRR, 0x3e);
    analogWrite(GGG, 0xb4);
    analogWrite(BBB, 0xaf);
    //////Serial.println("Other");
  }
  else if (buttonPress < 95) {
    foodCategory = 3;
    analogWrite(RRR, 0xf2);
    analogWrite(GGG, 0x1d);
    analogWrite(BBB, 0xff);
    //////Serial.println("Dairy S");
  }
  else if (buttonPress < 144) {
    foodCategory = 2;
    analogWrite(RRR, 0xff);
    analogWrite(GGG, 0x44);
    analogWrite(BBB, 0x33);
    ////Serial.println("Dairy L");
  }
  else if (buttonPress < 188) {
    foodCategory = 1;
    analogWrite(RRR, 0x6d);
    analogWrite(GGG, 0xff);
    analogWrite(BBB, 0x6f);
    ////Serial.println("Meat");
  }
  else if (buttonPress < 226) {
    foodCategory = 0;
    analogWrite(RRR, 0xff);
    analogWrite(GGG, 0xdd);
    analogWrite(BBB, 0x12);
    ////Serial.println("Produce");
  }
  else if (buttonPress < 262) {
    storageCategory = 0;
    analogWrite(R, 0x3e);
    analogWrite(G, 0xb4);
    analogWrite(B, 0xaf);
    ////Serial.println("Fridge");
  }
  else if (buttonPress < 295) {
    storageCategory = 1;
    analogWrite(R, 0x92);
    analogWrite(G, 0x6d);
    analogWrite(B, 0xaf);
    ////Serial.println("Freezer");
  }
  else if (buttonPress < 320) {
    cookedCategory = 0;
    analogWrite(RR, 0xee);
    analogWrite(GG, 0x88);
    analogWrite(BB, 0x73);
    ////Serial.println("Raw");
  }
  else if (buttonPress < 350) {
    cookedCategory = 1;
    analogWrite(RR, 0x6d);
    analogWrite(GG, 0xc1);
    analogWrite(BB, 0x6f);
    ////Serial.println("Cooked");
  }
  else if (buttonPress < 375) {
    cookedCategory = 2;

    analogWrite(RR, 0xd5);
    analogWrite(GG, 0xb6);
    analogWrite(BB, 0x4d);
    ////Serial.println("Misc");
  }


  ///////////////////////////////////////////////////////
  //  WPS CHECK

  ms = millis();               //record the current time
  myWPSButton.read();                //Read the button

  switch (STATE) {

    //This state watches for short and long presses, switches the LED for
    //short presses, and moves to the TO_BLINK state for long presses.
    case ONOFF:
      if (myWPSButton.wasReleased()) {
        switchLED();
        scannerState = !scannerState;
      }
      else if (myWPSButton.pressedFor(LONG_PRESS))
        STATE = TO_BLINK;
      else if (ledState == true) {
        if (ms - myWPSButton.lastChange() > 10000) {
          digitalWrite(WPS_LED_PIN, LOW);
          ledState = false;
          scannerState = ADD;
        }
        else if (scannerState == ADD) {
          digitalWrite(WPS_LED_PIN, LOW);
          ledState = false;
        }
      }
      break;

    case TO_BLINK:
      if (myWPSButton.wasReleased())
        STATE = BLINK;
      else
        fastBlink();
      break;

    case BLINK:
      if (myWPSButton.pressedFor(LONG_PRESS)) {
        STATE = TO_ONOFF;
        digitalWrite(WPS_LED_PIN, LOW);
        ledState = false;
      }
      else
        fastBlink();
      break;

    case TO_ONOFF:
      if (myWPSButton.wasReleased())
        STATE = ONOFF;
      break;
  }
  /////////////////////////////////////////////
  btnUP.read();                             //read the buttons
  btnDN.read();

  if (page != lastPage) {                 //print the count if it has changed
    constr();
    lastPage = page;
    ////Serial.print("BUTTON INPUT DETECTED! NEW PAGE VALUE: "); ////Serial.println(page, DEC);
  }

  switch (DISPLAY_STATE) {

    case WAIT:                                //wait for a button event
      if (btnUP.wasPressed())
        DISPLAY_STATE = INCR;
      else if (btnDN.wasPressed())
        DISPLAY_STATE = DECR;
      else if (btnUP.wasReleased())         //reset the long press interval
        rpt = REPEAT_FIRST;
      else if (btnDN.wasReleased())
        rpt = REPEAT_FIRST;
      else if (btnUP.pressedFor(rpt)) {     //check for long press
        rpt += REPEAT_INCR;               //increment the long press interval
        DISPLAY_STATE = INCR;
      }
      else if (btnDN.pressedFor(rpt)) {
        rpt += REPEAT_INCR;
        DISPLAY_STATE = DECR;
      }
      break;

    case DECR:                                //increment the counter
      page = min(page++, (int)((activeTags + (10 - 1)) / 10) - 1); //but not more than the specified maximum
      DISPLAY_STATE = WAIT;
      break;

    case INCR:                                //decrement the counter
      page = max(page--, MIN_COUNT);      //but not less than the specified minimum
      DISPLAY_STATE = WAIT;
      break;
  }
}

void switchLED()
{
  msLast = ms;                 //record the last switch time
  ledState = !ledState;
  digitalWrite(WPS_LED_PIN, ledState);
}

void fastBlink()
{
  if (ms - myWPSButton.lastChange() > 60000) {
    digitalWrite(WPS_LED_PIN, LOW);
    ledState = false;
    STATE = ONOFF;
  }
  else if (ms - msLast >= BLINK_INTERVAL)
    switchLED();
}


