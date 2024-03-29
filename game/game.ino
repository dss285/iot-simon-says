/*
 * Author: Denis Cosmin
 * Date: 19.09.2016
 * Name: Simon Says
 * 
 * To add a reset button connect: reset -> button <- pulldown resistor ground.
 * The buttons have 1k pulldown resitors.
 * The leds have a 220 ohm resistor.
 * 
 * Will use the following numbers for colors, pins and notes
 * 0 - Yellow
 * 1 - Green
 * 2 - Red
 * 3 - Blue
 * 
 */

/*
 * The game class, handles everything.
 */
class Game {
    private:
      int debounce(int last, int buttonPin);
      void playNote(int note, int noteSpeed) const;
      void flashLed(int led, int flashSpeed) const;
    public:
      static const int RASP_OUTPUT_PIN;
      static const int RASP_INPUT_PIN;
      static const int RED_PIN;
      static const int BLUE_PIN;
      static const int GREEN_PIN;
      static const int YELLOW_PIN;
      static const int MICROPHONE_PIN;
      static const int RED_BUTTON_PIN;
      static const int BLUE_BUTTON_PIN;
      static const int GREEN_BUTTON_PIN;
      static const int YELLOW_BUTTON_PIN;
      static const int RED_TONE;
      static const int BLUE_TONE;
      static const int GREEN_TONE;
      static const int YELLOW_TONE;
      static const int GAMEOVER_TONE;
      int gameLevel[200];
      int gameSpeed;
      int lastButtonValue;
      int currentLevel;
      int gameIsOver;
      double gameDifficulty;
      enum color { YELLOW, GREEN, RED, BLUE };
    public:
    Game();
    Game(int);
    void playLevel();
    int userInput();
    int gameOver();
    int getNote(int note) const;
    int pinToColorCode(int);
    int colorCodeToPin(int);
    int readButton(int buttonPin);
};

/* Pin settings */
static const int Game::RASP_OUTPUT_PIN      = 2;
static const int Game::RASP_INPUT_PIN       = 3;
static const int Game::MICROPHONE_PIN       = 5;
static const int Game::BLUE_PIN             = 6;
static const int Game::RED_PIN              = 7;
static const int Game::GREEN_PIN            = 8;
static const int Game::YELLOW_PIN           = 9;
static const int Game::BLUE_BUTTON_PIN      = 11;
static const int Game::RED_BUTTON_PIN       = 13;
static const int Game::GREEN_BUTTON_PIN     = 10;
static const int Game::YELLOW_BUTTON_PIN    = 12;
/* Tone frequencies */
static const int Game::RED_TONE             = 800;
static const int Game::BLUE_TONE            = 900;
static const int Game::YELLOW_TONE          = 1000;
static const int Game::GREEN_TONE           = 1100;
static const int Game::GAMEOVER_TONE        = 200;

// Construct and initialize the Game object.
Game::Game(int difficulty) : gameSpeed(2000), lastButtonValue(-1), currentLevel(0), gameDifficulty(difficulty), gameIsOver(0) {
    pinMode(Game::MICROPHONE_PIN, OUTPUT);
    pinMode(Game::BLUE_PIN, OUTPUT);
    pinMode(Game::RED_PIN, OUTPUT);
    pinMode(Game::GREEN_PIN, OUTPUT);
    pinMode(Game::YELLOW_PIN, OUTPUT);
}

Game::Game() : gameSpeed(2000), lastButtonValue(-1), currentLevel(0), gameDifficulty(10), gameIsOver(0) {
    pinMode(Game::MICROPHONE_PIN, OUTPUT);
    pinMode(Game::BLUE_PIN, OUTPUT);
    pinMode(Game::RED_PIN, OUTPUT);
    pinMode(Game::GREEN_PIN, OUTPUT);
    pinMode(Game::YELLOW_PIN, OUTPUT);
}

/*
 * Makes sure the button is pressed only once.
 */
int Game::debounce(int last, int buttonPin) {
      int current = digitalRead(buttonPin);
      if (last != current)
      {
        delay(5);
        current = digitalRead(buttonPin);
      }
      return current;
}

/*
 * Plays a note. 
 * Receives the button number and plays the corresponding note.
 */
void Game::playNote(int note, int noteSpeed) const {
    
    note = Game::getNote(note);
    
    tone(Game::MICROPHONE_PIN, note, noteSpeed);  
}

/*
 * Returns the corresponding color code based on pin.
 */
int Game::colorCodeToPin(int value) {
    int ret_val = -1;
   
    switch(value) {
      case RED:
          ret_val = Game::RED_PIN;
          break;
      case GREEN:
          ret_val = Game::GREEN_PIN;
          break;
      case BLUE:
          ret_val = Game::BLUE_PIN;
          break;
      case YELLOW:
          ret_val = Game::YELLOW_PIN;
          break;
      default:
        delay(1000);
        exit(0);
    }

    return ret_val;
}

/*
 * Converts the button pin to a color code.
 */
int Game::pinToColorCode(int value) {
    int ret_val = -1;
    switch(value) {
        case Game::RED_BUTTON_PIN:
            ret_val = RED;
            break;
        case Game::GREEN_BUTTON_PIN:
            ret_val = GREEN;
            break;
        case Game::BLUE_BUTTON_PIN:
            ret_val = BLUE;
            break;
        case Game::YELLOW_BUTTON_PIN:
            ret_val = YELLOW;
            break;
        default:
          delay(1000);
          exit(0);
    }

    return ret_val;
}

/*
 * The the corresponding note based on the color code it receives.
 */
int Game::getNote(int note) const {
    int return_value = -1;
    switch(note) {
      case YELLOW:
          return_value = Game::YELLOW_TONE;
          break;
      case GREEN:
          return_value = Game::GREEN_TONE;
          break;
      case RED:
          return_value = Game::RED_TONE;
          break;
      case BLUE:
          return_value = Game::BLUE_TONE;
          break;
      case 4:
          return_value = Game::GAMEOVER_TONE;
          break;        
      default:
        delay(1000);
        exit(0);
    }
    return return_value;
}

/*
 * Flashes a led. Receives the led code and sets it to the corresponding pin.
 */
void Game::flashLed(int led, int flashSpeed) const {


    led = Game::colorCodeToPin(led);

    digitalWrite(led, HIGH);
    delay(flashSpeed);
    digitalWrite(led, LOW);
}

/*
 * Plays the next level.
 */
void Game::playLevel() {
  Game::gameLevel[Game::currentLevel] = random(0, 4); // Create a random move every time. 0 to 4 exclusive.
  ++Game::currentLevel;
  int nextDificulty = Game::gameDifficulty * Game::currentLevel;
  if (Game::gameSpeed - nextDificulty >= 10 && Game::gameSpeed >= 750) {
    Game::gameSpeed -= nextDificulty; // decrease the speed;
  }
  
  // Play all the moves
  for (int i = 0; i < Game::currentLevel; ++i) {
      Game::playNote(Game::gameLevel[i], Game::gameSpeed);
      Game::flashLed(Game::gameLevel[i], Game::gameSpeed);
  }
}
/*
 * Reads the button value and returns the following codes:
 * 0 - Yellow 1 - Green 2 - Red 3 - Blue
 */
int Game::readButton(int buttonPin) {
    int currentButtonValue = Game::debounce(Game::lastButtonValue, buttonPin);
    int return_value = -1;
    if (lastButtonValue == LOW && currentButtonValue > LOW) {
        return_value = Game::pinToColorCode(buttonPin);
    }
    Game::lastButtonValue = currentButtonValue;
    if (return_value >= 0) {
    }
    return return_value;
}

int Game::gameOver() {
    if (Game::gameIsOver) {
      int i = 0;

    }
    return Game::gameIsOver;
}

/*
 * Gets the user button presses and checks them to see if they're good.
 */
int Game::userInput() {
    for (int i = 0; i < Game::currentLevel; ++i) {
      int buttonPressed = -1;
      while(true) {
          buttonPressed = readButton(Game::RED_BUTTON_PIN);
          if (buttonPressed != -1) { break; }
          buttonPressed = readButton(Game::GREEN_BUTTON_PIN);
          if (buttonPressed != -1) { break; }
          buttonPressed = readButton(Game::YELLOW_BUTTON_PIN);
          if (buttonPressed != -1) { break; }
          buttonPressed = readButton(Game::BLUE_BUTTON_PIN);
          if (buttonPressed != -1) { break; }
      }

      if (buttonPressed != gameLevel[i]) {
        int i = 0;
            while(i<3) {
              Game::playNote(4, 400);
              i++;
              delay(500);
            }
          Game::flashLed(buttonPressed, 1000);
          return 0;
      }

      Game::playNote(buttonPressed, Game::gameSpeed);
      Game::flashLed(buttonPressed, Game::gameSpeed);
    }
    delay(500);
    return 1;
}

Game g; //  Constructs the game object.
bool read_from_serial = true;
void setup() {
  Serial.begin(9600);
  randomSeed(0);
}

void loop() {

  if(read_from_serial) {
    while(!Serial.available() > 0) {
      delay(10);
    }
    String data = Serial.readStringUntil('\n');
    if (data == "newgame") {
      read_from_serial = false;
       delay(1000); // Wait for serial to finish printing.
    
        g = Game(100);
        g.gameIsOver = 0;
        
    }
  } else {
      if (g.gameOver() == 1) { 
          Serial.println(g.currentLevel);
          read_from_serial = true;
          Serial.readString();
        
      } else {
        g.playLevel();
        if (g.userInput() == 0) {
            g.gameIsOver = 1;
        }
      }
  }
}