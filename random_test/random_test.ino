#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

int result = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  srand(time(0));
}

void loop() {
  // put your main code here, to run repeatedly:
    result = rand() % 6 + 1;
    Serial.println(result);
    //return result;
}
