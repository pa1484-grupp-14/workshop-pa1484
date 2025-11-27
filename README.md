# Laboration PA1484

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
