Sources
=======
+ https://code.google.com/p/mfocuino/
+ http://regnerischernachmittag.wordpress.com/2013/05/13/libnfc-mit-arduino-nfc-shield-nutzen/

Instructions
============

Install arduino package

    $ git clone https://github.com/adafruit/Adafruit_NFCShield_I2C.git
    $ cd Adafruit_NFCShield_I2C
    $ patch < ../adafruit-nfc-shield.patch
    $ cd ..
    $ mv Adafruit_NFCShield_I2C ~/sketchbook/libraries/

    $ git clone https://code.google.com/p/libnfc
    $ cd libnfc
    $ patch -p1 < ../libnfc-uart.patch
    $ autoreconf -is --force
    $ ./configure
    $ make
    $ sudo make install
    $ cd ..

    $ sudo mkdir /usr/local/etc/nfc
    $ sudo mkdir /usr/local/etc/nfc/devices.d
    $ sudo cp libnfc.conf /usr/local/etc/nfc

    $ mkdir ~/sketchbook/mfocuino_adafruit
    $ cp mfocuino-adafruit.ino ~/sketchbook/mfocuino_adafruit

open mfocuino-adafruit.ino in arduino ide / verify / upload

    $ nfc-list
