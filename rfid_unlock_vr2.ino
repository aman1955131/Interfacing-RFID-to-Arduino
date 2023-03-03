int count = 0;               // count = 0
char input[12];              // character array of size 12
boolean flag = 0;            // flag =0
const int relay = D6;
const int relay2 = D7;
char id[13] = "180041C56BF7";  


void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(relay2, OUTPUT);
  Serial.begin(9600);       // begin serial port with baud rate 9600bps
  digitalWrite(relay, HIGH);
  digitalWrite(relay2, HIGH);
}

void loop()
{
  if (Serial.available())
  {
    count = 0;
    while (Serial.available() && count < 12)         // Read 12 characters and store them in input array
    {
      input[count] = Serial.read();
      count++;
      delay(5);
    }
    Serial.print(input);                             // Print RFID tag number


    if ((input[0] ^ input[2] ^ input[4] ^ input[6] ^ input[8] == input[10]) &&
        (input[1] ^ input[3] ^ input[5] ^ input[7] ^ input[9] == input[11])) {
      if (compare()) {
        Serial.println("No Error");
        digitalWrite(relay, !digitalRead(relay));
        delay(3000);
        serialflush();
      }
      else {
        digitalWrite(relay2, !digitalRead(relay2));
        delay(3000);
        serialflush();
      }
    }
    else {
      Serial.println("Error");
    }
  }
}

void serialflush() {
  while (Serial.available() > 0) {
    char t = Serial.read();
  }
}

bool compare() {
  for (int i = 0; i < 12; i++) {
    if (input[i] != id[i]) {
      return false;
    }
  }
  return true;
}
