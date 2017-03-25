/* Smart mouse code */

const int BAUD_RATE = 9600;

void setup()
{
	// initialize serial:
	Serial.begin(BAUD_RATE);

	// make the pins outputs:
	for (int i = 0; i <= 13; i++) {
		pinMode(i, INPUT);
	}

	Serial.print("Smartmouse setup() finished\n");

}

void loop()
{
  int val;
	// if there's any serial available, read it:
	while (Serial.available() > 0) {
		val = analogRead(8);
		Serial.println(val);
	}
}
