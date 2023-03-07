/*a
///              MP3 PLAYER PROJECT originaly from: http://educ8s.tv/arduino-mp3-player/
/// -------------- All resources used for the creation of this code: -----------------

/// - Library examples and code from: - https://wiki.dfrobot.com/DFPlayer_Mini_SKU_DFR0299 
                                      - http://www.trainelectronics.com/Arduino/MP3Sound/Arduino-basic-player/index.htm
                                      - https://educ8s.tv/arduino-mp3-player/ 
                                      - https://www.electronics-lab.com/project/mp3-player-using-arduino-dfplayer-mini/
                                      - http://markus-wobisch.blogspot.com/2016/09/arduino-sounds-dfplayer.html
                                      - https://alainsprojects.com/2020/03/06/df-player-mini-configuration/ 
                                      
/// - Video eplanations of the serial library: https://www.youtube.com/watch?v=gMv2xGHLXdU

/// - Forum threads used :- https://hackaday.io/project/35165-sda-the-best-new-pda/log/152891-hacking-the-df-player-mini
                          - https://community.particle.io/t/dfplayer-mini-play-specific-track/48468/9
                          - https://community.particle.io/t/quickest-easiest-way-of-controlling-the-dfplayer-mini/40246
                          - https://reprage.com/post/dfplayer-mini-cheat-sheet
                          - https://maker.pro/arduino/projects/how-to-use-the-dfmini-player-mp3-module-with-arduino
                          - https://circuitjournal.com/how-to-use-the-dfplayer-mini-mp3-module-with-an-arduino
                          - https://forum.arduino.cc/index.php?topic=351210.15
                          - https://arduino.stackexchange.com/questions/75649/with-the-press-of-a-button-i-need-to-play-an-intro-sound-file-then-one-of-50-o
                          
/// - DFPlayer Mini Data Sheet- http://files.amperka.ru/datasheets/DFPlayer_Mini.pdf
//////////////////////////////////////////
*/

#include "SoftwareSerial.h"
SoftwareSerial mySerial(10, 11); // Tx,Rx on arduino
# define Start_Byte 0x7E
# define Version_Byte 0xFF
# define Command_Length 0x06
# define End_Byte 0xEF
# define Acknowledge 0x00 //Returns info with command 0x41 [0x01: info, 0x00: no info]

# define ACTIVATED LOW

//------Arduino pins for each buttons---//
int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int button5 = 6;
boolean isPlaying = true; 



void setup () {

//---- Button declaration----//
pinMode(button1, INPUT);
digitalWrite(button1,HIGH);
pinMode(button2, INPUT);
digitalWrite(button2,HIGH);
pinMode(button3, INPUT);
digitalWrite(button3,HIGH);
pinMode(button4,INPUT);
digitalWrite(button4,HIGH);
pinMode(button5,INPUT);
digitalWrite(button5,HIGH);

//---Initial starting values---//
mySerial.begin (9600);
delay(1000);
isPlaying = true;


}



void loop () { 

//---BUtton functions---//
 if (digitalRead(button1) == ACTIVATED)
  {
    if(isPlaying)
    { 
      playButton1(); // Plays audio file 001.mp3       
    }
    
  }


 if (digitalRead(button2) == ACTIVATED)
  {
    if(isPlaying)
    {
      playButton2(); // Plays audio file 002.mp3
    }
  }

 if (digitalRead(button3) == ACTIVATED)
  {
    if(isPlaying)
    {
      playButton3(); // Plays audio file 003.mp3
    }
  }

 if (digitalRead(button4) == ACTIVATED)
  {
    if(isPlaying)
    {
      playButton4(); // Plays audio file 004.mp3
    }
  }

 if (digitalRead(button5) == ACTIVATED)
  {
    if(isPlaying)
    {
      playButton5(); // Plays audio file 005.mp3
    }
  }
}

void volume()
{
  setVolume(30); // Set sofware volume
  delay(50);
}

void playButton1()
{
  execute_CMD(0x03,0,1); // The command(0x03), the folder location(0), the file number(1 or 001.mp3)) 
  delay(50); // Delay time in milli seconds to execute the command
}

void playButton2()
{
  execute_CMD(0x03,0,2); 
  delay(50);
}

void playButton3()
{
  execute_CMD(0x03,0,3);
  delay(50);
}

void playButton4()
{
  execute_CMD(0x03,0,4);
  delay(50);
}

void playButton5()
{
  execute_CMD(0x03,0,5);
  delay(50);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay(50);
}
// -------The end calculations----- //
void execute_CMD(byte CMD, byte Par1, byte Par2)
// Excecute the command and parameters
{
// Calculate the checksum (2 bytes)
word checksum = -(Version_Byte + Command_Length + CMD + Acknowledge + Par1 + Par2);
// Build the command line
byte Command_line[10] = { Start_Byte, Version_Byte, Command_Length, CMD, Acknowledge,
Par1, Par2, highByte(checksum), lowByte(checksum), End_Byte};
//Send the command line to the module
for (byte k=0; k<10; k++)
{
mySerial.write( Command_line[k]);
}
}
