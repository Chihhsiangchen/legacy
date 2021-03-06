/* This is the firmware for the RFMUSB device (USB handling functions).
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   Copyright (C) 2013 Soeren Heisrath (forename at surename dot org)
 */

#include "../common/rfm12usb_config.h"
#define F_CPU 20000000UL
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "rfm12.h"
#include "usbstuff.h"
#include "oddebug.h"
#include "usbdrv.h"
#include "ook.h"

void test_ook()
{
	uint8_t testcode[3] = {0x41, 0x45, 0x51};
	rfmusb_ook_t testrq = {
		.len = 24,
		.count = 12,
		.delay = 500,
		.type = OOK_2722
	};
	uint8_t foodata[sizeof(rfmusb_ook_t) + 3];
	memcpy (foodata, &testrq, sizeof(rfmusb_ook_t));
	memcpy (foodata + sizeof(rfmusb_ook_t), testcode, 3);
	ook_queue_msg (foodata);
}

int main ()
{

	HW_INIT();
	DEBUG_LED(1);
	usbstuff_init ();
	FSK_INIT();
	DEBUG_LED(0);
	wdt_disable();

	/* crude bugfix ahead...
	 * the rfm12 did not reliably send, this procedure fixed it(tm)
	 */
	_delay_ms(100);
	rfm12_init();
	rfm12_tx_on();
	_delay_ms(10);
	rfm12_init();
	/* (you can open your eyes again now ...) */

	sei();
	test_ook();

	while (1)
	{
		rfm12_tick();
		handle_rx();
		ook_tick();
	}
}
