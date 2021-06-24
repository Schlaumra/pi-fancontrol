all: pifancontrol.c
	gcc pifancontrol.c -o pifancontrol -lpigpio -lrt

