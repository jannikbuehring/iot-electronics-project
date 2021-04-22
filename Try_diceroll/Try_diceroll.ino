#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>
#include <IRremote.h>
#include "LEDMatrix.h"

LEDMatrix ledMat(2,3,4,5);

int empty[8] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

int currentDice[8] = {
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000,
  0b00000000
};

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

int inc = 0;
const int digital = 10;
const int RECV_PIN = 11;
int interval = 250;
unsigned long previousMillisLoop, previousMillisRem = 0;
int iread, result, sensor, diceroll, remotevalue = 0;

IRrecv irrecv(RECV_PIN);

decode_results results;



int roll_dice(void){
    int res = rand() % 6 + 1;
    return res;
}

int changeDice(int original[]){
  for(int i=0; i<8; i++){
      currentDice[i] = original[i]; 
    }
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
        }
        else if (results.value == 0xFF18E7){
          result = 2;
        }
        else if (results.value == 0xFF7A85){
          result = 3;
        }
        else if (results.value == 0xFF10EF){
          result = 4;
        }
        else if (results.value == 0xFF38C7){
          result = 5;
        }
        else if (results.value == 0xFF5AA5){
          result = 6;
        } else {
          result = 0;
        }
        dump(&results);
        irrecv.resume(); // Receive the next value
//        Serial.print("Result vor return");
//        Serial.println(result); 
        //previousMillisRem=currentMillis;       
      }
      return result;
    //}
  }

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(digital, INPUT);
  srand(time(0));
}

void loop() {
  sensor = digitalRead(digital);
  if(Serial.available() >0){
  int readd = Serial.read();
  if(readd == 48 || readd == 49){
    inc = readd;
    Serial.println(inc);
  }
  }
  
  
  if(inc == 49){
    unsigned long currentMillis = millis();
    if (currentMillis - interval > previousMillisLoop){
      if(infraredread() != 0){
        remotevalue = infraredread();
      }
      if (sensor == 1){ 
        if(remotevalue == 0){
          //Serial.println("Zufall");
          diceroll = roll_dice();
        } else {
          //Serial.println("Remote");
          diceroll = remotevalue;
          remotevalue = 0;
          result = 0;
        }
        //Serial.println(diceroll);
        if (diceroll == 1){
          changeDice(one);
        } else if (diceroll == 2){
          changeDice(two);
        } else if (diceroll == 3){
          changeDice(three);
        } else if (diceroll == 4){
          changeDice(four);
        } else if (diceroll == 5){
          changeDice(five);
        } else if (diceroll == 6){
          changeDice(six);
        }
        previousMillisLoop = currentMillis;
      }
    }
     
    ledMat.writeData(currentDice);
    ledMat.update();
  }
  else{
    ledMat.writeData(empty);
    ledMat.update();
  }
}
