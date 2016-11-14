void initializeLocalDatabase() {
  EEPROM.setMemPool(0, EEPROMSizeMega);
  EEPROM.setMaxAllowedWrites(32767);//remove
  EEPROM.readByte(TABLES_PRESENT_ADDRESS);

  if (EEPROM.readByte(TABLES_PRESENT_ADDRESS) != TABLES_PRESENT) {
    createTagTable();
    createControlPanel();
    updateTablesPresent();
    Serial.println("New Tables Created");//remove
  }
  else {
    loadTables();
    Serial.println("Old Tables Loaded");//remove

  }
}

void createTagTable() {
  for (int i = 0; i < 101; i++) {
    tagTable[i].tagUID = 0;
    tagTable[i].scanTime = 0;
    tagTable[i].patternID = i;
    tagTable[i].activeState = 0;
    tagTable[i].storageCategory = 0;
    tagTable[i].foodCategory = 0;
    tagTable[i].cookedCategory = 0;
    tagTable[i].needsUpdate = 0;
  }
  EEPROM.updateBlock(TAG_TABLE_ADDRESS, tagTable, 101);
}

void createControlPanel() {
  controlPanel.panelUID = PANEL_UID;
  controlPanel.isRegistered = 0;
  controlPanel.isLinked = 0;
  controlPanel.panelVersion = PANEL_VERSION;
  controlPanel.firmwareVersionNum = FIRMWARE_VERSION_NUM;
  controlPanel.firmwareRevisionNum = FIRMWARE_REVISION_NUM;

  EEPROM.updateBlock(CONTROL_PANEL_ADDRESS, controlPanel);
}

void updateTablesPresent() {
  EEPROM.updateByte(TABLES_PRESENT_ADDRESS, TABLES_PRESENT);
}

void loadTables() {
  EEPROM.readBlock(TAG_TABLE_ADDRESS, tagTable, 101);
  EEPROM.readBlock(CONTROL_PANEL_ADDRESS, controlPanel);
}

void databaseDebugPrint() {
  EEPROM.readBlock(TAG_TABLE_ADDRESS, tagTable, 101);
  //Serial.println();
  //Serial.println(F("Control Panel Info"));
  //Serial.print(F("Panel UID: "));  Hex64BitNumberPrintln(controlPanel.panelUID);
  //Serial.print(F("Registration Status: "));  //Serial.println((byte)controlPanel.isRegistered);
  //Serial.print(F("Account Link Status: "));  //Serial.println((byte)controlPanel.isLinked);
  //Serial.print(F("Panel Version: "));  //Serial.println((byte)controlPanel.panelVersion);
  //Serial.print(F("Firmware Version: "));  //Serial.println(controlPanel.firmwareVersionNum);
  //Serial.print(F("Firmware Revision: "));  //Serial.println(controlPanel.firmwareRevisionNum);

  //Serial.println(F("----------------------------------------------------------------------"));
  //Serial.println(F("Tag Table Info"));
  for (int i = 0; i < 101; i++) {
    //Serial.print(F("Tag #"));  //Serial.print(i); //Serial.println(": ");
    //Serial.print(F("Tag UID: "));  //Serial.println(tagTable[i].tagUID, HEX);
    //Serial.print(F("Scan Time: "));  //Serial.println(tagTable[i].scanTime);
    //Serial.print(F("Pattern ID: "));  //Serial.println(tagTable[i].patternID);
    //Serial.print(F("Active State: "));  //Serial.println(tagTable[i].activeState);
    //Serial.print(F("Storage Category: "));  //Serial.println(tagTable[i].storageCategory);
    //Serial.print(F("Food Category: "));  //Serial.println(tagTable[i].foodCategory);
    //Serial.print(F("Cooked Category: "));  //Serial.println(tagTable[i].cookedCategory);
    //Serial.print(F("needsUpdate: "));  //Serial.println(tagTable[i].needsUpdate);
    //Serial.println(F("=================================================================="));
  }
}

void Hex64BitNumberPrintln (unsigned long long num) {
  unsigned long n = num >> 32;
  if (n != 0) {
    //Serial.print(n, HEX);
  }
  //Serial.println((unsigned long)num, HEX);
}

void updateTagTable () {
  EEPROM.updateBlock(TAG_TABLE_ADDRESS, tagTable, 101);
}
