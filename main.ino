#include <LiquidCrystal.h>
#include <DHT.h>

#define TEMP_BLUE_LED_PIN A1
#define TEMP_RED_LED_PIN A0
#define FAN_PIN 13
#define HUM_GREEN_LED_PIN A2
#define HUM_YELLOW_LED_PIN A3
#define LIGHT_SENSOR_PIN A4
#define trigPin 7
#define echoPin 6
#define BUZZER_PIN 8

#define DHTPIN 10
#define DHTTYPE DHT11

#define BLUE_LED_TEMP_MIN 10
#define BLUE_LED_TEMP_MAX 18
#define RED_LED_TEMP_MIN 19
#define RED_LED_TEMP_MAX 21
#define FAN_TEMP_MIN 22
#define HUM_GREEN_MAX 50

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);
int sensitivity = 500;

void setup() {
  pinMode(TEMP_BLUE_LED_PIN, OUTPUT);
  pinMode(TEMP_RED_LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);
  pinMode(HUM_GREEN_LED_PIN, OUTPUT);
  pinMode(HUM_YELLOW_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.begin(16, 2);
  dht.begin();

  Serial.begin(9600);
}


void loop() {
  float temperature = get_Temperature();
  float humidity = get_Humidity();
  float light_level = get_light_level();
  float distance = get_Distance();
  Serial.println("temperature");
  Serial.println(temperature);
  Serial.println("humidity");
  Serial.println(humidity);
  Serial.println("light_level");
  Serial.println(light_level);
  Serial.println("distance");
  Serial.println(distance);

  if (temperature >= BLUE_LED_TEMP_MIN && temperature <= BLUE_LED_TEMP_MAX) {
    digitalWrite(TEMP_BLUE_LED_PIN, HIGH);
     Serial.println("Blue");
  } else {
    digitalWrite(TEMP_BLUE_LED_PIN, LOW);
  }

  if (temperature >= RED_LED_TEMP_MIN && temperature <= RED_LED_TEMP_MAX) {
    digitalWrite(TEMP_RED_LED_PIN, HIGH);
    Serial.println("Red");
  } else {
    digitalWrite(TEMP_RED_LED_PIN, LOW);
  }

  if (temperature >= FAN_TEMP_MIN) {
    digitalWrite(FAN_PIN, HIGH);
  } else {
    digitalWrite(FAN_PIN, LOW);
  }

  if (humidity <= HUM_GREEN_MAX) {
    digitalWrite(HUM_GREEN_LED_PIN, HIGH);
    digitalWrite(HUM_YELLOW_LED_PIN, LOW);
    Serial.println("Green");
    
  } else if (humidity > HUM_GREEN_MAX) {
    digitalWrite(HUM_GREEN_LED_PIN, LOW);
    digitalWrite(HUM_YELLOW_LED_PIN, HIGH);
    Serial.println("Yellow");
  } else {
    digitalWrite(HUM_GREEN_LED_PIN, LOW);
    digitalWrite(HUM_YELLOW_LED_PIN, LOW);
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print("%");

  delay(5);

  if (distance < 30) {
    tone(BUZZER_PIN, 2000, 50);
    digitalWrite(BUZZER_PIN, HIGH);
    delay(5 * distance);
    digitalWrite(BUZZER_PIN, LOW);
    delay(5 * distance);
  }
}


float get_Distance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  Serial.println(duration);

  long distance = duration / 58.2;

  return distance;
}

