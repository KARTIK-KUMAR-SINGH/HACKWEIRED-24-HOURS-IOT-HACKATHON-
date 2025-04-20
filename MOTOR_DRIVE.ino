void setup()
{
  pinMode(5, OUTPUT);  // M1 A (in1)(forward)
  pinMode(6, OUTPUT);  // M1 B (in2)(backward)
  pinMode(10, OUTPUT); // M2 A (in3)(forward)
  pinMode(11, OUTPUT); // M2 B (in4)(backward)


  pinMode(2, OUTPUT); // Enable 1 (enA)
  pinMode(3, OUTPUT); // Enable 2 (enB)
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);    

  
  Serial.begin(9600);
}

void loop()
{
  analogWrite(5, 0);
  analogWrite(6, 45);
  analogWrite(10,0);
  analogWrite(11, 45);
}