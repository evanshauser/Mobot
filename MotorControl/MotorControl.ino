/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 13;
int inputRightSensor = 12;
int enablePin = 6;
int clockwiseControl = 2;
int counterClockwiseControl = 1;

const int SENSOR_SAFETY_DELAY = 10; // 10 us delay used to wait for sensor value

const int SENSOR_TIMOUT = 4000; // 3 ms until sensor doesn't return value

boolean isEnablePin, isClockwise, isCounterClockwise;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  Serial.begin(9600);
  
  pinMode(enablePin, OUTPUT);
  isEnablePin = true;
  
  pinMode(clockwiseControl, OUTPUT);
  isClockwise = true;
  
  pinMode(counterClockwiseControl, OUTPUT);
  isCounterClockwise = true;
  
  pinMode(inputRightSensor, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  
  Serial.println(PingDigitalSensor(inputRightSensor));
  
  isCounterClockwise = false;
  
  SetMotor(isClockwise, isCounterClockwise, isEnablePin);
}

void ChangeDirection()
{
}

void SetMotor(boolean forward, boolean back, boolean isEnabled)
{
  digitalWrite(clockwiseControl, booleanToHighLow(forward));
  digitalWrite(counterClockwiseControl, booleanToHighLow(back));
  digitalWrite(enablePin, booleanToHighLow(isEnabled));
}

int booleanToHighLow(boolean toConvert)
{
  if(toConvert)
    return HIGH;
  return LOW;
}

int PingDigitalSensor(int pin) {
  
  // init values
  long startTime;
  int sensorTime;
  
  // ping sensor
  pinMode( pin, OUTPUT );
  digitalWrite( pin, HIGH );  
  
  // delay to safely switch to input mode
  delayMicroseconds(SENSOR_SAFETY_DELAY);
  pinMode( pin, INPUT );

  // start timer (get current time, safe to use as overflows after 70 min)
  startTime = micros();

  // time how long the input is HIGH, but quit after 3ms as nothing happens after that
  while ( (digitalRead(pin) == HIGH) && 
          ((micros() - startTime) < SENSOR_TIMOUT) ); 
  
  sensorTime = micros() - startTime;

  return sensorTime;
}
