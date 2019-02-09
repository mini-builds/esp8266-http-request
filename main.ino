#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

WiFiClient client;

void setup()
{
    Serial.begin(115200);
    delay(10);

    // Replace with your network details
    WiFi.begin("** ssid **", "** key **");

    int attempt = 0;
    while ((WiFi.status() != WL_CONNECTED) && (attempt < 10))
    {
        delay(2000);
        Serial.println("Connecting to WiFi..");
        attempt++;
    }

    if(WiFi.status() == WL_CONNECTED)
        Serial.println("Connected to WiFi!");
    else
        Serial.println("Failed to connect to WiFi!");
}

long timeLastMeasured = 0;

void loop()
{
    if (millis() - timeLastMeasured >= 10000)
    {
        timeLastMeasured = millis();

        Serial.println("Start request");

        HTTPClient client;

        client.begin("http://jsonplaceholder.typicode.com/todos/1");
        int httpCode = client.GET();

        String payload = client.getString();
        Serial.println(payload);
        
        client.end();
    }
    
}