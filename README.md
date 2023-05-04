# Smart_Garden_ArduinoUno
This is a Smart Garden project designed using Arduino Uno and sensors. 

## The objective of this project is to automate tending to plants, especially seedlings. Seedings are affected by unfavourable weather conditions. To safeguard a seedling's growth and to save human effort smart garden could be used. 

Components Used: Arduino Uno, DHT11 sensor, Soil moisture sensor, DC water pump, LCD Display, Servo SG90 9g, 5V battery, one channel relay.


Smart garden employs two sensors soil moisture sensor and DHT11 sensor (to read the temperature of the garden). The soil moisture sensor gives analog values, moistureValue, indicating the moisture levels. However, to make it more comprehensible we mapt it into the moisturePercent variable, a variable that converts the analog readings into a scale of 100.
```
  int moistureValue = analogRead(SoilMoisturePIN);             //read the analog soil moisture readings from the sensor
  Serial.println(moistureValue);
  int moisturePercent = map(moistureValue, 0, 1023, 0, 100);       //mapping original values into percentile 
  int moistureThreshold = digitalRead(SoilMoistureThresholdPIN);  // a digital value provided by the sensor itself that decides if a soil is moist or not
 ``` 
 The moistureThreshold variable reads digtally from the soilMoistureThresholdPIN. This value comes set with the sensor to make it easy for users. The output gives an output (moistureThreshold) int values of 0 or 1. A value of 0 means the soil is moist, while a value of 1 means the soil is dry. These values come already set in the sensor. 
 Based on the moistureThreshold variable we can determine when to turn on the DC water pump on and when to turn it off.
 ```
if (moistureThreshold == LOW) {   
    lcd.print("OFF");
    digitalWrite(waterPump, LOW);  //the soil is moist to turn the waterpump off, no watering 
  } else {
    lcd.print("ON ");
    digitalWrite(waterPump, HIGH);  //the soil is dry to turn the waterpump on, water plants 
  }
```

## Contributors
Meron Yakob

The DHT11 sensor gives temperature reading of the temperature of the surround air in the garden. If it exceeds the optimal temperature then a shade can cover the plants. Otherwise, it shall remain open. This shed shall be controlled by servo motors and the effect of gravity. The shed remains open when the servo blades are at 180 degrees. To close the shades the blades are positioned at 0 degree, and thus gravity pulls the shade down.






