// Include the Servo library 
#include <Servo.h> 



// Declare the Servo pin 
int pushPin = 0; //define shock port
int servoPinRight = 2; 
int servoPinLeft = 3; 
int trigPin = 4;
int echoPin = 5;
int reedDigitalPin=6;
int servoPinSample = 7;
int ledPin=13;


// Declare variables for logic
boolean shouldMagnetRead = true;
long duration;
int distance;
int numberOfMagnets=0;
boolean stopForever = false;
// Create a servo object 
Servo ServoLeft, ServoRight, ServoSample; 

void setup() { 
   // We need to attach the servo to the used pin number 
    ServoLeft.attach(servoPinLeft); 
    ServoRight.attach(servoPinRight);
    ServoSample.attach(servoPinSample);
    // Initialise Servo Speed
    ServoLeft.write(90);
    ServoRight.write(90);
    ServoSample.write(90);

    pinMode(pushPin, INPUT); //define shock sensor as a input port
    pinMode(ledPin,OUTPUT);
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin(9600); // Starts the serial communication

    
    while(digitalRead(pushPin) == HIGH){
        // No Operation
        // Wait until a push button is pressed
    }
    delay(2000);
    
    
}

// Changed all the speed control functions to help ensure a drift LEFT.
//  ie- stop left first, start right first
// Included a small delay to force left on stops and starts.  -Glen
void stop(){
    ServoLeft.write(90);
    delay(100);
    ServoRight.write(90);

}

void forward(){
    ServoRight.write(33);
    delay(100);
    ServoLeft.write(148);  
}

void forwardSlow(){
    ServoRight.write(60); 
    ServoLeft.write(128); 
}

void backward(){
    ServoLeft.write(40); 
    ServoRight.write(148); 
}

void backup(){
    ServoLeft.write(0); 
    ServoRight.write(180); 
}
void sample(){
    delay(200);
    ServoSample.write(2);
    delay(1000);
    ServoSample.write(120);
    delay(1000);
    ServoSample.write(30);
//    delay(1000);
//    ServoSample.write(90);
}


void loop(){ 
    if(stopForever == true){
       ServoSample.write(110);
       digitalWrite(ledPin,HIGH);
       delay(200);
       ServoSample.write(130);
       digitalWrite(ledPin,LOW);

       delay(200);
    
        return;
    }
    delay(50);

    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance= duration*0.034/2;
    // Prints the distance on the Serial Monitor
    Serial.print("Distance: ");
    Serial.println(distance);

    if(digitalRead(reedDigitalPin) == HIGH && shouldMagnetRead == true){
        numberOfMagnets++;
        digitalWrite(ledPin,HIGH);
        stop();
        sample();
        forwardSlow();   //uncommented and changed to slow this so we start forward while near the magnet 
        delay(100); 
        shouldMagnetRead = false;
    }
    else if(digitalRead(reedDigitalPin) == LOW) {
        digitalWrite(ledPin,LOW);
        shouldMagnetRead = true;
        
    }
    /*
    if(numberOfMagnets > 5){
         stop();
         stopForever = true;
    }else{
        forward(); 
    }*/

    if(distance < 20){
        forwardSlow();
    }else{
        forward();
    }
    
    if(distance < 15){
        stop();
        //delay(1000);
        //backward();
        //delay(1000);        
        stopForever = true;
    }
}