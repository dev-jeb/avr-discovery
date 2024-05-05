# Project:
Temp

# Problem Description:
My girlfriend (she really is a wonderful person) likes to keep the house cold as fuck (I'm just a naturally cold person). I'm going to design a "box" I can velcro over the thermostat. I start shivering at $73^{\circ}F$. 

In celsius this is
$$
 C^{\circ} = \frac{F^{\circ} - 32}{1.8} = \frac{73 - 32}{1.8} = 23^{\circ} C
$$

Therefore, when $t < 23^{\circ}C$ red light, and when $t \geq 23^{\circ}C$ green light. This is to learn something and be obnoxious at the same time. I think she will enjoy her gift.

*Note*: I do the conversion above because the temp sensor I have on hand is calibrated in Celsius and I have a feeling Centigrade is the standard across electronics.

# Requirements:
- Red Light = too cold
- Green light = too hot
- battery powered
- We will pay special attention to maximizing operating life, which translates to minimizing power consumption.


## Software

We can talk bout software architecture for a moment.

### Temperature Sampling

To sample temperature at specified intervals, we rely solely on the watchdog timer for system reset, On system reset I will ensure the microcontroller jumps to the main loop. Therefore we can use the watchdog timer to sample temperature at regular intervals. Just to be clear, the watchdog timer is a hardware timer that can be used to reset the microcontroller in case of a software failure. It can also be used to wake the microcontroller from sleep mode at regular intervals, which is useful for low-power applications.

### LED Manipulation

LED circuit manipulation based on temperature readings is facilitated using a DPDT relay. This relay has two coils, a set coil and a reset coil, which control the green and red LEDs, respectively. By energizing the appropriate coil, we can toggle between the two LED states. The relay maintains its last energized state until the other coil is activated, providing a simple and efficient method for LED control. We will use the GPIO pins to set the relay.

### Temperature Measurement

For temperature measurement, we utilize the TMP36 sensor along with the built-in ADC on the ATmega328P microcontroller, ensuring accurate and reliable temperature readings.


### Execution Flow
1. **Watchdog Timer Wakeup:** The microcontroller wakes up from sleep mode at regular intervals using the watchdog timer.
2. **Temperature Sampling:** The microcontroller reads the temperature from the TMP36 sensor using the ADC.
3. **Temperature Comparison:** The microcontroller compares the temperature reading to the threshold value (23°C) to determine the LED state.
4. **LED Control:** The microcontroller energizes the appropriate coil in the relay to turn on the green or red LED based on the temperature reading.
5. **System Power-Down:** The microcontroller enters sleep mode to conserve power until the next watchdog timer wakeup.

### Dependencies
- **Watchdog Timer:** Used to wake up the microcontroller at regular intervals for temperature sampling.
- **ADC:** Used to read the temperature from the TMP36 sensor.
- **GPIO:** Used to control the relay coils for LED manipulation.
- **Low-Power Modes:** Utilized to minimize power consumption during idle periods.
 
 Wow, each one of those is going to need corresponding library functions. It going to be a good project. It will help me build out the libraries with stuff that matters.

By leveraging the watchdog timer for system reset, our software architecture becomes streamlined and straightforward, facilitating ease of development and maintenance.


## Hardware/Circuit:
### Components:
- **TMP36 Temperature Sensor**: Low voltage sensor for temperature measurement.

- **TX2-5V Latching Relay**: Control the LED indicators.
![alt text](/projects/temp/assets/image.png)
This relay serves to control the LED indicators. With two coils, a set coil and a reset coil, it facilitates toggling between states. The set coil activates the green LED, while the reset coil activates the red LED. Instead of traditional battery and button setup, voltage to the coils is regulated using the GPIO pins on our microcontroller. The relay maintains its last energized state until the other coil is activated. It operates on a 5V power supply.
![alt text](/projects/temp/assets/image-1.png)
- **Red LED**: Indicates "too cold" temperature status.
  - forward voltage: ~2.2V
  - current: ~20mA
- **Green LED**: Indicates "too hot" temperature status.
  - forward voltage: ~2.2V
  - current: ~20mA

# Circuit Parts:
- crystal oscillator
- voltage regulator
- wall wart
- atmeg328p
- tmp36
- relay
- red led
- green led
- 9V battery
- programmer

## Voltage Divider Approach:

Using a voltage divider to reduce the voltage from a battery to the required level for your microcontroller can be a solution, but it's not typically the best approach for maximizing battery life. 

Voltage dividers are not efficient when it comes to power consumption. They draw current from the source voltage continuously, even when the load (such as your microcontroller) is not active. This continuous current draw wastes power and can significantly reduce battery life, especially if the resistance values are high.

Instead of using a voltage divider, consider using a more efficient voltage regulation circuit, such as a low-dropout (LDO) voltage regulator or a buck converter. These circuits can efficiently step down the voltage from the battery to the required level while minimizing power loss.

When choosing a voltage regulator, look for one with low quiescent current (also known as ground or supply current), which is the current drawn by the regulator itself when no load is connected. Lower quiescent current means less wasted power when your microcontroller is in standby or low-power modes, thus maximizing battery life.


## LED Current: 
I need to deciede what current I want to run through my LED's. I will use the following formula to calculate the current limiting resistor:
$$
R = \frac{V_{cc} - V_{f}}{I}
$$
where:
- $V_{cc}$ is the supply voltage
- $V_{f}$ is the forward voltage of the LED
- $I$ is the desired current through the LED


# Power Consumption

## The Battery
I will have to test to see how bright it is but I am thinking about running the LED with a current of around 10 mA. With a standard alkaline 9V battery we can expect ~600 mAh capacity at this discharge current. Therefore, we can expect a battery life of around 60 hours. Lets say a person uses the device for one minute every day. 60 hours * 60 minutes = 3600 minutes  or 3600 days so best case ~10 years of battery life. The battery will not physically last this long. But we can assume it good for two to three years. We have not taken into account the power consumption of the microcontroller. Once every hour it will wake up, take a reading, update the LED's by  turning on the appropriate coil in the relay, and go back to sleep. Let's say this entire process took around 10 seconds. Lets say the microcontroller consumes 10 mA (this is only for approx. much smaller in practice). I estimate a ~2.5 year battery life. We would use 4 minutes a day at 10 mA (much lower in reality) for updating the LED's and 1 minute a day at 10 mA for the user viewing the state of the LED's. Remember we have a total of 60 hours of battery life at 10 mA. So 3600 minutes (total usage hours available) / 5 min (use per day) = 720 days or ~2 years. Therefore, we can be happy with a 9V battery for approximated everyday use.

The battery has turned out a lot tougher than I thought. We need to drive the circuit that contains the LEDs and the circuit that contains the microcontroller. 9V just seems like too much voltage to me but the mAh rating is great (~600 mAh) and they are cheap. I think Im going to go for a high resistance voltage divider to power the microcontroller and the LEDs. The microcontroller at 5V will be fine. The LEDs will be dimmer but I think it will be fine. I will have to test it out. I will use a 9V battery. I will use a 5V voltage regulator to power the microcontroller.

- LED Circuit:
  - operating voltage: 2.2V
  - current consumption: 20 mA
- Microcontroller Low Power Mode
  - operating voltage: 3.5V
  -  current consumption: TODO
We can run with an

## Microcontroller Power Consumption
![alt text](/projects/temp/assets/image-2.png)


#