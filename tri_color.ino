// --- Configuration des Pins (Inchangée) ---
#define S0 18
#define S1 19
#define S2 21
#define S3 22
#define sensorOut 23
#define RED_LED 25
#define GREEN_LED 26
#define BLUE_LED 27

// --- Paramètres d'étalonnage (Ajustés selon vos tests) ---
// Ces valeurs permettent de convertir la fréquence en 0-255
int redMin = 15,   redMax = 220; 
int greenMin = 15, greenMax = 220;
int blueMin = 15,  blueMax = 220;

void setup() {
  Serial.begin(115200);

  // Configuration Capteur
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configuration LED (Sorties PWM)
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  // Échelle de fréquence à 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.println("Système prêt : Détection de toutes les couleurs...");
}

void loop() {
  // 1. LECTURE des fréquences brutes
  int rBrut = readFrequency(LOW, LOW);   // Filtre Rouge
  delay(10);                             // Petite pause pour la stabilité
  int gBrut = readFrequency(HIGH, HIGH); // Filtre Vert
  delay(10);
  int bBrut = readFrequency(LOW, HIGH);  // Filtre Bleu

  // 2. CONVERSION (Mapping) en échelle 0-255
  // On utilise constrain pour éviter de dépasser 255 ou descendre sous 0
  int R = constrain(map(rBrut, redMin, redMax, 255, 0), 0, 255);
  int G = constrain(map(gBrut, greenMin, greenMax, 255, 0), 0, 255);
  int B = constrain(map(bBrut, blueMin, blueMax, 255, 0), 0, 255);

  // 3. AFFICHAGE des données pour contrôle
  Serial.printf("RGB: [%d, %d, %d] | Bruts: (r:%d, g:%d, b:%d)\n", R, G, B, rBrut, gBrut, bBrut);
  
  // 4. ACTIONS
  identifierNuance(R, G, B);
  piloterLED(R, G, B);

  delay(400); // Vitesse de lecture
}

// Fonction de lecture propre
int readFrequency(int s2, int s3) {
  digitalWrite(S2, s2);
  digitalWrite(S3, s3);
  return pulseIn(sensorOut, LOW);
}

// Commande de la LED par mélange de couleurs (PWM)
void piloterLED(int r, int g, int b) {
  analogWrite(RED_LED, r);
  analogWrite(GREEN_LED, g);
  analogWrite(BLUE_LED, b);
}

// Analyse précise des nuances
void identifierNuance(int r, int g, int b) {
  int total = r + g + b;

  if (total < 50) {
    Serial.println(">> NOIR / TROP SOMBRE");
  } 
  else if (r > 210 && g > 210 && b > 210) {
    Serial.println(">> BLANC / TRES CLAIR");
  }
  else if (r > 200 && g > 100 && g < 180 && b < 100) {
    Serial.println(">> ORANGE");
  }
  else if (r > 180 && g > 180 && b < 120) {
    Serial.println(">> JAUNE");
  }
  else if (r > 150 && b > 150 && g < 130) {
    Serial.println(">> VIOLET / ROSE");
  }
  else if (g > 150 && b > 150 && r < 130) {
    Serial.println(">> TURQUOISE / CYAN");
  }
  else if (r > g && r > b) {
    Serial.println(">> ROUGE");
  }
  else if (g > r && g > b) {
    Serial.println(">> VERT");
  }
  else if (b > r && b > g) {
    Serial.println(">> BLEU");
  }
  else {
    Serial.println(">> NUANCE MIXTE");
  }
}