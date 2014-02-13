int sensorPin = A0;
int sensorValue = 0;
int sum = 0;
int count = 0;

void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL2V56);
}

void loop()
{
  sensorValue = analogRead(sensorPin);
  sum += sensorValue;
  delay(30);
//  Serial.println(sensorValue);
  count++;
  if(count == 10){
    count = 0;
    Serial.println(sum/10);
    sum = 0;
  }
  delay(30);      
}


