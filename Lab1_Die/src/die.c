#include <pic14/pic12f675.h>
 
void delay (unsigned int tiempo);
int counter = 0;

void main(void)
{
    TRISIO=0b00100000;  //Se deja el pin para el boton en alto para que sea entrada    
    GPIO = 0; // Poner todos los pines en bajo
	ANSEL = 0;
    CMCON = 7;
 
    unsigned int time = 100;
 
    //Loop forever
    while ( 1 )
    {
		counter = counter + 1;
		if (GP5 == 1){  // si el boton se presiona
			if(counter==1){
				GP0=1;
				GP1=0;
				GP2=0;
				GP4=0;
				delay(50000);	
				counter=0;
				continue;
			}
			if(counter==2){
				GP0=0;
				GP1=1;
				GP2=0;
				GP4=0;
				delay(50000);	
				counter=0;
				continue;
			}
			if(counter==3){
				GP0=1;
				GP1=1;
				GP2=0;
				GP4=0;
				delay(50000);	
				counter=0;
				continue;
			}
			if(counter==4)
			{
				GP0=0;
				GP1=1;
				GP2=1;
				GP4=0;
				delay(50000);	
				counter=0;
				continue;
			}
			if(counter==5)
			{
				GP0=1;
				GP1=1;
				GP2=1;
				GP4=0;
				delay(50000);	
				counter=0;
				continue;
			}
			if(counter==6)
			{
				GP0=0;
				GP1=1;
				GP2=1;
				GP4=1;
				delay(50000);	
				counter=0;
				continue;
			}
		}
		if (counter == 6){
			counter=0;
			continue;
		}
    }
 
}

void delay(unsigned int tiempo)
{
	unsigned int i;
	unsigned int j;

	for(i=0;i<tiempo;i++)
	  for(j=0;j<1275;j++);
}
