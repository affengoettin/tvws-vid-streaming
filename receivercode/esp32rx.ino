#define RXD2 16
#define TXD2 17

#include <WiFi.h>
#include <WebServer.h>
#include "SPIFFS.h"

const char* ssid = "BigBoy";
const char* password = "BOTBurger1";

const uint16_t port = 8090;
const char * host = "192.168.1.18";

WebServer server(80);

bool receivingTransmit;
bool serverConnected;

void setup() {

  Serial.begin(115200);
  delay(100);

  // UART
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  Serial.println("UART connection initiated.");

  // SPIFFS 
  if(!SPIFFS.begin(true)){
    Serial.println("An error occurred while mounting SPIFFS.");
    return;
  }

  if(SPIFFS.remove("/test.txt")){
    Serial.println("Previous copy of data file found and removed.");
  } else {
    Serial.println("No previous data file found.");
  }
  
  // HTTP
  Serial.println("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("Got IP: "); Serial.println(WiFi.localIP());

//  serverConnected = false;
 
  server.on("/", handle_OnConnect);

  server.onNotFound([](){
    if (!handleFileRead(server.uri())){
      server.send(404, "text/plain", "404: Not Found");
    }
  });

  server.begin();
  Serial.println("HTTP server started.");
  
}

void loop() {
    server.handleClient();

//  TRYING OUT SOCKET SERVER SHIT   //
//  WiFiClient client;
//  if(!client.connect(host, port)){
//    Serial.println("Connection to socket server host failed.");
//    delay(1000);
//    return;
//  }
//  client.print("Hello from ESP32!");
//  Serial.println("Disconnecting...");
//  client.stop();
  
  if(Serial2.available()){
      char mun[65];
      memset(mun,0,65);
      Serial2.readBytes(mun,64);

      String munString = String(mun);

      if(munString.indexOf("START")>-1){
        receivingTransmit = true;
        Serial.println("TRANSMISSION START.");
      }
      else if(receivingTransmit){  
        File file = SPIFFS.open("/test.txt", "a");
        
        if(munString.indexOf("STOP") > -1){
          receivingTransmit = false;
          file.print(munString.substring(0, munString.indexOf("STOP")));

//          client.print(munString.substring(0, munString.indexOf("STOP")));
          
          Serial.print("Data saved: "); Serial.println(munString.substring(0, munString.indexOf("STOP")));
          Serial.println("END TRANSMISSION.");

//          Serial.println("Disconnecting from socket server.");
//          client.stop();
        }
        else{
          file.print(mun);

//          client.print(mun);
          
          Serial.print("Data saved: "); Serial.println(mun);  
        }
        Serial.print("Current size: "); Serial.println(file.size());
        file.close();     
        
     }
  }  
}

void handle_OnConnect() {
  Serial.println("Homepage rendered.");
  server.send(200, "text/html", SendHTML());
}

//void handle_VidStream() {
//  Serial.println("Video streaming page rendered.");
//  server.send(200, "text/html", VidHTML());
//}

bool handleFileRead(String path){
  Serial.println("File requested: " + path);
  if(SPIFFS.exists(path)){
    File file = SPIFFS.open(path, "r");
    size_t sent = server.streamFile(file, "text/plain");
//    size_t sent = server.streamFile(file, "video/MP2T");
    file.close();
    Serial.println(String("\tSent file: ") + path);
    return true;
  }
  return false;
}

//String VidHTML() {
//  String ptr = "<!DOCTYPE html> <html> \n";
//  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
//  ptr += "<title> Video StReAmInG, baby!</title>\n";
//  ptr += "</head>\n";
//  ptr += "<body>\n"; 
//  ptr += "<video
//}

String SendHTML() {
  String ptr = "<!DOCTYPE html> <html> \n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title> Video StReAmInG, baby!</title>\n";
  ptr += "</head>\n";
  ptr += "<body>\n"; 
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr; 
}
