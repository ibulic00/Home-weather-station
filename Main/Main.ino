#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Adafruit_BME280.h>
#include <SPI.h>

#define BME_SCK 14
#define BME_MISO 12
#define BME_MOSI 13
#define BME_CS 15
#define SEALEVELPRESSURE_HPA (1013.25)

WiFiClient client;
Adafruit_BME280 bme(BME_CS, BME_MOSI, BME_MISO, BME_SCK);

const char* ssid = "name";
const char* password = "password";
const unsigned long eventInterval = 60000; 
unsigned long previousTime = 0;


String url;


void setup() 
  {
  bme.begin(0x76);
     
  Serial.begin(115200);
  delay(100);
    
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
    
  WiFi.begin(ssid, password);
    
  while (WiFi.status() != WL_CONNECTED) 
    {
      delay(500);
      Serial.print(".");
    }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());  
}

void loop() 
{
    
   unsigned long currentTime = millis();
    if (currentTime - previousTime >= eventInterval) {
    
      
      
      Serial.print("connecting to ");
      Serial.println("whatsapp");
      
      HTTPClient http; 
      url = "http://api.callmebot.com/whatsapp.php?";
      url = url + "phone=+385...";
      url = url + "&text=Temperatura+je:+";
      url = url + String(bme.readTemperature());
      url = url + "°C";
      url = url + "%0APritisak+zraka+je:+";
      url = url + String(bme.readPressure());
      url = url + "+hPa";
      url = url + "%0AVlažnost+zraka+je:+";
      url = url + String(bme.readHumidity());
      url = url + "%";
      url = url + "&apikey=181910";
      http.begin(client,url); 
      int httpCode = http.GET(); 
      if (httpCode > 0) 
          { 
           String payload = http.getString(); 
           Serial.println(payload); 
          }
          previousTime = currentTime;
      http.end(); 
    
    }
}
