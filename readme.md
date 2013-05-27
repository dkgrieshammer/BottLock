# BottLock
This is the first attempt to connect our office's door lock to the Internets. Therefor an ABUS-security-lock will be connected to an stepper-motor on the hardwarez side. For trespassing ye shall use JSON to request the ethernet board and JSON it shall respond.

## Features requested (tbc.)
* parsing JSON-requests
* respond JSON-strings
* store tokens in eeprom (authentification)

## Testing
Content of *webstuff* goes to your server; 
JsonWebserver.ino goes onto your Uno. Of corse the $.ajax requests ip number needs to be adjusted to your network;

## NOTES
- Uno or Mega is needed since the ram of 168 is to small;
- JsonWebserver.ino expects an Ethernet-Shield with DHCP -> otherwise include static ip;
- the char callback in JsonWebserver.ino needs to match to your jsonpCallback in the $.ajax - request in index.html
- [aJson](https://github.com/interactive-matter/aJson/) seems promising for a merge with the example from David Mellis; we'll give it a try soon.
- alternatively the minimalist [json-arduino](https://github.com/not404/json-arduino) could rock - note that it only supports one-level objects (no nesting) 

## Credits
Web Server returning data as JSON-P, adapted from http://arduino.cc/en/Tutorial/WebServer, 
org. created by David A. Mellis and modified by Sam Fentress;