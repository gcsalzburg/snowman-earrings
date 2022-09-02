# ⛄ Snowman Earrings

An experiment in using the ATtiny85 and ISP programming.

![Earring in use](https://play.interactionmagic.com/snowman-earrings/images/earring.jpg)

## Design

| Pin | Function | Programming |
| --- | --- | --- |
| 0 | Push switch | MOSI |
| 1 | Left eye | MISO |
| 2 | Right eye | SCK |
| 3 | Inner mouth | - |
| 4 | Outer mouth | - |
| 5 | - | RST |

The nose LED is connected permanently to power supply.

+ Micro = [ATTINY85-20SU](https://www.mouser.co.uk/ProductDetail/microchip/attiny85-20su/?qs=8jWQYweyg6N%2FGXnwAe4Icw==&countrycode=DE&currencycode=EUR) 
+ LED = [Broadcom HSMA-C170-T0000](https://www.mouser.co.uk/ProductDetail/broadcom-limited/hsma-c170-t0000/?qs=tMOYG%252bw4%252bLzJIEVH84X7hQ==&countrycode=DE&currencycode=EUR)
+ Switch = [Omron B3U-1000P](https://www.mouser.co.uk/ProductDetail/omron/b3u-1000p/?qs=AO7BQMcsEu4ip80xyf2FwA==&countrycode=DE&currencycode=EUR)
+ Battery holder = [Keystone 3002](https://www.mouser.co.uk/ProductDetail/keystone-electronics/3002/?qs=Mn60vILZNNZWJpgHXc3g8Q==&countrycode=DE&currencycode=EUR)  
+ Power supply = CR2032 battery

## How to program

1. Upload the sketch `File > Examples > 11.ArduinoISP > ArduinoISP` to Arduino Uno.
2. Wire up UNO as shown below:

   | What | Uno | ATtiny85 |
   | --- | --- | --- |
   | 5V  | Vcc | Vcc |
   | Gnd | Gnd | Gnd |
   | SCK | Pin 13 | Pin 2 |
   | MISO | Pin 13 | Pin 1 |
   | MOSI | Pin 13 | Pin 0 |
   | RST | Pin 13 | Reset |

	Also add a 10μF capacitor between Uno RESET and GND, to avoid Arduino being auto reset when uploading to ATtiny85. This goes in backwards (i.e. anode of capacitor is in GND of Uno).

3. In Arduino IDE, select ATtiny85 from `Tools > Board` menu. See Clock to `8MHz (internal)`  (note that ATTiny85 default is 1MHz). If not found, install `attiny by Davis A. Mellis` boards in `Board Manager`. 

3. Select `Arduino as ISP` in `Tools > Programmer`.

3. Burn bootloader to ATtiny85 using `Tools > Burn Bootloader`

3. Now in `VSCode`, set COM port of Arduino Uno in PlatformIO project in `platformio.ini` and upload! If having problems, can also try using [Arduino IDE to upload](https://create.arduino.cc/projecthub/arjun/programming-attiny85-with-arduino-uno-afb829).


![ISP Programming with Arduino](http://play.interactionmagic.com/snowman-earrings/images/isp_programming.png)

![ISP Programming with Arduino](http://play.interactionmagic.com/snowman-earrings/images/programming-setup.jpg)

## Board design

A few views of the board, for reference:


![Board front](http://play.interactionmagic.com/snowman-earrings/images/board-front.jpg)

![Board rear](http://play.interactionmagic.com/snowman-earrings/images/board-back.jpg)

![Board schematic](http://play.interactionmagic.com/snowman-earrings/images/schematic.jpg)

![Board PCB layout](http://play.interactionmagic.com/snowman-earrings/images/board-design.jpg)
