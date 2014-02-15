int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A3;
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sum1 = 0;
int sum2 = 0;
int sum3 = 0;
int sum4 = 0;
int count = 0;
String JSONString = "";
String String1 = "{\"analogRead1\":\"";
String String2 = "\", \"analogRead2\":\"";
String String3 = "\", \"analogRead3\":\"";
String String4 = "\", \"analogRead4\":\"";
String String5 = "\"}";

void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL2V56);
}

void loop()
{
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  sum1 += sensorValue1;
  sum2 += sensorValue2;
  sum3 += sensorValue3;
  sum4 += sensorValue4;
  delay(30);
//  Serial.println(sensorValue);
  count++;
  if(count == 10){
    count = 0;
    JSONString = String1+ sum1/10 + String2 + sum2/10 + String3 + sum3/10 + String4 + sum4/10 + String5;
    Serial.println(JSONString);
    int sum1 = 0;
    int sum2 = 0;
    int sum3 = 0;
    int sum4 = 0;
  }
  delay(30);      
}


