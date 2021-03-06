//Run this code on board LOLIN(Wemos) D1 R2 & Mini which can be added from https://arduino.esp8266.com/stable/package_esp8266com_index.json
// Life saving resources: how to interface with the ESP + ATMega https://www.youtube.com/watch?v=dDktrUOnqq4
// reading args off an HTTP request using ESP   https://techtutorialsx.com/2016/10/22/esp8266-webserver-getting-query-parameters/
// Code originally borrowed from Sinau Programming sinauprogramming.com


#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "internet";
const char* password = "Bradpass";

ESP8266WebServer server(80);
MDNSResponder mdns;


void setup(void) {
    Serial.begin(115200);
    // keep these things from completing until the dips are set to serial for ESP board
    while (!Serial) {
        // wait for serial port to connect. Needed for native USB port only
    }

    // Board info and wifi connect, printed after switching dips to 5,6 and resetting
    Serial.println("");
    Serial.println("ESP8266 board info:");
    Serial.print("\tChip ID: ");
    Serial.println(ESP.getFlashChipId());
    Serial.print("\tCore Version: ");
    Serial.println(ESP.getCoreVersion());
    Serial.print("\tChip Real Size: ");
    Serial.println(ESP.getFlashChipRealSize());
    Serial.print("\tChip Flash Size: ");
    Serial.println(ESP.getFlashChipSize());
    Serial.print("\tChip Flash Speed: ");
    Serial.println(ESP.getFlashChipSpeed());
    Serial.print("\tChip Speed: ");
    Serial.println(ESP.getCpuFreqMHz());
    Serial.print("\tChip Mode: ");
    Serial.println(ESP.getFlashChipMode());
    Serial.print("\tSketch Size: ");
    Serial.println(ESP.getSketchSize());
    Serial.print("\tSketch Free Space: ");
    Serial.println(ESP.getFreeSketchSpace());

    // connect to Wifi
    WiFi.begin(ssid, password);
    Serial.println("");
    Serial.println("Trying to connect to Wifi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);

    }
    Serial.println("");
    Serial.print("Connected to ");  //
    Serial.println(ssid);
    Serial.print("IP address: ");  //
    Serial.println(WiFi.localIP());

    if (mdns.begin("esp8266", WiFi.localIP())) {
        Serial.println("MDNS responder started");
    }

//we only have 1 route that passes the plaintext body of a POST to the Arduino side of the board via the serial port
    server.on("/", HTTP_POST, []() {

        if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "No body in request!");
            return;
 
      }
 
      String message = server.arg("plain");
 
      server.send(200, "text/plain", "Request body received");
      Serial.println(message);

   
        server.send(200);
    });


    server.begin();
    Serial.println("HTTP server started");

}

void loop(void) {
    server.handleClient();
}
