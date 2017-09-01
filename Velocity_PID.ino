#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>
#include <Servo.h>

Encoder motorEncoder(2, 3);
Servo victor;

int prev_enc_val = 0;
int prev_error = 0;
int integrated_error = 0;

int current_vel;

void setup() {
  // put your setup code here, to run once:

  pinMode(2, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(13, INPUT);
  victor.attach(9);
  
  
  Serial.begin(9600);
  Serial.print("Current Error");
  Serial.print("\t");
  Serial.print("Differentiated Error");
  Serial.print("\t");
  Serial.print("Integrated Error");
  Serial.print("\t");
  Serial.print("Current Velocity");
  Serial.print("\t");
  Serial.println("Commanded Velocity"); 
}

void loop() {

  boolean disabled = (digitalRead(13) == 1);

  int commanded_vel = (analogRead(A0) - 512)*0.1;
  int cur_enc_val = motorEncoder.read();

  current_vel = ((9*current_vel) + (1*(cur_enc_val - prev_enc_val)))/10;

  int current_error = current_vel - commanded_vel;
  int differentiated_error = 0;
  
  if(disabled)
  {
    integrated_error = 0;
    differentiated_error = 0;
  }
  else
  {
    integrated_error += current_error;
    differentiated_error = current_error - prev_error;
  }

  float P = 30.0;
  float I = 0.5;
  float D = 2.5;
  float FF = 1.0;

  float output;

  if(disabled)
    output = 4;
  else
    output = P*current_error + I*integrated_error + D*differentiated_error + FF*commanded_vel;

  Serial.print(current_error);
  Serial.print("\t");
  Serial.print(differentiated_error);
  Serial.print("\t");
  Serial.print(integrated_error);
  Serial.print("\t");
  Serial.print(current_vel);
  Serial.print("\t");
  Serial.println(commanded_vel);

  victor.write(map(output, -256, 256, 0, 180));

  prev_enc_val = cur_enc_val;
  prev_error = current_error;

  delay(100);
}


