#include <TinyGPS++.h>
#include<LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
double logitude;
double latitude;
int temp=0;
int switcher = 8;                 // Connect Tilt sensor to Pin3 
int c=0;
int a=1;


int GPSBaud = 9600;

// Create a TinyGPS++ object called "gps"
TinyGPSPlus gps;

// Create a software serial port called "gpsSerial"

void setup()
{
  // Start the Arduino hardware serial port at 9600 baud
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("GPS Besed Vehicle ");
  lcd.setCursor(0,1);
  lcd.print("Tracking System");
  delay(100);
  // Start the software serial port at the GPS's default baud
  Serial.begin(GPSBaud);
  Serial.println();
}

void loop()
{
    while (Serial.available() > 0)
    if (gps.encode(Serial.read()))
      displayInfo();

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected"));
    while(true);
  }
   if(temp==1)
   {
      if(c<a)
      { 
        Serial.begin(9600);
        lcd.print("Are u Safe????");
        delay(2000);
        lcd.clear();
        lcd.print("Press Reset");
        delay(10000);
        Serial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
        delay(1000);  // Delay of 1000 milli seconds or 1 second
        Serial.println("AT+CMGS=\"+917059759087\"\r"); // Replace x with mobile number
        delay(1000);
       Serial.println("Vehicle Accident Happend at Place:");
        Serial.print("Latitude(N): ");             //enter latitude in msg
        Serial.println(latitude);                  //enter latitude value in msg
        Serial.print("Longitude(E): ");            //enter Longitude in Msg
        Serial.println(logitude);                  //enter longitude value in msg
        Serial.print("Help Please");
        delay(100);
        Serial.println((char)26);// ASCII code of CTRL+Z
        delay(1000);
        c++;
      }
   }
 }

void displayInfo()
{
    if(digitalRead(switcher)==1) 
    {  
       temp=1;
       Serial.println("Accident has happened");
       delay(1000);
    } 
    else
    {
       Serial.println();
    }
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    latitude=gps.location.lat();
    lcd.println("LAT:"); 
    lcd.print(latitude);
    delay(500);
    lcd.clear();
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    logitude=gps.location.lng(); 
    lcd.println("LONG:"); 
    lcd.print(logitude);
    delay(500);
    lcd.clear();
   }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
}
