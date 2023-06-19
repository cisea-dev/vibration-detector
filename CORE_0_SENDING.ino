/**
* SendToServerCode is task that handle function
* To sending data to the server --see variable API_SERVER
* Run On Core 1 
*/
void SendToServerCode(void* pvParameters) {
  Serial.print("SendingToServer running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[SENDING_TO_SERVER]) && (CONTROL_TABLE_STATE[SENDING])) {
      Serial.print("\n\n\n\nSendingToServer running on core ");
      Serial.println(xPortGetCoreID());
      String allOutput;
      serializeJson(allObject, allOutput);
      int response = HTTP_ERROR;
      int maxTry = 3;
      do {
        Serial.println("\n\n\n\nSendingToServer");
        Serial.println(allOutput);
        Serial.println("\n\n\n\n");
        maxTry--;
        response = POST(allOutput);
      } while ((response != HTTP_SUCCESS) && (maxTry > 0));
      if (maxTry == 0) {
        CONTROL_TABLE_STATE[RESTART] = true;
        CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "Failed Sending Data";
        CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "\nError\n";
        CONTROL_TABLE_DINAMIC[STATUS_ERROR] = response;
      }
      allObject.clear();
      ms = millis();
    }
  }
}

int POST(String dataPost) {
  HTTPClient http;
  http.begin(CONTROL_TABLE_STATIC[API_SERVER]);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(dataPost);
  return httpResponseCode;
}

/**
* ReadButtonCode is task to listen --see PIN_BTN_SELECT and PIN_BTN_ENTER
* Using this function will print on OLED
* LIST MENU --see menuItems[MENU_ITEM_COUNT]
* PIN_BTN_SELECT to select menu
* PIN_BTN_ENTER to enter selected menu
* Run On Core 1
*/
void ReadButtonCode(void* pvParameters) {
  Serial.print("ReadButtonCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[READ_BUTTON]) && CONTROL_TABLE_STATE[SELECT_MODE]) {
      Serial.print("ReadButtonCode running on core ");
      Serial.println(xPortGetCoreID());
      //*****If millis is greather than READ BUTTON TIME and SELECT_MODE on true*****
      CONTROL_TABLE_DIGITAL[BUTTON_SELECT] = digitalRead(PIN_BTN_SELECT);
      CONTROL_TABLE_DIGITAL[BUTTON_ENTER] = digitalRead(PIN_BTN_ENTER);
      if (CONTROL_TABLE_DIGITAL[0])
        CONTROL_TABLE_DIGITAL[2] = (CONTROL_TABLE_DIGITAL[2] + 1) % MENU_ITEM_COUNT;

      /*
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("Menu: ");

      for (int i = 0; i < MENU_ITEM_COUNT; i++) {
        if (i == CONTROL_TABLE_DIGITAL[BUTTON_ENTER]) {
          display.print(" > ");
        } else {
          display.print("");
        }
        display.println(menuItems[i]);
        if (CONTROL_TABLE_DIGITAL[1]) {
          switch (i) {
            case 0:
              //*****RUN ALL SYSTEM*****
              CONTROL_TABLE_STATE[RUNMODE] = true;
              CONTROL_TABLE_STATE[SENDING] = true;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = true;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 1:
              //*****STOP ALL SYSTEM*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = true;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 2:
              //*****RESTART ALL SYSTEM*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = true;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 3:
              //*****CALIBRATE MPU*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = false;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = true;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 4:
              //*****UPDATE FIRMWARE VIA OTA*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = true;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 5:
              //*****SENDING DATA TO SERVER*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = true;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 6:
              //*****RE CONNECT TO WIFI*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = true;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = true;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;

            case 7:
              //*****PRINT ALL DATA SENSOR*****
              CONTROL_TABLE_STATE[RUNMODE] = false;
              CONTROL_TABLE_STATE[SENDING] = false;
              CONTROL_TABLE_STATE[RESTART] = false;
              CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
              CONTROL_TABLE_STATE[SELECT_MODE] = false;
              CONTROL_TABLE_STATE[OTA] = false;
              CONTROL_TABLE_STATE[CALIBRATE] = false;
              CONTROL_TABLE_STATE[PRINT_DATA] = false;
              CONTROL_TABLE_STATE[PRINT_ALL_DATA] = true;
              CONTROL_TABLE_STATE[ISCALIBRATED] = false;
              break;
          }
        }
      }
      //*/
      ms = millis();
    }
  }
}

/**
* PrintOledCode is task to Print data on OLED 0.96
* Run On Core 1
*/
void PrintOledCode(void* pvParameters) {
  Serial.print("PrintCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[OLED]) && CONTROL_TABLE_STATE[PRINT_DATA]) {
      Serial.print("PrintCode running on core ");
      Serial.println(xPortGetCoreID());
      ms = millis();
    }
  }
}