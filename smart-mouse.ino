/* Smart mouse code */
#define ARRAY_END 10
const byte REQUEST_CLICK = 'C';
const byte REQUEST_COPY = 'c';
const byte REQUEST_PASTE = 'p';
const byte REQUEST_MOVE = 'm';

const int BAUD_RATE = 9600;

const int LEFT_BUTTON = 4;
const int RIGHT_BUTTON = 3;
const int COPY_BUTTON = 11;
const int PASTE_BUTTON = 10;
const int X_TURNER = A0;
const int Y_TURNER = A1;
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
void move(byte x, byte y){
  byte data [] = {REQUEST_MOVE, x, y, ARRAY_END};
  Serial.write(data, 4);
}
void copy(){
   byte data [] = {REQUEST_COPY, ARRAY_END};
   Serial.write(data, 2);
}



bool left_down = 0;
bool right_down = 0;
bool old_x = 0;
bool old_y = 0;
void loop()
{
 bool left_raw = digitalRead(LEFT_BUTTON);
 bool right_raw = digitalRead(RIGHT_BUTTON);
 int x_turner_raw = (analogRead(X_TURNER)) >> 2;
 int y_turner_raw = (analogRead(Y_TURNER)) >> 2;
 if(x_turner_raw<ARRAY_END+1)x_turner_raw=ARRAY_END+1;
 if(y_turner_raw<ARRAY_END+1)y_turner_raw=ARRAY_END+1;
 
 // RIGHT BUTTON
 if(right_raw && !right_down){
    click(2);
    right_down = 1;
 }else if(!right_raw){
    right_down = 0;
 }

 // LEFT_BUTTON
 if(left_raw && !left_down){
  click(1);
  left_down = 1;
 }else if(!left_raw){
    left_down = 0;
 }

 // X/Y-axis turner
 if(old_x!=x_turner_raw || old_y!=y_turner_raw){
    move(x_turner_raw,y_turner_raw);
    old_x = x_turner_raw;
    old_y = y_turner_raw;
 }
}

