# EmbeddedProject
Access control for door opening in short stays

## Sensors

- ultrasound sensor for proximity when in front of the board to lit the display
- PIR sensor
- RFID sensor for admin magnetic access
- Servo motor for opening/closing the door
- Joystick for menu navigation
- Buttons and joystick for menu navigation
- Leds for signal
- Wifi module for IoT connectivity via telegram Bot and clock time
- Hand clap sequence for opening
- Buzzer for wrong code input and in general for signaling

## Features

### 
- Sleep mode with AOD, while proximity sensor doesn't trigger
- First time initialization of the code.
- RFID access displays the menu for pincode setup, wifi setup, enable/disable rfid, factory reset.
- Wifi connection via WPS or via file.
- Database of access and access attempts.
- 2 pin codes, one for admin log in and one for user log in.
- Too  many wrong attempts blocks the pin access for some time, too many wrong-blocking timed attempts trigger an admin block.
  
### TELEGRAM BOT
#### USER side
- Request temporary code access for the time of the stay

#### ADMIN side
- Approve code request from clients
- Admin receives attempts access notifications and can view access logs

## Future works
  - Voice recognition
  - Camera support



