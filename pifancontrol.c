#include <pigpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Change this in order to change the base-pin of the transistor
#define lineBase 18

void startFan()
{
	gpioWrite(lineBase, 1);
}

void stopFan()
{
	gpioWrite(lineBase, 0);
}

// Handler for INT signal; Terminate GPIO and exit
void sigHandler(int signo)
{
	stopFan();
	gpioTerminate();
	exit(0);
}

int main(int argc, char **argv)
{
	// Init gpio and check errorcode
	int errCode = gpioInitialise();
	if (errCode < 0)
	{
		printf("Failed to initialise the gpio libary\n");
		exit(errCode);
	}

	/*
	 * Variables that can be changed
	 * waitSteps, speedSteps and temperatures must have the same size and have to be from big to small
	 * speedSteps have to be between 255 and 0
	 */
	unsigned int dutyCycle = 100;
	unsigned int waitSteps[] = {5, 15, 25, 35};
	unsigned int speedSteps[] = {255, 200, 135, 0};
	unsigned int temperatures[] = {55000, 50000, 48000, 0};

	// Variables for the program
	unsigned int temperature = 0;
	unsigned int sizeSteps = sizeof(speedSteps);
	FILE *temperatureF;

	// Check if they have the same amount
	if (sizeSteps != sizeof(temperatures) || sizeSteps != sizeof(waitSteps))
	{
		printf("The arrays are not the same size. Please check the variables!\n");
		exit(13);
	}

	// Set mode for pin and check errorcode
	errCode = gpioSetMode(lineBase, PI_OUTPUT);
	if (errCode != 0)
	{
		printf("Failed to set output mode for line %d\n", lineBase);
		exit(errCode);
	}
	
	// If program receives a INT signal call the function
	gpioSetSignalFunc(SIGINT, sigHandler);

	// Stop Fan
	stopFan();
	
	// Set the PWM frequency
	gpioSetPWMfrequency(lineBase, 10);
	
	while(1)
	{
		// Open temperature file and write it to temperature
		temperatureF = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
		fscanf(temperatureF, "%d", &temperature);

		// Checks for the temperature and if temperature is over the iterated temperature it sets the speed and sleeps
		for(unsigned int i = 0; i != sizeSteps ; ++i)
		{
			if(temperature >= temperatures[i])
			{
				gpioPWM(lineBase, speedSteps[i]);
				sleep(waitSteps[i]);
				break;

			}
		}
		// close the file
		fclose(temperatureF);
	}
}
