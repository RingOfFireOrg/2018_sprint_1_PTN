// Include the Servo library 
#include <Servo.h> 
// Declare the Servo pin 
int servoPinLeft = 3; 
int servoPinRight = 2; 
int Shock = 0; //define shock port

int reedDigitalPin=6;
int Led=13;
boolean shouldMagnetRead = true;
// Create a servo object 
Servo ServoLeft, ServoRight; 
void setup() { 
   // We need to attach the servo to the used pin number 
   ServoLeft.attach(servoPinLeft); 
   ServoRight.attach(servoPinRight);
   pinMode(Shock, INPUT); //define shock sensor as a input port
    pinMode(Led,OUTPUT);
    
    while(digitalRead(Shock) == HIGH){

    }
    delay(2000);
    
    
}

void stop(){
    ServoLeft.write(90); 
        ServoRight.write(90);
}

void forward(){
    ServoLeft.write(168); 
    ServoRight.write(20); 
}

void loop(){ 
    // Make servo go to 0 degrees 
    forward(); 
    //delay(1000); 
    // Make servo go to 90 degrees 
    //ServoLeft.write(90); 
    //delay(1000); 
    // Make servo go to 180 degrees 
    //ServoLeft.write(180); 
    //delay(1000); 

    // Make servo go to 0 degrees 
    //ServoRight.write(0); 
    //delay(1000); 
    // Make servo go to 90 degrees 
    //ServoRight.write(90); 
    //delay(1000); 
    // Make servo go to 180 degrees 
    //ServoRight.write(180); 
    //delay(1000); 
    int numberOfMagnets=0;
    
    

    if(digitalRead(reedDigitalPin) == HIGH && shouldMagnetRead == true){
        numberOfMagnets++;
        digitalWrite(Led,HIGH);
        stop();
        delay(1000);
        forward();
        shouldMagnetRead = false;
    }
    else if(digitalRead(reedDigitalPin) == LOW) {
        digitalWrite(Led,LOW);
        shouldMagnetRead = true;
    }
    if(numberOfMagnets > 5){
         stop();
    }
}