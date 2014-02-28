int sensorPin1 = A0;
int sensorPin2 = A1;
int sensorPin3 = A2;
int sensorPin4 = A4;
int sensorValue1 = 0;
int preSensorValue1 = 0;
int filteredSensorValue1 = 0;
int sensorValue2 = 0;
int preSensorValue2 = 0;
int filteredSensorValue2 = 0;
int sensorValue3 = 0;
int preSensorValue3 = 0;
int filteredSensorValue3 = 0;
int sensorValue4 = 0;
int preSensorValue4 = 0;
int filteredSensorValue4 = 0;
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
int alpha = 0.5;
int maxValue1 = 0;
int minValue1 = 9999;
int maxValue2 = 0;
int minValue2 = 9999;
int maxValue3 = 0;
int minValue3 = 9999;
int maxValue4 = 0;
int minValue4 = 9999;

void setup()
{
  Serial.begin(9600);
//  analogReference(INTERNAL2V56);
}

void loop()
{
  
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  if(preSensorValue1 == 0) preSensorValue1 = sensorValue1;
  if(preSensorValue2 == 0) preSensorValue2 = sensorValue2;
  if(preSensorValue3 == 0) preSensorValue3 = sensorValue3;
  if(preSensorValue4 == 0) preSensorValue4 = sensorValue4;
  filteredSensorValue1 = sensorValue1 / 10 * alpha + (preSensorValue1 * (1 - alpha));
  filteredSensorValue2 = sensorValue2 / 10 * alpha + (preSensorValue2 * (1 - alpha));
  filteredSensorValue3 = sensorValue3 / 10 * alpha + (preSensorValue3 * (1 - alpha));
  filteredSensorValue4 = sensorValue4 / 10 * alpha + (preSensorValue4 * (1 - alpha));
  preSensorValue1 = sensorValue1;
  preSensorValue2 = sensorValue2;
  preSensorValue3 = sensorValue3;
  preSensorValue4 = sensorValue4;
  if(filteredSensorValue1 > maxValue1){
    maxValue1 = filteredSensorValue1;
  }else if(filteredSensorValue1 < maxValue1){
    minValue1 = filteredSensorValue1;
  } 
  if(filteredSensorValue2 > maxValue2){
    maxValue2 = filteredSensorValue2;
  }else if(filteredSensorValue2 < maxValue2){
    minValue2 = filteredSensorValue2;
  }
  if(filteredSensorValue3 > maxValue3){
    maxValue3 = filteredSensorValue3;
  }else if(filteredSensorValue3 < maxValue3){
    minValue3 = filteredSensorValue3;
  }
  if(filteredSensorValue4 > maxValue4){
    maxValue4 = filteredSensorValue4;
  }else if(filteredSensorValue4 < maxValue4){
    minValue4 = filteredSensorValue4;
  }
  
  
  sum1 += filteredSensorValue1;
  sum2 += filteredSensorValue2;
  sum3 += filteredSensorValue3;
  sum4 += filteredSensorValue4;
  delay(30);
//  Serial.println(sensorValue4);
  count++;
  if(count == 10){
    count = 0;
    JSONString = String1+ (sum1-maxValue1-minValue1)/8 + String2 + (sum2-maxValue2-minValue2)/8 + String3 + (sum3-maxValue3-minValue3)/8 + String4 + (sum4-maxValue4-minValue4)/8 + String5;
    double z = (double)(sum1-maxValue1-minValue1)/8/1024*5;
//    printDouble(z,10);
    Serial.println(JSONString);
    sum1 = 0;
    sum2 = 0;
    sum3 = 0;
    sum4 = 0;
    maxValue1 = 0;
    minValue1 = 9999;
    maxValue2 = 0;
    minValue2 = 9999;
    maxValue3 = 0;
    minValue3 = 9999;
    maxValue4 = 0;
    minValue4 = 9999;
  }
  delay(30);      
}


void printDouble( double val, byte precision){
  // prints val with number of decimal places determine by precision
  // precision is a number from 0 to 6 indicating the desired decimial places
  // example: printDouble( 3.1415, 2); // prints 3.14 (two decimal places)

  Serial.print (int(val));  //prints the int part
  if( precision > 0) {
    Serial.print("."); // print the decimal point
    unsigned long frac;
    unsigned long mult = 1;
    byte padding = precision -1;
    while(precision--)
       mult *=10;
      
    if(val >= 0)
      frac = (val - int(val)) * mult;
    else
      frac = (int(val)- val ) * mult;
    unsigned long frac1 = frac;
    while( frac1 /= 10 )
      padding--;
    while(  padding--)
      Serial.print("0");
    Serial.println(frac,DEC) ;
  }
}


