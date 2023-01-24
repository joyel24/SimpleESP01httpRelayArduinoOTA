//On not found
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) { message += " " + server.argName(i) + ": " + server.arg(i) + "\n"; }
  server.send(404, "text/plain", message);
}

//on GET /
void handleRoot() {
  server.send(200, "text/html", "" "<h1><center><br> <a href=\"/ON1\">RELAY 1 ON</a></center></h1>");
}

//on GET /ON1
void Relay1_ON() {
  digitalWrite(RELAY1, ON);
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}
