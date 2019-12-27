#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// define all pins
// we will use these varibales to manage pin status
int LED_PIN = D0;
int MOTOR_PIN = D1;

// define the server
ESP8266WebServer server(80);

// collect and send status for all devices
// this function collects status of all pins and return in string format
/*
currently:
{
  bulb: true|false,
  door: true|false
}
*/
String sendStatus()
{
  String result;
  result = "{";

  // bulb
  result += "\"bulb\":";
  result += (digitalRead(LED_PIN) == HIGH) ? "true" : "false";
  result += ",";

  // door
  result += "\"door\":";
  result += (digitalRead(MOTOR_PIN) == HIGH) ? "true" : "false";
  // result += ",";

  result += "}";
  return result;
}

// root or status route
// this code is executed when a request is received on: 192.168.10.222/
void handle_OnRoot()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

// toggle bulb route
// this code is executed when a request is received on: 192.168.10.222/light
void handle_OnLight()
{
  digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", sendStatus());
}

// toggle door route
// this code is executed when a request is received on: 192.168.10.222/door
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
  // wifi informtion to which this arduion device will connect
  char ssid[] = "Olalalalala";
  char password[] = "despicable";

  // wifi setup
  // set ip address of the arduino device
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

  // web server will listen for folloing routes
  /*
  192.168.10.222/
  192.168.10.222/light
  192.168.10.222/door

  For example:
  sending a request to 192.168.10.222/light url via brower will execute function: handle_OnLight which toggle bulb pin
  */
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

  // connect to wifi and start http server
  setupNetwork();

  // setup pin modes
  pinModes();
}

void loop()
{
  // handle clients using http server
  server.handleClient();
}
