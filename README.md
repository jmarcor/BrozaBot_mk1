# BrozaBot_mk1
First official version of BrozaBot. Remote controlled car with Arduino, Bluetooth and Android control using Protocoder

At this point, the will-be rover is just an adapted rc car.

It features:
  - Analog steering with a servo
  - Analog speed with reverse with an ESC (electronic speed controller, cheap XYS BL20A type).
  - Connection with an Android device via Bluetooth using the HC-06 board
  - Control from the Android device with a simple app developed using the Protocoder (http://protocoder.org/) Android programming tool.

The basic car control consist in sending string messages through Bluetooth to the car. The syntax of the message is documented in the code: "<x>,<y>\n" with x and y being integers in ascii ranging from 0 to 100, with 50 as the centered/stop position.

Besides the code here you must configure the Bluetooth board with the appropriate PIN (or leave the default one), and pair it with your Android. The protocoder app includes a connection button but you need to look for the Bluetooth device in the Android Bluetooth settings and you will need the PIN to pair at some point.

Photos, schematics and videos are to be added in the incoming days!
Check the wiki for more info: https://github.com/jmarcor/BrozaBot_mk1/wiki
