#include "WiFi.h"
#include "ESPAsyncWebServer.h"
 
const char* ssid = "....";
const char* password = "....";
 
AsyncWebServer server(80);

void handleRoot(AsyncWebServerRequest *request) {
  char temp[1000];
  snprintf(temp, 1000,"<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>Diming LED</title> <script src=\"https://code.jquery.com/jquery-3.3.1.js\"></script> <script>$(document).ready(function(){$(\"[type = range]\").change(function(){var ledvalue=$(\"#led\").val();$(\".ledvalue\").text(ledvalue);});});</script> <style>body{background-color:lightgoldenrodyellow}.container{display:flex;flex-direction:column;align-items:center}.btn{padding:0.3em 0.5em;font-size:1.5em}</style></head><body><div class=\"container\"><h1>LED Diming</h1><h3>LED Light = <span class='ledvalue'>0</span></h3><form action=\"ledDiming\" method=\"get\" id=\"form1\"> <input type=\"range\" name=\"ledval\" id=\"led\" min=\"0\" max=\"255\"></form> <br> <button type=\"submit\" form=\"form1\" value=\"Submit\" class=\"btn\">Submit</button></div></body></html>");
  String webSite;
  request->send(200, "text/html",temp);
}
 
void setup(){
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());
 
   server.on("/", handleRoot);

  server.on("/get", [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "<h1>Hello world</h1>");
  });
  
  server.begin();
}
 
void loop(){
}
