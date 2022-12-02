#include <ServoTimer2.h>
#include <VirtualWire.h>

#define velocidade1 6
#define velocidade2 5

#define motor1D 4
#define motor1E 9
#define motor2D 3 
#define motor2E 11

#define pinrf 13
#define pinservo 7

int valorx;
int valory;

int frente;
int re;

int virard;
int virare;

ServoTimer2 servo;

struct tipopacote{
  int valor1;
  int valor2;
};

tipopacote pacote;

uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

void setup() {
 
vw_set_rx_pin(pinrf);
vw_setup(2000);
vw_rx_start();

pinMode(pinservo, OUTPUT);

pinMode(velocidade1, OUTPUT);
pinMode(velocidade2, OUTPUT);

pinMode(motor1D, OUTPUT);
pinMode(motor1E, OUTPUT);
pinMode(motor2D, OUTPUT);
pinMode(motor2E, OUTPUT);

servo.attach(pinservo);

Serial.begin(9600);

}

void loop() {

valorx = pacote.valor2;
valory = pacote.valor1;

frente = map(valory, 400, 1023, 0 ,255);
re = map(valory, 400, 0, 0, 255);

if( vw_have_message()){

  vw_get_message(buf, &buflen);
  memcpy(&pacote, &buf, buflen);
  Serial.println(valorx);

  if(valorx >= 550){

   virard = map(valorx, 530, 1023, 1488, 750);
   servo.write(virard);
  
  } else if (valorx <= 450){
    virare = map(valorx, 0, 470, 2250, 1505);
    servo.write(virare);
  
  } else{
    servo.write(1500);
  }
  if(valory >=400){
    
    analogWrite(velocidade1, frente);
    analogWrite(velocidade2, frente);

    digitalWrite(motor1D, HIGH);
    digitalWrite(motor2D, HIGH);

  }else if (valory <= 300){

    analogWrite(velocidade1, re);
    analogWrite(velocidade2, re);
    
    digitalWrite(motor1E, HIGH);
    digitalWrite(motor2E, HIGH);

  }
  else{
        
    digitalWrite(motor1D, LOW);
    digitalWrite(motor2D, LOW);
    digitalWrite(motor1E, LOW);
    digitalWrite(motor2E, LOW);
  }

}

}
