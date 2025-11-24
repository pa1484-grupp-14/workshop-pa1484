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
test upload_port environment="esp32":
  @just write Starting GoogleTest...
  pio test -e {{environment}} -vv --upload-port {{upload_port}}

# Generate compile_commands.json
[positional-arguments]
compile_commands environment="esp32":
  pio run -t compiledb -e {{environment}}

#  ___ ___ ___ _______
# | __/ __| _ \__ /_  )
# | _|\__ \  _/|_ \/ /
# |___|___/_| |___/___|
#

# Build ESP32 environment
[group('esp32')]
build:
  @just write Building ESP32 environment
  pio run -e esp32
  @just write ESP32 build complete. Run 'just upload' to upload to ESP32.

# Upload to ESP32 (T-Display-AMOLED)
[positional-arguments, group('esp32')]
upload upload_port:
    just write Uploading to {{upload_port}}...
    pio run --target upload --upload-port {{upload_port}}

# Open the serial monitor for the esp32 environment.
[group('esp32')]
monitor:
    @just write Starting serial monitor...
    pio device monitor -e esp32

# Builds the ESP32 target, uploads it, and starts the serial monitor.
[positional-arguments, group('esp32')]
esp32 upload_port:
  @just build-esp32
  @just upload {{upload_port}}
  @just monitor
