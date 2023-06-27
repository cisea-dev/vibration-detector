/*LIBRARY MPU 9250*/
#include "MPU9250.h"

/*LIBRARY GPS*/
#include <TinyGPSPlus.h>

/*LIBRARY OLED*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*LIBRARY WIFI*/
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/*PIN OLED*/
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

/*PIN BUTTON*/
#define PIN_BTN_SELECT 19
#define PIN_BTN_ENTER 18

/*PIN VIBRATION*/
#define PIN_VIB_ANALOG 33
#define PIN_VIB_DIGITAL 32
#define PIN_SW420 13
#define PIN_PIEZO 23

/*HTTP RESPONSE CODE*/
#define HTTP_SUCCESS 200
#define HTTP_ERROR 400

/*GPS*/
#define SERIALGPS Serial2
#define DECLIATION 0.23835

const char* CONTROL_TABLE_STATIC[10];
String CONTROL_TABLE_DINAMIC[10];
double CONTROL_TABLE_GPS[10];
int CONTROL_TABLE_VIBRATION[10];
float CONTROL_TABLE_MPU[34];
bool CONTROL_TABLE_STATE[10];
long CONTROL_TABLE_TIME[10];
int CONTROL_TABLE_DIGITAL[10];
long long CONTROL_TABLE_LONG[1000];
word var = 100000000;

/*MENU ON OLED*/
const int MENU_ITEM_COUNT = 8;
const char* menuItems[MENU_ITEM_COUNT] = {
  "RUN MODE",
  "STOP MODE",
  "RESTART MODE",
  "CALIBRATE MPU",
  "UPDATE OTA",
  "SENDING DATA",
  "RECONNECT WIFI",
  "READ SENSOR"
};

enum CT_MPU {
  ACC_X,
  ACC_Y,
  ACC_Z,
  GYRO_X,
  GYRO_Y,
  GYRO_Z,
  MAG_X,
  MAG_Y,
  MAG_Z,
  QUAN_X,
  QUAN_Y,
  QUAN_Z,
  QUAN_W,
  ROLL,
  PITCH,
  YAW,
  EULER_X,
  EULER_Y,
  EULER_Z,
  LIN_ACC_X,
  LIN_ACC_Y,
  LIN_ACC_Z,
  ACC_BIAS_X,
  ACC_BIAS_Y,
  ACC_BIAS_Z,
  GYRO_BIAS_X,
  GYRO_BIAS_Y,
  GYRO_BIAS_Z,
  MAG_BIAS_X,
  MAG_BIAS_Y,
  MAG_BIAS_Z,
  MAG_SCALE_X,
  MAG_SCALE_Y,
  MAG_SCALE_Z,
  TEMPERATURE,
  ISCONNECTED,
};

enum CT_STATIC {
  API_SERVER,
  SSID,
  PASSWORD,
  NTP_SERVER,
};

enum CT_DINAMIC {
  UUID,
  API_OTA,
  TIMESTAMP,
  STATUS_ERROR,
  GPS_TS,
};

enum CT_DIGITAL {
  BUTTON_SELECT,
  BUTTON_ENTER,
  STATE_MENU,
  DAYLIGHT,
};

enum CT_STATE {
  RUNMODE,
  SENDING,
  RESTART,
  INTERRUPT_BUTTON,
  SELECT_MODE,
  OTA,
  CALIBRATE,
  PRINT_DATA,
  ISCALIBRATED,
  PRINT_ALL_DATA,
  GET_NTP,
};

enum CT_TIME {
  SENDING_TO_SERVER,
  READ_ALL_SENSOR,
  SET_MPU_SENSOR,
  SET_VIB_SENSOR,
  SET_GPS_SENSOR,
  SET_CALIBRATE,
  SET_NTP,
  READ_BUTTON,
  OLED,
  OFFSET,
};

enum CT_GPS {
  LATITUDE,
  LONGITUDE,
  SPEED_KMPH,
  SPEED_MPH,
  ALTITUDE
};

enum CT_VIBRATION {
  DIGITAL_SW420,
  ANALOG_VIB,
  DIGITAL_VIB,
  ANALOG_PIEZO
};
