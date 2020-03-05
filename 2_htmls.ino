void indexf() {
    server.sendHeader("Connection", "close");                       // Headers again free connection and
    server.sendHeader("Cache-Control", "no-store, must-revalidate");// Don't chaching
    server.sendHeader("Access-Control-Allow-Origin", "*");          // Helpful when page contains JavaScript code that performing outgoung requests
    File file = SPIFFS.open("/index.html", "r");                            // Open default index file readonly
    server.streamFile(file, "text/html");             // Send file to clent as HTML document
    file.close();                                    // Close file
}

void room1() {
    server.sendHeader("Connection", "close");                       // Headers again free connection and
    server.sendHeader("Cache-Control", "no-store, must-revalidate");// Don't chaching
    server.sendHeader("Access-Control-Allow-Origin", "*");          // Helpful when page contains JavaScript code that performing outgoung requests
    File file = SPIFFS.open("/Room1.html", "r");                            // Open default index file readonly
    server.streamFile(file, "text/html");             // Send file to clent as HTML document
    file.close();                                    // Close file
}

void room2() {
    server.sendHeader("Connection", "close");                       // Headers again free connection and
    server.sendHeader("Cache-Control", "no-store, must-revalidate");// Don't chaching
    server.sendHeader("Access-Control-Allow-Origin", "*");          // Helpful when page contains JavaScript code that performing outgoung requests
    File file = SPIFFS.open("/Room2.html", "r");                            // Open default index file readonly
    server.streamFile(file, "text/html");             // Send file to clent as HTML document
    file.close();                                    // Close file
}
void room3() {
    server.sendHeader("Connection", "close");                       // Headers again free connection and
    server.sendHeader("Cache-Control", "no-store, must-revalidate");// Don't chaching
    server.sendHeader("Access-Control-Allow-Origin", "*");          // Helpful when page contains JavaScript code that performing outgoung requests
    File file = SPIFFS.open("/Room3.html", "r");                            // Open default index file readonly
    server.streamFile(file, "text/html");             // Send file to clent as HTML document
    file.close();                                    // Close file
}

void css() {
    server.sendHeader("Connection", "close");                       // Headers again free connection and
    File file = SPIFFS.open("/bootstrap.min.css", "r");                            // Open default index file readonly
    server.streamFile(file, "text/css");             // Send file to clent as HTML document
    file.close();                                    // Close file
}

void jsmain() {
    server.sendHeader("Connection", "close");            
    server.sendHeader("Cache-Control", "no-store, must-revalidate");// Don't chaching
    server.sendHeader("Access-Control-Allow-Origin", "*");          // Helpful when page contains JavaScript code that performing outgoung requests
               // Headers again free connection and
    File file = SPIFFS.open("/main.js", "r");                            // Open default index file readonly
    server.streamFile(file, "text/css");             // Send file to clent as HTML document
    file.close();                                    // Close file
}
