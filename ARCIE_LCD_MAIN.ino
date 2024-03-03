/*
  ARDUINO CONTROLLED INDEPENDENT ECOSYSTEM

  CODE: Reads soil moisture levels, humiidty levels, temperature in F
  OUTPUT: LCD DISPLAY

  TEAM 8 MEMBERS: Alex Benson, Isa Fontana, Macy Green
*/

// -------------------------------------
// LIBRARIES AND DEFINITIONS
#include <dht.h>                // humidity and temp
#include <LiquidCrystal.h>      // LCD Library

// change these values based on calibration
#define soilWet 500   // define max value we consider soil 'wet'
#define soilDry 750   // define min value we consider soil 'dry'

// sensor pins
#define sensorPower 8 // soil, digital out
#define sensorPin A0 // soil, analog in
#define DHT11_PIN 7 // humidity, temperature, digital out

dht DHT; // DHT11 module definituion

int Contrast = 75; // CONTRAST, CIRCUIT w/o POTENTIOMETER
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LCD PINS
// -------------------------------------


void setup() {
	pinMode(sensorPower, OUTPUT);
	digitalWrite(sensorPower, LOW);   // initially keep the sensor OFF

  analogWrite(6,Contrast); // LCD CONTRAST
  lcd.begin(16, 2);       // (columns, rows)
	
	Serial.begin(9600);
}

void loop() {
  // VARIABLES
  unsigned long currentMillis = millis(); // get current time in milliseconds
  int moisture = -1; // initializes moisture vairables
  unsigned long soilInterval = 1000; // takes reading every 8 hours, use 1000 for testing. 8 * 60 * 60 * 
  static unsigned long lastSoilTime = 0;

  // ---------SOIL---------
  if (currentMillis - lastSoilTime >= soilInterval) {
    lastSoilTime = currentMillis;
    moisture = readSensor();

    lcd.clear();
    lcd.setCursor(0, 0); // top left

    // determine status of our soil
    if (moisture < soilWet) {
      lcd.print("Soil: Good  ");
    } else if (moisture >= soilWet && moisture < soilDry) { // ANALOG OUTPUT, refer to calibration def to know what this means
      lcd.print("Soil: Too Wet  ");
    } else {
      lcd.print("Soil: Too Dry  ");
    }
    delay(3000); // wait for the next display
  }
	//----------------------

  // ----------HUMIDITY-&-TEMP----------
  int chk = DHT.read11(DHT11_PIN);
  float temperature = DHT.temperature;
  temperature = (temperature * (9/5)) + 32;
  float humidity = DHT.humidity;
  
  // Display humidity and temperature on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(char(223));
  lcd.print("F");

  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(humidity);
  lcd.print("%   ");
  delay(3000);
  //------------------------------------
  }     // end void setup look

// ------------FUNCTIONS------------
//  READ SENSOR FUNCTION returns the analog soil moisture measurement
int readSensor() {
	digitalWrite(sensorPower, HIGH);  // turn the sensor ON
	delay(10);                        // allow power to settle
	int val = analogRead(sensorPin);	// read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// turn the sensor OFF
	return val;							          // return analog moisture value
}
// ---------------------------------