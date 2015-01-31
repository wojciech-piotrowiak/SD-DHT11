 #include "DHT.h"        
 #include <SPI.h>
 #include <SD.h>
 #define DHTPIN 2          
 #define DHTTYPE DHT11    

 
    DHT dht(DHTPIN, DHTTYPE);
    const int chipSelect = 10;
 
    void setup()
    {
      Serial.begin(9600);     
      dht.begin();          
      pinMode(10, OUTPUT);
      if (!SD.begin(chipSelect)) {
      return;
  }
    }
 
    void loop()
    {
        float t = dht.readTemperature();  
        float h = dht.readHumidity();     
 
      if (isnan(t) || isnan(h))
      {
        Serial.println(">>>>>>>>>>>>>>>>>>>>Blad odczytu danych z czujnika!");
      }
      else
      {
          File dataFile = SD.open("dane.txt", FILE_WRITE);
          
            if (dataFile) {
              dataFile.print("Wilgotnosc: ");
              dataFile.print(h);
              dataFile.print(" % ");
              dataFile.print("Temperatura: ");
              dataFile.print(t);
              dataFile.println(" *C");
              dataFile.close();
          }
          // if the file isn't open, pop up an error:
          else {
            Serial.println("error opening datalog.txt");
          }
      }
 
      delay(60000);   
    }
