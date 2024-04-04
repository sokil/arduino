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

