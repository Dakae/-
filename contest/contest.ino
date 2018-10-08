#include <Servo.h>

typedef struct moter{
    int md;
    int ms;
}M;

typedef struct sencer{
    int in;
}S;

/*typedef */struct output1{
    int out;
}output1;

int speeds = 180;

Servo gateServo;

struct moter attackMoter = {4,5};   //MT1
struct moter bowMoter = {7,6};      //MT2
struct output1 light = {2};


struct sencer lightsencer = {16};
struct sencer fencesencer = {17};
struct sencer come1 = {18};
struct sencer come2 = {19};

void setup() {
  
    pinMode(attackMoter.md,OUTPUT);
    pinMode(attackMoter.ms,OUTPUT);
    pinMode(bowMoter.md,OUTPUT);
    pinMode(bowMoter.ms,OUTPUT);

    pinMode(light.out,OUTPUT);

    pinMode(lightsencer.in,INPUT);
    pinMode(fencesencer.in,INPUT);
    pinMode(come1.in,INPUT);
    pinMode(come2.in,INPUT);

    gateServo.attach(11);
    
    Serial.begin(9600);
}

void attack(int n){
    digitalWrite(attackMoter.md,LOW);
    if (n) {
        analogWrite(attackMoter.ms,speeds);
    }
    else {
        analogWrite(attackMoter.ms,0);
    }
}

void bow(int n){
    digitalWrite(bowMoter.md,LOW);
    if (n) {
        analogWrite(bowMoter.ms,speeds);
    }
    else {
        analogWrite(bowMoter.ms,0);
    }
}

void gateopen(int n){
    
    if (n==1) {
        gateServo.write(0);
    }
    else if (n==0){
        gateServo.write(90);
    }
}

void islight(int n){
    if(n==1){
      analogWrite(light.out,255);
    }
    else if(n==0){
      analogWrite(light.out,0);
    }
}

int isDay(int n){
    if (n>450){
      Serial.println("Day");
        return 1;
    }
    else 
      Serial.println("Night");
        return 0;
}//sencer 16

int isfence(int n){
    if(n<800){
      return 1;
    }
    else {
      return 0;
    };
}//sencer 17

int whoiscome(int a, int b){
    if(a>450&&b>450){
        return 1;
    }
    if(a<450&&b>450){
        return 0;
    }
    else 
        return -1;
}//sencer 18,19


void loop() {
      //낮인경우
    if(isDay(analogRead(lightsencer.in))==1){
       gateopen(1);
      islight(0);

      if(whoiscome(analogRead(come1.in),analogRead(come2.in))==1){
        gateopen(1);
        bow(1);
        }
      else{
          bow(0);
        }
      if(whoiscome(analogRead(come1.in),analogRead(come2.in))==0){
        gateopen(1);
        delay(3000);
        }
      if(isfence(analogRead(fencesencer.in))){
        gateopen(0);
        delay(5000);
        attack(1);
        }
        else {
            attack(0);
        }
      }
      //밤인 경우
    else if(isDay(analogRead(lightsencer.in))==0){
      gateopen(0);
      islight(1);

      if(whoiscome(analogRead(come1.in),analogRead(come2.in))==1){
        gateopen(1);
        delay(5000);
        }
      if(isfence(analogRead(fencesencer.in))){
        attack(1);
        }
        else {
            attack(0);
        }
      }
}
