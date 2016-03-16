#define TRIGGER_PIN 8
#define ECHO_PIN 7
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250

void setup()
{
   // Serial monitoring
   Serial.begin(9600);

   // Initializing Trigger Output and Echo Input
   pinMode(TRIGGER_PIN, OUTPUT);
   pinMode(ECHO_PIN, INPUT);

   // Reset the trigger pin and wait a half a second
   digitalWrite(TRIGGER_PIN, LOW);
   delayMicroseconds(500);
}

void loop()
{
  delay(MEASURE_DELAY);
  long distance = measure();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" mm");
}

long measure()
{
  long measureSum = 0;
  for (int i = 0; i < MEASURE_SAMPLES; i++)
  {
    delay(MEASURE_SAMPLE_DELAY);
    measureSum += singleMeasurement();
  }
  return measureSum / MEASURE_SAMPLES;
}

long singleMeasurement()
{
  long duration = 0;
  // Measure: Put up Trigger...
  digitalWrite(TRIGGER_PIN, HIGH);
  // ... wait for 11 µs ...
  delayMicroseconds(11);
  // ... put the trigger down ...
  digitalWrite(TRIGGER_PIN, LOW);
  // ... and wait for the echo ...
  duration = pulseIn(ECHO_PIN, HIGH);
  return (long) (((float) duration / USONIC_DIV) * 10.0);
}
