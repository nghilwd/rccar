# rccar
This is a small little project that I do in my free time: A small RC car control with a L298N motor driver and use Flysky GT2 as the transmitter

Pinout (for Arduino Uno):<br />
Pin 2 : Channel 2 (Throttle)<br />
Pin 3 : Channel 1 (Steering)<br />
Pin 5,6: right motor direction, connect directly to L298N pin 2 and 3<br />
Pin 7,8: left motor direction<br />
Pin 9: motor right speed pin<br />
Pin 10: motor left speed pin<br />
Thanks [The bored robot](https://theboredrobot.com/blogs/blog/simultaneously-reading-two-pwm-signals-from-an-rc-receiver-with-arduino) for the code to read 2 simultaneous pwm signal
