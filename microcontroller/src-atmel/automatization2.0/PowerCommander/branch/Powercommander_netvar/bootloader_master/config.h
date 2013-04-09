#ifndef CONFIG_H
#define CONFIG_H

// Bootloader defines
#define EEPR_ADDR_NODE 0x00

//#define TOGGLE_MCP_LED
#define TOGGLE_PORT_LED
#define PORT_LED PORTA
#define DDR_LED DDRA
#define BIT_LED  PA2

// spi.[ch] defines
#define SPI_HARDWARE
#define SPI_PORT PORTB		//for slave select
#define SPI_PIN PINB		//for slave select
#define SPI_DDR DDRB

#define SPI_PIN_MOSI PB5
#define SPI_PIN_MISO PB6
#define SPI_PIN_SCK PB7
#define SPI_PIN_SS PB4		// for slave select

//interrupt pin of MCP2515 for non interrupt drive can
#define SPI_PIN_MCP_INT PD2        //int0
#define SPI_REG_PIN_MCP_INT PIND   //int0


// can.[ch] defines
#define F_MCP F_CPU

#define PORT_SDO_CMD 21
#define PORT_SDO_DATA 22

#define JUMP_OPCODE "jmp"

#endif
