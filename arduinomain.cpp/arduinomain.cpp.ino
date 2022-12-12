int ledValue = HIGH;
int pin = 13;

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(0);
  pinMode(pin, OUTPUT);    // sets the digital pin 13 as output
  digitalWrite(pin, ledValue);
}

void HandleCommand(String command){
  ledValue = ledValue == HIGH ? LOW : HIGH;
  digitalWrite(pin, ledValue);
}

void loop() {
  if (Serial.available() > 0) {
    auto text = Serial.readString();
    HandleCommand(text);
  }
}
