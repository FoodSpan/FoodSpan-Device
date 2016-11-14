#include <SPI.h>
#include <MFRC522.h>
#include "ManufacturerInfo.h"
#include <EEPROMex.h>
#include <Button.h>
#include <gfxfont.h>
#include <Fonts/FreeMono12pt7b.h>

//updown buttons
#define UP_PIN 32
#define DN_PIN 33
#define REPEAT_FIRST 500   //ms required before repeating on long press
#define REPEAT_INCR 100    //repeat interval for long press
#define MIN_COUNT 0

//wps button
#define WPS_BUTTON_PIN 30
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 20
#define WPS_LED_PIN 31
#define LONG_PRESS 1250
#define BLINK_INTERVAL 100

//category buttons
#define NFC_RST_PIN         49
#define NFC_SS_PIN          53
#define CATEGORY_BUTTON_PIN A0

#define TABLES_PRESENT_ADDRESS  0
#define TAG_TABLE_ADDRESS  1
#define CONTROL_PANEL_ADDRESS 1011

#define TABLES_PRESENT 11 //random indicator number


//add the SPI pins for the Mega
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_RA8875.h>

// change these as u need them it is your choice
//#define RA8875_INT 21
#define RA8875_CS 22
#define RA8875_RESET 23

//colours for the tags
#define Light_Grey 0xE73C
#define Grey 0xB596
#define Red 0xF46E
#define Orange 0xFD4A
#define Yellow 0xFF06
#define Green 0xA647
#define Blue 0x8DBC
#define Purple 0x6B15
#define Pink 0xBC37
#define Light_pink 0xF475

#define R 2
#define G 3 
#define B 4


#define RR 10
#define GG 11
#define BB 12


#define RRR 5
#define GGG 6
#define BBB 7
/*
  Typical pin layout used:
  -----------------------------------------------------------------------------------------
              MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
              Reader/PCD   Uno           Mega      Nano v3    Leonardo/Micro   Pro Micro
  Signal      Pin          Pin           Pin       Pin        Pin              Pin
  -----------------------------------------------------------------------------------------
  RST/Reset   RST          9             49         D9         RESET/ICSP-5     RST
  SPI SS      SDA(SS)      10            53        D10        10               10
  SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
  SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
  SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
* */

