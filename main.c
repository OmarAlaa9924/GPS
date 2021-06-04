#include "TM4C123GH6PM.h"
#include <math.h>


//Initialization function
void Sys_init(){
	SYSCTL_RCGCGPIO_R |= 0x20;				//Activate Port F Clock
	while((SYSCTL_RCGCGPIO_R&0x20)==0);			//Wait for activation
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;			//Unlock Port F
	GPIO_PORTF_CR_R |= PF123_mask;				//Allow changes to PF4 to 0
        GPIO_PORTF_DIR_R |= PF123_mask;				//Set I/O
	GPIO_PORTF_DEN_R |= PF123_mask;				//Enable Digital output
	GPIO_PORTF_AMSEL_R &= ~PF123_mask;			//Disable analog
	GPIO_PORTF_AFSEL_R &= ~PF123_mask;			//Disable Alternate Function
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;			//PTCL GPIO on PF4-0
	GPIO_PORTF_DATA_R &= ~PF123_mask;			//Init LEDs to be off
	//***********************************************************************
	
	SYSCTL_RCGCGPIO_R |= PA;				//Activate Port A Clock
	while((SYSCTL_RCGCGPIO_R&0x01)==0){};			//Wait for activation
        GPIO_PORTA_DIR_R |= pinsA;			        //Set I/O
	GPIO_PORTA_DEN_R |= pinsA;				//Enable Digital output
	GPIO_PORTA_AMSEL_R &= ~pinsA;			        //Disable analog
	GPIO_PORTA_AFSEL_R &= ~pinsA;			        //Disable Alternate Function
	GPIO_PORTA_PCTL_R &= ~0xFFFFFF00;		        //PTCL GPIO on PFA
	GPIO_PORTA_DATA_R &= ~pinsA;	
	//***********************************************************************
	SYSCTL_RCGCGPIO_R |= PB;				//Activate Port B Clock
	while((SYSCTL_RCGCGPIO_R&0x02)==0){};			//Wait for activation
        GPIO_PORTB_DIR_R |= pinsB;			        //Set I/O
	GPIO_PORTB_DEN_R |= pinsB;				//Enable Digital output
	GPIO_PORTB_AMSEL_R &= ~pinsB;			        //Disable analog
	GPIO_PORTB_AFSEL_R &= ~pinsB;			        //Disable Alternate Function
	GPIO_PORTB_PCTL_R &= ~0xFFFFFF00;			//PTCL GPIO on PFB
	GPIO_PORTB_DATA_R &= ~pinsB;
}
//Declare Variables
double totaldistance, distance,latHome, lonHome, latDest, lonDest,differenceLon, differenceLat, a, c, latHomeTmp, latDestTmp, t = 0;
double pi = 3.141592653589793;
double R = 6371; //Radius of the Earth
int displayed_distance =0 ;
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
	for(j=0;j<3180;j++){}}
}
void writeLED(){			//Write data on LEDs
	GPIO_PORTF_DATA_R &= ~PF123_mask;
	GPIO_PORTF_DATA_R |= RED;
}


void display(int d){
	int num1=0;
	int num2=0;
	int num3=0;
	num3 = d%10;
	d /= 10;
	num2 = d%10;
	d/=10;
	num1 = d%10;
	switch(num3)
	{
		case 1 :
		        GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R |= PB7;
		        break;
		case 2 :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R |= PB6;
		        GPIO_PORTB_DATA_R &= ~(PB7);
		        break;
		case 3 :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R |= PB6;
		        GPIO_PORTB_DATA_R |= PB7;
		        break;
		case 4 :
		        GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R |=  PB5;
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R &= ~(PB7);
		        break;
		case 5 :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R |=  PB5;
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R |=  PB7;
		        break;
		case 6 :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R |=  PB5;
		        GPIO_PORTB_DATA_R |= PB6;
		        GPIO_PORTB_DATA_R &= ~(PB7);
		        break;
		case 7 :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R |=  PB5;
		        GPIO_PORTB_DATA_R |= PB6;
		        GPIO_PORTB_DATA_R |= PB7;
		        break;
		case 8 :
			GPIO_PORTB_DATA_R |= PB4;
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R &= ~(PB7);
		        break;
		case 9 :
			GPIO_PORTB_DATA_R |= PB4;
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R |= PB7;
		        break;
		default :
			GPIO_PORTB_DATA_R &= ~(PB4);
		        GPIO_PORTB_DATA_R &= ~(PB5);
		        GPIO_PORTB_DATA_R &= ~(PB6);
		        GPIO_PORTB_DATA_R &= ~(PB7);
		        break;	
	}
	switch(num2)
	{
		case 1 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R |= PB3;          //b0=1         binary output 0001   (All the outputs are the same in each switch case)
		        break;
		case 2 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3 =0
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R |= PB2;          //b1=1
		        GPIO_PORTB_DATA_R &= ~(PB3);       //b0=0         binary output 0010
		        break;
		case 3 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R |= PB2;          //b1=1
		        GPIO_PORTB_DATA_R |= PB3;          //b0=1         binary output 0011
		        break;
		case 4 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R |=  PA7;         //b2=1
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R &= ~(PB3);       //b0=0         binary output 0100
		        break;
		case 5 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R |=  PA7;         //b2=1
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R |=  PB3;         //b0=1         binary output 0101
		        break;
		case 6 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R |=  PA7;         //b2=1
		        GPIO_PORTB_DATA_R |= PB2;          //b1=1
		        GPIO_PORTB_DATA_R &= ~(PB3);       //b0=0         binary output 0110
		        break;
		case 7 :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R |=  PA7;         //b2=1
		        GPIO_PORTB_DATA_R |= PB2;          //b1=1
		        GPIO_PORTB_DATA_R |= PB3;          //b0=1         binary output 0111
		        break;
		case 8 :
			GPIO_PORTA_DATA_R |= PA6;          //b3=1
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R &= ~(PB3);       //b0=0         binary output 1000
		        break;
		case 9 :
			GPIO_PORTA_DATA_R |= PA6;          //b3=1
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R |= PB3;          //b0=1         binary output 1001
		        break;
		default :
			GPIO_PORTA_DATA_R &= ~(PA6);       //b3=0
		        GPIO_PORTA_DATA_R &= ~(PA7);       //b2=0
		        GPIO_PORTB_DATA_R &= ~(PB2);       //b1=0
		        GPIO_PORTB_DATA_R &= ~(PB3);       //b0=0         binary output 0000
		        break;	
	}
	switch(num1)
	{
		case 1 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R |= PA5;         
		        break;
		case 2 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R |= PA4;         
		        GPIO_PORTA_DATA_R &= ~(PA5);         
		        break;
		case 3 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R |= PA4;         
		        GPIO_PORTA_DATA_R |= PA5;         
		        break;
		case 4 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R |=  PA3;        
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R &= ~(PA5);      
		        break;
		case 5 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R |=  PA3;        
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R |=  PA5;        
		        break;
		case 6 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R |=  PA3;        
		        GPIO_PORTA_DATA_R |= PA4;         
		        GPIO_PORTA_DATA_R &= ~(PA5);      
		        break;
		case 7 :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R |= PA3;         
		        GPIO_PORTA_DATA_R |= PA4;         
		        GPIO_PORTA_DATA_R |= PA5;         
		        break;
		case 8 :
			GPIO_PORTA_DATA_R |= PA2;         
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R &= ~(PA5);      
		        break;
		case 9 :
			GPIO_PORTA_DATA_R |= PA2;         
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R |= PA5;         
		        break;
		default :
			GPIO_PORTA_DATA_R &= ~(PA2);      
		        GPIO_PORTA_DATA_R &= ~(PA3);      
		        GPIO_PORTA_DATA_R &= ~(PA4);      
		        GPIO_PORTA_DATA_R &= ~(PA5);      
		        break;	
	}
}

int main(){
	Sys_init();
	while(1){
		displayed_distance = (int) (totaldistance *1000); //converting from km to m
		display(displayed_distance);
			if(totaldistance>0.1) {
				writeLED();
			}else{
				calc();
				latHome = latDest;
				lonHome = lonDest;
				latDest+=0.000001;
				lonDest+=0.000001;
				totaldistance += distance;       //distance calculated is in km
			}
	}
}
