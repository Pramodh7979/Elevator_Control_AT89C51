#include<regx51.h>
#include "lcd.h"
#include<string.h>
#define segment P0
#define keypad P1
#define motor P3
unsigned int keypad_scan();
void move_elevator(unsigned int target_floor, unsigned int current_floor);
void main(void){
	unsigned int key;
	unsigned int current_floor = 0;
	unsigned int target_floor;
	char keyval = 0;
	unsigned int keycnt = 0;
	unsigned int cmppw = 0;
	char dpw[5] = "5555";
	char epw[5];
	motor = 0x00;
	lcd_cmd(0x38);
	lcd_cmd(0x0c);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
	segment = 0x3f;
	while(1){
		lcd_cmd(0x80);
		lcd_string("Enter password");
		keyval = pw_keypad();
		if(keyval != 0){
			epw[keycnt] = keyval;
			lcd_cmd(0xc0+keycnt);
			lcd_data('*');
			keycnt += 1;
		}
		if(keycnt == 4){
			lcd_cmd(0x01);
			keycnt = 0;
			cmppw = strcmp(dpw,epw);
			
			if(cmppw == 0){
				lcd_cmd(0x80);
				lcd_string("Correct Password");
				
				delay(500);
				break;
			}
			else{
				lcd_cmd(0x80);
				lcd_string("Wrong Password");
				delay(500);}
			}
		}
	lcd_cmd(0x01);
	lcd_string("Enter floor ");
	delay(250);	
	target_floor = 0;
	while(1){
			key = keypad_scan();
			target_floor = key;
			move_elevator(target_floor, current_floor);
			target_floor = key;
			current_floor = target_floor;
	}
}
unsigned int keypad_scan(){
	unsigned int key;
	keypad = 0xf7; //row-1
			if(keypad == 0xf6){ //key 1
				key = 1;
				segment = 0x06;}
			else if(keypad == 0xf5){
				key = 2;
				segment = 0x5b;}
			else if(keypad == 0xf3){				// key 3
				key = 3;
				segment = 0x4f;}
		keypad = 0xef; // row 2
			if(keypad == 0xee){ // key 4
				key = 4;
				segment = 0x66;}
			else if(keypad == 0xed){ //key 5
				key = 5;
				segment = 0x6d;}
		keypad = 0x3f; // row 4
			if(keypad == 0x3d){ // key 0
				key = 0;
				segment = 0x3f;}
		return key;
}
void move_elevator(unsigned int target_floor, unsigned int current_floor){

	if(target_floor > current_floor){
		lcd_cmd(0x01);
		lcd_cmd(0x38);
		lcd_cmd(0x0c);
		motor = 0x74;
		while(current_floor < target_floor){
			mdelay(200);
			current_floor++;
		}
		motor = 0x00;
		lcd_string("YOU HAVE REACHED");
		delay(250);
		lcd_cmd(0x01);
		lcd_string("Enter floor ");}
	else if(target_floor < current_floor){
		motor = 0xb8;
		while(target_floor < current_floor){
			mdelay(200);
			current_floor--;
		}
		motor = 0x00;
		lcd_cmd(0x01);
		lcd_string("YOU HAVE REACHED");
		delay(250);
		lcd_cmd(0x01);
		lcd_string("Enter floor ");}
	
	else{
		motor =0x00;
	}
}
