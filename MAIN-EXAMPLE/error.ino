// /*************************************************************************
//  * 
//  * >>PopSci Speedbelt<<
//  * 
//  * Determine your stride length-
//  * 
//  * Stride Length = 28.5"
//  * 
//  * Set sensor sample rate at 30 seconds-
//  * 
//  * Stride length x strides (vibrations) per 60 sec-
//  * 
//  * ((# strides x 2) x stride length)/12 = feet/minute
//  * 
//  * Convert to MPH-
//  * 
//  * (x feet/minute / 5280 feet) x 60 = speed MPH
//  * 
//  * Here are some resources for Stride Calculators:
//  * 
//  * Johnson Outdoors Gear LLC -
//  * http://www.tech4o.com/detail.aspx?id=181
//  * 
//  * Walking with Attitude - 
//  * http://www.walkingwithattitude.com/fitness-tools/stride-length
//  * 
//  *************************************************************************/

// // Arduino 1.0

// //unsigned char i;
// //unsigned char j;
// ///*Port Definitions*/
// //int Max7219_pinCLK = 10;
// //int Max7219_pinCS = 9;
// //int Max7219_pinDIN = 8;
// //unsigned char disp1[13][8]={
// //  {
// //    0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C  }
// //  ,//0
// //  {
// //    0x10,0x18,0x14,0x10,0x10,0x10,0x10,0x10  }
// //  ,//1
// //  {
// //    0x7E,0x2,0x2,0x7E,0x40,0x40,0x40,0x7E  }
// //  ,//2
// //  {
// //    0x3E,0x2,0x2,0x3E,0x2,0x2,0x3E,0x0  }
// //  ,//3
// //  {
// //    0x8,0x18,0x28,0x48,0xFE,0x8,0x8,0x8  }
// //  ,//4
// //  {
// //    0x3C,0x20,0x20,0x3C,0x4,0x4,0x3C,0x0  }
// //  ,//5
// //  {
// //    0x3C,0x20,0x20,0x3C,0x24,0x24,0x3C,0x0  }
// //  ,//6
// //  {
// //    0x3E,0x22,0x4,0x8,0x8,0x8,0x8,0x8  }
// //  ,//7
// //  {
// //    0x0,0x3E,0x22,0x22,0x3E,0x22,0x22,0x3E  }
// //  ,//8
// //  {
// //    0x3E,0x22,0x22,0x3E,0x2,0x2,0x2,0x3E  }
// //  ,//9
// //  //{0x8,0x14,0x22,0x3E,0x22,0x22,0x22,0x22},//A
// //  //{0x3C,0x22,0x22,0x3E,0x22,0x22,0x3C,0x0},//B
// //  //{0x3C,0x40,0x40,0x40,0x40,0x40,0x3C,0x0},//C
// //  //{0x7C,0x42,0x42,0x42,0x42,0x42,0x7C,0x0},//D
// //  //{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x7C},//E
// //  //{0x7C,0x40,0x40,0x7C,0x40,0x40,0x40,0x40},//F
// //  //{0x3C,0x40,0x40,0x40,0x40,0x44,0x44,0x3C},//G
// //  {
// //    0x44,0x44,0x44,0x7C,0x44,0x44,0x44,0x44  }
// //  ,//H
// //  //{0x7C,0x10,0x10,0x10,0x10,0x10,0x10,0x7C},//I
// //  //{0x3C,0x8,0x8,0x8,0x8,0x8,0x48,0x30},//J
// //  //{0x0,0x24,0x28,0x30,0x20,0x30,0x28,0x24},//K
// //  //{0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x7C},//L
// //  {
// //    0x81,0xC3,0xA5,0x99,0x81,0x81,0x81,0x81  }
// //  ,//M
// //  //{0x0,0x42,0x62,0x52,0x4A,0x46,0x42,0x0},//N
// //  //{0x3C,0x42,0x42,0x42,0x42,0x42,0x42,0x3C},//O
// //  {
// //    0x3C,0x22,0x22,0x22,0x3C,0x20,0x20,0x20  }
// //  ,//P
// //  //{0x1C,0x22,0x22,0x22,0x22,0x26,0x22,0x1D},//Q
// //  //{0x3C,0x22,0x22,0x22,0x3C,0x24,0x22,0x21},//R
// //  //{0x0,0x1E,0x20,0x20,0x3E,0x2,0x2,0x3C},//S
// //  //{0x0,0x3E,0x8,0x8,0x8,0x8,0x8,0x8},//T
// //  //{0x42,0x42,0x42,0x42,0x42,0x42,0x22,0x1C},//U
// //  //{0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18},//V
// //  //{0x0,0x49,0x49,0x49,0x49,0x2A,0x1C,0x0},//W
// //  //{0x0,0x41,0x22,0x14,0x8,0x14,0x22,0x41},//X
// //  //{0x41,0x22,0x14,0x8,0x8,0x8,0x8,0x8},//Y
// //  //{0x0,0x7F,0x2,0x4,0x8,0x10,0x20,0x7F},//Z
// //};

// //defines the Sensor pin connections
// //int GroundPin= A0;
// int sensePin= 0; //A1
// //defines normal and threshold voltage levels
// int normalReading= 0;
// int threshold= 10;

// //Define stride
// float strideLength = 1; // set 28.5
// //Feet per minute
// float FPM = 0;
// //MPH
// int MPH = 0;

// //void Write_Max7219_byte(unsigned char DATA)
// //{
// //  unsigned char i;
// //  digitalWrite(Max7219_pinCS,LOW);
// //  for(i=8;i>=1;i--)
// //  {
// //    digitalWrite(Max7219_pinCLK,LOW);
// //    digitalWrite(Max7219_pinDIN,DATA&0x80);// Extracting a bit data
// //    DATA = DATA<<1;
// //    digitalWrite(Max7219_pinCLK,HIGH);
// //  }
// //}
// //void Write_Max7219(unsigned char address,unsigned char dat)
// //{
// //  digitalWrite(Max7219_pinCS,LOW);
// //  Write_Max7219_byte(address);
// //  //address,code of LED
// //  Write_Max7219_byte(dat);
// //  //data,figure on LED
// //  digitalWrite(Max7219_pinCS,HIGH);
// //}
// //void Init_MAX7219(void)
// //{
// //  Write_Max7219(0x09, 0x00);
// //  Write_Max7219(0x0a, 0x03);
// //  Write_Max7219(0x0b, 0x07);
// //  Write_Max7219(0x0c, 0x01);
// //  Write_Max7219(0x0f, 0x00);
// //}
// ////decoding :BCD
// ////brightness
// ////scanlimit;8 LEDs
// ////power-down mode:0,normal mode:1
// ////test display:1;EOT,display:0

// //this function returns the average reading of the sensePin when no large vibration is detected
// int calibrate()
// {
//   int n= 100;
//   long total=0;
//   for (int i=0; i<100; i++) {
//     total= total + analogRead(sensePin);
//     delay(1);
//   }
//   return total/n;
// }

// void setup()
// {
//   Serial.begin(9600);
// //  pinMode(Max7219_pinCLK,OUTPUT);
// //  pinMode(Max7219_pinCS,OUTPUT);
// //  pinMode(Max7219_pinDIN,OUTPUT);
// //  delay(50);
// //  Init_MAX7219();
//   //sets Sensor GroundPin as output pin, GroundPin being set to LOW
// //  pinMode(GroundPin, OUTPUT);
// //  digitalWrite(GroundPin, LOW);
//   normalReading= calibrate();
// }

// void loop()
// {
//   int numberofStrides = 0;
//   //Determine the speed
//   {
//     //if the sensor reading is higher than the threshold value, then the stride is turned incremented
//     for (int i=0; i<30000; i++)
//     {
//       int reading= analogRead(sensePin);
//       if (reading > normalReading + threshold)
//       {
//         //Stride
//         //digitalWrite(LEDPin, HIGH);
//         numberofStrides++;
//       }
//     }
//     //Calculate feet per minute
//     FPM = ((numberofStrides * 2) * strideLength)/12;
// //    Serial.print("FPM: "); Serial.println(FPM);
//     //Convert to MPH
//     MPH = (FPM / 5280) * 60;
//     Serial.print("MPH: "); Serial.println(MPH);
//   }

//   //Display the final speed
//   //for(j=0;j<13;j++)

// //  if (MPH < 10) {
// //    j=MPH;
// //    if (j < 1) {
// //      j = 0;
// //    }
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //  }
// //
// //  if (MPH > 9) {
// //    j=MPH/10;
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //    j=MPH % 10;
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //  }
// //
// //  //Display M
// //  {
// //    j=11;
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //  }
// //
// //  //Display P
// //  {
// //    j=12;
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //  }
// //
// //  //Display H
// //  {
// //    j=10;
// //    for(i=1;i<9;i++)
// //      Write_Max7219(i,disp1[j][i-1]);
// //    delay(500);
// //  }

// }