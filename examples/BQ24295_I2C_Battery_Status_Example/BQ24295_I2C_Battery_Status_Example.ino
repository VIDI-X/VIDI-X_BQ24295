#include "VIDI-X_BQ24295.h"

// Defining I2C pins for the VIDI X microcomputer
// It may be necessary to adjust the I2C pins depending on your ESP32 module
#define I2C_SDA 33
#define I2C_SCL 32

// Initializing the BQ24295 IC object
BQ24295_IC bq24295(I2C_SDA, I2C_SCL, 400000); // SDA, SCL, and I2C speed in Hz

unsigned long previousMillis = 0;        // Stores the time of the last call to BattVoltageTest
const long interval = 5 * 60 * 1000;     // Interval between tests (5 minutes in milliseconds)

void setup() {
  Serial.begin(115200);  // Open serial communication at 115200 bps
  delay(1000);           // Short pause for stabilization

  Serial.println("Initializing BQ24295...");
  
  // You can add any initialization or configuration here if necessary
  BattVoltageTest();
}

void BattStatt() {
  Serial.print("Current charge voltage limit: ");
  Serial.println(bq24295.getChargeVoltageLimit());
  Serial.println(bq24295.getChargeVoltageLimitStr());

  Serial.print("Current low battery voltage: ");
  Serial.println(bq24295.getBatteryLowVoltage());
  Serial.println(bq24295.getBatteryLowVoltageStr());

  // Reading and printing Boost Voltage
  String boostVoltageStr = bq24295.getBoostVoltageStr();
  Serial.println(boostVoltageStr);

  // Reading and printing BHOT setting
  String bHotStr = bq24295.getBHotStr();
  Serial.println(bHotStr);

  // Reading and printing the thermal threshold
  String thermalRegulationThresholdStr = bq24295.getThermalRegulationThresholdStr();
  Serial.println(thermalRegulationThresholdStr);

  String inputCurrentLimitStr = bq24295.getInputCurrentLimitStr();
  Serial.println(inputCurrentLimitStr);
}

void BattVoltageTest() {
  float testVoltage = 4.2; // Starting voltage for testing
  float decrement = -0.1;  // Voltage decrement step
  
  Serial.println("Starting battery voltage test...");

  while (testVoltage >= 3.5) { 
    bq24295.setChargeVoltageLimit(convertVoltageToReg(testVoltage));
    delay(1000); 
    String status = bq24295.getStatus();

    if (status.indexOf("Not Charging") >= 0 || status.indexOf("Charge Termination Done") >= 0) {
      Serial.print("Battery stopped charging below voltage: ");
      Serial.println(testVoltage);
      break;
    }

    testVoltage += decrement; 
  }

  // Set charging voltage back to a safe 4.2V to continue charging
  bq24295.setChargeVoltageLimit(convertVoltageToReg(4.2));
  Serial.println("Continuing charging at 4.2V.");
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Saves the current time as the last test time
    previousMillis = currentMillis;

    // Calls the BattVoltageTest function to measure battery voltage
    BattVoltageTest();
  }

  // You can add the rest of the code that needs to run continuously here
}

uint8_t convertVoltageToReg(float voltage) {
  // Check if voltage boundaries are within the allowed range
  if (voltage < 3.504) voltage = 3.504;
  if (voltage > 4.4) voltage = 4.4;

  // Subtract the base voltage to get the addition
  float voltageOffset = voltage - 3.504;

  // Convert the addition into a register value
  // Reverse engineering is needed here as per the specification steps
  uint8_t regValue = 0;
  regValue |= (voltageOffset >= 0.512) ? (1 << 5) : 0;
  voltageOffset -= (regValue & (1 << 5)) ? 0.512 : 0;

  regValue |= (voltageOffset >= 0.256) ? (1 << 4) : 0;
  voltageOffset -= (regValue & (1 << 4)) ? 0.256 : 0;

  regValue |= (voltageOffset >= 0.128) ? (1 << 3) : 0;
  voltageOffset -= (regValue & (1 << 3)) ? 0.128 : 0;

  regValue |= (voltageOffset >= 0.064) ? (1 << 2) : 0;
  voltageOffset -= (regValue & (1 << 2)) ? 0.064 : 0;

  regValue |= (voltageOffset >= 0.032) ? (1 << 1) : 0;
  voltageOffset -= (regValue & (1 << 1)) ? 0.032 : 0;

  regValue |= (voltageOffset >= 0.016) ? 1 : 0;

  return regValue;
}
