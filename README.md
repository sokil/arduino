# Arduino

Usefull snippets

## Troubleshooting:

### Error uploading sketch

```
ser_open(): can't open device "/dev/ttyACM0": Permission denied
```

Add rights to `tty` device:

```
sudo usermod -a -G dialout <username>
sudo chmod a+rw /dev/ttyACM0
```

## Avrdude

Update usbavr:
```
avrdude -c avrisp -P /dev/ttyACM0 -b 19200 -U flash:w:usbasp.atmega8.2011-05-28.hex:i -p m8
```

Flash app:
```
avrdude -c usbasp -U flash:w:firmware.hex:i -p m328p -b 9600


avrdude warning: cannot query manufacturer for device: error sending control message: Protocol error
avrdude warning: cannot query product for device: error sending control message: Protocol error
avrdude error: cannot find USB device with vid=0x16c0 pid=0x5dc vendor='www.fischl.de' product='USBasp'
avrdude error: unable to open programmer usbasp on port usb
```

```
$ lsusb
Bus 003 Device 021: ID 16c0:05dc Van Ooijen Technische Informatica shared ID for use with libusb
```

```
sudo chmod 666 /dev/bus/usb/003/009
```

```
cat /etc/udev/rules.d/99-USBasp.rules 
# USBasp - USB programmer for Atmel AVR controllers
# Copy this file to /etc/udev/rules.d so

SUBSYSTEM=="usb", ENV{DEVTYPE}=="usb_device", ATTRS{idVendor}=="16c0", ATTRS{idProduct}=="05dc", MODE="0666"
```

```
avrdude -c usbasp -U flash:w:firmware.hex:i -p m328p -b 9600 -P USB
```

```
$ tail -f /var/log/syslog
2024-03-31T01:14:27.068591+02:00 notebook kernel: [ 1296.030108] usb 3-4: USB disconnect, device number 10
2024-03-31T01:14:29.347815+02:00 notebook wpa_supplicant[870]: wlp0s20f3: WNM: Preferred List Available
2024-03-31T01:14:29.976557+02:00 notebook kernel: [ 1298.937165] usb 3-4: new low-speed USB device number 11 using xhci_hcd
2024-03-31T01:14:30.128593+02:00 notebook kernel: [ 1299.092344] usb 3-4: New USB device found, idVendor=16c0, idProduct=05dc, bcdDevice= 1.04
2024-03-31T01:14:30.128650+02:00 notebook kernel: [ 1299.092373] usb 3-4: New USB device strings: Mfr=1, Product=2, SerialNumber=0
2024-03-31T01:14:30.128652+02:00 notebook kernel: [ 1299.092378] usb 3-4: Product: USBasp
2024-03-31T01:14:30.128655+02:00 notebook kernel: [ 1299.092383] usb 3-4: Manufacturer: www.fischl.de
2024-03-31T01:14:30.136526+02:00 notebook mtp-probe: checking bus 3, device 11: "/sys/devices/pci0000:00/0000:00:14.0/usb3/3-4"
2024-03-31T01:14:30.136618+02:00 notebook mtp-probe: bus: 3, device: 11 was not an MTP device
2024-03-31T01:14:30.149249+02:00 notebook mtp-probe: checking bus 3, device 11: "/sys/devices/pci0000:00/0000:00:14.0/usb3/3-4"
2024-03-31T01:14:30.149310+02:00 notebook mtp-probe: bus: 3, device: 11 was not an MTP device
2024-03-31T01:14:34.362770+02:00 notebook wpa_supplicant[870]: wlp0s20f3: WNM: Preferred List Available

```

# esp8266

## Firmware

### Official firmware

* AT firmware: https://www.espressif.com/en/support/download/at
* Datasheet: https://www.espressif.com/sites/default/files/2a-esp8266-sdk_getting_started_guide_en_0.pdf

### NodeMCU

https://github.com/nodemcu/nodemcu-firmware

## Terminal

```
minicom -D /dev/ttyUSB0
Port: /dev/ttyUSB0
Baud Rate (Data Rate): 115200
Data Bits: 8
Parity: none
Stop bits: 1
Flow control: none
```

## AT commands

## Flasher

Initial boot address is 0x00000.

### ESPTool

https://github.com/espressif/esptool

```
sokil@hp:~$ sudo esptool.py -p /dev/ttyUSB0 flash_id
esptool.py v2.6
Serial port /dev/ttyUSB0
Connecting....
Detecting chip type... ESP8266
Chip is ESP8266EX
Features: WiFi
MAC: 18:fe:34:d3:1f:b5
Uploading stub...
Running stub...
Stub running...
Manufacturer: e0
Device: 4014
Detected flash size: 1MB
Hard resetting via RTS pin...
```

Download latest firmware at: https://www.espressif.com/en/support/download/at?keys=&field_type_tid%5B%5D=14

Or extract local AT_V1.1_on_ESP8266_NONOS_SDK_V1.5.4.zip.

Flash it:

```
$ sudo esptool.py -p /dev/ttyUSB0 write_flash 0x00000 boot_v1.5.bin  0x01000 512+512/user1.1024.new.2.bin  0xfc000  esp_init_data_default.bin  0x7e000  blank.bin 0xfe000 blank.bin
esptool.py v2.6
Serial port /dev/ttyUSB0
Connecting....
Detecting chip type... ESP8266
Chip is ESP8266EX
Features: WiFi
MAC: 18:fe:34:d3:1f:b5
Uploading stub...
Running stub...
Stub running...
Configuring flash size...
Auto-detected Flash size: 1MB
Flash params set to 0x0020
Compressed 3232 bytes to 2336...
Wrote 3232 bytes (2336 compressed) at 0x00000000 in 0.2 seconds (effective 122.2 kbit/s)...
Hash of data verified.
Compressed 399204 bytes to 286943...
Wrote 399204 bytes (286943 compressed) at 0x00001000 in 25.6 seconds (effective 125.0 kbit/s)...
Hash of data verified.
Compressed 128 bytes to 77...
Wrote 128 bytes (77 compressed) at 0x000fc000 in 0.0 seconds (effective 93.5 kbit/s)...
Hash of data verified.
Compressed 4096 bytes to 26...
Wrote 4096 bytes (26 compressed) at 0x0007e000 in 0.0 seconds (effective 5224.4 kbit/s)...
Hash of data verified.
Compressed 4096 bytes to 26...
Wrote 4096 bytes (26 compressed) at 0x000fe000 in 0.0 seconds (effective 5422.5 kbit/s)...
Hash of data verified.

Leaving...
Hard resetting via RTS pin...

```





