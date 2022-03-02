// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>


#define address 0x4F
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16 , 2);
 
DallasTemperature sensors(&oneWire);
int counter;
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Wire.begin();
  // Start up the library
  sensors.begin();
  lcd.begin(16,2);
  lcd.backlight();
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  sensors.requestTemperatures(); 
  float tempbuiten = sensors.getTempCByIndex(0);

  if(tempbuiten != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("tempratuur buiten is: ");
    Serial.println(tempbuiten);
    lcd.setCursor(0, 0);
    lcd.print("tempbuiten:" + String(tempbuiten));
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }

   Wire.beginTransmission(address);
  Wire.write(0x00);
  Wire.requestFrom(address, 2);

  int temperature;
  if (Wire.available()) {
     //temperature = Wire.read();
      
         int a = Wire.read();
          int b = Wire.read();
            float temp = a;
  temp=temp+((float)b/1024.0);  
    Serial.print("Temp: ");  
  Serial.print(temp);  
Serial.print('\n');
lcd.setCursor(0, 1);
lcd.print("tempbinnen:" + String(temp));

  }
  Wire.endTransmission();
  Serial.println("-----------");
  //Serial.println(temperature);
 delay(1000);
 
 
 
}
