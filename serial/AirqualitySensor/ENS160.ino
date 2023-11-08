#include <Wire.h>
#include "SparkFun_ENS160.h"
 
SparkFun_ENS160 myENS; 
 
int ensStatus; 
 
void setup()
{
    Wire.begin();
    Serial.begin(115200);
    if( !myENS.begin() )
    {
        Serial.println("Did not begin.");
        while(1);
    }
 
    if( myENS.setOperatingMode(SFE_ENS160_RESET) )
        Serial.println("Ready.");
 
    delay(100);
    myENS.setOperatingMode(SFE_ENS160_STANDARD);
    ensStatus = myENS.getFlags();
    Serial.print("Gas Sensor Status Flag: ");
    Serial.println(ensStatus);
    
}
 
void loop()
{
    if( myENS.checkDataStatus() )
    {
        Serial.print("Air Quality Index (1-5) : ");
        Serial.println(myENS.getAQI());
 
        Serial.print("Total Volatile Organic Compounds: ");
        Serial.print(myENS.getTVOC());
        Serial.println("ppb");
 
        Serial.print("CO2 concentration: ");
        Serial.print(myENS.getECO2());
        Serial.println("ppm");
    }
    delay(200);
}
