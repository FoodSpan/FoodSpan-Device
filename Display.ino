void initializeGraphics()   {
  //Serial.println("initialization done.");
  //Serial.println("RA8875 start");
  tft.begin(RA8875_800x480);
  if (!tft.begin(RA8875_800x480)) {
    //Serial.println("RA8875 Not Found!");
    while (1);
  }
  //Serial.println("Found RA8875");
  tft.displayOn(true);
  tft.GPIOX(true);      // Enable TFT - display enable tied to GPIOX
  tft.graphicsMode();
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024); // PWM output for backlight
  tft.PWM1out(255);
  tft.graphicsMode();

  tft.drawBitmap(160, 0, foodspan, 480, 480, RA8875_GREEN);
  delay(1000);
  tft.fillScreen(RA8875_WHITE);
  updateGraphics();
}
void createText(int txt, int xcor, int ycor) {
  //Serial.println("createText function is working : ");
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(0);
  if (tagTable[txt].storageCategory == 0) {
    //Serial.print("Fridge, ");
    char string2[8] = "Fridge";
    tft.textSetCursor(xcor + 15, ycor + 132);
    tft.textWrite(string2);
  } else if (tagTable[txt].storageCategory == 1) {
    //Serial.print("Freezer ");
    char string2[8] = "Freezer";
    tft.textSetCursor(xcor + 15, ycor + 132);
    tft.textWrite(string2);
  }
  if (tagTable[txt].cookedCategory == 0) {
    //Serial.print("Raw, ");
    char string2[8] = "Raw";
    tft.textSetCursor(xcor + 15, ycor + 152);
    tft.textWrite(string2);
  } else if (tagTable[txt].cookedCategory == 1) {
    //Serial.print("Cooked, ");
    char string2[8] = "Cooked";
    tft.textSetCursor(xcor + 15, ycor + 152);
    tft.textWrite(string2);
  } else if (tagTable[txt].cookedCategory == 2) {
    //Serial.print("Misc, ");
    char string2[8] = "Misc";
    tft.textSetCursor(xcor + 15, ycor + 152);
    tft.textWrite(string2);
  }
  if (tagTable[txt].foodCategory == 0) {
    Serial.print("Produce, ");
    char string2[8] = "Produce";
    tft.textSetCursor(xcor + 15, ycor + 172);
    tft.textWrite(string2);
  } else if (tagTable[txt].foodCategory == 1) {
    Serial.print("Meat, ");
    char string2[8] = "Meat";
    tft.textSetCursor(xcor + 15, ycor + 172);
    tft.textWrite(string2);
  } else if (tagTable[txt].foodCategory == 2) {
    Serial.print("Dairy L, ");
    char string2[8] = "Dairy L";
    tft.textSetCursor(xcor + 15, ycor + 172);
    tft.textWrite(string2);
  } else if (tagTable[txt].foodCategory == 3) {
    Serial.print("Dairy S, ");
    char string2[8] = "Dairy S";
    tft.textSetCursor(xcor + 15, ycor + 172);
    tft.textWrite(string2);
  } else if (tagTable[txt].foodCategory == 4) {
    Serial.print("Other, ");
    char string2[8] = "Other";
    tft.textSetCursor(xcor + 15, ycor + 172);
    tft.textWrite(string2);
  }
  char string100[20];
  snprintf(string100, sizeof(string100), "%d days", (tagTable[txt].scanTime) );
  
  tft.textSetCursor(xcor + 15, ycor + 192);
  tft.textWrite(string100);

  Serial.println("");
  return;
}
void make(int x, int y)
{
  tft.fillScreen(RA8875_WHITE);
  int arrayA = 0;
  int colourA = 0;
  int alpha = -1;

  for (int i = 0; i <= 214; i += 213) {
    for (int j = 0; j < 613; j += 153) {
      alpha += 1;
      if (element_arr[alpha] != -1) {

        Serial.print("element_arr[alpha]: ");
        Serial.println(element_arr[alpha]);
        Serial.print("Patterns : ");
        arrayA = ((element_arr[alpha] - 1) / 10);
        Serial.println(arrayA);
        colourA = (element_arr[alpha]) % 10 == 0 ? 9 : (element_arr[alpha]) % 10 - 1;
        Serial.print("ColourA is : ");
        Serial.println(colourA);

        if (arrayA == 0) {
          tft.drawBitmap(x + j, y + i, array[0], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 1) {
          tft.drawBitmap(x + j, y + i, array[1], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 2) {
          tft.drawBitmap(x + j, y + i, array[2], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 3) {
          tft.drawBitmap(x + j, y + i, array[3], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 4) {
          tft.drawBitmap(x + j, y + i, array[4], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 5) {
          tft.drawBitmap(x + j, y + i, array[5], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 6) {
          tft.drawBitmap(x + j, y + i, array[6], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 7) {
          tft.drawBitmap(x + j, y + i, array[7], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 8) {
          tft.drawBitmap(x + j, y + i, array[8], 120, 120, pgm_read_word( &colour[colourA] ));
        } else if (arrayA == 9) {
          tft.drawBitmap(x + j, y + i, array[9], 120, 120, pgm_read_word( &colour[colourA] ));
        }
        tft.textMode();
        if (element_arr[alpha] < 10) {
          tft.textSetCursor(x + j + 49, y + i + 45);
        } else {
          tft.textSetCursor(x + j + 25, y + i + 45);
        }
        char string[5];
        snprintf(string, sizeof(string), "%d", tagTable[element_arr[alpha]].patternID);
        tft.textTransparent(RA8875_WHITE);
        tft.textEnlarge(2);
        tft.textWrite(string);
        createText(element_arr[alpha], x + j, y + i);
        tft.graphicsMode();
      }
    }
  }
  tft.textMode();
  tft.textSetCursor(665, 440);
  tft.textTransparent(RA8875_BLACK);
  tft.textEnlarge(1);
  char string5[9] = "Page 1/1";
  tft.textWrite(string5);
//  tft.textSetCursor(770, 440);
//  char string1[7];
//  snprintf(string1, sizeof(string1), "%d", (page + 1));
//  tft.textWrite(string1);
  tft.graphicsMode();
  Serial.println("DONE");
}


void constr() {

  Serial.println("Constructor initialized\n\n\n ///////////////// ");
  activeTags = countActive();

  for (int i = 0, j = 0;  i < 10; a++) {
    if (a >= 100) {
      element_arr[i] = -1;
      i++;
    }
    else if (tagTable[a].activeState == 1) {
      element_arr[i] = tagTable[a].patternID;
      i++;
    }
  }


  Serial.println("/////////////////////////");
  Serial.println("");
  make(33, 30);
}

void updateGraphics() {
  page = 0;
  a = 1;
  tft.graphicsMode();
  constr();
}

int countActive() {
  int counteractive = 0;
  for (int i = 1; i <= 100; i++) {
    if (tagTable[i].activeState == 1) {
      counteractive++;
    }
  }
  Serial.print("ACTIVE TAGS: "); Serial.println(counteractive);
  return counteractive;
}

