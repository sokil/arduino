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
