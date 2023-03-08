//====================================
//ESP8266 Station Point Control of LED
//====================================
#include <EEPROM.h>
#include <ESP8266WiFi.h>
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
    
   


    
    <big><big><big><big><p style=""><h2>Light Funtionality </h2>&nbsp; &nbsp;<button style="background-color:brown;color:white;><a href=/ledon style="text-decoration:none; "> <a href=/ledon><big><big><big><big><big><big><big><big><big><big>OFF</big></big></big></big></big> </big></big></big></big></big></a></button>
  &nbsp;<button style="background-color:brown;color:white;><a href=/ledoff style="text-decoration:none; "><a href=/ledoff><big><big><big><big><big><big><big><big><big><big>ON</big></big></big></big></big></big></big></big></big></big>&nbsp;&nbsp;</a></button></p><big></big></big></big></center>
  <br><br><br><br><center><a href="https://1.bp.blogspot.com/-vRUD-xv_kxk/XntX0mQz0GI/AAAAAAAAACk/f9hHStl94IIQEkIyN-Dk1hYq3M2xZggDwCLcBGAsYHQ/s1600/FB_IMG_15774802586585793.jpg" imageanchor="1" style="margin-left: 1em; margin-right: 1em;"><img border="0" data-original-height="260" data-original-width="204" src="https://1.bp.blogspot.com/-vRUD-xv_kxk/XntX0mQz0GI/AAAAAAAAACk/f9hHStl94IIQEkIyN-Dk1hYq3M2xZggDwCLcBGAsYHQ/s1600/FB_IMG_15774802586585793.jpg" /></a></center></body>
</html>
)***";
//--------------------------------------

bool p;
int led=2;
const char* ssid = "Lilmia";     //"Lilmia"  //"4th Floor";
const char* pass = "12345678";    //"12345678";  //"@GUB$SRIAZM";
//IPAddress IPaddr (192, 168, 168, 168);
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
  
  pinMode(led, OUTPUT);
  digitalWrite(led, EEPROM.read(0));
  Serial.begin(115200);
  Serial.println();
    Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, pass);

  //check NodeMCU is connected to Wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());
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
