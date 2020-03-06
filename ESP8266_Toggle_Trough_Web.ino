#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void setup(void) {
  const char* ssid = "your_ssid";
  const char* password = "your_password";
  
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", []() {
      server.send(200, "text/html", "<meta name='viewport' content='width=device-width, initial-scale=1'><h1>Toggle LED_BUILTIN</h1><button id='button' onclick='toggle()'>Toggle</button><script>const toggle=()=>{fetch('http://192.168.0.179/toggle');}</script>");
  });

  server.on("/toggle", []() {
    server.send(200, "text/html", "toggled");
    if(digitalRead(LED_BUILTIN)) {
      digitalWrite(LED_BUILTIN, 0);
    } else {
      digitalWrite(LED_BUILTIN, 1);
    }
  });

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
