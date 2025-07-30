int x; // Initializing variables
int y;
int z;
int w;
int a = 20;
int previousA = 20;

void setup() {
  // Motor control pins
  pinMode(2, OUTPUT); // Left motor IN1
  pinMode(3, OUTPUT); // Left motor IN2
  pinMode(5, OUTPUT); // Enable pin for left motor (ENA)
  pinMode(12, OUTPUT); // Right motor IN3
  pinMode(13, OUTPUT); // Right motor IN4
  pinMode(6, OUTPUT); // Enable pin for right motor (ENB)
  
  // DTMF input pins
  pinMode(8, INPUT);  // Output from D0 pin of DTMF
  pinMode(9, INPUT);  // Output from D1 pin of DTMF
  pinMode(10, INPUT); // Output from D2 pin of DTMF
  pinMode(11, INPUT); // Output from D3 pin of DTMF

  Serial.begin(9600); // Begin serial communication between Arduino and laptop

  // Enable both motors
  digitalWrite(5, HIGH); // Set ENA to HIGH
  digitalWrite(6, HIGH); // Set ENB to HIGH
}

void decoding() { // Decodes the 4-bit binary number into decimal number
  a = x + (y << 1) + (z << 2) + (w << 3);
}

void printing() { // Prints the value received from input pins 8, 9, 10 and 11 respectively
  Serial.print(" x ");
  Serial.print(x);
  Serial.print(" y ");
  Serial.print(y);
  Serial.print(" z ");
  Serial.print(z);
  Serial.print(" w ");
  Serial.print(w);
  Serial.print(" a ");
  Serial.print(a);
  Serial.println();
}

void move_forward() { // Both side tires of bot move forward
  digitalWrite(2, HIGH); // Left motor forward
  digitalWrite(3, LOW);
  digitalWrite(12, HIGH); // Right motor forward
  digitalWrite(13, LOW);
}

void move_backward() { // Both side tires of bot move backward
  digitalWrite(2, LOW); // Left motor backward
  digitalWrite(3, HIGH);
  digitalWrite(12, LOW); // Right motor backward
  digitalWrite(13, HIGH);
}

void move_left() { // Only left side tires move forward
  digitalWrite(2, HIGH); // Left motor forward
  digitalWrite(3, LOW);
  digitalWrite(12, LOW); // Right motor stop
  digitalWrite(13, LOW);
}

void move_right() { // Only right side tires move forward
  digitalWrite(2, LOW); // Left motor stop
  digitalWrite(3, LOW);
  digitalWrite(12, HIGH); // Right motor forward
  digitalWrite(13, LOW);
}

void halt() { // All motors stop
  digitalWrite(2, LOW); // Left motor stop
  digitalWrite(3, LOW);
  digitalWrite(12, LOW); // Right motor stop
  digitalWrite(13, LOW);
}

void reading() { // Take readings from input pins that are connected to DTMF D0, D1, D2 and D3 pins
  x = digitalRead(8);
  y = digitalRead(9);
  z = digitalRead(10);
  w = digitalRead(11);
}

void loop() {
  reading();
  decoding();

  if (a != previousA) { // Only act if the value has changed
    switch (a) {
      case 2:  // 0010 in binary
        move_forward();
        break;
      case 8:  // 1000 in binary
        move_backward();
        break;
      case 4:  // 0100 in binary
        move_left();
        break;
      case 6:  // 0110 in binary
        move_right();
        break;
      case 0:  // 0000 in binary
      default:
        halt();
        break;
    }
    printing();
    previousA = a; // Save the current value as previous
  }

  delay(100); // Add a small delay to avoid reading noise
}