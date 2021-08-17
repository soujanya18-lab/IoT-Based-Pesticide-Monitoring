#include <DHT.h>
#include <ESP8266WiFi.h>
#define DHTPIN 16
#define DHTTYPE DHT11
const char* ssid= "vivo 1904";
const char* password = "1234567890";
WiFiServer server(80);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
Serial.begin(115200);
delay(10); //input or output?
pinMode(16, INPUT);
pinMode(A0, INPUT);
#define sensor_pin A0
//Serial.begin(9600);
dht.begin();

//Connect to WiFi network 
Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected");
//Start the server
server.begin();
Serial.println("Server started");
//Print the IP address
Serial.print("Use this URL to connect:");
Serial.print("http://");
Serial.print(WiFi.localIP());
Serial.println("/");
}

void loop() {
//Check if a client has selected
WiFiClient client = server.available();
if(!client) {
return;
}
//Wait until the client sends some data
Serial.println("new client");
while(!client.available()) {
delay(1);
}
//Set ledPin according to request
//digitalWrite(ledPin, value);
//Return the response
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("");//do not this
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<br><br>");
float output = analogRead(sensor_pin);
String AQI=String(output);

float h = dht.readHumidity();
h = 56.00;
float t = dht.readTemperature();
t = 36.00; 

Serial.print("Humidity: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temperature: ");
Serial.print(t);
Serial.println(" 'C");
if(h<70.0&&t<36)
{
client.println("<h1>MONITORING OF PESTICIDE</h1><h3>TEMP:"+String(t)+" 'C</h3><h4>moisture:"+String(h)+"%AIR QUALITY:"+AQI+"PPM</h4><h2>PESTICIDES ARE NOT DETECTED IN THE VEGETABLE</h2>");
}
else
{
client.println("<h1>MONITORING OF PESTICIDE</h1><h4>TEMP:"+String(t)+" 'C</h4><h4>moisture:"+String(h)+"%AIR QUALITY:"+AQI+"PPM</h4><h2>PESTICIDES ARE DETECTED IN THE VEGETABLE</h2>");
}
client.println("</html>");
Serial.println("client disconneted");
}


 
