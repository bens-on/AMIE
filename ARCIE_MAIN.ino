/*
  ARDUINO CONTROLLED INDEPENDENT ECOSYSTEM

  CODE: Reads soil moisture levels, humiidty levels, temperature in F
  OUTPUT: Currently routed to serial monitor, will be displayed on LCD module

  TEAM 8 MEMBERS: Alex Benson, Isa Fontana, Macy Green
*/

// -------------------------------------
// LIBRARIES AND DEFINITIONS
#include <dht.h>

// change these values based on calibration
#define soilWet 500   // define max value we consider soil 'wet'
#define soilDry 750   // define min value we consider soil 'dry'

// sensor pins
#define sensorPower 8 // soil, digital out
#define sensorPin A0 // soil, analog in
#define DHT11_PIN 7 // humidity, temperature, digital out

dht DHT; // DHT11 module definituion
// -------------------------------------


void setup() {
	pinMode(sensorPower, OUTPUT);
	
	// initially keep the sensor OFF
	digitalWrite(sensorPower, LOW);
	
	Serial.begin(9600);
}

void loop() {
  // VARIABLES
  unsigned long currentMillis = millis(); // get current time in milliseconds
  int moisture = -1; // initializes moisture vairables
  unsigned long soilInterval = 8 * 60 * 60 * 1000; // takes reading every 8 hours, use 1000 for testing.
  static unsigned long lastSoilTime = 0;

  // ---------SOIL---------
  if (currentMillis - lastSoilTime >= soilInterval) {
    lastSoilTime = currentMillis;
    moisture = readSensor();

    Serial.print("Soil Moisture: ");
    Serial.println(moisture); // ANALOG OUTPUT, refer to calibration def to know what this means

    // determine status of our soil
    if (moisture < soilWet) {
      Serial.println("TOO WET");
    } else if (moisture >= soilWet && moisture < soilDry) {
      Serial.println("GOOD SOIL");
    } else {
      Serial.println("TOO DRY");
    }
  }
	//----------------------

  // ----------HUMIDITY-&-TEMP----------
  int chk = DHT.read11(DHT11_PIN);
  static unsigned long lastTempTime = 0;

  if (currentMillis - lastTempTime >= (60 * 1000)) {
    lastTempTime = currentMillis;

    float temperature = DHT.temperature;
    temperature = (temperature * (9/5)) + 32; // converts to F
    float humidity = DHT.humidity;
    Serial.print("Temperature = ");
    Serial.println(temperature);
    Serial.print("Humidity = ");
    Serial.println(humidity);
    Serial.println(" %");
  }
  //------------------------------------
} // end void setup look

// ------------FUNCTIONS------------
//  READ SENSOR FUNCTION returns the analog soil moisture measurement
int readSensor() {
	digitalWrite(sensorPower, HIGH);	// turn the sensor ON
	delay(10);				// allow power to settle
	int val = analogRead(sensorPin);	// read the analog value form sensor
	digitalWrite(sensorPower, LOW);		// turn the sensor OFF
	return val;				// return analog moisture value
}
// ---------------------------------
