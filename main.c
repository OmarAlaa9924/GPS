#include "Initializations.h"
#include "tm4c123gh6pm.h"
#include "Lcd.h"

int main(void)
{
  init();
	lcd_init();
	unsigned short int displayed[10];
	float total=0;
	float latHome=0; 
	float lonHome=0;
	float coordinates[2];
	
	command(lcd_Clear);
			
	while (1)
	{
			Extract(coordinates);
	  	total+= distance_total(latHome, lonHome , coordinates[0], coordinates[1]);
			latHome=coordinates[0];
			lonHome=coordinates[1];
			position(1,1); // go to line 1
			data_string("Distance =");
			position(1,2); // go to line 2
			sprintf(displayed,"%d",(unsigned short int)total); // returns the float number into string to display on LCD
		  data_string(displayed);
			check_100(total);
			delay(1000);
	}
		
}
