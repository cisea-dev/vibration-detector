void DEFAULT_INITIALIZATION() {
  CONTROL_TABLE_STATIC[API_SERVER] = "https://cisea.bukitasam.co.id/api-iot/api/v1/rain_sensor/post";
  CONTROL_TABLE_STATIC[SSID] = "Detector-Vibration";
  CONTROL_TABLE_STATIC[PASSWORD] = "@DV2023_";
  CONTROL_TABLE_STATIC[NTP] = "pool.ntp.org";

  CONTROL_TABLE_DINAMIC[UUID] = "b28eaf0c-449b-481d-8a31-9b8b3a7f3c14";
  CONTROL_TABLE_DINAMIC[API_OTA] = "https://s3.bukitasam.co.id/public/rain-detector/esp32/" + String(CONTROL_TABLE_DINAMIC[0]) + "/" + String(CONTROL_TABLE_DINAMIC[0]) + ".ino.esp32.bin";
  CONTROL_TABLE_DINAMIC[TIMESTAMP] = "2022-12-12 10:10:10";
  CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "";

  CONTROL_TABLE_DIGITAL[BUTTON_SELECT] = 0;
  CONTROL_TABLE_DIGITAL[BUTTON_ENTER] = 0;
  CONTROL_TABLE_DIGITAL[STATE_MENU] = 0;

  CONTROL_TABLE_STATE[RUNMODE] = true;
  CONTROL_TABLE_STATE[SENDING] = true;
  CONTROL_TABLE_STATE[RESTART] = false;
  CONTROL_TABLE_STATE[INTERRUPT_BUTTON] = false;
  CONTROL_TABLE_STATE[SELECT_MODE] = true;
  CONTROL_TABLE_STATE[OTA] = false;
  CONTROL_TABLE_STATE[CALIBRATE] = false;
  CONTROL_TABLE_STATE[PRINT_DATA] = true;
  CONTROL_TABLE_STATE[ISCALIBRATED] = false;
  CONTROL_TABLE_STATE[PRINT_ALL_DATA] = false;

  CONTROL_TABLE_TIME[SENDING_TO_SERVER] = 30000;
  CONTROL_TABLE_TIME[READ_ALL_SENSOR] = 2000;
  CONTROL_TABLE_TIME[SET_MPU_SENSOR] = 500;
  CONTROL_TABLE_TIME[SET_VIB_SENSOR] = 500;
  CONTROL_TABLE_TIME[SET_GPS_SENSOR] = 100;
  CONTROL_TABLE_TIME[READ_BUTTON] = 50;
  CONTROL_TABLE_TIME[OLED] = 1000;

  CONTROL_TABLE_GPS[LATITUDE] = 0.00;
  CONTROL_TABLE_GPS[LONGITUDE] = 0.00;
  CONTROL_TABLE_GPS[SPEED_KMPH] = 0.00;
  CONTROL_TABLE_GPS[SPEED_MPH] = 0.00;
  CONTROL_TABLE_GPS[ALTITUDE] = 0.00;

  CONTROL_TABLE_VIBRATION[DIGITAL_SW420] = 0.0;
  CONTROL_TABLE_VIBRATION[ANALOG_VIB] = 0.0;
  CONTROL_TABLE_VIBRATION[DIGITAL_VIB] = 0.0;
  CONTROL_TABLE_VIBRATION[ANALOG_PIEZO] = 0.0;

  CONTROL_TABLE_MPU[ACC_X] = 0.0;
  CONTROL_TABLE_MPU[ACC_Y] = 0.0;
  CONTROL_TABLE_MPU[ACC_Z] = 0.0;
  CONTROL_TABLE_MPU[GYRO_X] = 0.0;
  CONTROL_TABLE_MPU[GYRO_Y] = 0.0;
  CONTROL_TABLE_MPU[GYRO_Z] = 0.0;
  CONTROL_TABLE_MPU[MAG_X] = 0.0;
  CONTROL_TABLE_MPU[MAG_Y] = 0.0;
  CONTROL_TABLE_MPU[MAG_Z] = 0.0;
  CONTROL_TABLE_MPU[QUAN_X] = 0.0;
  CONTROL_TABLE_MPU[QUAN_Y] = 0.0;
  CONTROL_TABLE_MPU[QUAN_Z] = 0.0;
  CONTROL_TABLE_MPU[QUAN_W] = 0.0;
  CONTROL_TABLE_MPU[ROLL] = 0.0;
  CONTROL_TABLE_MPU[PITCH] = 0.0;
  CONTROL_TABLE_MPU[YAW] = 0.0;
  CONTROL_TABLE_MPU[EULER_X] = 0.0;
  CONTROL_TABLE_MPU[EULER_Y] = 0.0;
  CONTROL_TABLE_MPU[EULER_Z] = 0.0;
  CONTROL_TABLE_MPU[LIN_ACC_X] = 0.0;
  CONTROL_TABLE_MPU[LIN_ACC_Y] = 0.0;
  CONTROL_TABLE_MPU[LIN_ACC_Z] = 0.0;
  CONTROL_TABLE_MPU[ACC_BIAS_X] = 0.0;
  CONTROL_TABLE_MPU[ACC_BIAS_Y] = 0.0;
  CONTROL_TABLE_MPU[ACC_BIAS_Z] = 0.0;
  CONTROL_TABLE_MPU[GYRO_BIAS_X] = 0.0;
  CONTROL_TABLE_MPU[GYRO_BIAS_Y] = 0.0;
  CONTROL_TABLE_MPU[GYRO_BIAS_Z] = 0.0;
  CONTROL_TABLE_MPU[MAG_BIAS_X] = 0.0;
  CONTROL_TABLE_MPU[MAG_BIAS_Y] = 0.0;
  CONTROL_TABLE_MPU[MAG_BIAS_Z] = 0.0;
  CONTROL_TABLE_MPU[MAG_SCALE_X] = 0.0;
  CONTROL_TABLE_MPU[MAG_SCALE_Y] = 0.0;
  CONTROL_TABLE_MPU[MAG_SCALE_Z] = 0.0;
  CONTROL_TABLE_MPU[TEMPERATURE] = 0.0;
}

void CALIBRATE_MPU() {
  Serial.println("Calibrate MPU");
  //*
  MPU9250Setting setting;
  setting.accel_fs_sel = ACCEL_FS_SEL::A2G;
  setting.gyro_fs_sel = GYRO_FS_SEL::G250DPS;
  setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
  setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
  setting.gyro_fchoice = 0x03;
  setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
  setting.accel_fchoice = 0x01;
  setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;
  
  Wire.begin();
  delay(2000);
  if (!mpu.setup(0x68, setting)) {
    CONTROL_TABLE_STATE[RESTART] = true;
    CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "MPU9250 ERROR";
  }
  Serial.println("Accel Gyro calibration will start in 5sec.");
  Serial.println("Please leave the device still on the flat plane.");
  mpu.verbose(true);
  delay(5000);
  mpu.calibrateAccelGyro();

  Serial.println("Mag calibration will start in 5sec.");
  Serial.println("Please Wave device in a figure eight until done.");
  delay(5000);
  mpu.calibrateMag();
  mpu.verbose(false);
  mpu.setMagneticDeclination(DECLIATION);
  //*/
}

void CHECK_ERROR() {
  bool restart = CONTROL_TABLE_STATE[STATUS_ERROR];
  if (restart) {
    /*
    CONTROL_TABLE_DINAMIC[STATUS_ERROR] += "\n Restart On 5 Seconds";
    display.display();
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(CONTROL_TABLE_DINAMIC[STATUS_ERROR]);
    delay(5000);
    //*/
    Serial.print(CONTROL_TABLE_DINAMIC[STATUS_ERROR]);
  }
}