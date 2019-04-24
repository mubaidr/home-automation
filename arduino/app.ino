#include <C:\Users\mubai\AppData\Local\Arduino15\packages\esp8266\hardware\esp8266\2.5.0\variants\d1\pins_arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int LED_PIN = D0;   // D0
int MOTOR_PIN = D1; // D1

ESP8266WebServer server(80);

String sendStatus()
{
  String result;
  result = "";

  if (digitalRead(LED_PIN) == HIGH)
  {
    result = result + "bulb=1";
  }
  else
  {
    result = result + "bulb=0";
  }

  return result;
}

void handle_OnRoot()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

void handle_OnLight()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

void handle_OnDoor()
{
  digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN));
  delay(5000);
  digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN));
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

void handle_NotFound()
{
  server.send(404);
}

void setupNetwork()
{
  char ssid[] = "Olalalalala";
  char password[] = "despicable";

  // wifi setup
  IPAddress ip(192, 168, 10, 222);
  IPAddress gateway(192, 168, 10, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.mode(WIFI_STA);
  WiFi.hostname("esp8266");
  WiFi.begin(ssid, password);
  WiFi.config(ip, gateway, subnet);

  // wait for wifi connectivity
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }

  // define routes & start http server
  server.on("/", handle_OnRoot);
  server.on("/light", handle_OnLight);
  server.on("/door", handle_OnDoor);
  server.onNotFound(handle_NotFound);
  server.begin();

  // print local ip
  Serial.println("Server listening at: ");
  Serial.print(WiFi.localIP());
}

void pinModes()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(MOTOR_PIN, OUTPUT);
}

void setup()
{
  // debug
  Serial.begin(9600);

  // connec to wifi and start http server
  setupNetwork();

  // setup pin modes
  pinModes();
}

void loop()
{
  // handle clients using http server
  server.handleClient();
}
