all: pifancontrol.c 
	gcc pifancontrol.c -o pifancontrol -lpigpio -lrt
	mkdir -p /usr/local/bin
	cp pifancontrol /usr/local/bin/
	cp pifancontrol.service /etc/systemd/system
