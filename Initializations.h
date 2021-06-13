#ifndef GPIO_INIT_H_
#define GPIO_INIT_H_

void init(void);
unsigned char UART5_in(void);
void Extract(float coordinates[]);
void check_100 (unsigned short int d);
float distance_total (float latHome, float lonHome, float latDest, float lonDest);
float dist_calc(float latHome,float lonHome,float latDest,float lonDest);
void delay(int n);

#endif