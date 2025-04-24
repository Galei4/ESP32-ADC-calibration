# LinarADC Library

## Overview

The `LinarADC` library is designed to handle Analog-to-Digital Converter (ADC) operations on the ESP32 microcontroller. It provides functionalities for performing raw ADC readings, optional calibration, and saving the calibration results to different file formats (`.txt`, `.json`, `.bin`). The library also includes utilities for LED status indication, calibration, and storing processed data for further analysis.

## Key Features

- **Raw and Calibrated ADC Readings**: Perform raw ADC readings or use calibrated values based on the configuration.
- **Calibration Results Storage**: Save calibration results to SPIFFS (SPI Flash File System) in various formats for later use.
- **LED Indication**: Configurable LED pins for visual feedback during operations.
- **File Handling**: Supports reading and writing calibration data in `.txt`, `.json`, and `.bin` formats.
- **Linearization**: Generates a Look-Up Table (LUT) for linearizing ADC readings.

## Usage

### Initialization

To use the `LinarADC` class, you need to initialize it with the ADC pin, LED pins, and file details.

```cpp
LinarADC adc(34, ".bin", 2, 4, "CalibrationResults");
```

- `34`: ADC pin used for calibration.
- `".bin"`: File type for saving calibration results.
- `2`: Pin number for the first LED (green).
- `4`: Pin number for the second LED (red).
- `"CalibrationResults"`: Base name for the calibration file.

### Saving Calibration Data

To perform calibration and save the results:

```cpp
adc.save();
```

This function will:
1. Enable the DAC output.
2. Generate calibration values.
3. Save the calibration results to the specified file.
4. Verify the calibration by calculating the mean squared error (MSE).

### Starting the ADC

To start the ADC and attempt to read the calibration file:

```cpp
adc.begin();
```

This function will:
1. Initialize the ADC with 12-bit resolution.
2. Attempt to read the calibration file from SPIFFS.
3. If the file is valid, it will use the calibration data; otherwise, it will fall back to a polynomial formula.

### Reading ADC Values

To read a value from the ADC:

```cpp
int value = adc.read(34);
```

- `34`: The ADC pin to read from.

This function will return the calibrated value if calibration data is available; otherwise, it will return a value calculated using a polynomial formula.

## Example

```cpp
#include <LinarADC.h>

LinarADC adc(34, ".bin", 2, 4, "CalibrationResults");

void setup() {
    Serial.begin(115200);
    if (adc.save()) {
        Serial.println("Calibration saved successfully.");
    } else {
        Serial.println("Calibration failed.");
    }

    if (adc.begin()) {
        Serial.println("ADC started with calibration.");
    } else {
        Serial.println("ADC started without calibration.");
    }
}

void loop() {
    int adcValue = adc.read(34);
    Serial.println(adcValue);
    delay(1000);
}
```

## File Formats

The library supports saving and reading calibration data in the following formats:

- **.txt**: Plain text format with comma-separated values.
- **.json**: JSON format with an array of calibration values.
- **.bin**: Binary format for efficient storage and retrieval.

## Error Handling

The library provides LED indications for different states:

- **Short Green LED Blink**: Successful operation.
- **Long Red LED Blink**: Error or failure in operation.

## Dependencies

- **Arduino.h**: Core Arduino library.
- **driver/dac.h**: ESP32 DAC driver.
- **FS.h**: File system library.
- **SPIFFS.h**: SPI Flash File System library.
- **ArduinoJson.h**: JSON library for handling JSON files.

## License

This library is open-source and available under the MIT License. Feel free to modify and distribute it as needed.

## Contributing

Contributions are welcome! Please open an issue or submit a pull request for any improvements or bug fixes.

## Author

[Your Name]

## Acknowledgments

- Thanks to the ESP32 community for their support and resources.
- Special thanks to the developers of the ArduinoJson library for making JSON handling easy.

---

This `README` provides a comprehensive guide to using the `LinarADC` library. For further details, refer to the code comments and the example provided.
