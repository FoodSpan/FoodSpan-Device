void initializeScanner() {
  SPI.begin();               // Init SPI bus
  mfrc522.PCD_Init();        // Init MFRC522 card
  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }
}

void checkScanner() {
  switch (scannerState) {
    case (ADD):
      scannerAdd();
      break;

    case (DELETE):
      scannerDelete();
      break;

  }
}

void scannerAdd() {

  MFRC522::StatusCode status;

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //remove
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Serial.println("ADD ATTEMPt");
  //Serial.print(F("Card UID(HEX):"));    //Dump HEX UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  //Serial.print(F(" PICC type: "));   // Dump PICC type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  //Serial.println(mfrc522.PICC_GetTypeName(piccType));
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.
  readBlock(1, readbackblock);//read the block back

  //remove
  /////////////////////////////////////////////////////////////////////////////
  //Serial.print("read block: ");
  for (int j = 0 ; j < 16 ; j++) //print the block contents
  {
    //Serial.print (readbackblock[j]);
    //Serial.print (" ");
  }
  //Serial.println ("");
  //////////////////////////////////////////////////////////////////////////////

  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD

  addNewTag(readbackblock[0], arrayToLong(mfrc522.uid.uidByte));
  resetButtons();
}



void addNewTag(byte patternId, unsigned long tagUID) {
  if (tagTable[patternId].activeState == 0) {
    tagTable[patternId].tagUID = tagUID;
    tagTable[patternId].scanTime = getTime();
    tagTable[patternId].patternID = patternId;
    tagTable[patternId].activeState = 1;
    tagTable[patternId].storageCategory = storageCategory;
    tagTable[patternId].foodCategory = foodCategory;
    tagTable[patternId].cookedCategory = cookedCategory;
    tagTable[patternId].needsUpdate = 1;
    updateTagTable();
    updateGraphics();
  } else {
    tagError();
  }
}

void scannerDelete() {
  MFRC522::StatusCode status;

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  //remove
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //Serial.println("DELETING ATTEMPt");
  //Serial.print(F("Card UID(HEX):"));    //Dump HEX UID
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    //Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  //Serial.print(F(" PICC type: "));   // Dump PICC type
  MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
  //Serial.println(mfrc522.PICC_GetTypeName(piccType));
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  byte readbackblock[18];//This array is used for reading out a block. The MIFARE_Read method requires a buffer that is at least 18 bytes to hold the 16 bytes of a block.
  readBlock(1, readbackblock);//read the block back

  //remove
  ////////////////////////////////////////////////////////////////////////////
  //Serial.print("read block: ");
  for (int j = 0 ; j < 16 ; j++) //print the block contents
  {
    //Serial.print (readbackblock[j]);
    //Serial.print (" ");
  }
  //Serial.println ("");
  //////////////////////////////////////////////////////////////////////////////

  mfrc522.PICC_HaltA(); // Halt PICC
  mfrc522.PCD_StopCrypto1();  // Stop encryption on PCD

  deleteTag(readbackblock[0], arrayToLong(mfrc522.uid.uidByte));
  resetButtons();
}

void deleteTag(byte patternId, unsigned long tagUID) {
  if (tagTable[patternId].tagUID == tagUID) {
    tagTable[patternId].activeState = 0;
    tagTable[patternId].needsUpdate = 1;
    updateTagTable();
    scannerState = ADD;
    updateGraphics();

    //databaseDebugPrint();//////remove
  } else {
    tagError();
  }
}

unsigned long arrayToLong(byte array[]) {
  unsigned long result = 0;

  for (int i = 0, j = mfrc522.uid.size; i < j; i++) {
    result += (long)array[i] << (8 * (j - 1 - i));
  }
  return result;
}

int readBlock(int blockNumber, byte arrayAddress[])
{
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0) {
    //Serial.print(blockNumber);  //block number is a trailer block (modulo 4); quit and send error code 2
    //Serial.println(" is a trailer block.");
    //Serial.println("Reading Trailer Block:");
  }

  /*****************************************authentication of the desired block for access***********************************************************/
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, blockNumber, &key, &(mfrc522.uid));
  //byte PCD_Authenticate(byte command, byte blockAddr, MIFARE_Key *key, Uid *uid);
  //this method is used to authenticate a certain block for writing or reading
  //command: See enumerations above -> PICC_CMD_MF_AUTH_KEY_A  = 0x60 (=1100000),    // this command performs authentication with Key A
  //blockAddr is the number of the block from 0 to 15.
  //MIFARE_Key *key is a pointer to the MIFARE_Key struct defined above, this struct needs to be defined for each block. New cards have all A/B= FF FF FF FF FF FF
  //Uid *uid is a pointer to the UID struct that contains the user ID of the card.
  if (status != MFRC522::STATUS_OK) {
    //Serial.print("PCD_Authenticate() failed (read): ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return 3;//return "3" as error message
  }
  //it appears the authentication needs to be made before every block read/write within a specific sector.
  //If a different sector is being authenticated access to the previous one is lost.


  /*****************************************reading a block***********************************************************/

  byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
    //Serial.print("MIFARE_read() failed: ");
    //Serial.println(mfrc522.GetStatusCodeName(status));
    return 4;//return "4" as error message
  }
  //Serial.println("block was read");
}
