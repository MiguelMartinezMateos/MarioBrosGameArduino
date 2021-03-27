# MarioBrosGameArduino

This project has been developed with Arduino using the Adafruit library, to run it is necesary to get a LCD Display of 128x64 bits (link below):

https://www.amazon.es/AZDelivery-Pantalla-Display-pulgadas-Raspberry/dp/B01L9GC470/ref=sr_1_1_sspa?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=Pantalla+LCD+128x64+tecnooit&qid=1616884300&sr=8-1-spons&psc=1&smid=A1X7QLRQH87QA3&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUExVlFZN0VJREVMQU1TJmVuY3J5cHRlZElkPUEwNzkwNjg5M0s0TkRIWFdEWE1VMSZlbmNyeXB0ZWRBZElkPUEwOTMwNTYyM1NONUZYWTVaUFRSUiZ3aWRnZXROYW1lPXNwX2F0ZiZhY3Rpb249Y2xpY2tSZWRpcmVjdCZkb05vdExvZ0NsaWNrPXRydWU=


You will also need an Arduino nano:

https://www.amazon.es/ELEGOO-ATmega328P-Compatible-Arduino-Proyecto/dp/B0716T2L77/ref=sr_1_1_sspa?__mk_es_ES=%C3%85M%C3%85%C5%BD%C3%95%C3%91&dchild=1&keywords=arduino+nano&qid=1616884789&sr=8-1-spons&psc=1&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFFWU5HR1JDRDZLUk0mZW5jcnlwdGVkSWQ9QTA2MTc3OTBMUDlXRTlRQUxWV1QmZW5jcnlwdGVkQWRJZD1BMDUwNzM4MDJEUEtINEtUUDEyWUImd2lkZ2V0TmFtZT1zcF9hdGYmYWN0aW9uPWNsaWNrUmVkaXJlY3QmZG9Ob3RMb2dDbGljaz10cnVl


You can download the required libraries (<Adafruit_SSD1306.h>, <Fonts/FreeSans9pt7b.h>) here:

https://github.com/adafruit/Adafruit_SSD1306
https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Fonts/FreeSans9pt7b.h

Connect the SCL pin of the Display to the analogic A5 pin of the arduino and the SDA pin to the A4.
