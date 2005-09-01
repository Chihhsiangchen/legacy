#include <windows.h>
#include "config.h"
#include "pixel3d.h"

unsigned char pixmap[NUM_LEVELS][NUM_PLANES][PLANEBYTES];

HANDLE serialPortHandle;
DCB serialConfig;

void uart_init(char *portName) {
	serialPortHandle = CreateFile(portName, 
							      GENERIC_READ | GENERIC_WRITE, 
							      0, 
							      NULL, 
							      OPEN_EXISTING, 
							      FILE_FLAG_NO_BUFFERING, 
							      NULL);
	
	GetCommState(serialPortHandle, &serialConfig);
	serialConfig.BaudRate = CBR_57600;
	serialConfig.Parity = NOPARITY;
	serialConfig.ByteSize = 8;
	serialConfig.StopBits = ONESTOPBIT;
	serialConfig.fOutxCtsFlow = FALSE;
	serialConfig.fOutxDsrFlow = FALSE;
	serialConfig.fRtsControl = RTS_CONTROL_ENABLE;
	serialConfig.fOutX = FALSE;
	serialConfig.fInX = FALSE;
	SetCommState(serialPortHandle, &serialConfig);
}

void uart_delete() {
     CloseHandle(serialPortHandle);
}

void put_c(const char inChar) {
	char buffer = inChar;
	DWORD charsWritten = 0;
	WriteFile(serialPortHandle, &buffer, sizeof(char), &charsWritten, NULL);
}

int put_str(char *inBuffer) {
	DWORD charsWritten = 0;
	WriteFile(serialPortHandle, inBuffer, strlen(inBuffer), &charsWritten, NULL);
	return charsWritten;
}

void drawBar(char quater, char value) {
	char minx, maxx, miny, maxy, x, y, z;
	
	switch (quater) {
	case 0:
		minx = 0, maxx = 4;
		miny = 0, maxy = 4;
		break;
	case 1:
		minx = 4, maxx = 8;
		miny = 0, maxy = 4;
		break;
	case 2:
		minx = 0, maxx = 4;
		miny = 4, maxy = 8;
		break;
	case 3:
		minx = 4, maxx = 8;
		miny = 4, maxy = 8;
		break;
	}
	for (x = minx; x < maxx; x++) {
		for (y = miny; y < maxy; y++) {
			for (z = 0; z < value; z++) {
				setpixel3d((pixel3d){x,y,z}, 3);
			}
		}
	}
}

void sendPixmap() {
	char i, j, k;
	put_c(UART_ESCAPE);
	put_c(UART_SOI);
	for (i = 0; i < 3; i++) {
        put_c(UART_ESCAPE);
		put_c(UART_SOF);
		for (j = 0; j < NUM_PLANES; j++) {
			for (k = 0; k  < PLANEBYTES; k++) {
				if (pixmap[i][j][k] == UART_ESCAPE)
					put_c(UART_ESCAPE);
				put_c(pixmap[i][j][k]);
			}
		}
	}
}
