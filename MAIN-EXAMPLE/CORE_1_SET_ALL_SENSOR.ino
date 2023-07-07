/**
*this fum
*
* CORE 0
*/
void SetCalibrateMPUCode(void* pvParameters) {
  Serial.print("SetCalibrateMPUCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    bool calib = EEPROM.read(0);
    if (!calib) {
      CALIBRATE_MPU();
    } else {
      if (mpu.update()) {
      static uint32_t prev_ms = millis();
      if (millis() > prev_ms + 25) {
        CONTROL_TABLE_MPU[ACC_X] = mpu.getAccX();
        CONTROL_TABLE_MPU[ACC_Y] = mpu.getAccY();
        CONTROL_TABLE_MPU[ACC_Z] = mpu.getAccZ();
        CONTROL_TABLE_MPU[GYRO_X] = mpu.getGyroX();
        CONTROL_TABLE_MPU[GYRO_Y] = mpu.getGyroY();
        CONTROL_TABLE_MPU[GYRO_Z] = mpu.getGyroZ();
        CONTROL_TABLE_MPU[MAG_X] = mpu.getMagX();
        CONTROL_TABLE_MPU[MAG_Y] = mpu.getMagY();
        CONTROL_TABLE_MPU[MAG_Z] = mpu.getMagZ();
        CONTROL_TABLE_MPU[QUAN_X] = mpu.getQuaternionX();
        CONTROL_TABLE_MPU[QUAN_Y] = mpu.getQuaternionY();
        CONTROL_TABLE_MPU[QUAN_Z] = mpu.getQuaternionZ();
        CONTROL_TABLE_MPU[QUAN_W] = mpu.getQuaternionW();
        CONTROL_TABLE_MPU[ROLL] = mpu.getRoll();
        CONTROL_TABLE_MPU[PITCH] = mpu.getPitch();
        CONTROL_TABLE_MPU[YAW] = mpu.getYaw();
        CONTROL_TABLE_MPU[EULER_X] = mpu.getEulerX();
        CONTROL_TABLE_MPU[EULER_Y] = mpu.getEulerY();
        CONTROL_TABLE_MPU[EULER_Z] = mpu.getEulerZ();
        CONTROL_TABLE_MPU[LIN_ACC_X] = mpu.getLinearAccX();
        CONTROL_TABLE_MPU[LIN_ACC_Y] = mpu.getLinearAccY();
        CONTROL_TABLE_MPU[LIN_ACC_Z] = mpu.getLinearAccZ();
        CONTROL_TABLE_MPU[TEMPERATURE] = mpu.getTemperature();
        Serial.print("[");
        Serial.print(mpu.getYaw(), 2);
        Serial.print("/");
        Serial.print(mpu.getPitch(), 2);
        Serial.print("/");
        Serial.println(mpu.getRoll(), 2);
      }
    }
    }
  }
}

/**
  SetVIBCode is task that handle function
  To set GPS value on CONTROL_TABLE_VIBRATION
  Run On Core 1
*/
void SetVIBCode(void* pvParameters) {
  /*Run On Core 1*/
  Serial.print("SetVIBCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(100);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[SET_VIB_SENSOR]) && (CONTROL_TABLE_STATE[RUNMODE])) {
      int a, b, c, d;
      a = analogRead(PIN_SW420);
      b = analogRead(PIN_VIB_ANALOG);
      c = digitalRead(PIN_VIB_DIGITAL);
      d = analogRead(PIN_PIEZO);
      Serial.printf("DIGITAL_SW420 : %d\t ANALOG_VIB : %d\t DIGITAL_VIB : %d\t ANALOG_PIEZO : %d\t\n", a, b, c, d);
      CONTROL_TABLE_VIBRATION[DIGITAL_SW420] = a;
      CONTROL_TABLE_VIBRATION[ANALOG_VIB] = b;
      CONTROL_TABLE_VIBRATION[DIGITAL_VIB] = c;
      CONTROL_TABLE_VIBRATION[ANALOG_PIEZO] = d;

      ms = millis();
    }
  }
}


/**
  SetGPSCode is task that handle function
  To set GPS value on CONTROL_TABLE_GPS
  Run On Core 1
*/
void SetGPSCode(void* pvParameters) {
  /*Run On Core 1*/
  Serial.print("SetGPSCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[SET_GPS_SENSOR]) && (CONTROL_TABLE_STATE[RUNMODE])) {
      //*
      while (SERIALGPS.available() > 0) {
        bool enc = gps.encode(SERIALGPS.read());
        CONTROL_TABLE_DINAMIC[TIMESTAMP] = "2023-01-01 01:01:01";
        switch (enc) {
          case 0:
            //*****ERROR ENCODING GPS*****
            Serial.println("ENCODING GPS FAILED");
            break;

          case 1:
            //*****SUCCESS ENCODING GPS*****
            if (gps.location.isValid() || gps.location.isUpdated()) {
              CONTROL_TABLE_GPS[LATITUDE] = gps.location.lat();
              CONTROL_TABLE_GPS[LONGITUDE] = gps.location.lng();
              CONTROL_TABLE_GPS[SPEED_KMPH] = gps.speed.kmph();
              CONTROL_TABLE_GPS[SPEED_MPH] = gps.speed.mph();
            }
            if ((gps.date.isValid() && (gps.time.isValid()) || gps.date.isUpdated()) || gps.time.isUpdated()) {
              CONTROL_TABLE_DINAMIC[TIMESTAMP] = String(gps.date.year()) + "-";
              CONTROL_TABLE_DINAMIC[TIMESTAMP] += String(gps.date.month()) + "-";
              CONTROL_TABLE_DINAMIC[TIMESTAMP] += String(gps.date.day());

              if (gps.time.hour() < 10) CONTROL_TABLE_DINAMIC[GPS_TS] += "0" + String(gps.time.hour());
              if (gps.time.minute() < 10) CONTROL_TABLE_DINAMIC[GPS_TS] += "0" + String(gps.time.minute());
              if (gps.time.second() < 10) CONTROL_TABLE_DINAMIC[GPS_TS] += "0" + String(gps.time.second());
              if (gps.time.centisecond() < 10) CONTROL_TABLE_DINAMIC[GPS_TS] += "0" + String(gps.time.centisecond());
            }
        }
      }
      //*/
      ms = millis();
    }
  }
}


void SetNTPCode(void* pvParameters) {
  Serial.print("SetNTPCode running on core : ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if (millis() - ms > CONTROL_TABLE_TIME[SET_NTP] || CONTROL_TABLE_STATE[GET_NTP]) {
      CONTROL_TABLE_STATE[GET_NTP] = false;
      configTime(CONTROL_TABLE_TIME[OFFSET], CONTROL_TABLE_DIGITAL[DAYLIGHT], CONTROL_TABLE_STATIC[NTP_SERVER]);
      struct tm timeinfo;
      if (!getLocalTime(&timeinfo)) {
        Serial.println("Failed to obtain time");
        return;
      }
      char timestamp[20];
      strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);
      // Serial.print("Timestamp : ");
      // Serial.println(String(timestamp));
      CONTROL_TABLE_DINAMIC[TIMESTAMP] = String(timestamp);
    }
  }
}

void RestartESPCode(void* pvParameters) {
  Serial.print("SetNTPCode running on core : ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    if (CONTROL_TABLE_STATE[RESTART]) {
      Serial.print("\n\n Restart WIFI \n\n");
      delay(100);
      ESP.restart();
    }
  }
}