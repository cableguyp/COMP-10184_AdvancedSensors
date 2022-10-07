// I, Caleb Priede, 000803812 certify that this material is my original work.
// No other person's work has been used without due acknowledgement.
 
// library for Arduino framework  
#include <Arduino.h> 
// 1-Wire sensor communication libary 
#include <OneWire.h> 
// DS18B20 sensor library 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 

DeviceAddress sensorAddress;
uint8_t deviceCount;

 // function to print a device address
String printAddress(DeviceAddress deviceAddress)
{
  String dataString = "";
  for (int i = 0; i < 8; i++)
  { 
      dataString += String(deviceAddress[i], HEX);
  }
  return dataString;
}

void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 

  // Start the DS18B20 sensor 
  DS18B20.begin();

  Serial.println("Temperature Application");
  deviceCount = DS18B20.getDeviceCount();

  DS18B20.getAddress(sensorAddress, 0);
  String address = printAddress(sensorAddress);

  if(deviceCount > 0){
    Serial.println("Found DS18B20 sensor with address: " + address);
  } else {
    Serial.println("No DS18B20 temperature sensors installed!");
  } 
} 
 
void loop() { 
  if(deviceCount > 0){
    float fTemp; 
 
    // ask DS18B20 for the current temperature 
    DS18B20.requestTemperatures(); 
  
    // fetch the temperature.  We only have 1 sensor, so the index is 0. 
    fTemp = DS18B20.getTempCByIndex(0); 

    String temperatureText;
    if(fTemp < 10){
      temperatureText = "Cold!";
    } else if(fTemp >= 10 && fTemp < 15){
      temperatureText = "Cool!";
    } else if(fTemp >= 15 && fTemp < 25){
      temperatureText = "Perfect!";
    } else if(fTemp >= 25 && fTemp < 30){
      temperatureText = "Warm!";
    } else if(fTemp >= 30 && fTemp < 35){
      temperatureText = "Hot!";
    } else if(fTemp > 35){
      temperatureText = "Too Hot!";
    }

    // print the temp to the USB serial monitor 
    Serial.println("Current temperature is: " + String(fTemp) + "° C or " + temperatureText);   
  }
 
  // wait 5s (5000ms) before doing this again 
  delay(5000); 
} 