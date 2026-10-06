#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

Adafruit_MPU6050 mpu;

// Sensor pins
#define INDEX_FLEX_PIN 34
#define MIDDLE_FLEX_PIN 35
#define HALL_SENSOR_PIN 32
#define PALM_TOUCH_PIN 27

// Glove ON/OFF state
bool gloveEnabled = true;

// Button debounce
bool lastReading = HIGH;
bool stableState = HIGH;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup()
{
  Serial.begin(115200);

  // MPU6050
  Wire.begin(21, 22);

  // Analog sensors
  pinMode(INDEX_FLEX_PIN, INPUT);
  pinMode(MIDDLE_FLEX_PIN, INPUT);
  pinMode(HALL_SENSOR_PIN, INPUT);

  // Pushbutton / TTP223 simulation
  pinMode(PALM_TOUCH_PIN, INPUT_PULLUP);

  // Start MPU6050
  if (!mpu.begin())
  {
    Serial.println("MPU6050 NOT FOUND!");
    while (1)
      delay(10);
  }

  Serial.println("MPU6050 CONNECTED!");
  Serial.println("AIR MOUSE GLOVE STARTED!");
  Serial.println("Palm button = ON/OFF");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

void loop()
{
  // -------------------------
  // PALM TOUCH ON/OFF
  // -------------------------

  bool reading = digitalRead(PALM_TOUCH_PIN);

  if (reading != lastReading)
  {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay)
  {
    if (reading != stableState)
    {
      stableState = reading;

      // Button pressed
      if (stableState == LOW)
      {
        gloveEnabled = !gloveEnabled;

        if (gloveEnabled)
          Serial.println(">>> GLOVE ON <<<");
        else
          Serial.println(">>> GLOVE OFF <<<");
      }
    }
  }

  lastReading = reading;


  // -------------------------
  // READ MPU6050
  // -------------------------

  sensors_event_t acceleration;
  sensors_event_t gyro;
  sensors_event_t temperature;

  mpu.getEvent(&acceleration, &gyro, &temperature);


  // -------------------------
  // READ SENSORS
  // -------------------------

  int indexValue = analogRead(INDEX_FLEX_PIN);
  int middleValue = analogRead(MIDDLE_FLEX_PIN);
  int hallValue = analogRead(HALL_SENSOR_PIN);


  // -------------------------
  // PRINT SENSOR VALUES
  // -------------------------

  Serial.print("X: ");
  Serial.print(acceleration.acceleration.x);

  Serial.print("  Y: ");
  Serial.print(acceleration.acceleration.y);

  Serial.print("  Z: ");
  Serial.print(acceleration.acceleration.z);

  Serial.print("  Index: ");
  Serial.print(indexValue);

  Serial.print("  Middle: ");
  Serial.print(middleValue);

  Serial.print("  Hall: ");
  Serial.println(hallValue);


  // -------------------------
  // ONLY PROCESS GESTURES
  // IF GLOVE IS ON
  // -------------------------

  if (gloveEnabled)
  {
    // Index finger
    if (indexValue < 2000)
      Serial.println("Index: LIFTED");
    else
      Serial.println("Index: BENT");


    // Middle finger
    if (middleValue < 2000)
      Serial.println("Middle: STRAIGHT");
    else
      Serial.println("Middle: BENT");


    // Thumb / Hall sensor
    if (hallValue > 3000)
      Serial.println("Thumb: ZOOM IN");
    else if (hallValue < 1000)
      Serial.println("Thumb: ZOOM OUT");
    else
      Serial.println("Thumb: NEUTRAL");
  }
  else
  {
    Serial.println("Glove disabled - gestures ignored");
  }

  Serial.println("-------------------------");

  delay(200);
}