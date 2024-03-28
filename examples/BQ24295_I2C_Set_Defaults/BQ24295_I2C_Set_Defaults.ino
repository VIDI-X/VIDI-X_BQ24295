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

  // Print initialization message
  Serial.println("Initializing BQ24295...");

  // Reset the BQ24295 settings to factory defaults
  resetToFactoryDefaults();
}

void loop() {
  // This sketch does not perform any operation in the loop
  // It's intended to run the setup function once to reset settings
  delay(1000);  // Just keep the loop alive
}

void resetToFactoryDefaults() {
  // Reset all configurable settings to factory defaults
  
  // Set charge voltage limit to default (4.208V)
  bq24295.setChargeVoltageLimit(0b101100);
  
  // Set battery low voltage to default (3.0V)
  bq24295.setBatteryLowVoltage(1);
  
  // Set boost voltage to default (5.125V)
  bq24295.setBoostVoltage(0b1001);
  
  // Set thermal regulation threshold to default (120°C)
  bq24295.setThermalRegulationThreshold(0b11);
  
  // Set fast charge current limit to default (2048mA)
  bq24295.setFastChargeCurrent(0b110000);
  
  // Other settings can be added here based on specific project requirements
  
  Serial.println("Charging settings reset to factory defaults.");
}