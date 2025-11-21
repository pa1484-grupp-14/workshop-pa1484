set shell := ["bash", "-uc"]
set windows-shell := ["powershell.exe", "-NoLogo", "-Command"]
set dotenv-load := true

#   ___                       _
#  / __|___ _ _  ___ _ _ __ _| |
# | (_ / -_) ' \/ -_) '_/ _` | |
#  \___\___|_||_\___|_| \__,_|_|
#

# List the available commands and doc comments
default:
  just --list

[positional-arguments, private, unix]
@write *args="":
  echo "$@"

[positional-arguments, private, windows]
@write *args="":
  Write-Host "$args"

[private]
clean_pio:
  @just write Cleaning build files
  pio run --target clean

[private, no-exit-message]
clean_libdeps:
  @just write Cleaning dependencies recursively
  rm -r .pio/libdeps

# Clean the pio dependencies, libraries, and build files
clean: clean_pio clean_libdeps

# Run GoogleTest specified in /test
[positional-arguments]
test environment="esp32":
  @just write Starting GoogleTest...
  pio test -e {{environment}}

# Generate compile_commands.json
[positional-arguments]
compile_commands environment="esp32":
  pio run -t compiledb -e {{environment}}

#  _  _      _   _
# | \| |__ _| |_(_)_ _____
# | .` / _` |  _| \ V / -_)
# |_|\_\__,_|\__|_|\_/\___|
#

# Build native environment
[group('native')]
build-native:
    @just write Building native environment
    pio run -e native
    @just write Native build complete. Run 'just run' to execute.

# Run the natively compiled binary
[group('native')]
run-native:
  @just write Executing native build
  ./.pio/build/native/program
  @just write Execution finished.

# Build and run the native environment
[group('native')]
native: build-native run-native

#  ___ ___ ___ _______
# | __/ __| _ \__ /_  )
# | _|\__ \  _/|_ \/ /
# |___|___/_| |___/___|
#

# Build ESP32 environment
[group('esp32')]
build-esp32:
  @just write Building ESP32 environment
  pio run -e esp32
  @just write ESP32 build complete. Run 'just upload' to upload to ESP32.

# Upload to ESP32 (T-Display-AMOLED)
[positional-arguments, group('esp32')]
upload $UPLOAD_PORT:
    just write Uploading to $UPLOAD_PORT...
    pio run --target upload --upload-port $UPLOAD_PORT

# Open the serial monitor for the esp32 environment.
[group('esp32')]
monitor:
    @just write Starting serial monitor...
    pio device monitor -e esp32

# Builds the ESP32 target, uploads it, and starts the serial monitor.
[positional-arguments, group('esp32')]
esp32 $UPLOAD_PORT:
  @just build-esp32
  @just upload $UPLOAD_PORT
  @just monitor
