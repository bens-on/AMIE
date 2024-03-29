# AMIE
ECE202 Sophomore Design Project | Arduino Monitored Independent Ecosystem

# EDIT LOG
- 2/23/24 by Alex Benson (inital code and objectives)
- 2/27/24 by Alex Benson (inital Arduino Uno Case Model uploaded)
- 3/2/24 by Alex Benson (added code for the LCD integration)
- 3/8/24 by Alex Benson (added ARCIE_MAIN_FUNCTIONS_LCD, this is the main code for the LCD display in function form. this can call the soil monitor at certain intervals.)
- 3/28/24 by Alex Benson (added AMIE_I2C_LCD_MAIN, this is the main code for the LCD with I2C connection. In function form. Added trivial details to repo)

# OBJECTIVES
- COMPLETE: Initial Testing of current code to make sure readings are accurate and that the loop is able to execute with both the temp/humidity AND soil moisture content statements
- CANCELLED: Add RGB LED control to simulate daylight cycle. This can be done with BLUE and GREEN lights for a period of 12 hours.
- COMPLETE: Add the ability to display values on the LCD screen, switching from humidity/temp to soil moisture readings every 10 seconds or so.
- COMPLETED: Grow light added as outside hardware, not included in code.
- COMPLETED: Transfer code to I2C format for minimal hardware connections.
