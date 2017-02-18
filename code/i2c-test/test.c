#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{

	int file;
	char * filename = "/dev/i2c-0";


	if ((file == open(filename, O_RDWR)) < 0)
	{
		printf("fout bij openen i2c interface\n");
		exit(1);
	}

	int addr = 0b00101001;

	//if(ioctl(file, I2C_SLAVE, addr) < 0)
	//{
	//	printf("Geen verbingeng met slave mogelijk\n");
	//	exit(2);
	//}
	
	int buf = 0b10101010;

	write(file, &buf, 1);
	
	write(file, &buf, 1);

	write(file, &buf, 1);
	printf("Gelukt!\n");

	return 0;
}