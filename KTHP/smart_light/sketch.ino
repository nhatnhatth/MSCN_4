#define BLYNK_TEMPLATE_ID "TMPL6SVPzxYwS"
#define BLYNK_TEMPLATE_NAME "smart light"
#define BLYNK_AUTH_TOKEN "EuSVkcnuhs-23UQUlPJk_qTWpi2VU0ql"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int led =13;            // led is connected to esp32 D13 

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

BlynkTimer timer;


#define button1_pin 5

#define relay1_pin 4

int relay1_state = 0;


//Change the virtual pins according the rooms
#define button1_vpin    V1

//------------------------------------------------------------------------------
// This function is called every time the device is connected to the Blynk.Cloud
// Request the latest state from the server
BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
}

//--------------------------------------------------------------------------
// This function is called every time the Virtual Pin state change
//i.e when web push switch from Blynk App or Web Dashboard
BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
} 

void setup() {
  pinMode(button1_pin, INPUT_PULLUP);
  pinMode(relay1_pin, OUTPUT);
  //During Starting all Relays should TURN OFF
  digitalWrite(relay1_pin, HIGH);
  Blynk.begin(auth, ssid, pass);
  Serial.begin(115200);
  pinMode(led, OUTPUT);     
  pinMode(12, INPUT); 
}

void loop() {
  int a = analogRead(2);
  int value = analogRead(12);
  Serial.println(a);
  Serial.println(value);
  if(a>1000 && value>1000){
    Serial.println("a");
    digitalWrite(led, HIGH);
  }else{
    digitalWrite(led, LOW);
  }
  Blynk.run();
  timer.run();
  listen_push_buttons();
}

void listen_push_buttons(){
    //--------------------------------------------------------------------------
    if(digitalRead(button1_pin) == LOW){
      delay(200);
      control_relay(1);
      Blynk.virtualWrite(button1_vpin, relay1_state); //update button state
    }
}


void control_relay(int relay){
  //------------------------------------------------
  if(relay == 1){
    relay1_state = !relay1_state;
    digitalWrite(relay1_pin, relay1_state);
    Serial.print("Relay1 State = ");
    Serial.println(relay1_state);
    delay(50);
  }
}