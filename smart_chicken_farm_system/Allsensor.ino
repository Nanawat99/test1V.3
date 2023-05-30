/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6YTZby9Pp"
#define BLYNK_TEMPLATE_NAME "Smart Chicken Farm System"
#define BLYNK_AUTH_TOKEN "ryj7AW5uO2NHvPtof-6IZJdvZzCBuv99"
// #define BLYNK_DEBUG

// #define APP_DEBUG

//#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Preferences.h>
#include <DHT.h>
#include <BH1750FVI.h>
#include <TimeLib.h>
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);
Preferences pref;
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Nawatwifi";
char pass[] = "123456789";

int timerValue = 0; // variable to hold the timer value in seconds


// define the GPIO connected with Relays and switches
#define RelayPin1 17  //D23
#define RelayPin2 16  //D22
#define RelayPin3 4  //D21
#define RelayPin4 0  //D19


#define wifiLed   1   //D2
#define DHTPIN 2 //D18  pin connected with DHT
//#define LDR_PIN 13

//Change the virtual pins according yours
#define VPIN_BUTTON_1    V2
#define VPIN_BUTTON_2    V3
#define VPIN_BUTTON_3    V4
#define VPIN_BUTTON_4    V5
#define VPIN_LDR         V6
#define VPIN_TEMPERATURE V0
#define VPIN_HUMIDITY    V1
#define VPIN_BUTTON_5    V9

// Uncomment whatever type you're using!
#define DHTTYPE DHT22     // DHT 11



bool led_set[2];
long timer_start_set[2] = {0xFFFF, 0xFFFF};
long timer_stop_set[2] = {0xFFFF, 0xFFFF};



long hour_start = 0xFFFF;
long minute_start = 0xFFFF;
long second_start = 0xFFFF;


long hour_end = 0xFFFF;
long minute_end = 0xFFFF;
long second_end = 0xFFFF;


unsigned char weekday_set[2];

long rtc_sec;
unsigned char day_of_week;

bool led_status[2];
bool update_blynk_status[2];
bool led_timer_on_set[2];

// Relay State
bool toggleState_1 = HIGH; //Define integer to remember the toggle state for relay 1
bool toggleState_2 = HIGH; //Define integer to remember the toggle state for relay 2
bool toggleState_3 = HIGH; //Define integer to remember the toggle state for relay 3
bool toggleState_4 = HIGH; //Define integer to remember the toggle state for relay 4
bool toggleState_5 = HIGH; //Define integer to remember the toggle state for relay 4


float temperature1 = 0;
float humidity1   = 0;
int lux = 0;
int wifiFlag = 0;

DHT dht(DHTPIN, DHTTYPE);

char auth[] = BLYNK_AUTH_TOKEN;

BlynkTimer timer;

// When App button is pushed - switch the state
BLYNK_WRITE(V0)
{
  int val = param.asInt();

  if ( led_timer_on_set[0] == 0 )
    led_set[0] = val;
  else
    update_blynk_status[0] = 1;
}
BLYNK_WRITE(VPIN_BUTTON_1) {
  toggleState_1 = param.asInt();
  digitalWrite(RelayPin1, !toggleState_1);
  pref.putBool("Relay1", toggleState_1);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  toggleState_2 = param.asInt();
  digitalWrite(RelayPin2, !toggleState_2);
  pref.putBool("Relay2", toggleState_2);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  toggleState_3 = param.asInt();
  digitalWrite(RelayPin3, !toggleState_3);
  pref.putBool("Relay3", toggleState_3);
}

BLYNK_WRITE(VPIN_BUTTON_4) {
  toggleState_4 = param.asInt();
  digitalWrite(RelayPin4, !toggleState_4);
  pref.putBool("Relay4", toggleState_4);
}



BLYNK_WRITE(VPIN_BUTTON_C) {
  all_SwitchOff();
}


BLYNK_WRITE(V7) 
{
unsigned char week_day;
 
  TimeInputParam t(param);

  if (t.hasStartTime() && t.hasStopTime() ) 
  {
    timer_start_set[1] = (t.getStartHour() * 60 * 60) + (t.getStartMinute() * 60) + t.getStartSecond();
    timer_stop_set[1] = (t.getStopHour() * 60 * 60) + (t.getStopMinute() * 60) + t.getStopSecond();
    hour_start = t.getStartHour();
    minute_start = t.getStartMinute();
    second_start = t.getStartSecond();

 
    hour_end = t.getStopHour();
    minute_end = t.getStopMinute();
    second_end = t.getStopSecond();
    
    Serial.println(String("Start Time: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
                   
    Serial.println(String("Stop Time: ") +
                   t.getStopHour() + ":" +
                   t.getStopMinute() + ":" +
                   t.getStopSecond());
                   
    for (int i = 1; i <= 7; i++) 
    {
      if (t.isWeekdaySelected(i)) 
      {
        week_day |= (0x01 << (i-1));
        Serial.println(String("Day ") + i + " is selected");
      }
      else
      {
        week_day &= (~(0x01 << (i-1)));
      }
    } 

    weekday_set[1] = week_day;
  }
  else
  {
    
    timer_start_set[1] = 0xFFFF;
    timer_stop_set[1] = 0xFFFF;

    hour_start = 0xFFFF;
    minute_start = 0xFFFF;
    second_start = 0xFFFF;

    hour_end = 0xFFFF;
    minute_end = 0xFFFF;
    second_end = 0xFFFF;
  }
}
void manual_control()
{float t = dht.readTemperature();
  if (t > 30 && toggleState_1 == HIGH) {
    digitalWrite(RelayPin1, HIGH);
    toggleState_1 = LOW;
    pref.putBool("Relay1", toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  }
  else if (t <= 28 && toggleState_1 == LOW) {
    digitalWrite(RelayPin1, LOW);
    toggleState_1 = HIGH;
    pref.putBool("Relay1", toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
    }
  float h = dht.readHumidity();
  if (h < 50 && toggleState_2  == HIGH) {
    digitalWrite(RelayPin2, HIGH);
    toggleState_2 = LOW;
    pref.putBool("Relay2", toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  }
  else if (h > 55 && toggleState_2 == LOW) {
    digitalWrite(RelayPin2, LOW);
    toggleState_2 = HIGH;
    pref.putBool("Relay2", toggleState_2);
    Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
    }
  if (lux < 500 && toggleState_3  == LOW) {
    digitalWrite(RelayPin3, LOW);
    toggleState_3 = HIGH;
    pref.putBool("Relay3", toggleState_1);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  }
  else if (lux >= 500  && toggleState_3 == HIGH) {
    digitalWrite(RelayPin3, HIGH);
    toggleState_3 = LOW;
    pref.putBool("Relay3", toggleState_3);
    Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
    }
}

BLYNK_WRITE(InternalPinRTC) 
{
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013
  unsigned long blynkTime = param.asLong(); 
  // if (timer_start_set[1] == 0xFFFF || timer_stop_set[1] == 0xFFFF){
  //   Serial.println("Time not set..");

  if (hour_start == 0xFFFF || hour_end == 0xFFFF){
     Serial.println("Time not set..");
    //  digitalWrite(RelayPin4, LOW);
  }else{
    
    if (blynkTime >= DEFAULT_TIME) 
    {
      setTime(blynkTime);

      day_of_week = weekday();
    
      if ( day_of_week == 1 )
        day_of_week = 7;
      else
        day_of_week -= 1; 
      
      rtc_sec = (hour()*60*60) + (minute()*60) + second();
      int start_sec = (hour_start*60*60) + (minute_start*60) + second_start;
      int end_sec = (hour_end*60*60) + (minute_end*60) + second_end;

      if (rtc_sec >= start_sec && rtc_sec <= end_sec){
        digitalWrite(RelayPin4, HIGH);
        toggleState_4 = LOW;
        pref.putBool("Relay4", toggleState_4);
        Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
      }else{
        digitalWrite(RelayPin4, LOW);
        toggleState_4 = HIGH;
        pref.putBool("Relay4", toggleState_4);
        Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
      }
    
      // Serial.println(blynkTime);
      Serial.println("Time start: " + String(hour_start) + ":" + String(minute_start) + ":" + String(second_start));
      Serial.println("Time end: " + String(hour_end) + ":" + String(minute_end) + ":" + String(second_end));
      Serial.println(String("RTC Server: ") + hour() + ":" + minute() + ":" + second());
      
      Serial.println(String("Day of Week: ") + weekday()); 
    }
    
  }
  
}

void checkBlynkStatus() { // called every 3 seconds by SimpleTimer

  bool isconnected = Blynk.connected();
  if (isconnected == false) {
    wifiFlag = 1;
    digitalWrite(wifiLed, LOW);
    Serial.println("Blynk Not Connected");
  }
  if (isconnected == true) {
    wifiFlag = 0;
    digitalWrite(wifiLed, HIGH);
    // Serial.println("Blynk Connected");
  }
}

BLYNK_CONNECTED() {
  // update the latest state to the server
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5);
  Blynk.syncVirtual(VPIN_TEMPERATURE);
  Blynk.syncVirtual(VPIN_HUMIDITY);
  Blynk.syncVirtual(VPIN_LDR);
  Blynk.syncVirtual(V7);
  Blynk.syncVirtual(V5);
  Blynk.syncVirtual(V9);
  Blynk.sendInternal("rtc", "sync"); 
}

void checkTime() 
{
  Blynk.sendInternal("rtc", "sync"); 
}

void led_mng()
{
  bool time_set_overflow;
  bool led_status_buf[2];
  
  for (int i=0; i<2; i++)
  {
    led_status_buf[i] = led_status[i];
    time_set_overflow = 0;
    
    if ( timer_start_set[i] != 0xFFFF && timer_stop_set[i] != 0xFFFF)
    {
      if ( timer_stop_set[i] < timer_start_set[i] ) time_set_overflow = 1;

      if ((((time_set_overflow == 0 && (rtc_sec >= timer_start_set[i]) && (rtc_sec < timer_stop_set[i])) ||
        (time_set_overflow  && ((rtc_sec >= timer_start_set[i]) || (rtc_sec < timer_stop_set[i])))) && 
        (weekday_set[i] == 0x00 || (weekday_set[i] & (0x01 << (day_of_week - 1) )))) )
        {
          led_timer_on_set[i] = 1;
        }
        else
          led_timer_on_set[i] = 0;
    }
    else
      led_timer_on_set[i] = 0;

    if ( led_timer_on_set[i] )
    {
      led_status[i] = 1;
      led_set[i] = 0;
    }
    else
    {
      led_status[i] = led_set[i];
    }

    if ( led_status_buf[i] != led_status[i] )
      update_blynk_status[i] = 1;  
  }
    // HARDWARE CONTROL
  // digitalWrite(D0, led_status[0]);  
  // digitalWrite(D1, led_status[1]);  
}

void readSensor() {
  lux = LightSensor.GetLightIntensity();
  Serial.print("Lux - "); Serial.println(lux);
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  else {
    humidity1 = h;
    temperature1 = t;
    Serial.print("Temperature - "); Serial.println(t);
    Serial.print("Humidity - "); Serial.println(h);
  }
}


void sendSensor()
{
  readSensor();
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  Blynk.virtualWrite(VPIN_LDR, lux);
 
}



void all_SwitchOff() {
  toggleState_1 = 0; digitalWrite(RelayPin1, LOW); pref.putBool("Relay1", toggleState_1); Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1); delay(100);
  toggleState_2 = 0; digitalWrite(RelayPin2, LOW); pref.putBool("Relay2", toggleState_2); Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2); delay(100);
  toggleState_3 = 0; digitalWrite(RelayPin3, LOW); pref.putBool("Relay3", toggleState_3); Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3); delay(100);
  toggleState_4 = 0; digitalWrite(RelayPin4, LOW); pref.putBool("Relay4", toggleState_4); Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4); delay(100);
  toggleState_5 = 0; pref.putBool("Relay5", toggleState_5); Blynk.virtualWrite(VPIN_BUTTON_5, toggleState_5); delay(100);
  Blynk.virtualWrite(VPIN_TEMPERATURE, temperature1);
  Blynk.virtualWrite(VPIN_HUMIDITY, humidity1);
  Blynk.virtualWrite(VPIN_LDR, lux);
}

void getRelayState()
{
  //Serial.println("reading data from NVS");
  toggleState_1 = pref.getBool("Relay1", 0);
  digitalWrite(RelayPin1, !toggleState_1);
  Blynk.virtualWrite(VPIN_BUTTON_1, toggleState_1);
  delay(200);
  toggleState_2 = pref.getBool("Relay2", 0);
  digitalWrite(RelayPin2, !toggleState_2);
  Blynk.virtualWrite(VPIN_BUTTON_2, toggleState_2);
  delay(200);
  toggleState_3 = pref.getBool("Relay3", 0);
  digitalWrite(RelayPin3, !toggleState_3);
  Blynk.virtualWrite(VPIN_BUTTON_3, toggleState_3);
  delay(200);
  toggleState_4 = pref.getBool("Relay4", 0);
  digitalWrite(RelayPin4, !toggleState_4);
  Blynk.virtualWrite(VPIN_BUTTON_4, toggleState_4);
  delay(200);
  
}
void setup()
{
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  Serial.begin(115200);;
  //Open namespace in read-write mode
  pref.begin("Relay_State", false);
  LightSensor.begin();
  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);


  //During Starting all Relays should TURN OFF
  digitalWrite(RelayPin1, !toggleState_1);
  digitalWrite(RelayPin2, !toggleState_2);
  digitalWrite(RelayPin3, !toggleState_3);
  digitalWrite(RelayPin4, !toggleState_4);

  digitalWrite(wifiLed, LOW);

  dht.begin();    // Enabling DHT sensor

  //WiFi.begin(ssid, pass);
  timer.setInterval(2000L, checkBlynkStatus); // check if Blynk server is connected every 2 seconds
  timer.setInterval(1000L, sendSensor); // Sending Sensor Data to Blynk Cloud every 1 second
  timer.setInterval(1000L, checkTime);
  Blynk.config(auth);
  delay(1000);

  getRelayState(); //fetch data from NVS Flash Memory
  //  delay(1000);


  
}

void loop()
{
  if (timerValue > 0)
  {
    delay(timerValue * 1000); // convert timer value to milliseconds and wait that amount of time
    timerValue = 0; // reset the timer value
    Blynk.virtualWrite(V7, 0); // update the timer widget on the app to show the timer has expired
  }
  Blynk.run();
  timer.run(); // Initiates SimpleTimer
  manual_control();
}

