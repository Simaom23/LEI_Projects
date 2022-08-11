int WINNING_TIME=20000,LED_TRANSITION_TIME=500,ATTEMPTS=0,BLINKING_DELAY=400,lastbuttonState=0,buttonState=0,buttonPlay=11,buttonReset=12;
int LEDS[]={2,3,4,5,6,7,8,9,10};
int LEDS_ON[]={0,0,0,0,0,0,0,0,0};
long timepass=0, lastDebounceTime=0;
void LED_SEQUENCE_ATTEMPT(){
  for(byte i=0; i<=8; i++){
    if(buttonState==digitalRead(buttonReset)){
      LED_RESET();
      i=0;
    }
    if(digitalRead(buttonPlay)==lastbuttonState)
      lastDebounceTime=millis();
    if((millis()-lastDebounceTime)>50)
      if (digitalRead(buttonPlay)!=buttonState){
          buttonState=digitalRead(buttonPlay);
          if (buttonState==1)
            ATTEMPTS++;
      }
    buttonState=0;
    digitalWrite(LEDS[i], HIGH);
    timepass=millis();
    while(millis()-timepass<=LED_TRANSITION_TIME)
      if(buttonState==digitalRead(buttonPlay) && buttonState!=digitalRead(LEDS[i])){
        digitalWrite(LEDS[i], HIGH);
        LEDS_ON[i]=1;
      }
    if(LEDS_ON[i]==0)
      digitalWrite(LEDS[i], LOW);
  } 
}
void LED_RESET(){
  ATTEMPTS=0;
  for(byte i=0; i<=8; i++){
    digitalWrite(LEDS[i], LOW);
    LEDS_ON[i]=0;
  }
}
void LED_VICTORY(){
  int LEDS_ON_HIGH=0;
  for(byte i=0; i<=8; i++)
    if(LEDS_ON[i]==1)
      LEDS_ON_HIGH++;
  if(LEDS_ON_HIGH==9){
    timepass=millis();
    while(millis()-timepass<=WINNING_TIME){
      for(byte i=0; i<=8; i++){
        digitalWrite(LEDS[i], HIGH);
        LEDS_ON[i]=1;
      }
      delay(BLINKING_DELAY);
      for(byte i=0; i<=8; i++){
        digitalWrite(LEDS[i], LOW);
        LEDS_ON[i]=0;
      }
      delay(BLINKING_DELAY);
    }
   Serial.println("O seu numero de cliques foi:");
   Serial.println(ATTEMPTS);
   ATTEMPTS=0;
  }
}
void setup() {
  for(byte i=0; i<=8; i++)
    pinMode(LEDS[i], OUTPUT);
  pinMode(11, INPUT_PULLUP);
  pinMode(12,INPUT_PULLUP);
  Serial.begin(9600);
}
void loop(){
  LED_SEQUENCE_ATTEMPT();
  LED_VICTORY();
}
