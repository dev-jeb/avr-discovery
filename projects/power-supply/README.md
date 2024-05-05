# Project
Power Supply

# Problem Description
In the past I have been using an Arduino Uno to power my projects. With these boards you can basically plug and play. Connect with USB and you have 5 volts. You can also easily program this board with the built in firmware. I don't know how this stuff works and that bothers me. I would like to move away from this and use bare atmega328p controller. The first step in doing this is providing a safe and reliable way to power the controller. This project will be me documenting my own journey through this we well written tutorial [source](https://www.sparkfun.com/tutorials/57)

# Objective
We will create a power supply that can be safely pugged into a wall and used to power our controller. This power supply will provide a 5V output and have a switch to turn it on and off. There will be an LED indicator to show when the power supply is on. This power supply will be implemented on a breadboard.
We will also ensure to some extent that the power supply protects against common issues such as overcurrent, overvoltage, and reverse polarity.

# End Goal

I think it is important to document in depth what we expect the final product to be. This will help us to stay on track and not get lost in the expansion of scope. Therefore, the final product will be a power supply that is built on a breadboard. This power supply will have the following features:
- **Input**: Can be plugged into the wall
- **Output**: 5V
- **Switch**: A switch used to turn the power supply on and off
- **LED Indicator**: A green LED that will turn on when the power supply is on
- **Protection**: The power supply will have some protection against overcurrent, overvoltage, and reverse polarity

# Circuit Design
The fist thing we must do is get a basic circuit design. Then we will identify the important parts in that circuit and the requirements for those parts. This will help us to understand what we need to buy and how to put it all together.

## Circuit Diagram

![alt text](/projects/power-supply/assets/image.png)
![alt text](/projects/power-supply/assets/image-1.png)

### Wall Wart

You should read this [write up](http://www.dxing.info/equipment/wall_warts_bryant.dx).

We are looking for a wall wart that can supply approximately $9V$ across the interval [$0,100$]mA.

We need a 3V buffer between the wall wart and the 5V linear regulator. The input voltage must be 3V higher than the output voltage.

I have found a 9V 2A rated wall wart. I have no idea what this will output under an 10mA load.

I worry about the current induced by the capacitors. When the load is small there will be a large current spike when the capacitors are charging. This could be a problem. I just want to make sure all of our components are rated for the current that will be flowing through them. Therefore, I need to know the voltage that the wall wart will output under a small load. I will measure this with a multimeter.




### Diode1


### Fuse1

### 5V Linear Regulator
From the wall wart we will have ~9V DC. We will use a 5V linear regulator to convert that 9V to 5V. This will not be perfect as the regulator will have some error to it but this is good enough for our purposes.

### Capacitors (C1 and C2)
These capacitors will be used to filter out the ripple in the output of the wall wart. They will also help to stabilize the output of the linear regulator. WIthout these capacitors the output of our power supply would not be constant. Instead it would fluctuate around our desired 5V.

### Resistor (R1)

### LED Indicator

