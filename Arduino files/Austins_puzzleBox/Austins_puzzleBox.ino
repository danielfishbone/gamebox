/*
  circuit => LCD
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

  circuit => Keypad 
 * keypad Row 1 pin to analog A5 pin
 * keypad Row 2 pin to analog A0 pin
 * keypad Row 3 pin to analog A1 pin
 * keypad Row 4 pin to analog A3 pin
 * keypad Col 1 pin to analog A4 pin
 * keypad Col 2 pin to analog A6 pin
 * keypad Col 3 pin to analog A2 pin

 circuit => Buttons  (10-Keys on the schematic diagram)
 *one pin of each button goes to the digital I/O while the other goes to GND 
 * Button 1 pin to digital pin 23
 * Button 2 pin to digital pin 25
 * Button 3 pin to digital pin 27
 * Button 4 pin to digital pin 29
 * Button 5 pin to digital pin 31
 * Button 6 pin to digital pin 33
 * Button 7 pin to digital pin 3
 * Button 8 pin to digital pin 2
 * Button 9 pin to digital pin 14
 * Button 0 pin to digital pin 15

 
 circuit => MONO 
 * counting the MONO ports from left to right Top to Bottom
 * MONO Row 1 Col 1 pin to digital pin 53
 * MONO Row 1 Col 2 pin to digital pin 49
 * MONO Row 1 Col 3 pin to digital pin 47
 * MONO Row 1 Col 4 pin to digital pin 45
 * MONO Row 1 Col 5 pin to digital pin 43
 * MONO Row 2 Col 1 pin to digital pin 51 
 * MONO Row 2 Col 2 pin to digital pin 41
 * MONO Row 2 Col 3 pin to digital pin 39
 * MONO Row 2 Col 4 pin to digital pin 37 
 * MONO Row 2 Col 5 pin to digital pin 35
 
 circuit => Emergency Button
 * Button pin 1 to digital pin 4
 * Button pin 2 to ground

 circuit => DFmini
 *Rx pin --1K-- to digital pin 18 
 *Tx pin --1k-- to digital pin 19
 *GND pin to GND
 *VCC pin to 5v
 *SPK1 to SpeakerL +
 *SPK2 to SpeakerR +
 *GND to SpeakerL -
 *GND to SpeakerR -

*/
#include <Keypad.h>
#include <LiquidCrystal.h>

const int requiredNum = 4; // value that holds howmany key entries required for 9-keys
//*****************************************************lcd pins***********
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 

//*******************************************************keypad pins**************
const byte ROW_KP = 4;
const byte COLS_KP = 3;

//*********************************************buttons (10-keys) pins*************
const int LED_MATRIX[11] = {48,46,44,42,40,38,36,34,32,16};

const int button1 = 23;
const int button2 = 25;
const int button3 = 27;
const int button4 = 29;
const int button5 = 31;
const int button6 = 33;
const int button7 = 3;
const int button8 = 2;
const int button9 = 14;
const int button0 = 15;
const int Buttons[11]= {button0,button1,button2,button3,button4,button5,button6,button7,button8,button9};

//*****************************************************emergencyBTN pin***********
const int emergencyBTN = 4;
const int redyBTN = A13;

//*****************************************************MONO Ports*****************
 const int MonoR1C1 = 53;
 const int MonoR1C2 = 49;
 const int MonoR1C3 = 47;
 const int MonoR1C4 = 45;
 const int MonoR1C5 = 43;
 const int MonoR1[6] = {MonoR1C1,MonoR1C2,MonoR1C3,MonoR1C4,MonoR1C5};
 
 const int MonoR2C1 = 51;
 const int MonoR2C2 = 41;
 const int MonoR2C3 = 39;
 const int MonoR2C4 = 37;
 const int MonoR2C5 = 35;
 const int MonoR2[6] = {MonoR2C1,MonoR2C2,MonoR2C3,MonoR2C4,MonoR2C5};

//*********************************************Toggle Switches********************


//*********************************variable to get values from the key matrix*****
char g ;
char key;
char keys_KP[ROW_KP][COLS_KP] = 
{
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
  
  };

//************************************************************************************



byte rowPinsKP[ROW_KP] = {A5, A0,A1, A3}; //connect to the row pinouts of the KEYPAD
byte colPinsKP[COLS_KP] = {A4, A6, A2}; //connect to the column pinouts of the KEYPAD



Keypad keypad_KP = Keypad( makeKeymap(keys_KP), rowPinsKP, colPinsKP, ROW_KP, COLS_KP );
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.print("ready to play?");

pinMode(emergencyBTN,INPUT_PULLUP);  
pinMode(redBTN,INPUT_PULLUP);  
for (int i = 0; i<10;i++) //set the feedback leds as output
{
  pinMode(LED_MATRIX[i],OUTPUT);
  }
for (int i = 0; i<10;i++) //set the feedback leds as output
{
  pinMode(Buttons[i],INPUT_PULLUP);
  }  
for (int i = 0; i<5;i++) //set the MONO Row2 as input
{
  pinMode(MonoR2[i],INPUT_PULLUP);
  }

}
for (int i = 0; i<5;i++) //set the MONO Row2 as output
{
  pinMode(MonoR1[i],OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

while(digitalRead(emergencyBTN)==false)// when you press the emergency stop btn
{
  while(1) // wait for release of the emergency button efore continuing 
  {
  if (digitalRead(emergencyBTN)== true)
  {
    break;
    }   
    }
get_num_bt(0,1);
}
}

//Function definitions 

// this gets keypad entries and display on lcd
int get_num_kp(int x, int y)
{
  char a;
  String  value = "";
  int integer =0;
  int last_integer=0;
  String space="            ";



  while(1){
  a = keypad_KP.getKey();
   if(a != NO_KEY || a != '*' || a != '#' || a != ' ')
   {
    value += String(a);
    }
    lcd.setCursor(x,y);
    integer = value.toInt();
    lcd.print(integer);
    if(integer != last_integer)
    {
     last_integer = integer;
      }
   if ( a == '*')
   {
    value = "";
    lcd.setCursor(x,y);
    lcd.print(space);
    integer = 0;
    }   
   if ( a == '#')
   {
    value = "";
    break;
    }
 }
 return (integer);
 }
