#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Joystick pins (updated for correct orientation)
#define VRX_PIN 35  // Y-axis
#define VRY_PIN 34  // X-axis
#define SW_PIN 25

const int SNAKE_SIZE = 4;
const int MAX_LENGTH = 100; // Max number of segments

int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
int length = 1;

int foodX = 20, foodY = 20;
int dirX = 1, dirY = 0;
int speed = SNAKE_SIZE;
int score = 0;
bool gameOver = false;

void setup() {
  Serial.begin(115200);
  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 allocation failed");
    for (;;);
  }

  randomSeed(analogRead(0));
  resetGame();
}

void loop() {
  if (gameOver) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println("   GAME OVER");
    display.setCursor(20, 35);
    display.print(" Score: ");
    display.println(score);
    display.setCursor(10, 50);
    display.display();

    if (digitalRead(SW_PIN) == LOW) {
      delay(500);  // debounce
      resetGame();
    }
    return;
  }

  // Joystick control
  int xVal = analogRead(VRY_PIN);
  int yVal = analogRead(VRX_PIN);

  if (xVal < 1000 && dirX == 0) { dirX = -1; dirY = 0; } // Left
  else if (xVal > 3000 && dirX == 0) { dirX = 1; dirY = 0; } // Right
  else if (yVal < 1000 && dirY == 0) { dirX = 0; dirY = -1; } // Up
  else if (yVal > 3000 && dirY == 0) { dirX = 0; dirY = 1; } // Down

  // Move snake body
  for (int i = length - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move head
  snakeX[0] += dirX * speed;
  snakeY[0] += dirY * speed;

  // Collision with wall
  if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
    gameOver = true;
    return;
  }

  // Collision with self
  for (int i = 1; i < length; i++) {
    if (abs(snakeX[0] - snakeX[i]) < SNAKE_SIZE && abs(snakeY[0] - snakeY[i]) < SNAKE_SIZE) {
      gameOver = true;
      return;
    }
  }

  // Eat food
  if (abs(snakeX[0] - foodX) < SNAKE_SIZE && abs(snakeY[0] - foodY) < SNAKE_SIZE) {
    foodX = random(0, SCREEN_WIDTH / SNAKE_SIZE) * SNAKE_SIZE;
    foodY = random(0, SCREEN_HEIGHT / SNAKE_SIZE) * SNAKE_SIZE;
    if (length < MAX_LENGTH) length++;
    score++;
  }

  // Draw game
  display.clearDisplay();

  // Draw food
  display.fillRect(foodX, foodY, SNAKE_SIZE, SNAKE_SIZE, SSD1306_WHITE);

  // Draw snake
  for (int i = 0; i < length; i++) {
    display.fillRect(snakeX[i], snakeY[i], SNAKE_SIZE, SNAKE_SIZE, SSD1306_WHITE); 
  }

  // Display score
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("Score: ");
  display.println(score);

  display.display();
  delay(100);
}

void resetGame() {
  snakeX[0] = 64;
  snakeY[0] = 32;
  length = 1;
  dirX = 1;
  dirY = 0;
  score = 0;
  gameOver = false;
  foodX = random(0, SCREEN_WIDTH / SNAKE_SIZE) * SNAKE_SIZE;
  foodY = random(0, SCREEN_HEIGHT / SNAKE_SIZE) * SNAKE_SIZE;
}
