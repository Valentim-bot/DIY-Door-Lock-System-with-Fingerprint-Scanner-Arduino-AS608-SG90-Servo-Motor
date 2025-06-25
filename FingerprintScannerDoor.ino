
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define LED_PIN 5  // Define LED pin

Servo myservo;  // create Servo object to control a servo
// twelve Servo objects can be created on most boards

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

int fingerprintID = 0;
String IDname;

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);  // Set LED pin as output

  // Fingerprint sensor module setup
  finger.begin(57600);

   myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  myservo.write(pos); 


  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

void loop() {
  fingerprintID = getFingerprintIDez();
  delay(50);

  if (fingerprintID == 1 || fingerprintID == 3 || fingerprintID == 4 || fingerprintID == 5) {
    IDname = "Itamar";
    
    pos = 0;    // variable to store the servo position
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    digitalWrite(LED_PIN, HIGH);  // Turn on LED
    delay(1900);                       // waits 1900 ms for the servo to reach the position

    pos = 180;    // variable to store the servo position
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(1900);                       // waits 15 ms for the servo to reach the position  
    Serial.println("LED ON: Authorized Fingerprint Detected");
 

  } else {
    digitalWrite(LED_PIN, LOW);  // Turn off LED
    Serial.println("LED OFF: Unauthorized Fingerprint");
    pos = 180;    // variable to store the servo position
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);
    pos = 179;    // variable to store the servo position
    myservo.write(pos);
    delay(500);
  }
}

// Returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK) return -1;
  
  // Found a match!
  Serial.print("Found ID #"); 
  Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); 
  Serial.println(finger.confidence);
  return finger.fingerID; 
}
