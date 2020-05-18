
// Sensor data

int led1 = A5;
//int led2 = D7;

int photoresistor = A0;
int analogValue;

int second_count = 0;

int light_time = 7200; // Two hours in seconds

bool light_active = false;

void setup() {
    
    // Leds
    pinMode(led1, OUTPUT);
    //pinMode(led2, OUTPUT);
    
    // Photoresistor
    pinMode(photoresistor, INPUT);

}


void loop() {
    
    // Read photoresistor value
    analogValue = analogRead(photoresistor);
    
    // Delay 1 seconds
    delay(1000);
    
    // Run second_count timer-
    second_count += 1;
    
    // If in light count down
    if (light_active == true) 
    {
        light_time -= 1;
    }
    
    // If on the 5th second : Publish to IFTTT
    if (second_count > 10) {
        // Alert Messages
        
        // Toggle light
        if (analogValue > 4 && analogRead(photoresistor) > 4) {
            digitalWrite(led1,LOW);
            //digitalWrite(led2,LOW);
            // If changed
            if (light_active == false) {
                Particle.publish("light-detect","light");
            }
            light_active = true;
        } else {
            digitalWrite(led1,HIGH);
            //digitalWrite(led2,HIGH);
            // If changed
            if (light_active == true) {
                Particle.publish("light-detect","dark");
            }
            light_active = false;
        }
        
        // Reset counter
        second_count = 0;
    }
}