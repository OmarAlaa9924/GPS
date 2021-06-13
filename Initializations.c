#include "Initializations.h"
#include "tm4c123gh6pm.h"
#include <Math.h>
#define PI 3.14159265359
#include <string.h> // strtok
#include <stdlib.h> // strtod
#include "LCD.h"

void init ()
{ // PORT E lcd controls
	SYSCTL_RCGCGPIO_R |= 0x00000010;
  while ((SYSCTL_PRGPIO_R&0x10) == 0){};
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R |= 0x3E;
	GPIO_PORTE_DIR_R = 0x0E;
	GPIO_PORTE_DEN_R = 0x3E;
	GPIO_PORTE_AMSEL_R = 0x00;
	GPIO_PORTE_AFSEL_R = 0x30;
	GPIO_PORTE_PCTL_R = 0x00110000;
  GPIO_PORTE_PUR_R = 0x00;
	
	// UART5 PORT E
	SYSCTL_RCGCUART_R |= 0x0020;
	while((SYSCTL_PRUART_R & 0x0020)==0){};
	UART5_CTL_R &= ~0x0001;
	UART5_IBRD_R = 104;
	UART5_FBRD_R = 11; 
	UART5_LCRH_R = 0x0070;
	UART5_CTL_R = 0x0301;
  
	// PORT B lcd data
	SYSCTL_RCGCGPIO_R |= 0x00000002;
  while ((SYSCTL_PRGPIO_R&0x02) == 0){};
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_CR_R |= 0xFF;
	GPIO_PORTB_DIR_R = 0xFF;
	GPIO_PORTB_DEN_R = 0xFF;
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_AFSEL_R = 0x00; 
	GPIO_PORTB_PCTL_R = 0x00000000;
  GPIO_PORTB_PUR_R = 0x00;
		
	//PORT F
	SYSCTL_RCGCGPIO_R |= 0x00000020;
  while ((SYSCTL_PRGPIO_R&0x20) == 0){};
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x1F;
	GPIO_PORTF_AMSEL_R = 0x00;
	GPIO_PORTF_PCTL_R = 0x00000000; 
	GPIO_PORTF_DIR_R = 0x0E;
  GPIO_PORTF_AFSEL_R = 0x00; 
  GPIO_PORTF_PUR_R = 0x00;
  GPIO_PORTF_DEN_R = 0x1F;
	GPIO_PORTF_DATA_R &= ~0x0E;
}


void check_100(unsigned short int d) // turns LED on if distance > 100m
{
	if(d > 100){
		GPIO_PORTF_DATA_R |= 0x0E;
	}

}

unsigned char UART5_in(void) // checks if FIFO is empty to start read from UART
{
	while((UART5_FR_R & 0x10)!=0);
	return ((unsigned char)(UART5_DR_R & 0xFF));
}

void Extract(float coordinates[])
{
	unsigned char ch;                           // used to read from UART data
	unsigned char flag=0;                       // this flag is used to control the extraction of data loop condition
	unsigned char* lat;                         // used to store the value of latitude
	unsigned char* lon;                         // used to store the value of londitude
	unsigned char* n_s;                         // used to store the character which indicates are we north or south
	unsigned char* e_w;                         // used to store the character which indicates are we east or west
	unsigned char* gps_fix;                     // check if gps finished its fix and sent correct data
	float latfloat;                            // used to store the  float part of latitude
	float lonfloat;                           // used to store the float part of longitude
	unsigned char latint;                    // used to store the intger part of latitude
	unsigned char lonint;                    // used to store the intger part of longitude
	float latreal;                           // used to store the real and final value of float part of latitude
	float lonreal;                          // used to store the real and final value of float part of longitude
	unsigned char gpsdata[50]; 	          // an array containing the NMEA sentence
	//checking character character till we get the desired NMEA sentence
		while(flag==0){
			    ch = UART5_in();
				if(ch =='$'){
					ch = UART5_in();
				if(ch=='G'){
					ch = UART5_in();
				if(ch=='P'){
					ch = UART5_in();
	 		  if(ch=='G'){
					ch = UART5_in();
				if(ch=='G'){
					ch = UART5_in();
				if(ch=='A'){
					ch = UART5_in();
				if(ch==','){
					for(int i=0;i<50;i++){
				  	gpsdata[i]= UART5_in();             // if gps sends "$GPGGA," then we store the rest of our desired NMEA sentence
					}
				}
				}
				}
	  		}
				}
				}
				}
			lat = strtok(gpsdata, ",");              // strtok function is used to divide the data ch the array
			lat = strtok(NULL, ",");
			n_s = strtok(NULL, ",");
			lon = strtok(NULL, ",");
			e_w = strtok(NULL, ",");
		  gps_fix = strtok(NULL, ",");
			if(gps_fix[0]=='1'){ 
				flag=1;
			}
		}
		latfloat= strtod(lat,NULL);              // dividing the gps degree latitude to convert it to decimal using equations
		lonfloat= strtod(lon,NULL);             // dividing the gps degree longitude to convert it to decimal using equations
		latfloat=latfloat/100;
		lonfloat=lonfloat/100;
		latint=(unsigned char)latfloat;
		lonint=(unsigned char)lonfloat;
		latfloat=latfloat-latint;
		lonfloat=lonfloat-lonint;
		latfloat=(latfloat*100)/60;
		lonfloat=(lonfloat*100)/60;
		latreal=latint+latfloat; // final latitude value
		lonreal=lonint+lonfloat; // final longitude value
		if(n_s[0] == 'S'){
			latreal*=-1;
		}
		if(e_w[0]=='W'){
			lonreal*=-1;
		}
		coordinates[0]=latreal;
		coordinates[1]=lonreal;
}
