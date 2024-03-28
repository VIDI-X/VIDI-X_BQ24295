# VIDI-X_BQ24295 Arduino library

| ![VIDI-X_BQ24295](https://soldered.com/productdata/2022/03/DSC_3449-Edit.jpg) |
| :------------------------------------------------------------------------------------: |
|                      VIDI-X_BQ24295 is Arduino library for [Li-ion-charger-BQ24295-with-5V-USB-output-board-hardware-design](https://github.com/SolderedElectronics/Li-ion-charger-BQ24295-with-5V-USB-output-board-hardware-design)                      |

## Upgrades and Improvements

The VIDI X Team, with the assistance of advanced artificial intelligence techniques, has significantly enhanced this library by adding new functionalities, improving the existing code, and optimizing performance for a better user experience and greater efficiency. Our upgrades include the introduction of comprehensive getter methods for critical battery charging parameters, enhancing the library's capability for real-time monitoring and control. Notably, we've added functionalities to accurately read and interpret the charge voltage limit, battery low voltage threshold, boost voltage settings, battery temperature thresholds (BHOT), and the input current limit. These enhancements allow for precise control over the charging process, tailored adjustments based on battery conditions, and more informed decision-making in energy management systems. The newly integrated features, such as detailed string representations of these parameters, provide users with straightforward, human-readable insights into the battery's charging state and health. This extension of the library, achieved with the VIDI X Team's expertise and AI assistance, greatly broadens its application scope, making it an invaluable tool for developers working on sophisticated battery-powered projects.

### Repository Contents

- **/src** - source files for the library (.h & .cpp)
- **/examples** - examples for using the library
- **/doc** - hardware design for BQ24295 board.
- **_other_** - _keywords_ file highlights function words in your IDE, _library.properties_ enables implementation with Arduino Library Manager.

### Hardware design

You can find hardware design for BQ24295 board in [Li-ion-charger-BQ24295-with-5V-USB-output-board-hardware-design](https://github.com/SolderedElectronics/Li-ion-charger-BQ24295-with-5V-USB-output-board-hardware-design) hardware repository.

### Documentation

- Datasheet for the BQ24295 board is [here](https://soldered.com/productdata/2022/03/Soldered_bq24295_datasheet.pdf)

The BQ24295 is a versatile Li-ion battery charger designed to provide efficient and reliable charging for single-cell lithium-ion or lithium-polymer batteries. It supports various charging modes, including constant current (CC) and constant voltage (CV) charging, to ensure the battery is charged quickly and safely.
The BQ24295 charger operates on a wide input voltage range, typically from 4.35V to 17V, allowing it to be powered by a variety of power sources, including USB ports and AC adapters. It also features integrated power path management, which allows simultaneous charging of the battery while powering the connected device, providing uninterrupted operation.

- Installing an Arduino library

Access Arduino library documentation [here](https://docs.arduino.cc/software/ide-v1/tutorials/installing-libraries/) or [here](https://docs.arduino.cc/software/ide-v2/tutorials/ide-v2-installing-a-library/).

### Board compatibility

The library is compatible with ESP32 board & microcontroller families with I2C.

### About VIDI-X

VIDI Project X is a developing microcomputer, completely designed, and developed in Croatia. It is powered by a powerful ESP32 processor, contains two cores and a TFT touchscreen. VIDI X is equipped with a few interesting sensors and a special port that allows additional expansion of functionality. The possibilities for usage of VIDI X microcomputer are endless. It is possible to attach additional sensors and use them to control complex systems like a smart house or classroom. Its Wi-Fi and BT communication properties are used to connect other external systems.
- 👀 If You’re interested in VIDI Project X visit the link [https://vidi-x.org](https://vidi-x.org/)

![Vidi Project X microcomputer](https://vidilab.com/media/k2/items/cache/679aa550c461b354cef4c5f72fe8c7ab_XL.jpg)

### Original source

This library is possible thanks to original [Arduino_BQ24295](https://github.com/daumemo/Arduino_BQ24295) library. Thank you, daumemo.

### License

Check license details in the LICENSE file. Long story short, use these open-source files for any purpose you want to, as long as you apply the same open-source licence to it and disclose the original source. No warranty - all files in this repository are distributed in the hope that they will be useful, but without any warranty. They are provided "AS IS", therefore without warranty of any kind, either expressed or implied. The entire quality and performance of what you do with the contents of this repository are your responsibility. In no event, VIDI-TO d.o.o. will be liable for your damages, losses, including any general, special, incidental or consequential damage arising out of the use or inability to use the contents of this repository.

## Have fun!
