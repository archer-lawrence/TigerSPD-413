/*
 * FSMCTool.c
 *
 *  Created on: Dec 10, 2019
 *      Author: archer
 */

#define null (void *)0
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "usbd_cdc_if.h"
#include "FSMCTool.h"

uint FSMCBase = MAX10_DEFAULT;
int FSMCOffset = 0;


char *trim(char *str)
{
    size_t len = 0;
    char *frontp = str;
    char *endp = NULL;

    if( str == NULL ) { return NULL; }
    if( str[0] == '\0' ) { return str; }

    len = strlen(str);
    endp = str + len;

    /* Move the front and back pointers to address the first non-whitespace
     * characters from each end.
     */
    while( isspace((unsigned char) *frontp) ) { ++frontp; }
    if( endp != frontp )
    {
        while( isspace((unsigned char) *(--endp)) && endp != frontp ) {}
    }

    if( frontp != str && endp == frontp )
            *str = '\0';
    else if( str + len - 1 != endp )
            *(endp + 1) = '\0';

    /* Shift the string so that it starts at str so that if it's dynamically
     * allocated, we can still free it on the returned pointer.  Note the reuse
     * of endp to mean the front of the string buffer now.
     */
    endp = str;
    if( frontp != str )
    {
            while( *frontp ) { *endp++ = *frontp++; }
            *endp = '\0';
    }

    return str;
}
void FSMCMenu(void)
{
	uint8_t offset = 0;

	printf("\n\n\n\rFSMC Tool\n\r");
	printf("B <value><cr> -- set base register (0x%08x)\n\r", FSMCBase);
	printf("o <value><cr> -- set memory offset (%d)\n\r", FSMCOffset);
	printf("r <cr>        -- read once from base+offset\n\r");
	printf("w <value><cr> -- write to base+offset\n\r");
	printf("R <cr>        -- read loop from base+offset\n\r");
	printf("W <value><cr> -- write loop to base+offset\n\r");
	printf("\n\rQ quit\n\r");
}
void FSMCTool(void)
{
	char buf[80];

	while(1)
	{
		FSMCMenu();
		VCP_ReadLine(buf, sizeof(buf));
		char cmd = buf[0];

		if(cmd == 'Q')
			return;
		else if(cmd == 'B')
		{
			buf[0] = ' ';
			trim(buf);
			FSMCBase = strtol(buf, null, 16);
		}
		else if(cmd == 'o')
		{
			buf[0] = ' ';
			trim(buf);
			FSMCOffset = strtol(buf, null, 16);
		}
		else if(cmd == 'r')
		{
			buf[0] = *(uint8_t *)(FSMCBase + FSMCOffset);
		}
		else if(cmd == 'w')
		{
			buf[0] = ' ';
			trim(buf);
			uint8_t val = strtol(buf, null, 16);
			*(uint8_t *)(FSMCBase + FSMCOffset) = val;
		}

	}
}
