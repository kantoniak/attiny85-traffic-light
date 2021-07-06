# ATTINY85 traffic light

Simple traffic light implemented using ATTINY85. Lights cycle between configurations and user can move to the next one by pressing a button.

## Software

The code is a PlatformIO project. It basically cycles between states after a timeout. The states are as follows, with possible actions marked with colors:
![State graph](readme/states.svg)
User can manually move to the next state by pressing a button (the red cycle).
μC will enter deep sleep after 10 minutes since last button press.

### Energy savings

The light runs on a single CR2032 cell (about 220 mAh), so it should consume minimal amounts of energy. Current optimizations are:

* Deep sleep after 10 minutes (see 0f1c727)
