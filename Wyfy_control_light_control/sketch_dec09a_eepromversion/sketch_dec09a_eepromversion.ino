//====================================
//ESP8266 Access Point Control of LED
//====================================
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>
bool q;
//user interface HTML code----------------
String html = R"***(
<!DOCTYPE html>
<html>
  <head>    
    <title>SWITCH LED</title>
  </head>
  <body style="background-color:rgb(148, 225, 255); border: 15px solid #51f80e;"><big><big><big><big><big></big>
    <marquee direction = "left" loop="" ><h1  style="color:rgb(255, 55, 55)"><center><u>Developed By Eagle Hunter Group</u></center></h1></marquee><br><center>Group Member(Millat,Moin,Maruf,Abir,Atik)
    <h3>SWITCH LED</h3></big></big></big></big>
    <big><big><big><big><p style=""><h2>Light Funtionality </h2>&nbsp; &nbsp;<button style="background-color:brown;color:white;><a href=/ledon style="text-decoration:none; "> <a href=/ledon><big><big><big><big><big><big><big><big><big><big>ON</big></big></big></big></big> </big></big></big></big></big></a></button>
  &nbsp;<button style="background-color:brown;color:white;><a href=/ledoff style="text-decoration:none; "><a href=/ledoff><big><big><big><big><big><big><big><big><big><big>OFF</big></big></big></big></big></big></big></big></big></big>&nbsp;&nbsp;</a></button></p><big></big></big></big></center>
  </body>
</html>
)***";
//--------------------------------------

bool p;
int led=2;
const char* ssid = "Eagle_Hunter";
const char* pass = "amra amrai to";
IPAddress IPaddr (192, 168, 168, 168);
IPAddress IPmask(255, 255, 255, 0);
ESP8266WebServer server(80);
//--------------------------------------
void handleRoot()
{
  server.send(200, "text/html", html);
}
void ledon()
{
 
  p=1;
  EEPROM.write(0,p);
  q=EEPROM.read(0);
  EEPROM.commit();
  digitalWrite(led, q);
  server.send(200, "text/html", html);
}
void ledoff()
{
  //
  p=0;
  EEPROM.write(0,p);
   q=EEPROM.read(0);
   EEPROM.commit();
  digitalWrite(led, q);
  server.send(200, "text/html", html);
}
//===============================================
void setup()
{
  EEPROM.begin(32);
  
  pinMode(led, OUTPUT); delay(1000);
  digitalWrite(led, EEPROM.read(0));
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.softAP(ssid,pass);
  WiFi.softAPConfig(IPaddr, IPaddr, IPmask); 
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/ledon", ledon);
  server.on("/ledoff", ledoff);
  server.begin();
  Serial.println("HTTP server started");
}
//===============================================
void loop()
{
  digitalWrite(led, EEPROM.read(0));
  server.handleClient();
}
