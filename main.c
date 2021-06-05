#include "TM4C123GH6PM.h"
#include <math.h>



//Initialization function
void Sys_init(){
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
	//***********************************************************************

	SYSCTL_RCGCGPIO_R |= PA;							//Activate Port A Clock
	while((SYSCTL_RCGCGPIO_R&0x01)==0){};			//Wait for activation
  GPIO_PORTA_DIR_R |= pinsA;					//Set I/O
	GPIO_PORTA_DEN_R |= pinsA;					//Enable Digital output
	GPIO_PORTA_AMSEL_R &= ~pinsA;			//Disable analog
	GPIO_PORTA_AFSEL_R &= ~pinsA;			//Disable Alternate Function
	GPIO_PORTA_PCTL_R &= ~0xFFFFFF00;				//PTCL GPIO on PFA
	GPIO_PORTA_DATA_R &= ~pinsA;	
	//***********************************************************************
	SYSCTL_RCGCGPIO_R |= PB;							//Activate Port B Clock
	while((SYSCTL_RCGCGPIO_R&0x02)==0){};		//Wait for activation		
  GPIO_PORTB_DIR_R |= 0xE0;					   //Set I/O
	GPIO_PORTB_DEN_R |= 0xE0;					//Enable Digital output
	GPIO_PORTB_AMSEL_R &= ~0xE0;			//Disable analog
	GPIO_PORTB_AFSEL_R &= ~0xE0;			//Disable Alternate Function
	GPIO_PORTB_PCTL_R &= ~0xFFF00000;				//PTCL GPIO on PFB
	GPIO_PORTB_DATA_R &= ~0xE0;
}
//Declare Variables
double totaldistance, distance,latHome, lonHome, latDest, lonDest,differenceLon, differenceLat, a, c, latHomeTmp, latDestTmp, t = 0;
double pi = 3.141592653589793;
double R = 6371; //Radius of the Earth
int displayed_distance =0 ;
int ones,tens,hundreds=0;
//--------------------------------------------------------------------------
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


void delay(int n){
	int i,j;
	for(i=0;i<n;i++){
	for(j=0;j<n;j++){}}
}
void writeLED(){			//Write data on LEDs
	GPIO_PORTF_DATA_R &= ~PF123_mask;
	GPIO_PORTF_DATA_R |= RED;
}


void display(int hundreds,int tens,int ones){
	while(1){
		GPIO_PORTA_DATA_R &= 0X7F;
		GPIO_PORTA_DATA_R |= 0X60;
	switch(hundreds)
	{
		
		case 1 :
			      GPIO_PORTB_DATA_R = 0x30;
		        break;
		case 2 :
			      GPIO_PORTB_DATA_R = 0x6D;
		        break;
		case 3 :
			      GPIO_PORTB_DATA_R = 0x79;
		        break;
		case 4 :
			      GPIO_PORTB_DATA_R = 0x33;
		        break;
		case 5 :
			      GPIO_PORTB_DATA_R = 0x5B;
		        break;
		case 6 :
			      GPIO_PORTB_DATA_R = 0x5F;
		        break;
		case 7 :
			      GPIO_PORTB_DATA_R = 0x70;
		        break;
		case 8 :
			      GPIO_PORTB_DATA_R = 0x7F ;
		        break;
		case 9 :
			      GPIO_PORTB_DATA_R = 0x7B;
		        break;
		default :
			      GPIO_PORTB_DATA_R = 0x7E;
		        break;	
	}
	delay(500);
	GPIO_PORTA_DATA_R &= 0XBF;
		GPIO_PORTA_DATA_R |= 0XA0;
	switch(tens)
	{
		case 1 :
			      GPIO_PORTB_DATA_R = 0x30;
		        break;
		case 2 :
			      GPIO_PORTB_DATA_R = 0x6D;
		        break;
		case 3 :
			      GPIO_PORTB_DATA_R = 0x79;
		        break;
		case 4 :
			      GPIO_PORTB_DATA_R = 0x33;
		        break;
		case 5 :
			      GPIO_PORTB_DATA_R = 0x5B;
		        break;
		case 6 :
			      GPIO_PORTB_DATA_R = 0x5F;
		        break;
		case 7 :
			      GPIO_PORTB_DATA_R = 0x70;
		        break;
		case 8 :
			      GPIO_PORTB_DATA_R = 0x7F ;
		        break;
		case 9 :
			      GPIO_PORTB_DATA_R = 0x7B;
		        break;
		default :
			      GPIO_PORTB_DATA_R = 0x7E;
		        break;		
	}
	delay(500);
	GPIO_PORTA_DATA_R &= 0XDF;
	GPIO_PORTA_DATA_R |= 0XC0;
	switch(ones)
	{
		case 1 :
			      GPIO_PORTB_DATA_R = 0x30;
		        break;
		case 2 :
			      GPIO_PORTB_DATA_R = 0x6D;
		        break;
		case 3 :
			      GPIO_PORTB_DATA_R = 0x79;
		        break;
		case 4 :
			      GPIO_PORTB_DATA_R = 0x33;
		        break;
		case 5 :
			      GPIO_PORTB_DATA_R = 0x5B;
		        break;
		case 6 :
			      GPIO_PORTB_DATA_R = 0x5F;
		        break;
		case 7 :
			      GPIO_PORTB_DATA_R = 0x70;
		        break;
		case 8 :
			      GPIO_PORTB_DATA_R = 0x7F ;
		        break;
		case 9 :
			      GPIO_PORTB_DATA_R = 0x7B;
		        break;
		default :
			      GPIO_PORTB_DATA_R = 0x7E;
		        break;	
	}
 }
}

int main(){
	Sys_init();
	while(1){
				calc();
				latHome = latDest;
				lonHome = lonDest;
				latDest+=0.000001;
				lonDest+=0.000001;
				totaldistance += distance;
		if(totaldistance>0.1) {
				writeLED();
			displayed_distance = (int) (totaldistance *1000);
	     ones = displayed_distance%10;
	     displayed_distance /= 10;
	     tens= displayed_distance%10;
	     displayed_distance/=10;
	     hundreds = displayed_distance%10;
			display(hundreds,tens,ones);
			
			}  
			
	}

}
