#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "MY-ESP8266";
const char* password = "choompol";

IPAddress local_ip(192, 168, 1, 1);
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

int cnt = 0;

void setup(void){
	Serial.begin(115200);

	WiFi.softAP(ssid, password);
	WiFi.softAPConfig(local_ip, gateway, subnet);
	delay(100);

	server.onNotFound([]() {
		server.send(404, "text/plain", "Path Not Found");
	});

	server.on("/", []() {
		String msg = "<H1>SWITCH ";
		msg +=	" <a href='/on'>ON</a>";
		msg +=	" <a href='/off'>OFF</a>";
		msg +=	"</H1>";
		server.send(200, "text/plain", msg);
	});
	server.on("/on", []() {
		String msg = "<H1>ON</H1>";
		server.send(200, "text/plain", msg);
	});
	server.on("/off", []() {
		String msg = "<H1>OFF</H1>";
		server.send(200, "text/plain", msg);
	});

	server.begin();
	Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}

