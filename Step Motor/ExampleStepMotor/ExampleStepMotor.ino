/*
 * Using module TB6560 to controle step motor
 * 
 * CLK+ -> Pin 9
 * CW+  -> Pin 8
 * CLK- , CW-  -> GND
 * 
 * 
 */


#define ratio 210

float Distance = 0; // Record the number of steps we've taken void setup() 

void setup()
{
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);
}

void loop() 
{
    digitalWrite(9, HIGH);
    delay(1);
    digitalWrite(9, LOW);
    delay(1);
    
    Distance ++; // record this step // Check to see if we are at the end of our move
    Serial.println((Distance * 360)/ratio);
    
    // two rotation for 1/8 bridge and 1 rotation for 1/6 bridge (for this code)
    if (Distance == ratio)   // We are! Reverse direction (invert DIR signal)
    { 
        //delay(3000);
        if (digitalRead(8) == LOW) 
            digitalWrite(8, HIGH); 
        else 
            digitalWrite(8, LOW);  //*/  // Reset our distance back to zero since we're // starting a new move
        
        Distance = 0; // Now pause for half a second delay(500);
    }
}
