/* Smart mouse code */
#include <EEPROM.h>
#define ARRAY_END 10
#define BYTE_LIMIT 1000
#define REQUEST_CLICK  'C'
#define REQUEST_CLICKUP  'U'
#define REQUEST_COPY  'c'
#define REQUEST_PASTE  'p'
#define REQUEST_MOVE  'm'
#define STATUS 's'

#define BAUD_RATE  9600;

#define LEFT_BUTTON  2
#define RIGHT_BUTTON  4
#define COPY_BUTTON  11
#define PASTE_BUTTON  10
#define X_TURNER  A0
#define Y_TURNER  A1
void setup()
{
  // initialize serial:
  Serial.begin(9600);

  // Digital inputs
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);  
  
 
  // ANALOG inputs
  pinMode(X_TURNER, INPUT);
  pinMode(Y_TURNER, INPUT);

  Serial.print("Smartmouse setup() finished\n");

}

void click(byte button){
  byte data[] = {REQUEST_CLICK, button,ARRAY_END};
  Serial.write(data, 3);
}
void clickUp(byte button){
  byte data[] = {REQUEST_CLICKUP, button,ARRAY_END};
  Serial.write(data, 3);
}
void move(byte x, byte y){
  byte data [] = {REQUEST_MOVE, x, y, ARRAY_END};
  Serial.write(data, 4);
}
void copy(){
   byte data [] = {REQUEST_COPY, ARRAY_END};
   Serial.write(data, 2);
}
void paste(){
  byte data [1 + BYTE_LIMIT] = {'?'};
  data[0] = REQUEST_PASTE;
  // This loop makes sense
  // R
  byte j = 0;
  int i;
  for(i=0;j=EEPROM.read(i), i<BYTE_LIMIT; i++){
    data[i+1] = j;
    data[i+2] = ARRAY_END;
  }
  Serial.write(data, 1+i);
}
/*
void store_clipboard(byte* computer_clipboard){
  
  for(int i=0; i<BYTE_LIMIT && computer_clipboard[i]!=0 && computer_clipboard[i]!=ARRAY_END; i++){
    EEPROM.write(i, computer_clipboard[i]);
  }
}*/

void store_iff_can(){
  int i = 0;
  int j = 0;
  bool hit_zero = 0;
  while(Serial.available() > 0){
    j = Serial.read();
    if(j==0){ hit_zero = true;}
    
    if(!hit_zero){
    EEPROM.write(i, j);
    i++;
    }
    if(j==ARRAY_END){ hit_zero = true;}
  }
  if(i>0){
    byte data [] = {STATUS,i, i, ARRAY_END};
    Serial.write(data, 4);
  }
}


bool left_down = 0;
bool right_down = 0;
bool copy_down = 0;
bool paste_down = 0;
bool old_x = 0;
bool old_y = 0;
void loop()
{
 bool left_raw = digitalRead(LEFT_BUTTON);
 bool right_raw = digitalRead(RIGHT_BUTTON);
 bool copy_raw = digitalRead(COPY_BUTTON);
 bool paste_raw = digitalRead(PASTE_BUTTON);
 int x_turner_raw = (analogRead(X_TURNER)) >> 2;
 int y_turner_raw = (analogRead(Y_TURNER)) >> 2;
 if(x_turner_raw<ARRAY_END+1)x_turner_raw=ARRAY_END+1;
 if(y_turner_raw<ARRAY_END+1)y_turner_raw=ARRAY_END+1;

  store_iff_can();
 
 // RIGHT BUTTON
 if(right_raw && !right_down){
    click(2);
    right_down = 1;
 }else if(!right_raw && right_down){
    clickUp(2);
    right_down = 0;
 }

 // LEFT_BUTTON
 if(left_raw && !left_down){
  click(1);
  left_down = 1;
 }else if(!left_raw && left_down){
    clickUp(1);
    left_down = 0;
 }

 // COPY BUTTON
 if(copy_raw && !copy_down){
    copy();
    copy_down = 1;
 }else if(!copy_raw){
    copy_down = 0;
 }

 // PASTE BUTTON
 if(paste_raw && !paste_down){
    paste();
    paste_down = 1;
 }else if(!paste_raw){
    paste_down = 0;
 }

 // X/Y-axis turner
 if(old_x!=x_turner_raw || old_y!=y_turner_raw){
    move(x_turner_raw,y_turner_raw);
    old_x = x_turner_raw;
    old_y = y_turner_raw;
 }
}

