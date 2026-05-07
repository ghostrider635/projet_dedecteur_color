// Pins TCS3200
#define S0 18
#define S1 19
#define S2 21
#define S3 22
#define sensorOut 23

// Pins LED RGB
#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

int redFrequency = 0;
int greenFrequency = 0;
int blueFrequency = 0;

void setup() {
  Serial.begin(115200);

  // Capteur
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // LED RGB
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Mise à l'échelle fréquence à 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  eteindreLED();
}

void loop() {

  // Lire rouge
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);

  // Lire vert
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);

  // Lire bleu
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  blueFrequency = pulseIn(sensorOut, LOW);

  Serial.print("R: ");
  Serial.print(redFrequency);

  Serial.print(" G: ");
  Serial.print(greenFrequency);

  Serial.print(" B: ");
  Serial.println(blueFrequency);

  detecterCouleur();

  delay(300);
}

void detecterCouleur() {

  // Plus la valeur est basse, plus la couleur est détectée fortement

  if (redFrequency < greenFrequency && redFrequency < blueFrequency) {
    Serial.println("ROUGE");
    afficherRouge();
  }

  else if (greenFrequency < redFrequency && greenFrequency < blueFrequency) {
    Serial.println("VERT");
    afficherVert();
  }

  else if (blueFrequency < redFrequency && blueFrequency < greenFrequency) {
    Serial.println("BLEU");
    afficherBleu();
  }

  else {
    eteindreLED();
  }
}

void afficherRouge() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void afficherVert() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}

void afficherBleu() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void eteindreLED() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}
