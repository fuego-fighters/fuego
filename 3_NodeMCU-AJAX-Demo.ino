

#define SSID "Redmi"               // Wi-Fi Access point SSID
#define PASSWORD "helloworld"       // Wi-Fi password


// callback function that is called by Web server in case if /ajax_input?LED=1&LED2=...
void ajaxInputs() {
  char htmlBuff[300];
  sprintf(htmlBuff,"<div calss='divstyle col-md-6' style='border:5px solid gray;'> <ul> <li class='lidesign'>Name: 1A</li> <li class='lidesign'>Tempreture: %.2f C </li>"
  "<li class='lidesign'>Humidity: %.2f %</li> <li class='lidesign'>Heat Index: %.2f C</li> <li class='lidesign'>Serial: DHT_22</li> </ul> </div>",
  temp,rel_h,hd);
  server.sendHeader("Connection", "close");                         // Headers to free connection ASAP and 
  server.sendHeader("Cache-Control", "no-store, must-revalidate");  // Don't cache response
  server.send(200, "text/html",htmlBuff);       // 200 - means Success html result code
}


void ajaxFire() {
  server.sendHeader("Connection", "close");                         // Headers to free connection ASAP and 
  server.sendHeader("Cache-Control", "no-store, must-revalidate");  // Don't cache response
  if (hd>heatindex_alert){
    server.send(200, "text/html","fire");  
  }else{
    server.send(200,"text/html","ok");
  }
}
// callback function that is called by Web server if no sutable callback function fot URL found
void startServer(){
    server.on("/ajax", HTTP_GET, ajaxInputs);
    server.on("/af", HTTP_GET, ajaxFire); //on fire AF ya sa7beeeeeeetttttyyyyyyy
    server.on("/", HTTP_GET, indexf);
    server.on("/Room1.html", HTTP_GET, room1);
    server.on("/Room2.html", HTTP_GET, room2);
    server.on("/Room3.html", HTTP_GET, room3);
    server.on("/bootstrap.min.css",HTTP_GET,css);
    server.on("/main.js",HTTP_GET,jsmain);
    server.begin();            
}

void StartWifi()
{                                
    WiFi.mode(WIFI_STA);        // Initialize Wi-Fi in STAtion mode. NodeMCU will act as Wi-Fi Client.
    WiFi.begin(SSID, PASSWORD); // Start connecting to AP with ssid and password

    Serial.print("Connecting Wi-Fi.");
    // Wait until connection succesfull
    while (WiFi.status() != WL_CONNECTED) {
      delay(100);
      Serial.print(".");
    }
    Serial.print("IP: ");
    Serial.println( WiFi.localIP());
}
// callback function that is called by Web server if no sutable callback function fot URL found
