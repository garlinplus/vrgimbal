http://api.ning.com/files/gj9J14QXQplh01W-I7PJYHrdrWzGn2NOxu26wtIbdCK46jmWS7y0sinUZInpC9ni0MBltObsn4AlNjNkuncv*fseObz6OtMD/20130510_181943.JPG

http://api.ning.com/files/gj9J14QXQpni63hTPa35l2LhrcO3SzSPfK09OYJfPv52pM4LOMdJc7gRTHb*EHoKKL0TN1duZy94U7eG7Pwh3fAWWknlle6H/20130510_182037.JPG

http://api.ning.com/files/gj9J14QXQpmYqxkNUELHNcKGKVdQUBqJKOEk9y0N8nCPneTS3kH*jp-V6Wt38Z62jnb-pW37r3*FPSb60AiOLpPwl6UlIbT5/20130510_160730.JPG

Dear Friends,

after one week of work to first sample of electronics , we are ready with workspace enviroment for developer that want join our team.

Electronic Specification:

In VR Gimbal We decide to use this kind of electronic parts  :
  * as micro we use STM32F1 64 pin.
  * 1 MPU6000 + HMC5883 for Z axis Direct Drive CAM using i2c bus.
  * 1 MPU6000 on spi bus. for Roll and Pitch cam.
  * EEPROM for storage the parameter of gimbal.
  * 3 ST Driver for manage 3 Brushless Motors with 9 Hardware PWM Output.
  * 1 input for Ublox GPS.
  * 4 PPM Radio Input or 1 PPMSUM radio input until 8 channel or more.
  * 1 Telemetry port for mavlink control.

As developer enviroment we use VR Ide Universal (based on eclipse) compatible with VRBRAIN and MP32 board now also with VR GIMBAL.

The developer lib and hal at the begin will be compatible with our APM\_LIB ported to STM32F1 library the same used on MP32F1 board.

That support all the APM library available and arduino language sintax .

In our code we decide to port on VR Gimbal :

  * AP\_COMMON
  * AP\_VAR
  * AP\_InertialSensor
  * AP\_IMU
  * AP\_Camera
  * AP\_Mount
  * Mavlink

and other utility yet available on our standard F1 package ...

We would develop also a utility for manage the board on pc and on android smartphone.
Your name will be in the list of developer of this project. The code will be opensource as other in this great community ... the support in development and donation are welcome .

For more info about the project contact me at info@virtualrobotix.com
In our roadmap the first  stable version of code will be available in 1 month.

In the next week will be available the enviroment , with hal and library , then starting to implement the code functionality for manage the first opensource 32 bit 3 axis direct drive.

I hope that you like our project and join us in development.

In VR Lab mecatronix group are working hard and is yet available a good gimbal for GOPRO

Join us in VR Gimbal User group here :
http://www.virtualrobotix.com/group/vr-gimbal-user-group?xg_source=activity

New Wiki and online manual available here:
http://vrgimbal.wordpress.com/