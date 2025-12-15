# PA1484 – Software Development:  Project

## Archived

This project is completed and will no longer recieve any updates.

## Introduction

This project consists of a weather app designed for a LILYGO T4 S3 microcontroller. 

It aims convey weather forecasts and historical weather data for a couple of popular cities in sweden, using a simple GUI interface.

An experimental native build can also be made to test the program on a household PC. (requires SDL2 as well as a compiler compatible with PlatformIO.)

## Prerequisites

### General

1. Ensure one of the following combinations is installed:

- **[just](https://github.com/casey/just) and [platformio](https://platformio.org/install/cli)**
    - For installation on windows, see [scoop](https://scoop.sh/).
    - For installation on Linux or MacOS, please refer to your operating systems package manager.

- **["PlatformIO IDE"](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) plugin for Visual Studio Code**
    - For installation see [PlatformIO IDE](https://platformio.org/platformio-ide) for more details.

2. Connect the ESP32 to your computer via a USB cable.

### Linux

Run the following command to add access to the ESP32 port, e.g. `/dev/ttyACM0`:
```sh
usermod -aG dialout $USER
```

### NixOS

Add the following to your NixOS configuration:
```nix
users.users."<YOUR_USERNAME>" } = { # Please change to your personal username
    extraGroups = [ /* other groups such as 'wheel' */ "dialout" ];
    # Other settings for your user here
};
```

---

## Building/Running the program

You can do ONE of the following:

- Open Visual Studio Code and navigate to the PlatformIO plugin. Then press build, upload (to the device), and then monitor. See screenshot below.
- Run `just esp32 ESP32_PORT_NAME"`, see `just --list` for more details. Replace `ESP32_PORT_NAME` with the appropriate port name for your system, e.g. `COM3` on Windows or `/dev/ttyACM0` on Linux.

![[screenshot](./assets/screenshot.png)](./assets/screenshot.png)

---

## Features

As part of the project the team was given a set of user stories to fulfill, an `x` indicates that the user story has been fulfilled.

- [x] US1.1C: As a user, I want to see a starting screen to display the current program
version and group number on the first screen.
- [x] US1.2C: US1.2C: As a user, I want to see the weather forecast for the next 7 days for the
selected city on the second screen in terms of temperature and weather conditions
with symbols (e.g., clear sky, rain, snow, thunder) per day at 12:00.
- [x] US1.3: As a user, I want to have a screen to view weather forecast data.
- [x] US2.1: As a user, I want to be able to navigate between different screens (like forecast
screen) by sliding a finger over the touch screen.
- [x] US3.1: As a user, I want to have a screen to view historical weather data.
- [x] US3.2D: As a user, on the third screen I want to view the latest months (SMHI API
period: latest-months) of historical hourly data for selected weather parameter in the
selected city, using a slider to interact with the historical graph by scrolling where a
depleted slider corresponds to the oldest datapoint and a full slider corresponds to the
latest datapoint.
- [x] US4.1: As a user, on the fourth screen, I want to access a single settings screen to
configure both the city and weather parameter options.
- [x] US4.2B: As a user, I want to select from four weather parameters, namely
temperature (1), humidity (6), wind speed (4), and Air pressure (9), using a dropdown
list, to customize the historical graph.
- [x] US4.3B: As a user, I want to select from five different cities, namely
Karlskrona(65090), Stockholm(97400), Göteborg(72420), Malmö(53300), and
Kiruna(180940), using a dropdown, to view their weather data for the historical data
and starting screen forecast.
- [x] US4.4: As a user, I want to reset the selected city and weather parameter to default
using a button.
- [x] US4.5: As a user, I want to set my default city and weather parameter to the current
selection using a button, so they are automatically selected when I start the device.
- [x] US4.6: As a user, I want the device to store my default city and weather parameter so
that they are retained even after a restart.

## Contribution guide

### Visual Studio Code (Recommended)

1. Install the correct extension.
   - Head over to the extensions tab on your left.
   - Search for ["PlatformIO IDE"](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide) and install it.

### Other editor with LSP support

1. Run `just compile_commands` to generate `compile_commands.json` that will describe how to build each file within the repository.

---

## FAQ

1. The board uses USB as the JTAG upload port. When printing serial port information on USB_CDC_ON_BOOT configuration needs to be turned on.
   If the port cannot be found when uploading the program or the USB has been used for other functions, the port does not appear.
   Please enter the upload mode manually.

   1. Connect the board via the USB cable
   2. Press and hold the **BOOT** button , While still pressing the **BOOT** button
   3. Release the **RST** button
   4. Release the **BOOT** button
   5. The USB port should be fixed and will not flash again. You can click Upload.
   6. Press the **RST** button to exit download mode


