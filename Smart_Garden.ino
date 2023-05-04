
// Libraries imported 
#include <DHT.h>        // library for the DHT11, temperature sensor
#include <Wire.h>        //library for I2C communication
#include <LiquidCrystal_I2C.h>   //library for the LCD display
#include <Servo.h>                // library for the servo motors

#define DHTPIN 2                      //pin connected to DHT11
#define SoilMoisturePIN A0            //pin connected to soilMoisturePIN
#define SoilMoistureThresholdPIN 3    //pin connected to soilMoistureThresholdPIN
#define waterPump 4                   //pin 
int optimalTemp = 27;               //optimal temperature
const int buzzer_pin = 12;            //pin connected to buzzer
byte const servor_pin = 9;            //pin connected to servo motor
bool sound = true;                    //boolean value used to toggle buzzer sound between close and open shed


#define DHTTYPE DHT11                  //specifying the device's for the library use
DHT dht(DHTPIN, DHTTYPE);              // this class stores the pin connected to the device & its type

// Set the LCD address to 0x27 or 0x3F (depending on the module you have)
LiquidCrystal_I2C lcd(0x27, 16, 2);        //specifying the I2C address, Columns count, rows count of the LCD

//servo
Servo myservo;  // create servo object

//setup() method starts here
void setup() {
  Serial.begin(9600);       //setting a clock speed for the communications that involve I2C
  dht.begin();             //dht sensor starts sensing
  pinMode(SoilMoistureThresholdPIN, INPUT);   //setting soilMOistureThresholdPIN to be regarded as input
  pinMode(waterPump, OUTPUT);               //setting waterPump pin to be as an input
  pinMode(servor_pin, OUTPUT);              //setting servo pin to be as an input
  myservo.attach(servor_pin);               // attach servo to pin 9  
  pinMode(buzzer_pin, OUTPUT);             //set buzzer_pin as output pin


  lcd.init();                            //starts the LCD display
  lcd.backlight();                       //allows the LCD to display
  lcd.setCursor(0, 0);                   //set cursor to start at first row first column
  lcd.print("Smart Garden!");            //LCD text to be printed
  delay(1000);
}

void loop() {

  //humudity and temperature
  float humidity = dht.readHumidity();            //read humudity levels from the DHT11 sensor
  float temperature = dht.readTemperature();       //read humudity levels from the DHT11 sensor

  // in the following lines readings are displayed in the serial monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  Temperature: ");
  Serial.print(temperature);
  Serial.println("°C");


  // Soil moisture reading
  int moistureValue = analogRead(SoilMoisturePIN);             //read the analog soil moisture readings from the sensor
  Serial.println(moistureValue);
  int moisturePercent = map(moistureValue, 0, 1023, 0, 100);       //mapping original values into percentile 
  int moistureThreshold = digitalRead(SoilMoistureThresholdPIN);  // a digital value provided by the sensor itself that decides if a soil is moist or not

  // overhead cover
  if ((temperature > optimalTemp)) {   // if the temperature is higher than the optimal temperature open the shade
    closeRoof();                         //closes the shade to protect plants
  } else if ((temperature <= optimalTemp)) {   //else normal temperature and keep the shade open
    openRoof();                         //opens the shade to protect plants
  }

 //the following lines display moisture level readings on the serial monitor
  Serial.print("Moisture: ");
  Serial.print(moisturePercent);
  Serial.println("%");
  Serial.print("Moisture Trigger: ");
  Serial.println(moistureThreshold);


  //lcd display
  lcd.setCursor(0, 0); //start writing on the first column first raw the following entries
  lcd.print("H:");
  lcd.print(humidity, 1);
  lcd.print("% ");
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.println("C ");
  lcd.setCursor(0, 1);   // start writing on the second raw first column
  lcd.print("SM:");
  lcd.print(moisturePercent, 1);
  lcd.print("% ");
  lcd.print("Pump:");
  // water pump
  if (moistureThreshold == LOW) {   
    lcd.print("OFF");
    digitalWrite(waterPump, LOW);  //the soil is moist to turn the waterpump off, no watering 
  } else {
    lcd.print("ON ");
    digitalWrite(waterPump, HIGH);  //the soil is dry to turn the waterpump on, water plants 
  }


}

//method to close the shade of the roof
void closeRoof() {
  if (sound){     //the first time a buzzer gives sound is when closing the roof, because an open shed is assumed to be the initial state of the system
    buzz();    //give sound notice  
    sound = false;   //toggle sound value so that the next time it gives sound is when the shed is opening
  }   
  myservo.write(180);  // move servo to current position    
  
}
// method to open the shade of the roof
void openRoof() {
  if (!sound){
     buzz();             //give sound notice  
     sound = true;      //toggle sound value so that the next time it gives sound is when the shed is closing
   }
   myservo.write(0);  // move servo to current position
}
//method to give a buzz sound indicator when shade opens or closes 
void buzz(){
  for (int i= 0; i< 8000;i++){
    digitalWrite(buzzer_pin, HIGH);  
  } 
  digitalWrite(buzzer_pin, LOW); 
}

