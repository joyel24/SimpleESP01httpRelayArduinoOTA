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
  //If there is only one relay
  if (NumberOfRelays == 1){
    String answer = "<h1 style=font-size:100px> <center> <br>RELAY 1:<a href=\"/ON1\">";
    //Show lightblue background in the ON RELAY1 button if Relay is already on
    if (digitalRead(RELAY1) == ON){
      answer += "<button style=font-size:100px\;background-color:lightblue>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px>OFF</button></a><br>";
    }
    //Show lightblue background in the OFF RELAY1 button if Relay is off
    else if(digitalRead(RELAY1) == OFF){
      answer += "<button style=font-size:100px>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px\;background-color:lightblue>OFF</button></a></center> </h1>";
    }
    //Without condition, the answer looks like : server.send(200, "text/html", "<h1 style=font-size:100px> <center> <br>RELAY 1:<a href=\"/ON1\"><button style=font-size:100px>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px>OFF</button></a> </center> </h1>");
    server.send(200, "text/html", answer);
  }
  //If there are 2 relays
  else if(NumberOfRelays == 2){
    String answer = "<h1 style=font-size:100px> <center> <br>RELAY 1:<a href=\"/ON1\">";
    if (digitalRead(RELAY1) == ON){
      answer += "<button style=font-size:100px\;background-color:lightblue>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px>OFF</button></a><br>";
    }
    else if(digitalRead(RELAY1) == OFF){
      answer += "<button style=font-size:100px>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px\;background-color:lightblue>OFF</button></a><br>";
    }
    
    if (digitalRead(RELAY2) == ON){
      answer += "RELAY 2:<a href=\"/ON2\"><button style=font-size:100px\;background-color:lightblue>ON</button></a></pre> </pre><a href=\"/OFF2\"><button style=font-size:100px>OFF</button></a></center> </h1>";
    }
    else if(digitalRead(RELAY2) == OFF){
      answer += "RELAY 2:<a href=\"/ON2\"><button style=font-size:100px>ON</button></a></pre> </pre><a href=\"/OFF2\"><button style=font-size:100px\;background-color:lightblue>OFF</button></a></center> </h1>";
    }
    
    //wihtout conditions, the answer looks like : server.send(200, "text/html", "<h1 style=font-size:100px> <center> <br>RELAY 1:<a href=\"/ON1\"><button style=font-size:100px\;background-color:lightblue>ON</button></a></pre> </pre><a href=\"/OFF1\"><button style=font-size:100px>OFF</button></a><br>RELAY 2:<a href=\"/ON2\"><button style=font-size:100px>ON</button></a></pre> </pre><a href=\"/OFF2\"><button style=font-size:100px>OFF</button></a></center> </h1>");  
    server.send(200, "text/html", answer);
  }
}

//on GET /ON1
void Relay1_ON() {
  digitalWrite(RELAY1, ON);                           //Enable Relay
  server.sendHeader("Location", String("/"), true);   //  Redirects to
  server.send ( 302, "text/plain", "");               //  home
}
//on GET /Off1
void Relay1_OFF() {
  digitalWrite(RELAY1, OFF);
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}
//on GET /ON2
void Relay2_ON() {
  digitalWrite(RELAY2, ON);
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}
//on GET /Off2
void Relay2_OFF() {
  digitalWrite(RELAY2, OFF);
  server.sendHeader("Location", String("/"), true);
  server.send ( 302, "text/plain", "");
}
