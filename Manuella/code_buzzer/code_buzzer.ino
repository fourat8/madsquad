//int bouton = 6;
int HP = 7;
void setup() {
  // put your setup code here, to run once:
  //pinMode(bouton, INPUT);
  pinMode(HP,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  //int boutonEtat = digitalRead(bouton);

  
    tone(HP, 300, 100);
    delay(200);
  
}
