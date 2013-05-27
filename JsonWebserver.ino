/*
 Web Server returning data as JSON-P, adapted from http://arduino.cc/en/Tutorial/WebServer
 
 A simple web server that returns the value of the analog input pins as
 a JSON-P object, using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13 (standard configuration)
 * Analog inputs attached to pins A0 through A5 (optional)
 * Example of reading LM35 on pin A0:
     LM35 pins: {1: 5V, 2: A0, 3: gnd}
 
 created 18 Dec 2009
 by David A. Mellis
 
 modified 19 Mar 2012
 by Sam Fentress
 
 */
 
#include <SPI.h>
#include <Ethernet.h>
 
// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x0D, 0xD3, 0xCF };
// IPAddress ip(169,254,1,1);
char callback[27] = "arduinoEthernetComCallback";
 
// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);
 
void setup()
{
  //Serial output
  Serial.begin(9600);
  Serial.println("++++++++++++++++++++++++++++");
  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  printIP();
}
 
void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();

        Serial.print(c);
        if(c == '\n') Serial.println();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: application/json");
          client.println();
 
          // output the value of each analog input pin as a json-p object
          // client.print(callback);
          client.print("arduinoEthernetComCallback");
          client.print("({");
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            client.print("\"A");
            client.print(analogChannel);
            client.print("\": ");
            //temperatur reading
            if(analogChannel == 0) {
                client.print(((5.0 * analogRead(A0) * 100.0) / 1024), 1); // implement temperature measurement with LM35 on Pin0
              }else {
                client.print(analogRead(analogChannel));
              }
            if (analogChannel != 5) {
              client.print(",");
            }
          }
          client.println("})");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
} 

void printIP () {
  // print your local IP address:
  Serial.print("My IP address: ");
  for (byte thisByte = 0; thisByte < 4; thisByte++) {
    // print the value of each byte of the IP address:
    Serial.print(Ethernet.localIP()[thisByte], DEC);
    Serial.print("."); 
  }
  Serial.println();
}