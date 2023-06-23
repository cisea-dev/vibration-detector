/**
  SetMPUCode is task that handle function
  To set MPU value on CONTROL_TABLE_MPU
  Run On Core 0
*/
void SetMPUCode(void* pvParameters) {
  /*Run On Core 0*/
  Serial.print("SetMPUCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[SET_MPU_SENSOR]) && (CONTROL_TABLE_STATE[RUNMODE])) {
      Serial.print("SetMPUCode running on core ");
      Serial.println(xPortGetCoreID());
      Serial.println(CONTROL_TABLE_MPU[ISCONNECTED] ? "MPU Connected" : "MPU Not Connected");

      bool isCalib = CONTROL_TABLE_STATE[ISCALIBRATED];
      /******
        switch (isCalib) {
        case 0:
          Serial.println("MPU Not Calibrated");
          break;

        case 1:
          Serial.println("MPU Calibrated");

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

          break;
        }//*/
      ms = millis();
    }
  }
}

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
    if ((millis() - ms > CONTROL_TABLE_TIME[SET_CALIBRATE]) && CONTROL_TABLE_STATE[!ISCALIBRATED]) {
      /*
      Serial.println("Accel Gyro calibration will start in 5sec.");
      Serial.println("Please leave the device still on the flat plane.");
      
      CONTROL_TABLE_STATE[RUNMODE] = false;
      CONTROL_TABLE_STATE[SENDING] = false;
      CONTROL_TABLE_STATE[RESTART] = false;
      CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
      CONTROL_TABLE_STATE[SELECT_MODE] = false;
      CONTROL_TABLE_STATE[OTA] = false;
      CONTROL_TABLE_STATE[CALIBRATE] = false;
      CONTROL_TABLE_STATE[PRINT_DATA] = false;
      CONTROL_TABLE_STATE[ISCALIBRATED] = true;

      CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "Accel Gyro calibration will start in 5sec.\n";
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] += "Please leave the device still on the flat plane.\n";
      
      display.display();
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(CONTROL_TABLE_DINAMIC[STATUS_ERROR]);
      
      mpu.verbose(true);
      delay(5000);
      mpu.calibrateAccelGyro();
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "Mag calibration will start in 5sec.\n";
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] += "Please Wave device \nin a figure eight until done.";
      display.display();
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(CONTROL_TABLE_DINAMIC[STATUS_ERROR]);
      delay(5000);
      mpu.calibrateMag();
      mpu.verbose(false);
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "Mag calibration will start in 5sec.\n";
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] += "Please Wave device \nin a figure eight until done.";
      CONTROL_TABLE_DINAMIC[STATUS_ERROR] += "Calibrate Done";
      display.display();
      display.clearDisplay();
      display.setCursor(0, 0);
      display.println(CONTROL_TABLE_DINAMIC[STATUS_ERROR]);
      CONTROL_TABLE_MPU[ACC_BIAS_X] = mpu.getAccBiasX() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
      CONTROL_TABLE_MPU[ACC_BIAS_Y] = mpu.getAccBiasY() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
      CONTROL_TABLE_MPU[ACC_BIAS_Z] = mpu.getAccBiasZ() * 1000.f / (float)MPU9250::CALIB_ACCEL_SENSITIVITY;
      CONTROL_TABLE_MPU[GYRO_BIAS_X] = mpu.getGyroBiasX() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
      CONTROL_TABLE_MPU[GYRO_BIAS_Y] = mpu.getGyroBiasY() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
      CONTROL_TABLE_MPU[GYRO_BIAS_Z] = mpu.getGyroBiasZ() / (float)MPU9250::CALIB_GYRO_SENSITIVITY;
      CONTROL_TABLE_MPU[MAG_BIAS_X] = mpu.getMagBiasX();
      CONTROL_TABLE_MPU[MAG_BIAS_Y] = mpu.getMagBiasY();
      CONTROL_TABLE_MPU[MAG_BIAS_Z] = mpu.getMagBiasZ();
      CONTROL_TABLE_MPU[MAG_SCALE_X] = mpu.getMagScaleX();
      CONTROL_TABLE_MPU[MAG_SCALE_Y] = mpu.getMagScaleY();
      CONTROL_TABLE_MPU[MAG_SCALE_Z] = mpu.getMagScaleZ();
      //*/
    }
  }
}

/**
  SetVIBCode is task that handle function
  To set GPS value on CONTROL_TABLE_VIBRATION
  Run On Core 1
*/
void SetVIBCode(void* pvParameters) {
  /*Run On Core 0*/
  Serial.print("SetVIBCode running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[SET_VIB_SENSOR]) && (CONTROL_TABLE_STATE[RUNMODE])) {
      Serial.print("SetVIBCode running on core ");
      Serial.println(xPortGetCoreID());
      //*
      CONTROL_TABLE_VIBRATION[DIGITAL_SW420] = digitalRead(PIN_SW420);
      CONTROL_TABLE_VIBRATION[ANALOG_VIB] = analogRead(PIN_VIB_ANALOG);
      CONTROL_TABLE_VIBRATION[DIGITAL_VIB] = digitalRead(PIN_VIB_DIGITAL);
      CONTROL_TABLE_VIBRATION[ANALOG_PIEZO] = analogRead(PIN_PIEZO);
      //*/
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
      Serial.print("SetGPSCode running on core ");
      Serial.println(xPortGetCoreID());
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
      CONTROL_TABLE_DINAMIC[TIMESTAMP] = String(timestamp);
    }
  }
}