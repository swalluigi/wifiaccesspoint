/*
  WiFiAccessPoint.ino creates a WiFi access point and provides a web server on it.

  Steps:
  1. Connect to the access point "yourAp"
  2. Point your web browser to http://192.168.4.1/H to turn the LED on or http://192.168.4.1/L to turn it off
     OR
     Run raw TCP "GET /H" and "GET /L" on PuTTY terminal with 192.168.4.1 as IP address and 80 as port

  Created for arduino-esp32 on 04 July, 2018
  by Elochukwu Ifediora (fedy0)
*/

#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define LED_BUILTIN 2   // Set the GPIO pin where you connected your test LED or comment this line out if your dev board has a built-in LED

// Set these to your desired credentials.
const char *ssid = "ok";
const char *password = "pls_work";

WiFiServer server(80);

#define forward 13
#define backward 12
#define up 14
#define down 27
#define right 26
#define left 25
#define clockwise 33
#define counterclockwise 32

void setup() {
  pinMode (up, OUTPUT);
  pinMode (down, OUTPUT);
  pinMode (left, OUTPUT);
  pinMode (right, OUTPUT);
  pinMode (clockwise, OUTPUT);
  pinMode (counterclockwise, OUTPUT);
  pinMode (forward, OUTPUT);
  pinMode (backward, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  // You can remove the password parameter if you want the AP to be open.
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
           client.print("welcome to Ian's quad control page <br>");
            client.print("<button><a href=\"/u\">up</a> <button><br>");
            client.print("<button><a href=\"/d\">down</a> <button><br>");
            client.print("<button><a href=\"/l\">left</a> <button><br>");
            client.print("<button><a href=\"/r\">right</a> <button><br>");
            client.print("<button><a href=\"/c\">clockwise</a> <button><br>");
            client.print("<button><a href=\"/cc\">counter clockwise</a> <button><br>");
            client.print("<button><a href=\"/f\">forward</a> <button><br>");
            client.print("<button><a href=\"/b\">backward</a> <button><br>");

            client.print("<button><a href=\"/s\">stop</a> <button><br>");
            
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /u")) {
            digitalWrite(up, HIGH);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, LOW);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);
               
        }
        if (currentLine.endsWith("GET /d")) {
          digitalWrite(up, LOW);
            digitalWrite(down, HIGH);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, LOW);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);                      // GET /L turns the LED off
        }
         if (currentLine.endsWith("GET /l")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, HIGH);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, LOW);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);         
      }
       if (currentLine.endsWith("GET /r")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, HIGH);
            digitalWrite(clockwise, LOW);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);         
    }
     if (currentLine.endsWith("GET /c")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, HIGH);
            digitalWrite(clockwise, HIGH);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);           
        }
        if (currentLine.endsWith("GET /cc")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, HIGH);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);           
        }
        if (currentLine.endsWith("GET /f")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, HIGH);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);           
        }
        if (currentLine.endsWith("GET /b")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, HIGH);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);           
       }
       if (currentLine.endsWith("GET /s")) {
            digitalWrite(up, LOW);
            digitalWrite(down, LOW);
            digitalWrite(left, LOW);
            digitalWrite(right, LOW);
            digitalWrite(clockwise, LOW);
            digitalWrite(counterclockwise, LOW);
            digitalWrite(forward, LOW);
            digitalWrite(backward, LOW);           
       }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
