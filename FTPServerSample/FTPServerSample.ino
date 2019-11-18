// FTPServerSample.ino

#include "ESP32FtpServer.h"

// For Wifi Access Point
const char* ssid = "ftpESP32";
const char* passwordWifi = "123456789";

// For Ftp server 
const char* username = "anonymous";
const char* passwordFtp = ""; // Doesn't matter when "anonymous"

FtpServer ftpSrv; 

void setup(void) {
  Serial.begin(115200);
  WiFi.softAP(ssid, passwordWifi);
  Serial.println(WiFi.softAPIP());
 
  if (SPIFFS.begin(true)) {
    Serial.println("SPIFFS opened!");
    ftpSrv.begin(username, passwordFtp);   
  }
}

void loop(void) {
  ftpSrv.handleFTP();
}
