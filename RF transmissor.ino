#include <VirtualWire.h>             

#define pinpotx A0
#define pinpoty A1
#define pinrf 12 
struct tipopacote {
  int valor1;
  int valor2;
};

tipopacote pacote;

void setup() {

vw_set_tx_pin(pinrf);
vw_set_ptt_inverted(true);
vw_setup(2000);

} 

void loop() {

int valorx = analogRead(pinpotx);
int valory = analogRead(pinpoty);

pacote.valor2 = valorx;
pacote.valor1 = valory;

vw_send((uint8_t*)&pacote, sizeof(pacote));
vw_wait_tx();
delay(100);

}


