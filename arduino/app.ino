#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// define all pins
int LED_PIN = D0;
int MOTOR_PIN = D1;

// define the server
ESP8266WebServer server(80);

// collect and send status for all devices
String sendStatus()
{
  String result;
  result = "{";

  // bulb
  result += "bulb:";
  result += digitalRead(LED_PIN) == HIGH ? "1" : "0";

  // door
  result += "door:";
  result += digitalRead(MOTOR_PIN) == HIGH ? "1" : "0";

  result += "}";
  return result;
}

// root or status route
void handle_OnRoot()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

// toggle bulb route
void handle_OnLight()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

// toggle door route
void handle_OnDoor()
{
  digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN));
  delay(3000);
  digitalWrite(MOTOR_PIN, !digitalRead(MOTOR_PIN));
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

// invalid route
void handle_NotFound()
{
  server.send(404);
}

// setup network and connection
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

// setup all pin modes
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
