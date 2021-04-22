#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <IRremote.h>
#include "LEDMatrix.h"

LEDMatrix ledMat(2,3,4,5);

int one[8] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00011000,
  0b00011000,
  0b00000000,
  0b00000000,
  0b00000000
};

int two[8] = {
  0b00000000,
  0b00000110,
  0b00000110,
  0b00000000,
  0b00000000,
  0b01100000,
  0b01100000,
  0b00000000
};

int three[8] = {
  0b00000000,
  0b00000110,
  0b00000110,
  0b00011000,
  0b00011000,
  0b01100000,
  0b01100000,
  0b00000000
};

int four[8] = {
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000,
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000
};

int five[8] = {
  0b00000000,
  0b01100110,
  0b01100110,
  0b00011000,
  0b00011000,
  0b01100110,
  0b01100110,
  0b00000000
};

int six[8] = {
  0b01100110,
  0b01100110,
  0b00000000,
  0b01100110,
  0b01100110,
  0b00000000,
  0b01100110,
  0b01100110
};

const int digital = 7;
const int RECV_PIN = 11;
long interval = 100;
long previousMillis = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;

int iread, result, temp, sensor, diceroll = 0;

int roll_dice(void){
    result = rand() % 6 + 1;
    temp = 0;
    return result;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(digital, INPUT);
  srand(time(0));
}

void dump(decode_results *results) {
  // Dumps out the decode_results structure.
  // Call this after IRrecv::decode()
  int count = results->rawlen;
  //Serial.print(results->value, HEX);
  //Serial.print(" (");
  //Serial.print(results->bits, DEC);
  //Serial.println(" bits)");
  //Serial.print("Raw (");
  //Serial.print(count, DEC);
  //Serial.print("): ");
}

int infraredread() {
  if (irrecv.decode(&results)) {
      if (results.value == 0xFF30CF){
        result = 1;
        temp = 1;
      }
      else if (results.value == 0xFF18E7){
        result = 2;
        temp = 1;
      }
      else if (results.value == 0xFF7A85){
        result = 3;
        temp = 1;
      }
      else if (results.value == 0xFF10EF){
        result = 4;
        temp = 1;
      }
      else if (results.value == 0xFF38C7){
        result = 5;
        temp = 1;
      }
      else if (results.value == 0xFF5AA5){
        result = 6;
        temp = 1;
      }
      else{
        result = 0;
        return result;
      }
    //Serial.println(result);
    dump(&results);
    irrecv.resume(); // Receive the next value
    return result;
  }
  else{
    return 0;
  }
}

int getdicenumber(){
  iread = 0;
  if(temp == 0){
    iread = infraredread();
  }
  else{
  }
  sensor = digitalRead(digital);
  //Serial.println(sensor);
  if (sensor == 1){
    /*unsigned long currentMillis = millis();

   if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
    }*/
    //delay(100);
    if (iread > 0) {
      temp = 0;
      return iread;
    }
    else{
      iread = roll_dice();
      return iread;
    }
  }
  else{
    return 0;
  }
}


void loop() {
  diceroll = getdicenumber();
  //Serial.println(diceroll);
  if(diceroll > 0){
    Serial.println(diceroll);
    /*switch(diceroll) {
      case 1: 
        ledMat.writeData(one);
        //ledMat.update();
        break;
      case 2:
        ledMat.writeData(two);
        //ledMat.update();
        break;
      case 3:
        ledMat.writeData(three);
        //ledMat.update();
        break;
      case 4:
        ledMat.writeData(four);
        //ledMat.update();
        break;
      case 5:
        ledMat.writeData(five);
        //ledMat.update();
        break;
      case 6:
        ledMat.writeData(six);
        //ledMat.update();
        break;
      default:
        Serial.println("Whoops");
        break;
    }
  }
  else{*/
  }
  //ledMat.update();
}
