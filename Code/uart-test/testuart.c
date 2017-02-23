#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#include <termios.h>

int uart_set_attr(int file, int snelheid, int pariteit);

int main(void)
{

	char portname[20] = "/dev/ttymxc4";

	int fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
	if(fd < 0)
	{
		printf("Uart device kan niet worden geopend.\n");
		exit(1);
	}

	printf("Uart device: %d\n", fd);

	uart_set_attr(fd, B115200, 0);


	write(fd, "Hello!", 6);
	
	return 0;
}

int uart_set_attr(int file, int snelheid, int pariteit)
{
	struct termios tty;

	cfsetospeed(&tty, snelheid);		// Set rx baud
	cfsetispeed(&tty, snelheid);		// Set tx baud
	                         	
	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;		// Set 8-bit per transfer

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); 	// geen xon/xoff ctrl

	// We stellen de pariteit in
	tty.c_cflag &= ~(PARENB | PARODD);
    tty.c_cflag |= pariteit;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if(tcsetattr(file, TCSANOW, &tty) != 0)
    {
    	printf("Instellen uart attributes niet mogelijk.\n");
    	return -1;
    }

    return 0;                		
}
