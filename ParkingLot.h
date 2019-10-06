#ifndef ParkingLot_h
#define ParkingLot_h

struct space{
  int pin; // Pin for photoresistor on analog input
  int value; // value that holds the analog read in a photoresistor
  bool available; // If the resistor gets light then true, if no light then false
};

struct level{
  space A = {0,0,true}; // Declare a struct for space A
  space B = {1,0,true}; // Declare a struct for space B
  space C = {2,0,true}; // Declare a struct for space C
  bool dataLot; // Data for serial. true means spaces available, false means no spaces available.
} ; 

level one; // Declare  a struct for level one parking lot
level two; // Declare  a struct for level two parking lot

#endif
