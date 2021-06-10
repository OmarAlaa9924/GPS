#include <stdint.h>



//Initialization function
void Sys_init(){
	//PORTF
	SYSCTL_RCGCGPIO_R |= 0x20;			//Activate Port F Clock
	while((SYSCTL_RCGCGPIO_R&0x20)==0);		//Wait for activation
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;		//Unlock Port F
	GPIO_PORTF_CR_R |= PF123_mask;			//unlock used pins
        GPIO_PORTF_DIR_R |= PF123_mask;			//Set I/O
	GPIO_PORTF_DEN_R |= PF123_mask;			//Enable Digital output
	GPIO_PORTF_AMSEL_R &= ~PF123_mask;		//Disable analog
	GPIO_PORTF_AFSEL_R &= ~PF123_mask;		//Disable Alternate Function
	GPIO_PORTF_PCTL_R &= ~0x0000FFF0;		//PTCL GPIO on PF3-1
	GPIO_PORTF_DATA_R &= ~PF123_mask;		//Init LEDs to be off
	//***********************************************************************
        //PORTA
	SYSCTL_RCGCGPIO_R |= PA;			//Activate Port A Clock
	while((SYSCTL_RCGCGPIO_R&0x01)==0){};		//Wait for activation
        GPIO_PORTA_DIR_R |= 0xE0;			//Set I/O
	GPIO_PORTA_DEN_R |= 0xE0;			//Enable Digital output
	GPIO_PORTA_AMSEL_R &= ~0xE0;			//Disable analog
	GPIO_PORTA_AFSEL_R &= ~0xE0;			//Disable Alternate Function
	GPIO_PORTA_PCTL_R &= ~0xFFF00000;		//PTCL GPIO on PA
	GPIO_PORTA_DATA_R &= ~0xE0;	
	//***********************************************************************
	//PORTB
	SYSCTL_RCGCGPIO_R |= PB;		        //Activate Port B Clock
	while((SYSCTL_RCGCGPIO_R&0x02)==0){};		//Wait for activation		
        GPIO_PORTB_DIR_R |= pinsB;		        //Set I/O
	GPIO_PORTB_DEN_R |= pinsB;		        //Enable Digital output
	GPIO_PORTB_AMSEL_R &= ~pinsB;			//Disable analog
	GPIO_PORTB_AFSEL_R &= ~ pinsB;			//Disable Alternate Function
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;		//PTCL GPIO on PB
	GPIO_PORTB_DATA_R &= ~pinsB;
	//***********************************************************************
	//UART
 SYSCTL_RCGCUART_R |= SYSCTL_RCGCUART_R1;
 SYSCTL_RCGCGPIO_R |= SYSCTL_RCGCGPIO_R2;

UART0_CTL_R &= ~ UART_CTL_UARTEN;
UART0_IBRD_R = 104;	
UART0_FBRD_R = 11;
UART0_LCRH_R |= (UART_LCRH_WLEN_8 | UART_LCRH_FEN)	;
UART0_CTL_R = (UART_CTL_RXE | UART_CTL_TXE | UART_CTL_UARTEN);
	
GPIO_PORTA_AFSEL_R |= 0x30;
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R &= ~0x00FF0000)|(GPIO_PCTL_PC5_U1TX|GPIO_PCTL_PC4_U1RX);
GPIO_PORTA_DEN_R |= 0x30;
GPIO_PORTA_AMSEL_R &= ~0x30;	
}	

//-------------------------------------------------------------------------
//Declare Variables
double totaldistance, distance,latHome, lonHome, latDest, lonDest,differenceLon, differenceLat, a, c, latHomeTmp, latDestTmp, t = 0;
double pi = 3.141592653589793;
double R = 6371; //Radius of the Earth
int displayed_distance =0 ;
int ones,tens,hundreds=0;
//--------------------------------------------------------------------------
void calc() //Calculates distance between two coordinates
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
//-----------------------------------------------------------------------------
uint8_t UART1_Available(){
	return ((UART1_FR_R &UART_FR_RXFE)==UART_FR_RXFE)? 0:1;
}
char UART0_read(){
	 while(UART1_Available() !=1){};
		return (char) (UART1_DR_R & 0xFF);
		}

void UART1_write(char data){
	while((UART1_FR_R & UART_FR_TXFF)==UART_FR_TXFF){};
		UART1_DR_R = data;
}
//-----------------------------------------------------------------------------
void update_coordinates(){
	latHome = latDest;
	lonHome = lonDest;
	latDest+=0.0005;
	lonDest+=0.0005;	
}
void delay(int n){	//Delay Function
	int i,j;
	for(i=0;i<n;i++){
	for(j=0;j<n;j++){}}
}

//------------------------------------------------------------------------------
void writeLED(){	//Turn on Red LED
	GPIO_PORTF_DATA_R &= ~PF123_mask;
	GPIO_PORTF_DATA_R |= RED;
}
//-------------------------------------------------------------------------------
void split_displayed_num(){ //Splits number to hundreds, tens and ones
	displayed_distance = (int) (totaldistance *1000);
	ones = displayed_distance%10;
        displayed_distance /= 10;
	tens= displayed_distance%10;
	displayed_distance/=10;
        hundreds = displayed_distance%10;
}
//Generating a function that consider all posible values(0-9) for 7 sigment output by setting mask for each digital output. 

unsigned char mask(int num){ 
	switch(num){
		case 1 : return 0x30;		    
		case 2 : return 0x6D;
		case 3 : return 0x79;
		case 4 : return 0x33;
		case 5 : return 0x5B;
		case 6 : return 0x5F;
		case 7 : return 0x70;
		case 8 : return 0x7F;
		case 9 : return 0x7B;
		default : return 0x7E;		
	}
}
//Generating a function that displays the output calculated distance on 7 segment display

void display(int hundreds,int tens,int ones){
	while(1){
		GPIO_PORTA_DATA_R &= 0X7F;
		GPIO_PORTA_DATA_R |= 0X60;
		GPIO_PORTB_DATA_R = mask(hundreds); 
		delay(100);
		GPIO_PORTA_DATA_R &= 0XBF;
		GPIO_PORTA_DATA_R |= 0XA0;
		GPIO_PORTB_DATA_R = mask(tens);
		delay(100);
		GPIO_PORTA_DATA_R &= 0XDF;
		GPIO_PORTA_DATA_R |= 0XC0;
		GPIO_PORTB_DATA_R = mask(ones);
		delay(100);
	}
}

//----------------------------------------------------------------------
int main(){
	Sys_init();
	while(1){
		calc();
		update_coordinates();	
		totaldistance += distance;
		if(totaldistance>0.1) {
			writeLED();
			split_displayed_num();
			display(hundreds,tens,ones);			
		}  			
	}
}
