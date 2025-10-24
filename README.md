# Snake_Game_Joystick

A classic Snake Game implemented on an Arduino-compatible microcontroller using an SSD1306 OLED display and a joystick module.
The player controls the snake’s movement using the joystick, guiding it to eat food and grow longer without hitting itself.

🎮 Features

Real-time snake movement using analog joystick control.

OLED display visualization (128x64).

Randomly generated food positions.

Score tracking.

Game over detection with reset option.

Smooth movement and responsive controls.

🧠 Components Required
Component	Quantity	Description
Arduino / ESP32 Board	1	Main microcontroller board
OLED Display (SSD1306 128x64)	1	For displaying the game
Joystick Module	1	Used for snake movement and selection
Jumper Wires	As needed	For connections
Breadboard	1	(Optional) For easy wiring
⚙️ Pin Connections
Component	Pin	Arduino/ESP32 Pin
Joystick (VRx)	→	35
Joystick (VRy)	→	34
Joystick (SW)(Button)	→	25
OLED SDA	→	GPIO 21 (Typical I2C SDA pin)
OLED SCL	→	GPIO 22 (Typical I2C SCL pin)
OLED VCC	→	3.3V / 5V
OLED GND	→	GND

(Update SDA/SCL pins as per your board configuration if needed.)

🧩 Libraries Used

Make sure you have installed the following libraries via Arduino Library Manager:

Adafruit_GFX

Adafruit_SSD1306

🚀 How to Use

Open the Snake_Joystick_Game.ino file in the Arduino IDE.

Select the correct board and COM port from Tools → Board / Port.

Install required libraries (as mentioned above).

Upload the sketch to your Arduino/ESP32 board.

Control the snake using the joystick:

Move Up/Down/Left/Right using analog movement.

Press the joystick button to restart after Game Over.

🕹️ Game Rules

Eat food to grow the snake and increase your score.

Avoid colliding with yourself or the screen edges.

The game ends when a collision occurs — press the joystick to restart.

🧾 Example Output (OLED Display)
SCORE: 5
[Snake moves across screen]
GAME OVER
Press Joystick to Restart

🧠 Code Overview

setup(): Initializes OLED and joystick inputs.

loop(): Main game loop for updating movement, drawing, and detecting collisions.

resetGame(): Resets all positions and score after Game Over.

drawSnake(), drawFood(), checkCollision(): Handle rendering and logic.

🛠️ Future Improvements

Add difficulty levels (speed increase with score).

Implement border wrapping mode.

Add sound effects with a buzzer.

Add menu or pause functionality.

📜 License

This project is open-source and free to use for educational and personal purposes.
