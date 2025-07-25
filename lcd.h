#define datalines P2
#define keypad P1
#include<string.h>
sbit rs=P3^0;
sbit en=P3^1;

//user function declaration
void lcd_cmd(unsigned char);	//controlling
void lcd_data(unsigned char);  //8 bit data display
void lcd_init(void);	//initialzation
void lcd_string(unsigned char ch[]);		//string display
void delay(unsigned int);		//delay
void lcd_number(unsigned long);
int check_password();
char pw_keypad(void);
void mdelay(unsigned int d);

//user function defination
void lcd_cmd(unsigned char ch){
	datalines=ch;
	rs=0;
	en=1;
	delay(10);
	en=0;
}
void lcd_data(unsigned char ch){
	datalines=ch;
	rs=1;
	en=1;
	delay(10);
	en=0;
}
void delay(unsigned int ch){
	int a,b;
	for(a=0;a<ch;a++)
	for(b=0;b<1000;b++);
}


void lcd_string(unsigned char ch[]){
	int x;
	for(x=0; ch[x]!='\0';x++){
		lcd_data(ch[x]);
	}
}
char pw_keypad(void){
	unsigned char key;
		keypad = 0xf7; //row-1
			if(keypad == 0xf6){ //key 1
				key = '1';}
			else if(keypad == 0xf5){
				key = '2';}
			else if(keypad == 0xf3){				// key 3
				key = '3';}
		keypad = 0xef; // row 2
			if(keypad == 0xee){ // key 4
				key = '4';}
			else if(keypad == 0xed){ //key 5
				key = '5';}
		keypad = 0x3f; // row 4
			if(keypad == 0x3d){ // key 0
				key = '0';}
		return key;
}
void mdelay(unsigned int d){
	int i,j;
	for(i=0;i<d;i++){
		for(j=0;j<d;j++);}
}
