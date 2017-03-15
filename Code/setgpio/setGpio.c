#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char ** argv)
{
	if(argc < 2)
	{
		printf("Geef een 1 of een 0 mee als parameter.\n");
		exit(1);
	}

	printf("Setting led to %d\n",atoi(argv[1]));

	int file;
	char buffer[50];
	int gpio = 42;

	// Generating gpio42 device
	file = open("/sys/class/gpio/export", O_WRONLY);
	sprintf(buffer, "%d", gpio);
	write(file, buffer, strlen(buffer));
	close(file);

	// Set gpio as output
	sprintf(buffer, "/sys/class/gpio/gpio%d/direction", gpio);
	file = open(buffer, O_WRONLY);
	write(file, "out", 3);
	close(file);

	// Set gpio value
	sprintf(buffer, "/sys/class/gpio/gpio%d/value", gpio);
	file = open(buffer, O_WRONLY);
	if(atoi(argv[1]) == 0)
	{
		write(file, "0", 1);
	}
	else
	{
		write(file, "1", 1);
	}
	close(file);

	// Remove gpio device
	file = open("/sys/class/gpio/unexport", O_WRONLY);
	sprintf(buffer, "%d", gpio);
	write(file, buffer, strlen(buffer));
	close(file);	

	return 0;
}