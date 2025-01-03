 int relay = 8;
 volatile byte relayState = LOW;
 // PIR Motion Sensor is connected to D2.
 int PIRInterrupt = 2;
 // LDR pin is connected to Analog 0
 int LDRPin = A0;
 // LDR value is stored on LDR reading
 int LDRReading;
 // LDR Threshold value
 int LDRThreshold = 300;
 // Timer Variables
 long lastMotionTime = 0;
 long motionDelay = 3000; // 5 seconds delay after motion is detected
 void setup() {
 // Pin for relay module set as output
 pinMode(relay, OUTPUT);
 digitalWrite(relay, HIGH); // Relay OFF initially
 // PIR motion sensor set as an input
 pinMode(PIRInterrupt, INPUT);
 // Triggers detectMotion function on rising mode to handle motion events
 attachInterrupt(digitalPinToInterrupt(PIRInterrupt), detectMotion, RISING);
 // Serial communication for debugging purposes
 Serial.begin(9600);
 }
 void loop() {
 // Read the LDR value
 LDRReading = analogRead(LDRPin);
// Print LDR value to serial monitor (for debugging and threshold adjustment)
 Serial.println(LDRReading);
 // Check ambient light condition
 if (LDRReading > LDRThreshold) {
 // Room is dark
 digitalWrite(relay, LOW); // Keep LED ON
 relayState = HIGH;
 Serial.println("LED ON (Dark Room)");
 } else {
 // Room is bright
 if ((millis()- lastMotionTime) > motionDelay) {
 // If no motion detected recently, turn LED OFF
 digitalWrite(relay, HIGH); // Turn LED OFF
 relayState = LOW;
 Serial.println("LED OFF (Bright Room)");
 }
 }
 delay(50); // Small delay for stability
 }
 void detectMotion() {
 Serial.println("Motion Detected");
 // Turn LED ON for 5 seconds
 digitalWrite(relay, LOW); // Turn LED ON
 relayState = HIGH;
 lastMotionTime = millis();
 Serial.println("LED ON (Motion)");
 }
