#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

// Variables globales
int intr_count = 0;
int sec = 0;
int msec = 0;
int color = 5;
int estado;
int guess_length = 4;
int sequence[14] = {2,1,0,1};
int sequence_index = 0;
int i;
int tiempo = 2;

//Definicion de estados para FSM
#define SG 0 // Start Game
#define DS 1 // Display Sequence
#define SI  2 // Sequence Input
#define CL  3 // Change Level
#define GF 4 // Game finished
#define WT 5 //Waiting Time

int estado; // Se define el estado base o default.

//Definicion de los funciones
void GreenLight(void){
    PORTB = (0<<PB0)|(1<<PB1)|(0<<PB2)|(0<<PB3); //Activa luz verde 
}
void BlueLight(void){
    PORTB = (0<<PB0)|(0<<PB1)|(0<<PB2)|(1<<PB3); //Activa luz azul 
}
void RedLight(void){
    PORTB = (0<<PB0)|(0<<PB1)|(1<<PB2)|(0<<PB3); //Activa luz roja 
}
void YellowLight(void){
    PORTB = (1<<PB0)|(0<<PB1)|(0<<PB2)|(0<<PB3); //Activa luz amarilla 
}
void AllOff(void){
    PORTB = (0<<PB0)|(0<<PB1)|(0<<PB2)|(0<<PB3); //Activa luz amarilla 
}
void Blink(void){
    PORTB ^= (1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3); // Parpadea todas
}

void CreateSequence(void){
    for (i = 0; i < guess_length; i++){
      sequence[i] = intr_count % 4;
    }
}


void lights_setup() {//funciones para configurar puertos de semaforo
  GIMSK |= 0xD8; // Enables Ports B and C Pin Change Interrupts
  PCMSK2 |= 0b11111111; // PCINT11 - pD0
  PCMSK1 |= 0b00000001; // PCINT8 - pA0
  //PCMSK0 |= 0b10000000; // PCINT11 - pD0
  DDRB = 0x0F; //Configuracion del puerto
  TCCR0B = 0x5; //para el reloj
  MCUCR |= (1<<ISC11);    // se configura con flanco negativo del reloj
}

void timer_setup(){//funcion para inicializar el timer
  TCCR0A=0x00;   //Se usa el modo normal de operacion del timer
  TCCR0B=0x00;
  TCCR0B |= (1<<CS00)|(1<<CS02);   //Para disminuir la frecuencia
  sei();

  TCNT0 = 0; //InicializarelTimer0
  TIMSK  |= (1 << TOIE0); //activa interrupcion de timer 0


}

void statusChange(){
  switch (estado){
    case WT:
      
      if (color < 5){
          estado = SG;
          intr_count = 0; //resetea contadores
          sec = 0;
          msec =0;
      }
      else{
        estado = WT; // mantiene el estado hasta que el boton se presiona
      }
      break;

    case SG:
      if (msec == 4){
        estado = DS;
        intr_count = 0;
        sec = 0;
        msec =0;
        sequence_index = 0;
        guess_length = 4;
        color = 5; // desactiva el boton
        //CreateSequence();
      }
      else{
        estado = SG;
      }
      break;

    case DS:


        if (sequence[sequence_index] == 0){
            GreenLight();
        }
        else if (sequence[sequence_index] == 1){
            RedLight();
        }
        else if (sequence[sequence_index] == 2){
            BlueLight();
        }
        else if (sequence[sequence_index] == 3){
            YellowLight();
        }


      if (sec == tiempo){ // si pasaron 2 segundos cambia a siguiente
        if (sequence_index >= guess_length-1){
          estado = SI;
          intr_count = 0;
          sec = 0;
          msec =0;
          AllOff();
          sequence_index = 0;
        } 
        else{
          sequence_index++;
          estado = DS;
          sec = 0;
        }
      }
      else{
          estado = DS;
      }
      break;

    case SI:
      if (color == 5){
        estado = SI;
      }
      else {
        
        if (color == 0){
            GreenLight();
        }
        else if (color == 1){
            RedLight();
        }
        else if (color == 2){
            BlueLight();
        }
        else if (color == 3){
            YellowLight();
        }
        if (msec == 3){
          msec = 0;
        if (color == sequence[sequence_index]){
            color = 5;
            AllOff();
            if (sequence_index == guess_length-1){
              estado = CL;
              sec = 0;
            }
            else{
              estado = SI;
              sequence_index++;
            }
        } else{
            AllOff();
            estado = GF;
            msec = 0;
        }
        }
      }
      break;

    case CL:

      estado = DS;
      intr_count = 0;
      sec = 0;
      msec =0;
      sequence_index = 0;
      guess_length++;
      color = 5; // desactiva el boton
      //CreateSequence();
      break;

    case GF:
      if (msec == 6){
        estado = WT;
        intr_count = 0;
        sec = 0;
        msec =0;
        color = 5;
        //CreateArray();
      }
      else{
        estado = GF;
      }
      break;


    default:
      break;
  }
}

int main(void)
{

  lights_setup();
  timer_setup();
  estado = WT;

  while (1) {
    statusChange();
  }
}

ISR (TIMER0_OVF_vect){      //Interrupcion por contador
  if (intr_count == 10){  //cuenta medio segundo para los parpadeps
    if( estado == SG ){
      Blink();
    }
    else if( estado == GF){
      Blink();
    }
    ++msec; //contador de medios de segundo
  }
  if (intr_count == 60){    // cuenta un segundo
    intr_count = 0;
    ++sec; // cuenta un segundo
  }
  else intr_count++;
}

ISR (INT1_vect){        // Interrupcion por boton
  color = 3;
}

ISR (PCINT1_vect){        // Interrupcion por boton
  color = 1;
}

ISR (PCINT2_vect){        // Interrupcion por boton
 color = 0;
}

ISR (INT0_vect){        // Interrupcion por boton
  color = 2;
} 