#include "HEADER.hpp";

TaskHandle_t ReadAllSensor;
TaskHandle_t SetMPUSensor;
TaskHandle_t SetVIBSensor;
TaskHandle_t SetGPSSensor;
TaskHandle_t SetCalibrateMPU;
TaskHandle_t SetNTP;
TaskHandle_t SendingToServer;
TaskHandle_t ReadButton;
TaskHandle_t PrintOled;
TaskHandle_t OtaFirmware;

StaticJsonDocument<50000> allObject;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
MPU9250 mpu;
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  SERIALGPS.begin(9600);
  DEFAULT_INITIALIZATION();
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
  }
  display.display();
  delay(2000);
  //*****WIFI*****
  WiFi.begin(CONTROL_TABLE_STATIC[SSID], CONTROL_TABLE_STATIC[PASSWORD]);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  Serial.println(WiFi.localIP());

  //*****OLED*****
  //*
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    CONTROL_TABLE_STATE[RESTART] = true;
    CONTROL_TABLE_DINAMIC[STATUS_ERROR] = "OLED ERROR";
  } else {
    display.display();
    delay(2000);
    display.clearDisplay();
  }
  //*/

  //*****MPU 9250*****
  //CALIBRATE_MPU();

  //*****BUTTON*****
  pinMode(PIN_BTN_SELECT, INPUT);
  pinMode(PIN_BTN_ENTER, INPUT);

  //*****VIBRATION*****
  // pinMode(PIN_VIB_ANALOG, INPUT);
  // pinMode(PIN_PIEZO, INPUT);
  // pinMode(PIN_SW420, INPUT);
  // pinMode(PIN_VIB_DIGITAL, INPUT);
  CHECK_ERROR();

  xTaskCreatePinnedToCore(
    ReadAllSensorCode, /* Function to implement the task */
    "ReadAllSensor",   /* Name of the task */
    10000,             /* Stack size in words */
    NULL,              /* Task input parameter */
    1,                 /* Priority of the task */
    &ReadAllSensor,    /* Task handle. */
    1);                /* Core where the task should run */
  delay(500);

  // xTaskCreatePinnedToCore(
  //   SetMPUCode,     /* Function to implement the task */
  //   "SetMPUSensor", /* Name of the task */
  //   10000,          /* Stack size in words */
  //   NULL,           /* Task input parameter */
  //   2,              /* Priority of the task */
  //   &SetMPUSensor,  /* Task handle. */
  //   1);             /* Core where the task should run */
  // delay(500);

  xTaskCreatePinnedToCore(
    SetVIBCode,     /* Function to implement the task */
    "SetVIBSensor", /* Name of the task */
    10000,          /* Stack size in words */
    NULL,           /* Task input parameter */
    5,              /* Priority of the task */
    &SetVIBSensor,  /* Task handle. */
    1);             /* Core where the task should run */
  delay(500);

  // xTaskCreatePinnedToCore(
  //   SetGPSCode,     /* Function to implement the task */
  //   "SetGPSSensor", /* Name of the task */
  //   10000,          /* Stack size in words */
  //   NULL,           /* Task input parameter */
  //   4,              /* Priority of the task */
  //   &SetGPSSensor,  /* Task handle. */
  //   1);             /* Core where the task should run */
  // delay(500);

  xTaskCreatePinnedToCore(
    ReadButtonCode, /* Function to implement the task */
    "ReadButton",   /* Name of the task */
    10000,          /* Stack size in words */
    NULL,           /* Task input parameter */
    2,              /* Priority of the task */
    &ReadButton,    /* Task handle. */
    0);             /* Core where the task should run */
  delay(500);

  xTaskCreatePinnedToCore(
    SendToServerCode,  /* Function to implement the task */
    "SendingToServer", /* Name of the task */
    10000,             /* Stack size in words */
    NULL,              /* Task input parameter */
    10,                /* Priority of the task */
    &SendingToServer,  /* Task handle. */
    0);                /* Core where the task should run */
  delay(500);

  xTaskCreatePinnedToCore(
    PrintOledCode, /* Function to implement the task */
    "PrintOled",   /* Name of the task */
    10000,         /* Stack size in words */
    NULL,          /* Task input parameter */
    0,             /* Priority of the task */
    &PrintOled,    /* Task handle. */
    0);            /* Core where the task should run */
  delay(500);

  //*
  xTaskCreatePinnedToCore(
    SetNTPCode,
    "SetNTP",
    10000,
    NULL,
    5,
    &SetNTP,
    0);
  delay(500);
  //*/

  xTaskCreatePinnedToCore(
    SetCalibrateMPUCode, /* Function to implement the task */
    "SetCalibrateMPU",   /* Name of the task */
    10000,               /* Stack size in words */
    NULL,                /* Task input parameter */
    0,                   /* Priority of the task */
    &SetCalibrateMPU,    /* Task handle. */
    0);                  /* Core where the task should run */
  delay(500);
}

void loop() {
  int a, b, c, d;
  a = analogRead(PIN_SW420);
  b = analogRead(PIN_VIB_ANALOG);
  c = digitalRead(PIN_VIB_DIGITAL);
  d = analogRead(PIN_PIEZO);
  Serial.println("");
  Serial.println(a);
  Serial.println(b);
  Serial.println("");
  delay(100);
  //*
  CONTROL_TABLE_VIBRATION[DIGITAL_SW420] = a;
  CONTROL_TABLE_VIBRATION[ANALOG_VIB] = b;
  CONTROL_TABLE_VIBRATION[DIGITAL_VIB] = c;
  CONTROL_TABLE_VIBRATION[ANALOG_PIEZO] = d;
}
