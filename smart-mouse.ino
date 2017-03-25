/* Smart mouse code */

const int BAUD_RATE = 9600;
const int LEFT_BUTTON = 4;
const int RIGHT_BUTTON = 3;
const int X_TURNER = A0;
const int Y_TURNER = A1;
void setup()
{
  // initialize serial:
  Serial.begin(9600);

  // Digital inputs
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
  pin
  
 
  // ANALOG inputs
  pinMode(X_TURNER, INPUT);
  pinMode(Y_TURNER, INPUT);

  Serial.print("Smartmouse setup() finished\n");

}
bool left_down = 0;
bool right_down = 0;
bool old_val = 0;
void loop()
{
 bool left_raw = digitalRead(LEFT_BUTTON);
 bool right_raw = digitalRead(RIGHT_BUTTON);
 int x_turner_raw = (analogRead(X_TURNER)-20);
 if(x_turner_raw<0)x_turner_raw=0;
 
 // RIGHT BUTTON
 if(right_raw && !right_down){
    Serial.println("RIGHT\n");
    right_down = 1;
 }else if(!right_raw){
    right_down = 0;
 }

 // LEFT_BUTTON
 if(left_raw && !left_down){
  Serial.println("LEFT\n");
  left_down = 1;
 }else if(!left_raw){
    left_down = 0;
 }

 // X-axis turner
 if(old_val > x_turner_raw + 2 || old_val < x_turner_raw - 2){
    old_val = x_turner_raw;
    Serial.println(x_turner_raw);
 }
}

