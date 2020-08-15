// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

int NumSensors=0;
/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  NumSensors=sensors.getDeviceCount();
  Serial.print(NumSensors);Serial.print(" sensor");
  if((NumSensors>1)&(NumSensors!=0))
    Serial.print("s");
  Serial.println(" available");
  
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  float temp[2];
  long double setTemp[2];
  long double setCp[2];
  setCp[0]=1.8880;
  setCp[1]=1.864;
  setTemp[0]=350;
  setTemp[1]=300;
  float massFlow=0.0581;
  float avgTemp;
  float enthalpy[2];
  double Cp[2];
  //Serial.println(setCp[0]);
//  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  
  // After we got the temperatures, we can print them here.
//  for(int i=0;i<NumSensors;i++)
//  {
//    Serial.print("Probe ");Serial.print(i);Serial.print(" : ");
//    Serial.print(sensors.getTempCByIndex(i));
//    if(i<NumSensors-1)
//      Serial.print(",");
//  }
//Serial.println("Tempartures");  
for (int i=0;i<NumSensors;i++){
  temp[i]=sensors.getTempCByIndex(i)+273;
  //Serial.print("T");Serial.print(i);Serial.print(" : \n");
   
   
//Serial.println("T %d is : %f",i,temp[i]);
}
avgTemp=(temp[0]+temp[1])/2;
Cp[0]=setCp[0]-((setCp[0]-setCp[1])*(setTemp[0]-temp[0]))/(setTemp[0]-setTemp[1]);
Cp[1]=setCp[1]-((setCp[0]-setCp[1])*(setTemp[0]-temp[1]))/(setTemp[0]-setTemp[1]);
enthalpy[0]=massFlow*Cp[0]*avgTemp;
enthalpy[1]=massFlow*Cp[1]*avgTemp;
Serial.println(".........................................Temparetures................................");
Serial.println("Tempareture of input water");
Serial.println(temp[0]-273);
Serial.println("Tempareture of output water");
Serial.println(temp[1]-273);
Serial.println("........................................Cps.........................................");
Serial.println("Cp of input water");
Serial.println(Cp[0]);
Serial.println("Cp of output water");
Serial.println(Cp[1]);
Serial.println("......................................Enthalpys.....................................");
Serial.println("Enthalpy of input water");
Serial.println(enthalpy[0]);
Serial.println("Enthalpy of output water");
Serial.println(enthalpy[1]);
delay(1000);
}
