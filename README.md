# Arduino C++ interface for a joystick (linux)

- SFML for joystick events.
- Sends joystick events in a simple format through Serial USB
- Uses stty command to open communication with Arduino, may require sudo priviledges.

## Compilation (Tested on Ubuntu 22.04)

```
sudo apt-get update && sudo apt-get install build-essential libsfml-dev
git clone https://github.com/brht0/arduinojoystick
cd arduinojoystick
make && sudo ./out
```
