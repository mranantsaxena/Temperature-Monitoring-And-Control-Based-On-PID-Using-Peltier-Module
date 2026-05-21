#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS  2 
#define MOSFET_PWM   5
const float SETPOINT   = 33.0;
float Kp = 8.0;
float Ki = 0.5;
float Kd = 5.0;

float integral        = 0.0;
float lastError       = 0.0;
unsigned long lastTime = 0;
const int PWM_MIN = 0;
const int PWM_MAX = 255;
const float TEMP_MAX_SAFE = 45.0;
const float DEADBAND = 0.10;

const unsigned long SAMPLE_MS = 250;
OneWire           oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
void setup() {
  Serial.begin(9600);
  sensors.begin();
  pinMode(MOSFET_PWM, OUTPUT);
  analogWrite(MOSFET_PWM, 0);
  Serial.println("=== PID Temp Controller ===");
  Serial.print  ("Setpoint : "); Serial.print(SETPOINT); Serial.println(" C");
  Serial.print  ("Kp="); Serial.print(Kp);
  Serial.print  ("  Ki="); Serial.print(Ki);
  Serial.print  ("  Kd="); Serial.println(Kd);
  Serial.println("Time(ms) | Temp(C) | Error | PID_Out | PWM");
  lastTime = millis();
}
void loop() {
  unsigned long now = millis();
  if (now - lastTime < SAMPLE_MS) return;
  float dt = (now - lastTime) / 1000.0; 
  lastTime  = now;
  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  if (temp == DEVICE_DISCONNECTED_C) {
    Serial.println("ERROR: DS18B20 not found – heater OFF");
    analogWrite(MOSFET_PWM, 0);
    return;
  }
  if (temp >= TEMP_MAX_SAFE) {
    Serial.print("SAFETY CUTOFF at ");
    Serial.print(temp); Serial.println(" C – heater OFF");
    analogWrite(MOSFET_PWM, 0);
    integral = 0;
    return;
  }
  float error      = SETPOINT - temp;

  integral += error * dt;
  integral  = constrain(integral, -100.0, 100.0);

  float derivative = (error - lastError) / dt;
  lastError        = error;
  float pidOut = (Kp * error) + (Ki * integral) + (Kd * derivative);
  int pwmVal;

      if (error <= DEADBAND) {
        pwmVal   = 0;
        integral = 0;
      } else {
        pwmVal = (int)constrain(pidOut * 8.0, 0, 255);
      }
  analogWrite(MOSFET_PWM, pwmVal);

  Serial.print(now);       Serial.print(" | ");
  Serial.print(temp, 2);   Serial.print(" | ");
  Serial.print(error, 2);  Serial.print(" | ");
  Serial.print(pidOut, 3); Serial.print(" | ");
  Serial.println(pwmVal);
}