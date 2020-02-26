

#define SSID "Mariam amr mi a2"               // Wi-Fi Access point SSID
#define PASSWORD "12345678"       // Wi-Fi password


// callback function that is called by Web server in case if /ajax_input?LED=1&LED2=...
void ajaxInputs() {
  server.sendHeader("Connection", "close");                         // Headers to free connection ASAP and 
  server.sendHeader("Cache-Control", "no-store, must-revalidate");  // Don't cache response
  server.send(200, "text/html", "Hello World");       // 200 - means Success html result code
}
// callback function that is called by Web server if no sutable callback function fot URL found
void startServer(){
    server.on("/ajax_inputs", HTTP_GET, ajaxInputs);
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
    Serial.println();
    Serial.print("SUCCESS - Local IP: ");
    Serial.println(WiFi.localIP());     // Prints IP address got
}