#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Pinger.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>


const char* ssid = "ten wifi";
const char* password = "pass wifi";
const char* pcIP = "ip pc"; 
const char* pcMac = "mac cua LAN/wifi";

ESP8266WebServer server(80); 
WiFiUDP UDP;
WakeOnLan WOL(UDP);
Pinger pinger;

bool pcOnline = false;
unsigned long lastPingTime = 0;

// ai code ho web (ae co the design lai)
String getHTML(bool isOnline) {
  String s = "<html><head><meta name='viewport' content='width=device-width, initial-scale=1'><meta http-equiv='refresh' content='5'>";
  s += "<style>body{font-family:sans-serif;text-align:center;background:#f4f4f4;padding-top:50px;}";
  s += ".card{background:white;display:inline-block;padding:30px;border-radius:15px;box-shadow:0 4px 6px rgba(0,0,0,0.1);}";
  s += ".on{color:#2ecc71;}.off{color:#e74c3c;} .btn{background:#3498db;color:white;padding:15px 25px;border:none;border-radius:5px;font-size:18px;cursor:pointer;text-decoration:none;display:inline-block;margin-top:20px;}</style></head><body>";
  s += "<div class='card'><h1>PC Status: " + String(isOnline ? "<span class='on'>ONLINE</span>" : "<span class='off'>OFFLINE</span>") + "</h1>";
  if(!isOnline) s += "<a href='/wake' class='btn'>TURN ON PC</a>";
  s += "</div></body></html>";
  return s;
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi Connected!");
  Serial.print("IP ESP8266: ");
  Serial.println(WiFi.localIP());

  WOL.calculateBroadcastAddress(WiFi.localIP(), WiFi.subnetMask());
  pinger.OnEnd([](const PingerResponse& response) {
    pcOnline = (response.ReceivedResponse > 0); 
    return true;
  });

  server.on("/", []() {
    server.send(200, "text/html", getHTML(pcOnline));
  });

  server.on("/wake", []() {
    WOL.sendMagicPacket(pcMac);
    server.send(200, "text/html", "<h1>Sending Magic Packet...</h1><script>setTimeout(()=>location.href='/',3000)</script>");
  });

  server.begin();
}

void loop() {
  server.handleClient();
  if (millis() - lastPingTime >= 10000) {
    pinger.Ping(pcIP);
    lastPingTime = millis();
  }
}