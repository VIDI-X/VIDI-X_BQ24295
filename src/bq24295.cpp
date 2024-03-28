/**
 * # BQ24295 v.1.1 (Updated Version)
 *
 * This library was originally developed by daumemo.com 
 * (https://github.com/daumemo/Arduino_BQ24295) and is based on the work with 
 * the BQ24295 charging management chip by Texas Instruments, used alongside 
 * the VIDI X microcomputer, https://vidi-x.org (based on ESP32), with the 
 * Arduino and I2C library.
 *
 * ## Upgrades and Improvements
 *
 * The VIDI X Team, with the assistance of advanced artificial intelligence 
 * techniques, has significantly enhanced this library by adding new 
 * functionalities, improving the existing code, and optimizing performance 
 * for a better user experience and greater efficiency. Our upgrades include 
 * the introduction of comprehensive getter methods for critical battery 
 * charging parameters, enhancing the library's capability for real-time 
 * monitoring and control. Notably, we've added functionalities to accurately 
 * read and interpret the charge voltage limit, battery low voltage threshold, 
 * boost voltage settings, battery temperature thresholds (BHOT), and the input 
 * current limit. These enhancements allow for precise control over the 
 * charging process, tailored adjustments based on battery conditions, and more 
 * informed decision-making in energy management systems. The newly integrated 
 * features, such as detailed string representations of these parameters, 
 * provide users with straightforward, human-readable insights into the 
 * battery's charging state and health. This extension of the library, 
 * achieved with the VIDI X Team's expertise and AI assistance, greatly 
 * broadens its application scope, making it an invaluable tool for developers 
 * working on sophisticated battery-powered projects.
 *
 * We extend our gratitude to daumemo.com for laying the foundation that 
 * inspired us towards further innovations.
 *
 * ## License
 *
 * This project continues to be licensed under the GNU Lesser General Public 
 * License (LGPL) to ensure free use, distribution, and modification of the 
 * code with the obligation to share changes under the same conditions. 
 * Considering the newly introduced upgrades and modifications, we recommend 
 * using LGPL version 3 or later to ensure greater compatibility with modern 
 * software standards and better protection of both users' and authors' 
 * freedoms.
 *
 * This license change aims to better align with the latest practices in the 
 * software industry, ensuring that all modifications and improvements are 
 * clearly documented and shared in the spirit of open source. LGPL version 3 
 * provides more detailed guidelines on patents and tivo-compatible version, 
 * thus offering additional security and clarity for all users and contributors.
 *
 * For more information about LGPL v3 and the differences from previous 
 * versions, please visit [GNU's official page]
 * (https://www.gnu.org/licenses/lgpl-3.0.html).
 *
 * ---
 * *This text has been generated with the help of AI artificial intelligence to 
 * promote innovation and knowledge sharing within the community.*
 */

#include "bq24295.h"
#include <Wire.h>

#define BQ24295_I2C_ADD 0x6B
#define BQ24295_WATCHDOG_FAULT "Watchdog timer expiration. "
#define BQ24295_OTG_FAULT "VBUS overloaded in OTG, or VBUS OVP, or battery is too low. "
#define BQ24295_CHRG_FAULT_01 "Input fault (OVP or bad source). "
#define BQ24295_CHRG_FAULT_10 "Thermal shutdown. "
#define BQ24295_CHRG_FAULT_11 "Charge Timer Expiration. "
#define BQ24295_BAT_FAULT "Battery OVP. "
#define BQ24295_NTC_FAULT_1 "NTC Cold. "
#define BQ24295_NTC_FAULT_0 "NTC Hot. "

#define BQ24295_VBUS_STAT_00 "Unknown (no input, or DPDM detection incomplete). "
#define BQ24295_VBUS_STAT_01 "USB host. "
#define BQ24295_VBUS_STAT_10 "Adapter port. "
#define BQ24295_VBUS_STAT_11 "OTG. "
#define BQ24295_CHRG_STAT_00 "Not Charging. "
#define BQ24295_CHRG_STAT_01 "Pre-charge. "
#define BQ24295_CHRG_STAT_10 "Fast Charging. "
#define BQ24295_CHRG_STAT_11 "Charge Termination Done. "
#define BQ24295_DPM_STAT_0 "No DPM. "
#define BQ24295_DPM_STAT_1 "VINDPM or IINDPM. "
#define BQ24295_PG_STAT_0 "Not Power Good. "
#define BQ24295_PG_STAT_1 "Power Good. "
#define BQ24295_THERM_STAT_0 "Thermals Are Normal. "
#define BQ24295_THERM_STAT_1 "In Thermal Regulation. "
#define BQ24295_VSYS_STAT_0 "Not in VSYSMIN regulation. "
#define BQ24295_VSYS_STAT_1 "In VSYSMIN regulation. "

BQ24295_IC::BQ24295_IC(int i2c_sda, int i2c_sck, int clockSpeed){
    Wire.begin(i2c_sda, i2c_sck);
    Wire.setClock(clockSpeed);
}

uint8_t BQ24295_IC::getRegister(uint8_t registerToRead){
    uint8_t data = 0;
    Wire.beginTransmission(BQ24295_I2C_ADD);
    Wire.write(registerToRead);
    Wire.endTransmission();
    Wire.requestFrom(BQ24295_I2C_ADD, 1);
    if (Wire.available())
    {
        data = (uint8_t)Wire.read();
    }
    return data;
}

void BQ24295_IC::setRegister(uint8_t valueToWrite, uint8_t registerToWrite){
    Wire.beginTransmission(BQ24295_I2C_ADD);
    Wire.write(registerToWrite);
    Wire.write(valueToWrite);
    Wire.endTransmission();
}

String BQ24295_IC::getPartNumber(){
    uint8_t reg = getRegister(0x0A);
    reg = reg>>5;
    if(reg == 0b110) return "bq24295";
    else return "unknown";
}

uint8_t BQ24295_IC::getRevisionNumber(){
    uint8_t reg = getRegister(0x0A);
    return (reg & 0b111);
}

String BQ24295_IC::getFaults(){
    uint8_t reg = getRegister(0x09);
    String val = "";
    if (reg & (1<<7)) val += BQ24295_WATCHDOG_FAULT;
    if (reg & (1<<6)) val += BQ24295_OTG_FAULT;
    if (reg & 0b00110000){
        uint8_t twobit = (reg & 0b00110000) >> 4;
        if (twobit == 0b01) val += BQ24295_CHRG_FAULT_01;
        else if (twobit == 0b10) val += BQ24295_CHRG_FAULT_10;
        else val += BQ24295_CHRG_FAULT_11;
    }
    if (reg & (1<<3)) val += BQ24295_BAT_FAULT;
    if (reg & (1<<1)) val += BQ24295_NTC_FAULT_1;
    if (reg & 1) val += BQ24295_NTC_FAULT_0;

    if (val == "") val = "No Faults";

    return val;
}

String BQ24295_IC::getStatus(){
    uint8_t reg = getRegister(0x08);
    String val = "";
    uint8_t stat = (reg & 0b11000000) >> 6;
    if (stat == 0b11) val += BQ24295_VBUS_STAT_11;
    else if (stat == 0b10) val += BQ24295_VBUS_STAT_10;
    else if (stat == 0b01) val += BQ24295_VBUS_STAT_01;
    else val += BQ24295_VBUS_STAT_00;

    stat = (reg & 0b00110000) >> 4;
    if (stat == 0b11) val += BQ24295_CHRG_STAT_11;
    else if (stat == 0b10) val += BQ24295_CHRG_STAT_10;
    else if (stat == 0b01) val += BQ24295_CHRG_STAT_01;
    else val += BQ24295_CHRG_STAT_00;

    if (reg & (1<<3)) val += BQ24295_DPM_STAT_1;
    else val += BQ24295_DPM_STAT_0;

    if (reg & (1<<2)) val += BQ24295_PG_STAT_1;
    else val += BQ24295_PG_STAT_0;

    if (reg & (1<<1)) val += BQ24295_THERM_STAT_1;
    else val += BQ24295_THERM_STAT_0;

    if (reg & 1) val += BQ24295_VSYS_STAT_1;
    else val += BQ24295_VSYS_STAT_0;

    return val;

}

String BQ24295_IC::getStatus(uint8_t bitIndex){
    uint8_t reg = getRegister(0x08);
    String val = "";

    if (bitIndex < 4){
        if (bitIndex == 0){
            if (reg & 1) val += BQ24295_VSYS_STAT_1;
            else val += BQ24295_VSYS_STAT_0;
        }
        else if (bitIndex == 1){
            if (reg & (1<<1)) val += BQ24295_THERM_STAT_1;
            else val += BQ24295_THERM_STAT_0;
        }
        else if (bitIndex == 2){
            if (reg & (1<<2)) val += BQ24295_PG_STAT_1;
            else val += BQ24295_PG_STAT_0;
        }
        else {
            if (reg & (1<<3)) val += BQ24295_DPM_STAT_1;
            else val += BQ24295_DPM_STAT_0;
        }
    }
    else if (bitIndex == 4){
        uint8_t stat = (reg & 0b00110000) >> 4;
        if (stat == 0b11) val += BQ24295_CHRG_STAT_11;
        else if (stat == 0b10) val += BQ24295_CHRG_STAT_10;
        else if (stat == 0b01) val += BQ24295_CHRG_STAT_01;
        else val += BQ24295_CHRG_STAT_00;
    }
    else if (bitIndex == 5){
        uint8_t stat = (reg & 0b11000000) >> 6;
        if (stat == 0b11) val += BQ24295_VBUS_STAT_11;
        else if (stat == 0b10) val += BQ24295_VBUS_STAT_10;
        else if (stat == 0b01) val += BQ24295_VBUS_STAT_01;
        else val += BQ24295_VBUS_STAT_00;
    }
    else return "invalid bitIndex value";
}

void BQ24295_IC::forceInputSourceDetect(){
    uint8_t reg = getRegister(0x07);
    reg |= 0b10000000;
    setRegister(reg, 0x07);
}

void BQ24295_IC::setSlowSafetyTimer(bool value){
    uint8_t reg = getRegister(0x07);
    reg &=~ (1<<6);
    if (value) reg |= (1<<6);
    setRegister(reg, 0x07);
}

void BQ24295_IC::disableBatfet(bool value){
    uint8_t reg = getRegister(0x07);
    reg &=~ (1<<5);
    if (value) reg |= (1<<5);
    setRegister(reg, 0x07);
}

void BQ24295_IC::setInterrupts(bool chrg_fault, bool bat_fault){
    uint8_t reg = getRegister(0x07);
    reg &=~ 0b11;
    if (chrg_fault) reg |= (1<<1);
    if (bat_fault) reg |= 1;
    setRegister(reg, 0x07);
}

void BQ24295_IC::setBoostVoltage(uint8_t value){
    uint8_t reg = getRegister(0x06);
    reg &= 0b00001111;
    reg |= ((value & 0b1111) << 4);
    setRegister(reg, 0x06);
}

void BQ24295_IC::setBHot(uint8_t value){
    uint8_t reg = getRegister(0x06);
    reg &= 0b11110011;
    reg |= ((value & 0b11) << 2);
    setRegister(reg, 0x06);
}

void BQ24295_IC::setThermalRegulationThreshold(uint8_t value){
    uint8_t reg = getRegister(0x06);
    reg &= 0b11111100;
    reg |= (value & 0b11);
    setRegister(reg, 0x06);
}

void BQ24295_IC::enableChargeTermination(bool value){
    uint8_t reg = getRegister(0x05);
    reg &=~ (1<<7);
    if (value) reg |= (1<<7);
    setRegister(reg, 0x05);
}

void BQ24295_IC::setI2cWatchdogTimer(uint8_t value){
    uint8_t reg = getRegister(0x05);
    reg &= 0b11001111;
    reg |= ((value & 0b11) << 4);
    setRegister(reg, 0x05);
}

void BQ24295_IC::enableSafetyChargingTimer(bool value){
    uint8_t reg = getRegister(0x05);
    reg &=~ (1<<3);
    if (value) reg |= (1<<3);
    setRegister(reg, 0x05);
}

void BQ24295_IC::setFastChargeTimer(uint8_t value){
    uint8_t reg = getRegister(0x05);
    reg &= 0b11111001;
    reg |= ((value & 0b11) << 1);
    setRegister(reg, 0x05);
}

void BQ24295_IC::setChargeVoltageLimit(uint8_t value){
    uint8_t reg = getRegister(0x04);
    reg &= 0b00000011;
    reg |= ((value & 0b111111) << 2);
    setRegister(reg, 0x04);
}

void BQ24295_IC::setBatteryLowVoltage(uint8_t value){
    uint8_t reg = getRegister(0x04);
    reg &= 0b11111101;
    reg |= ((value & 0b1) << 1);
    setRegister(reg, 0x04);
}

void BQ24295_IC::setBattRechargeThreshold(uint8_t value){
    uint8_t reg = getRegister(0x04);
    reg &= 0b11111110;
    reg |= (value & 0b1);
    setRegister(reg, 0x04);
}

void BQ24295_IC::setPreChargeCurrent(uint8_t value){
    uint8_t reg = getRegister(0x03);
    reg &= 0b00001111;
    reg |= ((value & 0b1111) << 4);
    setRegister(reg, 0x03);
}

void BQ24295_IC::setTerminationCurrent(uint8_t value){
    uint8_t reg = getRegister(0x03);
    reg &= 0b11110000;
    reg |= (value & 0b1111);
    setRegister(reg, 0x03);
}

void BQ24295_IC::setFastChargeCurrent(uint8_t value){
    uint8_t reg = getRegister(0x02);
    reg &= 0b00000011;
    reg |= ((value & 0b111111) << 2);
    setRegister(reg, 0x02);
}

void BQ24295_IC::setBCold(uint8_t value){
    uint8_t reg = getRegister(0x02);
    reg &= 0b11111101;
    reg |= ((value & 0b1) << 1);
    setRegister(reg, 0x02);
}

void BQ24295_IC::force20pctCharge(uint8_t value){
    uint8_t reg = getRegister(0x02);
    reg &= 0b11111110;
    reg |= (value & 0b1);
    setRegister(reg, 0x02);
}

void BQ24295_IC::resetRegisters(){
    uint8_t reg = getRegister(0x01);
    reg |= (1<<7);
    setRegister(reg, 0x01);
    delay(50);
    reg = getRegister(0x01);
    reg &=~ (1<<7);
    setRegister(reg, 0x01);
}

void BQ24295_IC::resetI2cTimer(){
    uint8_t reg = getRegister(0x01);
    reg |= (1<<6);
    setRegister(reg, 0x01);
    delay(1);
}

void BQ24295_IC::enableOTG(bool value){
    uint8_t reg = getRegister(0x01);
    reg &=~ (1<<5);
    if (value) reg |= (1<<5);
    setRegister(reg, 0x01);
}

void BQ24295_IC::enableCharging(uint8_t value){
    uint8_t reg = getRegister(0x01);
    reg &=~ (1<<4);
    if (value) reg |= (1<<4);
    setRegister(reg, 0x01);
}

void BQ24295_IC::setMinimumSystemVoltage(uint8_t value){
    uint8_t reg = getRegister(0x01);
    reg &= 0b11110001;
    reg |= ((value & 0b111) << 1);
    setRegister(reg, 0x01);
}

void BQ24295_IC::enableLowPowerMode(bool value){
    uint8_t reg = getRegister(0x00);
    reg &=~ (1<<7);
    if (value) reg |= (1<<7);
    setRegister(reg, 0x00);
}

void BQ24295_IC::setInputVoltageLimit(uint8_t value){
    uint8_t reg = getRegister(0x00);
    reg &= 0b10000111;
    reg |= ((value & 0b1111) << 3);
    setRegister(reg, 0x00);
}

void BQ24295_IC::setInputCurrentLimit(uint8_t value){
    uint8_t reg = getRegister(0x00);
    reg &= 0b11111000;
    reg |= (value & 0b111);
    setRegister(reg, 0x00);
}

uint8_t BQ24295_IC::getChargeVoltageLimit(){
    uint8_t reg = getRegister(0x04);
    return (reg >> 2) & 0b111111; // Extracts 6 bits representing the charge voltage limit
}

uint8_t BQ24295_IC::getBatteryLowVoltage(){
    uint8_t reg = getRegister(0x04);
    return (reg >> 1) & 0b1; // Extracts the bit representing the battery's low voltage
}

String BQ24295_IC::getChargeVoltageLimitStr(){
    uint8_t reg = getRegister(0x04);
    uint8_t VREG = (reg >> 2) & 0b111111;
    float voltage = 3.504 + VREG * 0.016; // Calculates the voltage
    String str = "Reg = " + String(VREG) + " -> Charge Voltage: " + String(voltage, 3) + "V (3.504V + " + String(VREG) + " * 0.016V)";
    return str;
}

String BQ24295_IC::getBatteryLowVoltageStr(){
    uint8_t reg = getRegister(0x04);
    uint8_t VREG = (reg >> 1) & 0b1;
    float voltage = VREG == 0 ? 2.8 : 3.0; // Determines the voltage
    String str = "Reg = " + String(VREG) + " -> Battery Low Voltage: " + String(voltage, 1) + "V (" + (VREG == 0 ? "2.8V" : "3.0V") + ")";
    return str;
}

String BQ24295_IC::getBoostVoltageStr() {
    uint8_t reg = getRegister(0x06);
    uint8_t value = (reg >> 4) & 0xF; // Extracts 4 bits for boost voltage
    float voltage = 4.55 + (value * 0.064); // Calculates the voltage
    return "Reg = " + String(value, HEX) + " -> Boost Voltage: " + String(voltage, 2) + "V (4.55V + " + String(value) + " * 0.064V)";
}

String BQ24295_IC::getBHotStr() {
    uint8_t reg = getRegister(0x06);
    uint8_t value = (reg >> 2) & 0x3; // Extracts 2 bits for BHOT
    String temp = value == 0 ? "Vbhot0 1" : value == 1 ? "Vbhot1" : value == 2 ? "Vbhot2" : "Vbhot3";
    return "Reg = " + String(value, HEX) + " -> BHOT Temperature: " + temp;
}

String BQ24295_IC::getThermalRegulationThresholdStr() {
    uint8_t reg = getRegister(0x06);
    uint8_t value = reg & 0x3; // Extracts 2 bits for thermal threshold
    String temp;
    switch (value) {
        case 0: temp = "60°C"; break;
        case 1: temp = "80°C"; break;
        case 2: temp = "100°C"; break;
        case 3: temp = "120°C"; break;
        default: temp = "Unknown";
    }
    return "Reg = " + String(value, HEX) + " -> Thermal Threshold: " + temp;
}

uint8_t BQ24295_IC::getInputCurrentLimit(){
    uint8_t reg = getRegister(0x00);
    return reg & 0b111; // Extracts the current input limit setting
}

String BQ24295_IC::getInputCurrentLimitStr() {
    uint8_t inputCurrentSetting = getInputCurrentLimit(); 
    String description = "Current Input Limit: ";

    // Mapping of the setting to actual current values continues as previously provided.
    switch (inputCurrentSetting) {
        case 0b000: return description + "100mA (0b000)";
        case 0b001: return description + "150mA (0b001)";
        case 0b010: return description + "500mA (0b010)";
        case 0b011: return description + "900mA (0b011)";
        case 0b100: return description + "1A (0b100)";
        case 0b101: return description + "1.5A (0b101)";
        case 0b110: return description + "2A (0b110)";
        case 0b111: return description + "3A (0b111)";
        default: return description + "Unknown value";
    }
}
