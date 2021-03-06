#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/pgmspace.h>

#include <stdint.h>
#include <string.h>
#include "lcd.h"
#include "cron.h"
#include "menu.h"
#include "input.h"
#include "clock.h"
#include "coffee.h"

#define MTOP_DEFAULT 7
#define NUM_ENTRIES 12

static uint8_t midx = 0, mtop;
static volatile menuentry_t *menu_p;
//#define ment(a) ((menuentry_t) (*(menu_p + (a*sizeof(menuentry_t)))))
#define ment(a) ((menuentry_t) (menu_p[a])) /* * sizeof(menuentry_t)))) */
#define mtop(a) ((sizeof(a) / sizeof(menuentry_t)) -1)


/* main menu */
volatile menuentry_t mainmenu[] =
	{
		(menuentry_t) {
			"Schalt an!",
			1,
			send_c_on
		},
		(menuentry_t) {
			"t+ 30 Min",
			1800,
			send_c_on
		},
		(menuentry_t) {
			"t+ 40 Min",
			2400,
			send_c_on
		},
		(menuentry_t) {
			"t+ 55 Min",
			3000,
			send_c_on
		},
		(menuentry_t) {
			"t+ 85 Min",
			5100,
			send_c_on
		},
		(menuentry_t) {
			"t+ 95 Min",
			5700,
			send_c_on
		},
		(menuentry_t) {
			"Mach aus!",
			0, /* after 10 minutes run for 15 minutes */
			send_c_off
		},
		(menuentry_t) {
			"Zeitwahl >>",
			0,
			time_c_custom
		},
		(menuentry_t) {
			"debug >>",
			0,
			mdebug_jump
		}
	};


/* DEBUG STUFF */
volatile menuentry_t debugmenue[] =
	{
		(menuentry_t) {
			"clear cron",
			0,
			cron_init
		},
		(menuentry_t) {
			"reboot",
			0,
			dbg_reboot
		},
		(menuentry_t) {
			"set clock",
			0,
			clk_set
		},
		(menuentry_t) {
			"<<<",
			0,
			menu_init
		}
	};

void dbg_reboot ()
{
	wdt_enable(0);
	sei();
	while (42);
}


void mdebug_jump (uint16_t foo)
{
	midx = 0;
	mtop = mtop(debugmenue);
	menu_p = (menuentry_t *) &(debugmenue);
	//menu_p = (menuentry_t *) &(debugmenue[0]);
	menu_display();
}

uint8_t id_next (uint8_t in_entry)
{
	if (in_entry >= mtop) return 0;
	return in_entry +1;
}

uint8_t id_last (uint8_t in_entry)
{
	if (in_entry == 0) return mtop;
	return in_entry -1;
}

void menu_display()
{
	lcd_clrscr();
	lcd_gotoxy (0,0);
	
	lcd_putc(0x7e); /* right arrow */
	
	lcd_puts (ment(midx).name);
	lcd_gotoxy (15,0);
	
	lcd_putc(0x7f); /* left arrow */

	lcd_gotoxy (1,1);
	lcd_puts(ment(id_next(midx)).name);
}

void menu_select() 
{
	if (ment(midx).func != NULL)
		(ment(midx).func)(ment(midx).func_param);
}

void menu_init()
{

	midx = 0;
	mtop = mtop(mainmenu);
	//menu_p = (menuentry_t *) &mainmenu;
	menu_p = &mainmenu;
	
	/* set up input hooks */
	input_hook (BTN_UP,     menu_next);
	input_hook (BTN_DOWN,   menu_last);
	input_hook (BTN_SELECT, menu_select);

	menu_display();
}

void menu_last()
{
	midx = id_last(midx);
	menu_display();
	return;
}

void menu_next()
{
	midx = id_next(midx);
	menu_display();
}
