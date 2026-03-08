# EmbeddedProject
Access control for door opening in short stays

## Sensors

- (Biasio) ultrasound sensor for proximity when in front of the board to lit the display or (PIR sensor)
- RFID sensor for admin magnetic access
- Servo motor for opening/closing the door
- (Pietro) Joystick for menu navigation
- (Pietro) Buttons and joystick for menu navigation
- Leds for signal
- (Mich M) Wifi module for IoT connectivity via telegram Bot and clock time
- Hand clap sequence for opening
- (Biasio) Buzzer for wrong code input and in general for signaling

## Features

### 
- (Biasio) Sleep mode with AOD, while proximity sensor doesn't trigger
- First time initialization of the code.
- RFID access displays the menu for pincode setup, wifi setup, enable/disable rfid, factory reset.
- (Mich M) Wifi connection via WPS or via file.
- (Mich C) Database of access and access attempts.
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



## Prerequisites

### Software
Ensure you have the following installed before cloning:
* **[Git LFS](https://git-lfs.com/)**: Required. We use Large File Storage to track the SIMPLELINK SDK libraries.
* **Code Composer Studio (CCS) v12.8**.

### Hardware:
* **TexasInstruments' MSP-EXP432P401R Board**
* **Texas Instruments' BoosterPack BOOSTXL-EDUMKII**

## Getting Started

Follow these steps to build the project:

### 1. Clone the Repository
Because we use Git LFS, make sure LFS is initialized on your machine before cloning:
```bash
git lfs install
git clone <your-repository-url>
cd <your-repository-name>


### 2. Import the project in CCStudio
The git repo is a full workspace for ccstudio, so when opening the IDE select the cloned folder as the active workspace. The project should be already configured and working out of the box.
