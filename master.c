/*  
* Master program for 2022 Dakota Dreams Camp
* 
* This program includes different "fun" functions that students can call to 
* make the robot perform a variety of tasks, such as driving around without 
* hitting obstacles, playing a song, and following an object.  The structure of
* this program allows students to experience choosing actions for the robot 
* without needing to understand all the details required to perform those actions.
* 
* 
*/ 
#include "simpletools.h"                    // Include simpletools   
#include "abdrive360.h"                  
#include "ping.h" 
#include "abvolts.h"
int irLeft, irRight, distance;             // Global variables
volatile int ticker;
int *cog;

#define C6 1047                              // Define tones for speaker
#define D6b 1109
#define D6 1175
#define E6b 1245
#define E6 1319
#define F6 1397
#define G6b 1480
#define G6 1568
#define A6b 1661
#define A6 1760
#define B6b 1865
#define B6 1976 
#define C7 2093
#define D7b 2218
#define D7 2349
#define E7b 2489
#define E7 2637
#define F7 2794
#define G7b 2960
#define G7 3136
#define A7b 3322
#define A7 3520
#define B7b 3729
#define B7 3951
#define C8 4186
int all_notes[] = {C6, D6b, D6, E6b, E6, F6, G6b, G6, A6b, A6, B6b, B6, C7,
                   D7b, D7, E7b, E7, F7, G7b, G7, A7b, A7, B7b, B7, C8}; 
int NUM_NOTES = 25;  

                
void turn90Right();                       // Declare helper functions 
void turn90Left(); 
void turn180();
void timer();

// Declare fun functions!
void drive_around(volatile int time);
void play_song_mhall();
void sing_and_dance();
void follow(volatile int time);
void magic_beeps(volatile int time);
void piano_bot(volatile int time);
void drive_square(int side_length);
void drive_3squares(int longest_side_length);
 
int main() 
{ 
  ticker = 0;
  // Run a timer on a separate processor for timed activities
  cog = cog_run(timer, 128);  
  
  /* 
  Examples: 
  drive_around(30);  // Drive around for 30 seconds, avoiding obstacles
  pause(500);        // Pause for 500 milliseconds
  play_song_mhall(); // Play "Mary Had a Little Lamb"
  pause(500);
  sing_and_dance();  // Play some music and dance
  pause(500);
  follow(30);        // Follow an object using ultrasonic sensor
  pause(500);
  magic_beeps(20);   // Play different tones based on ultrasonic sensor distance
  pause(500);
  piano_bot(30);     // Play different tones based on which sensor is triggered
  pause(500);
  drive_square(50);  // Drive in a square, where each side is 50 ticks long
  pause(500);
  drive_3squares(120); // Drive in 3 consecutively smaller squares, where the
                       // longest side is 120 ticks long
                       
                       
  //Put your code below! Call any of the fun functions you want!*/
  
  

  /* End of your code */
  cog_end(cog);  
}

void timer()                          
{
   while(1)
   {
     pause(1000);
     ticker++;  
   }
}
        
void drive_around(int time)
{
  int drive_time = ticker + time;
  freqout(4, 500, 3000);                      // Speaker tone: .5 s, 3 kHz 
  low(26);                                    // D/A0 & D/A1 to 0 V for infrared
  low(27); 
  drive_setRampStep(10);                      // 10 ticks/sec / 20 ms
  while(drive_time - ticker > 0) 
  { 
    drive_ramp(96, 96);                     // Forward 2 RPS 
    // While disatance greater than or equal 
    // to 20 cm, wait 5 ms & recheck. 
    while(ping_cm(8) >= 30) pause(5);         // Wait until object in range 
    drive_ramp(0, 0);                         // Then stop 
    freqout(11, 1, 38000);                    // Check left & right objects 
    irLeft = input(10); 
    freqout(1, 1, 38000);
    irRight = input(2);
    if(irLeft == 0 && irRight == 0){          // Left & right obstacles? 
      high(6);		                     
      high(3);                                 
      turn180();                               // do a 180 
    } else if(irRight == 0) {                 // Only right obstacle? 
      high(3);                                 
      turn90Left();                         // turn left
    } else if(irLeft == 0) {                  // Only left obstacle? 
      high(6); 
      turn90Right();                         // turn right 
    } 
    low(3);                                   // shut off lights before       
    low(6);                                   // continuing to roam 
  } 
  drive_ramp(0,0);                           // Stop when done
}  
void turn90Left()                             // function to turn left 
{  
  drive_speed(-64, -64); 
  pause(200); 
  drive_goto(26, -26);  
  pause(7); 
} 

void turn90Right()                            // function to turn right 
{  
  drive_speed(-64, -64); 
  pause(200); 
  drive_goto(-26, 26);  
  pause(7); 
}

void turn180()                               // function to do a 180 
{  
  drive_speed(-64, -64);  
  pause(300); 
  drive_goto(51, -52); 
  pause(7);  
}

void play_song_mhall()                      // play "Mary Had a Little Lamb"
{
  int notes1[] = {E6, D6, C6, D6, E6, E6, E6};
  int notes2[] = {D6, D6, D6};
  int notes3[] = {E6, G6, G6};
  int notes4[] = {E6, D6, D6, E6, D6, C6};
  int i = 0;
  
  for(i = 0; i < 7; i++){
    freqout(4, 500, notes1[i]);
    pause(50);
  }
  pause(500);
  for(i = 0; i < 3; i++) {
    freqout(4, 500, notes2[i]);
    pause(50);
  }
  pause(500);
  for(i = 0; i < 3; i++) {
    freqout(4, 500, notes3[i]);
    pause(50);
  }
  pause(500);
  for(i = 0; i < 7; i++){
    freqout(4, 500, notes1[i]);
    pause(50);
  }  
  for(i = 0; i < 6; i++){
    freqout(4, 500, notes4[i]);
    pause(50);
  }     
} 

void sing_and_dance()  // Move in place and play a little song
{
  drive_speed(64, -64);
  pause(1000);
  freqout(4, 500, D7);
  freqout(4, 250, C7);
  freqout(4, 250, B6);
  freqout(4, 250, A6);
  drive_speed(-64, 64);
  pause(250);
  freqout(4, 250, E6);
  freqout(4, 250, G6);
  drive_speed(64, -64);
  pause(250);
  drive_speed(-64, 64);
  pause(250);
  freqout(4, 250, B6);
  freqout(4, 250, A6);
  drive_goto(104, -104);
}  

// maintain a set distance between the robot and an object
void follow(volatile int time)
{
  int distance, setPoint, errorVal, kp, speed;
  int drive_time = ticker + time;
  setPoint = 32;                              // Desired cm distance
  kp = -10;                                   // Proportional control

  drive_setRampStep(6);                       // 7 ticks/sec / 20 ms

  while(drive_time - ticker > 0)                                    // main loop
  {
    distance = ping_cm(8);                    // Measure distance
    errorVal = setPoint - distance;           // Calculate error
    speed = kp * errorVal;                    // Calculate correction speed

    if(speed > 128) speed = 128;              // Limit top speed
    if(speed < -128) speed = -128;

    drive_rampStep(speed, speed);             // Use result for following
  }
  drive_ramp(0,0);                           // Stop when done
}

void magic_beeps(volatile int time)
{
  int note;                                  // Variable for index                
  int play_time = ticker + time;
  while(play_time - ticker > 0)                                   // Main loop
  {
    distance = ping_cm(8);                   // Get cm distance from Ping)))
    
    note = distance % NUM_NOTES;             // Modulus to transform distance
                                        // to a value between 0 and NUM_NOTES - 1
                                             
    freqout(4, 125, all_notes[note]);         // Play the tone
  }
} 

void piano_bot(volatile int time)
{
  low(26);                                   // D/A0 & D/A1 to 0 V
  low(27);
 
  int play_time = ticker + time;
  while(play_time - ticker > 0)                                   // Main loop
  {
    freqout(11, 1, 38000);                   // Left IR LED light
    irLeft = input(10);                      // Check left IR detector
 
    freqout(1, 1, 38000);                    // Repeat for right detector
    irRight = input(2);
    
    distance = ping_cm(8);                   // Get cm distance from Ping)))
    
    if(irLeft == 0 && irRight == 0){         // If both IR detect object
      freqout(4, 500, G6);                   // play tone G6
      pause(70);
    } else if(irLeft == 0){                  // If only left IR detects
      freqout(4, 500, C6);                   // play tone C6
      pause(70);
    } else if(irRight == 0) {                // If only right IR detects 
      freqout(4, 500, E6);                   // play tone E6
      pause(70);
    } else if(distance < 10) {               // If PING))) detects object
      freqout(4, 500, D6);                   // play tone D6
      pause(70);
    }                           
 
    if(irLeft == 0) high(6); else low(6);    // LED for left IR
    if(irRight == 0) high(3); else low(3);   // LED for right IR
 
    pause(70);                              // Pause before repeating
  }
}   

void drive_square(int side_length)
{
  for(int i=0; i<4; i++){                 // Drive for 4 sides of square
    drive_goto(side_length, side_length); // Drive forward for side
    pause(10);                            // Stop for a bit
    drive_goto(26, -25);                  // Turn 90 to robot’s right
    pause(10);                            // Stop for a bit 
  }
}

void drive_3squares(int longest_side_length)
{
  int side = longest_side_length; // Define a variable for the length of the side
  if(side < 120) side = 120;      // Ensure minimum side length of last square
  for(int i=0; i<3; i++){        // Drive in a square 3 times
    drive_square(side);
    side = side - 50;  // Change the size of side so the next square is smaller}
  }
}  

  
