#include "TM4C123GH6PM.h"
#include <math.h>

//Initialization function
void initLEDS(){
	SYSCTL_RCGCGPIO_R |= 0x20;							//Activate Port F Clock
	while((SYSCTL_RCGCGPIO_R&0x20)==0);			//Wait for activation
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;			//Unlock Port F
	GPIO_PORTF_CR_R |= PF123_mask;					//Allow changes to PF4 to 0
  GPIO_PORTF_DIR_R |= PF123_mask;					//Set I/O
	GPIO_PORTF_DEN_R |= PF123_mask;					//Enable Digital output
	GPIO_PORTF_AMSEL_R &= ~PF123_mask;			//Disable analog
	GPIO_PORTF_AFSEL_R &= ~PF123_mask;			//Disable Alternate Function
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;				//PTCL GPIO on PF4-0
	GPIO_PORTF_DATA_R &= ~PF123_mask;				//Init LEDs to be off
}
//Declare Variables
double distance,latHome, lonHome, latDest, lonDest,differenceLon, differenceLat, a, c, latHomeTmp, latDestTmp = 0;
double pi = 3.141592653589793;
double R = 6371; //Radius of the Earth
void calc()
{
    latHomeTmp = (pi / 180) * (latHome);
    latDestTmp = (pi / 180) * (latDest);
    differenceLon = (pi / 180) * (lonDest - lonHome);
    differenceLat = (pi / 180) * (latDest - latHome);
    a = sin(differenceLat / 2.) * sin(differenceLat / 2.) +
        cos(latHomeTmp) * cos(latDestTmp) *
        sin(differenceLon / 2.) * sin(differenceLon / 2.);
    c = 2 * atan2(sqrt(a), sqrt(1 - a));
    distance = R * c;
}

void writeLED(){			//Write data on LEDs
	GPIO_PORTF_DATA_R &= ~PF123_mask;
	GPIO_PORTF_DATA_R |= RED;
}
int main(){
	initLEDS();
	while(1){
			if(distance>0.1){
				writeLED();
			}else{
				calc();
				latDest+=0.000001;
				lonDest+=0.000001;

		}
	}
}