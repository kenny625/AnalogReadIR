int sensorPin[10];
int sensorValue[10];
int preSensorValue[10];
int filteredSensorValue[10];
int sum[10];
int maxValue[10];
int minValue[10];
int numSensors = 2;
int count = 0;
String JSONString = "";
String outputString[10];
String endString = "\"}";
int alpha = 0.5;

void setup()
{
  Serial.begin(9600);
//  analogReference(INTERNAL2V56);
  sensorPin[0] = A0;
  sensorPin[1] = A1;
  sensorPin[2] = A2;
  sensorPin[3] = A3;
  sensorPin[4] = A4;
  sensorPin[5] = A5;
  sensorPin[6] = A6;
  sensorPin[7] = A7;
  sensorPin[8] = A8;
  sensorPin[9] = A9;
  outputString[0] = "{\"analogRead1\":\"";
  outputString[1] = "\", \"analogRead2\":\"";
  outputString[2] = "\", \"analogRead3\":\"";
  outputString[3] = "\", \"analogRead4\":\"";
  outputString[4] = "\", \"analogRead5\":\"";
  outputString[5] = "\", \"analogRead6\":\"";
  outputString[6] = "\", \"analogRead7\":\"";
  outputString[7] = "\", \"analogRead8\":\"";
  outputString[8] = "\", \"analogRead9\":\"";
  outputString[9] = "\", \"analogRead10\":\"";
  initArray();
}

void loop()
{
  int i;
  for(i=0;i<numSensors;i++){
    sensorValue[i] = analogRead(sensorPin[i]);
    if(preSensorValue[i] == 0) preSensorValue[i] = sensorValue[i];
    filteredSensorValue[i] = sensorValue[i] / 10 * alpha + (preSensorValue[i] * (1 - alpha));
    preSensorValue[i] = sensorValue[i];
    if(filteredSensorValue[i] > maxValue[i]){
      maxValue[i] = filteredSensorValue[i];
    }else if(filteredSensorValue[i] < maxValue[i]){
      minValue[i] = filteredSensorValue[i];
    }
    sum[i] += filteredSensorValue[i];
  }

  delay(30);

  count++;
  if(count == 10){
    count = 0;
    JSONString = "";
    for(i=0;i<numSensors;i++){
      JSONString += outputString[i];
      JSONString += (sum[i]-maxValue[i]-minValue[i])/8;
      sum[i] = 0;
      maxValue[i] = 0;
      minValue[i] = 9999;
    }
    JSONString += endString;
    
//    JSONString = String1+ (sum1-maxValue1-minValue1)/8 + String2 + (sum2-maxValue2-minValue2)/8 + String3 + (sum3-maxValue3-minValue3)/8 + String4 + (sum4-maxValue4-minValue4)/8 + String5;
//    double z = (double)(sum1-maxValue1-minValue1)/8/1024*5;
//    printDouble(z,10);
    Serial.println(JSONString);
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

void initArray(){
  int i;
  for(i=0;i<numSensors;i++){
    sensorValue[i] = 0;
    preSensorValue[i] = 0;
    filteredSensorValue[i] = 0;
    sum[i] = 0;
    maxValue[i] = 0;
    minValue[i] = 9999;
  }
}


