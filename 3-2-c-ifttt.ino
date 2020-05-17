// Channel stuff

// ID: 

// URL: https://api.thingspeak.com/update

// Write Key: 

// Read Key: 


// Webhooks and sensor data

int led1 = A5;
int led2 = D7;

int photoresistor = A0;
int analogValue;

int second_count = 0;

bool light_active = false;

void setup() {
    
    // Leds
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    
    // Photoresistor
    pinMode(photoresistor, INPUT);

}




void loop() {
    
    // Delay 1 seconds
    delay(1000);
    
    // Run second_count timer
    second_count += 1;
    
    // Read photoresistor value
    analogValue = analogRead(photoresistor);
    
    // If on the 30th second : Publish to web
    if (second_count % 5 == 0) {
        // Alert Message
        //Particle.publish("light_level", String::format("%d",analogValue), PRIVATE);
        
        // Toggle light
        if (analogValue > 10) {
            digitalWrite(led1,LOW);
            digitalWrite(led2,LOW);
            // If changed
            if (light_active == false) {
                Particle.publish("light-detect","light");
            }
            light_active = true;
        } else {
            digitalWrite(led1,HIGH);
            digitalWrite(led2,HIGH);
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