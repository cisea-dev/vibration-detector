/**
* ReadAllSensorCode is task that handle function
* To read all sensor value
* GPS - MPU - VIBRATION
* Run On Core 0
*/
void ReadAllSensorCode(void* pvParameters) {
  /*Run On Core 0*/
  Serial.print("ReadAllSensor running on core ");
  Serial.println(xPortGetCoreID());
  for (;;) {
    delay(10);
    static uint32_t ms = millis();
    if ((millis() - ms > CONTROL_TABLE_TIME[READ_ALL_SENSOR]) && (CONTROL_TABLE_STATE[RUNMODE])) {
      StaticJsonDocument<1700> doc;  // Created 3 Object
      doc["uuid"] = CONTROL_TABLE_DINAMIC[UUID];
      JsonObject accelerometer_0 = doc["accelerometer"].createNestedObject();
      accelerometer_0["x"] = CONTROL_TABLE_MPU[ACC_X];  //ACC_X
      accelerometer_0["y"] = CONTROL_TABLE_MPU[ACC_Y];  //ACC_Y
      accelerometer_0["z"] = CONTROL_TABLE_MPU[ACC_Z];  //ACC_Z

      JsonObject gyro_0 = doc["gyro"].createNestedObject();
      gyro_0["x"] = CONTROL_TABLE_MPU[GYRO_X];  //GYRO_X
      gyro_0["y"] = CONTROL_TABLE_MPU[GYRO_Y];  //GYRO_Y
      gyro_0["z"] = CONTROL_TABLE_MPU[GYRO_Z];  //GYRO_Z

      JsonObject magnetometer_0 = doc["magnetometer"].createNestedObject();
      magnetometer_0["x"] = CONTROL_TABLE_MPU[MAG_X];  //MAG_X
      magnetometer_0["y"] = CONTROL_TABLE_MPU[MAG_Y];  //MAG_Y
      magnetometer_0["z"] = CONTROL_TABLE_MPU[MAG_Z];  //MAG_Z

      JsonObject quanternion_0 = doc["quanternion"].createNestedObject();
      quanternion_0["x"] = CONTROL_TABLE_MPU[QUAN_X];  //QUAN_X
      quanternion_0["y"] = CONTROL_TABLE_MPU[QUAN_Y];  //QUAN_Y
      quanternion_0["z"] = CONTROL_TABLE_MPU[QUAN_Z];  //QUAN_Z
      quanternion_0["w"] = CONTROL_TABLE_MPU[QUAN_W];  //QUAN_W

      doc["temperature"] = CONTROL_TABLE_MPU[TEMPERATURE];  //TEMPERATURE

      JsonObject rotation_0 = doc["rotation"].createNestedObject();
      rotation_0["roll"] = CONTROL_TABLE_MPU[ROLL];    //ROLL
      rotation_0["pitch"] = CONTROL_TABLE_MPU[PITCH];  //PITCH
      rotation_0["yaw"] = CONTROL_TABLE_MPU[YAW];      //YAW

      JsonObject euler_0 = doc["euler"].createNestedObject();
      euler_0["x"] = CONTROL_TABLE_MPU[EULER_X];
      euler_0["y"] = CONTROL_TABLE_MPU[EULER_Y];
      euler_0["z"] = CONTROL_TABLE_MPU[EULER_Z];

      JsonObject linear_acc_0 = doc["linear_acc"].createNestedObject();
      linear_acc_0["x"] = CONTROL_TABLE_MPU[LIN_ACC_X];
      linear_acc_0["y"] = CONTROL_TABLE_MPU[LIN_ACC_Y];
      linear_acc_0["z"] = CONTROL_TABLE_MPU[LIN_ACC_Z];

      JsonObject acc_bias_0 = doc["acc_bias"].createNestedObject();
      acc_bias_0["x"] = CONTROL_TABLE_MPU[ACC_BIAS_X];
      acc_bias_0["y"] = CONTROL_TABLE_MPU[ACC_BIAS_Y];
      acc_bias_0["z"] = CONTROL_TABLE_MPU[ACC_BIAS_Z];

      JsonObject gyro_bias_0 = doc["gyro_bias"].createNestedObject();
      gyro_bias_0["x"] = CONTROL_TABLE_MPU[GYRO_BIAS_X];
      gyro_bias_0["y"] = CONTROL_TABLE_MPU[GYRO_BIAS_Y];
      gyro_bias_0["z"] = CONTROL_TABLE_MPU[GYRO_BIAS_Z];

      JsonObject mag_bias_0 = doc["mag_bias"].createNestedObject();
      mag_bias_0["x"] = CONTROL_TABLE_MPU[MAG_BIAS_X];
      mag_bias_0["y"] = CONTROL_TABLE_MPU[MAG_BIAS_Y];
      mag_bias_0["z"] = CONTROL_TABLE_MPU[MAG_BIAS_Z];

      JsonObject mag_scale_0 = doc["mag_scale"].createNestedObject();
      mag_scale_0["x"] = CONTROL_TABLE_MPU[MAG_SCALE_X];
      mag_scale_0["y"] = CONTROL_TABLE_MPU[MAG_SCALE_Y];
      mag_scale_0["z"] = CONTROL_TABLE_MPU[MAG_SCALE_Z];

      JsonObject gps_0 = doc["gps"].createNestedObject();
      gps_0["latitude"] = CONTROL_TABLE_GPS[LATITUDE];
      gps_0["longitude"] = CONTROL_TABLE_GPS[LONGITUDE];
      gps_0["altitude"] = CONTROL_TABLE_GPS[ALTITUDE];

      JsonObject speed_0 = doc["speed"].createNestedObject();
      speed_0["kmph"] = CONTROL_TABLE_GPS[SPEED_KMPH];
      speed_0["mph"] = CONTROL_TABLE_GPS[SPEED_MPH];

      JsonObject vibration_0 = doc["vibration"].createNestedObject();
      vibration_0["SW420"] = CONTROL_TABLE_VIBRATION[DIGITAL_SW420];
      vibration_0["anVib"] = CONTROL_TABLE_VIBRATION[ANALOG_VIB];
      vibration_0["digVib"] = CONTROL_TABLE_VIBRATION[DIGITAL_VIB];
      vibration_0["piezo"] = CONTROL_TABLE_VIBRATION[ANALOG_PIEZO];

      doc["gps_ts"] = CONTROL_TABLE_DINAMIC[GPS_TS];
      doc["ts"] = CONTROL_TABLE_DINAMIC[TIMESTAMP];
      allObject.add(doc);
      ms = millis();
    }
  }
}
