# Smart_GardeSmart Garden: Autonomous Seedling Management using Arduino Uno

## 📖 Project Description

The Smart Garden is an automated environmental control system designed using the Arduino Uno. Its primary mission is to safeguard high-sensitivity seedlings by maintaining a stable micro-climate, reducing human effort, and protecting plants from unfavorable weather conditions.

By integrating real-time sensory data with mechanical actuators, the system automates two critical gardening tasks:

- Precision Irrigation: Uses soil moisture sensing to trigger a DC water pump only when the substrate is dry, preventing both dehydration and root rot.
- Climate Shielding: Employs a DHT11 sensor to monitor ambient temperature. If heat levels exceed the seedling's safety threshold, a servo-controlled shade is deployed to prevent wilting.

The system provides transparency through a live LCD dashboard and an audible buzzer that signals whenever the protective shade adjusts its position.



The objective of this project is to automate tending to plants, especially seedlings. Seedings are affected by unfavourable weather conditions. To safeguard a seedling's growth and to save human effort smart garden could be used. 

## System Architecture 
System circuit schematics: 
![circuit schematics](media/circuit_schematics.png)
Software flowchart: 
![software system flowchart](media/software_flowchart.png)

## Components Used
- Microcontroller: Arduino Uno
- Sensors: DHT11 sensor (temperature/humidity), Analog Soil Moisture Probe
- Control: 1-channel 5v Relay Module
- Output: 16x2 LCD display
- Power:  4 x 1.5 V DC batteries


## Description
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
The DHT11 sensor gives temperature reading of the temperature of the surround air in the garden. If it exceeds the optimal temperature then a shade can cover the plants. Otherwise, it shall remain open. This shed shall be controlled by servo motors and the effect of gravity. The shed remains open when the servo blades are at 180 degrees. To close the shades the blades are positioned at 0 degree, and thus gravity pulls the shade down.

## Contributors
Meron Yakob

Noah Yohannes




