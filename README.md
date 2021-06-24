# Pi-fancontrol
The pi-fancontrol program controls an DC-fan controlled by a transistor that is connected with the GPIO (General Purpose Input Output) of the Raspberry Pi. It uses a PWM signal to roughly control the speed of the fan. If you want to control the speed of a DC-fan this is one way of doing it. Obviously it is not the best way but it does the job. For better efficiency and less rumor of the fan use a real PWM-fan for the Raspberry Pi.
## Draft
If you want to build this cooling system you need:
- DC-fan
- Transistor (I used a [BC337](https://www.onsemi.com/pdf/datasheet/bc337-d.pdf))
- Resistor (I used a 1 kΩ resistor)

