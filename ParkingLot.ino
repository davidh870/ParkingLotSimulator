
/* FIRST LEVEL LOT CODE */
#include <LiquidCrystal.h> // Library for LCD
#include <ParkingLot.h> // Library for carrying info on Parking Lot

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12 , en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2); // Setup LCD
  lcd.clear(); // Clear LCD 
  Serial.begin(9600); // Begin Serial Communication
}

/* Scans any available spaces in the first floor */
void spaceScanner(bool &a, bool &b, bool &c, bool &x, bool &y, bool &z){
  one.A.value = analogRead(one.A.pin); // Read photo resistor for A
  one.B.value = analogRead(one.B.pin); // Read photo resistor for B
  one.C.value = analogRead(one.C.pin); // Read photo resistor for C
  two.A.value = analogRead(two.A.pin); // Read photo resistor for D
  two.B.value = analogRead(two.B.pin); // Read photo resistor for E
  two.C.value = analogRead(two.C.pin); // Read photo resistor for F
  
  
  /* if photoresistor recieves no light, then change Available to false */
  if(one.A.value <= 450){
    a = false; // Space in A is taken
  }
  else {
    a = true; // Space in A is free
  }
  
  if(one.B.value <= 450 ){
    b = false; // Space is taken
  }
  else{
    b = true; // Space in B is free
  }

  if(one.C.value <= 450 ){
    c = false; // Space in C is taken
  }
  else{
    c = true; // Space in C is free
  }
  if(two.A.value <= 450){
    x = false; // Space in D is taken
  }
  else{
    x = true; // Space in D is free
  }
  if(two.B.value <= 450){
    y = false; // Space in E is taken
  }
  else{
    y = true; // Space in E is free
  }
  if(two.C.value <= 450){
    z = false; // Space in F is taken
  }
  else{
    z = true; // Space in F is free
  }
}

/* Sends data to second floor depending if there are spaces available in first floor */
void lotFull(bool &a, bool &b){
  if(one.A.available == true || one.B.available == true || one.C.available == true){
    a = true; // Change datalot to true meaning spaces available in first floor
    Serial.write(a); // send data to second floor
  }
  else if(one.A.available == false && one.B.available == false && one.C.available == false){
    a = false; // Change datalot to false meaning no spaces available in first floor
    Serial.write(a); // send data to second floor
  }
  if(two.A.available == true || two.B.available == true || two.C.available == true){
    b = true; // Change datalot to true meaning spaces available in second floor
  }
  else if(two.A.available == false && two.B.available == false && two.C.available == false){
    b = false; // Change datalot to false meaning no spaces available in second floor
  }
}

/* Print spaces available on LCD */
void levelOneLCD(){
  lcd.clear(); // Clear screen
  int i = 0; // position for cursor
  
 
  /* Print on LCD depending if space is Available */
  if(one.dataLot == true){
    lcd.setCursor(0,0);
    lcd.print("Free Parking in"); // print

    /* Checks if A is available */
    if(one.A.available == true){
      lcd.setCursor(i,1);
      lcd.print("A");
      i = i + 2; // Move i two spaces to the right for cursor
    }

    
    /* Checks if B is available */
    if(one.B.available == true){
      lcd.setCursor(i,1);
      lcd.print("B");
      i = i + 2; // Move i two spaces to the right for cursor
    } 

    /* Checks if C is available */
    if(one.C.available == true){
      lcd.setCursor(i,1);
      lcd.print("C");
      i = i + 2; // Move i two spaces to the right for cursor
    } 
    
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("GO TO NEXT LOT");
  }
}


void levelTwoLCD(){
  lcd.clear(); // Clear screen
  int i = 0; // position for cursor

    //Default message prior to receiving serial bit from 1st Arduino
    // Will display this message if LVL 1 has available spaces
    if (Serial.read() == true){
      lcd.setCursor(0,0);
      lcd.print("WAITING FOR");
      lcd.setCursor(0,1);
      lcd.print("LVL 1 TO FILL");
    }

    // If all spaces are occupied on LVL 1, then display spaces available on level 2
    /* Print on LCD depending if space is Available */
    else{
      /* If lot is not full, print available spaces */
      if (two.dataLot == true){
        lcd.setCursor(0,0);
        lcd.print("Free Parking in"); // print
    
        /* Checks if D is available */
        if(two.A.available == true){
          lcd.setCursor(i,1);
          lcd.print("D");
          i = i + 2; // Move i two spaces to the right for cursor
        }
        
        /* Checks if E is available */
        if(two.B.available == true){
          lcd.setCursor(i,1);
          lcd.print("E");
          i = i + 2; // Move i two spaces to the right for cursor
        }

        /* Checks if F is available */
        if(two.C.available == true){
          lcd.setCursor(i,1);
          lcd.print("F");
          i = i + 2; // Move i two spaces to the right for cursor
        }
      }
      /* If Lot is full, print "FULL" */
      else{
        lcd.setCursor(0,0);
        lcd.print("FULL");
      }
    }    
}


void loop() {
  // put your main code here, to run repeatedly:
  spaceScanner(one.A.available, one.B.available, one.C.available, two.A.available, two.B.available, two.C.available); // Scans any spaces available
  lotFull(one.dataLot, two.dataLot); // Send data to second floor
  if (Serial.available() > 0){ // Checks for any data recieved from serial
    levelTwoLCD(); // Print data in Level Two LCD
  }
  else{
    levelOneLCD(); // Print data in Level One LCD
  }
  delay(150);

}
