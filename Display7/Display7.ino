#define NUM_DISPLAY_PINS 8
#define TOTAL_NUMBERS 10
#define DP_LED 9
#define DIGIT_ERROR_CODE 110
#define CALCULATE_ERROR_CODE 111
#define MAX_STRING_LENGTH 4
#define MAX_ARGS 3

byte ERROR_LETTER[NUM_DISPLAY_PINS] = { 1, 0, 0, 1, 1, 1, 1, 0 };
byte WELCOME_LETTER[NUM_DISPLAY_PINS] = { 1, 1, 1, 1, 1, 1, 1, 1 };
byte TEST_LETTER[NUM_DISPLAY_PINS] = { 1, 0, 1, 1, 0, 1, 0, 1 };
byte DIGITAL_NUMBERS[TOTAL_NUMBERS][NUM_DISPLAY_PINS] = {
  //A  B  C  D  E  F  G  DP
  { 1, 1, 1, 1, 1, 1, 0, 0 },  // NUMBER 0
  { 0, 1, 1, 0, 0, 0, 0, 0 },  // NUMBER 1
  { 1, 1, 0, 1, 1, 0, 1, 0 },  // NUMBER 2
  { 1, 1, 1, 1, 0, 0, 1, 0 },  // NUMBER 3
  { 0, 1, 1, 0, 0, 1, 1, 0 },  // NUMBER 4
  { 1, 0, 1, 1, 0, 1, 1, 0 },  // NUMBER 5
  { 1, 0, 1, 1, 1, 1, 1, 0 },  // NUMBER 6
  { 1, 1, 1, 0, 0, 0, 0, 0 },  // NUMBER 7
  { 1, 1, 1, 1, 1, 1, 1, 0 },  // NUMBER 8
  { 1, 1, 1, 0, 0, 1, 1, 0 },  // NUMBER 9
};

void setPinesMode(byte pines[NUM_DISPLAY_PINS]) {
  for (byte i = 0; i <= NUM_DISPLAY_PINS; i++) {
    pinMode(pines[i], OUTPUT);
  }
}

void turnOnDisplay(byte num[NUM_DISPLAY_PINS]) {
  for (byte i = 0; i < NUM_DISPLAY_PINS; i++) {
    byte currentPin = i + 2;
    num[i]
      ? digitalWrite(currentPin, HIGH)
      : digitalWrite(currentPin, LOW);
  }
}

void printNumber(int num) {
  if (num < -9 || num > 9) {
    turnOnDisplay(ERROR_LETTER);
    return;
  }

  turnOnDisplay(DIGITAL_NUMBERS[abs(num)]);

  if (num < 0) {
    digitalWrite(DP_LED, HIGH);
  }
}

void splitBySpaceChar(String input, char** buffer) {
  int wordStart = 0;
  int wordEnd = 0;
  int currentFilledArg = 0;

  input.trim();
  int inputLen = input.length();
  for (int i = 0; i < inputLen; i++) {
    if (input[i] == ' ') {
      // ESTO PARA NO TENER EN CUENTA CARACTERES DE ESPACIO SEGUIDOS
      if (i > 0 && input[i - 1] == ' ') {
        wordStart = i + 1;
        continue;
      }

      String argString = input.substring(wordStart, i);
      argString.toCharArray(buffer[currentFilledArg], MAX_STRING_LENGTH);

      currentFilledArg++;
      wordStart = i + 1;
    } else if (i == inputLen - 1) {
      String argString = input.substring(wordStart, inputLen);
      argString.toCharArray(buffer[currentFilledArg], MAX_STRING_LENGTH);
    }
  }
}

char** createBuffer() {
  char** buffer = NULL;
  buffer = malloc(MAX_ARGS * sizeof(char*));
  if (buffer == NULL) {
    Serial.println("ERROR: MALLOC FAIL");
    return;
  }
  for (int i = 0; i < MAX_ARGS; i++) {
    buffer[i] = (char*)malloc(MAX_STRING_LENGTH * sizeof(char));
    if (buffer[i] == NULL) {
      Serial.println("ERROR: MALLOC FAIL");
      return;
    }
  }
  for (int i = 0; i < MAX_ARGS; i++) {
    for (int j = 0; j < MAX_STRING_LENGTH; j++) {
      buffer[i][j] = '\0';
    }
  }
  return buffer;
}

void setup() {
  Serial.begin(9600);
  byte pines[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
  setPinesMode(pines);
}

void loop() {
  if (Serial.available() > 0) {
    Serial.println("hola");
    char** splittedData = createBuffer();
    String serialInput = Serial.readStringUntil('\n');
    splitBySpaceChar(serialInput, splittedData);
    char messageType = *splittedData[0];
    if(messageType == 'M') {
      char messagePayload = *splittedData[1];
      if(messagePayload == 'B') {
        turnOnDisplay(WELCOME_LETTER);
      }else if(messagePayload == 'E') {
        turnOnDisplay(ERROR_LETTER);
      }
    }else if(messageType == 'N') {
      char* messagePayload = splittedData[1];
      printNumber(atoi(messagePayload));
    }
  }
}