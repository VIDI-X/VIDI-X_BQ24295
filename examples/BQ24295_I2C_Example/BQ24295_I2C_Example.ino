#include "VIDI-X_BQ24295.h"

// Defining I2C pins for the VIDI X microcomputer
// It may be necessary to adjust the I2C pins depending on your ESP32 module
#define I2C_SDA 33
#define I2C_SCL 32

// Initializing the BQ24295 IC object
BQ24295_IC bq24295(I2C_SDA, I2C_SCL, 400000); // SDA, SCL, and I2C speed in Hz

void setup() {
  Serial.begin(115200);  // Open serial communication at 115200 bps
  delay(1000);           // Short pause for stabilization

  Serial.println("Initializing BQ24295...");

  Serial.print("Current charge voltage limit: ");
  Serial.println(bq24295.getChargeVoltageLimit());
  Serial.println(bq24295.getChargeVoltageLimitStr());

  Serial.print("Current battery low voltage: ");
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

  // Reading and printing the battery status
  String status = bq24295.getStatus();
  Serial.println("Battery status: " + status);

  // Reading and printing fault information
  String faults = bq24295.getFaults();
  Serial.println("Faults: " + faults);
}

void loop() {

}
