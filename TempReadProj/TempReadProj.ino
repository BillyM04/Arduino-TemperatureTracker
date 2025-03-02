#include <Arduino.h>

/*
  This script is to simulate temperature data, it can be modified to 
  display data on a 7 seg display and use a push button to alter the 
  state of 'doorOpen'
*/

int tempReading = A0;
int button = 2;
int lastUpdate = 0;
volatile bool doorOpen = true;

int displayTemp[11][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 1, 1, 0, 0, 0, 0},
  {1, 1, 0, 1, 1, 0, 1},
  {1, 1, 1, 1, 0, 0, 1},
  {0, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {0, 0, 1, 1, 1, 1, 1},
  {1, 1, 1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 0, 1, 1},
  {0, 0, 0, 0, 0, 0, 0}};//7 seg display pins

struct tempData{
  float temp;
  bool doorStatus;
};

void stateChange(){
  doorOpen = !doorOpen;
}

void segDisplay(int num) {
  for (int i = 2; i <= 8; i++) {
    digitalWrite(i, displayTemp[num][i - 2]);
}}

void tempDisplay(float temp){
  int single = static_cast<int>(temp) % 10;
  int tenth = static_cast<int>(temp) / 10;

  switch(single){
    case 0: segDisplay(0); break;
    case 1: segDisplay(1); break;
    case 2: segDisplay(2); break;
    case 3: segDisplay(3); break;
    case 4: segDisplay(4); break;
    case 5: segDisplay(5); break;
    case 6: segDisplay(6); break;
    case 7: segDisplay(7); break;
    case 8: segDisplay(8); break;
    case 9: segDisplay(9); break;
  }
  switch(tenth){
    case 0: segDisplay(0); break;
    case 1: segDisplay(1); break;
    case 2: segDisplay(2); break;
    case 3: segDisplay(3); break;
    case 4: segDisplay(4); break;
    case 5: segDisplay(5); break;
    case 6: segDisplay(6); break;
    case 7: segDisplay(7); break;
    case 8: segDisplay(8); break;
    case 9: segDisplay(9); break;
  }
}


void setup() {
  Serial.begin(115200);
  pinMode(tempReading, INPUT);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button),stateChange,FALLING);
}


void loop() {
  tempData temp_data;
  temp_data.doorStatus = doorOpen;
  temp_data.temp = analogRead(tempReading)*(5.0/1023.0)*100; //5 is what i am assuming v level to be, so will maybe change when debugging

  tempDisplay(temp_data.temp);
  if(millis()%10000 >= 5000){
    temp_data.temp = 7.43;
  }
  else{
    temp_data.temp = 5.1894;
  }
  Serial.print("Temperature: ");
  Serial.print(temp_data.temp, 2);
  Serial.print("\tDoor status: ");
  Serial.print(doorOpen ? "Open" : "Closed");
  Serial.println("\r\n");
  delay(5000);
}
