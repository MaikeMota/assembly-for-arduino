#include "normalize.h"

/**
 *  This program reads a value from A0 and normalize its calling an assembly function 'normalize'
 */

void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
}

const int upperBound = 800;
const int lowerBound = 350;

void loop() {

  int RAWValue = analogRead(A0);
  int normalizeValue = normalize(RAWValue, upperBound, lowerBound);
  Serial.print("RAW Value");
  Serial.print("\t");
  Serial.print("Normalized Value");
  Serial.print("\t");
  Serial.print("Upper Bound");
  Serial.print("\t");
  Serial.println("Lower Bound");
  Serial.print("\t");
  Serial.print(RAWValue);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(normalizeValue);
  Serial.print("\t");
  Serial.print("\t");
  Serial.print(upperBound);
  Serial.print("\t");
  Serial.print("\t");
  Serial.println(lowerBound);
  delay(2500);  
}

