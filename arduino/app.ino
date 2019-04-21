#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int Led = 4;

ESP8266WebServer server(80);

String sendStatus()
{
  String res;

  res = "Noob arduino and its developers";

  return res;
}

void handle_OnRoot()
{
  server.send(200, "application/json", sendStatus());
}

void setupNetwork()
{
  char ssid[] = "Olalalalala";
  char pass[] = "despicable";

  // wifi setup
  WiFi.begin();

  // wait for wifi connectivity
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(250);
  }

  // define routes & start http server
  server.on("/", handle_OnRoot);
  server.begin();

  // print local ip
  Serial.println("Server listening at: ");
  Serial.print(WiFi.localIP());
}

void pinModes()
{
  pinMode(Led, OUTPUT);
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
