# include <AccelStepper.h>

AccelStepper alaStepper(1, 11, 12);
AccelStepper ylaStepper(1, 6, 7);

long int lastStepTime = 0;
int stepDelay = 50;

void setup() {
  alaStepper.setMaxSpeed(1000);
  alaStepper.setAcceleration(500);
  alaStepper.setCurrentPosition(0);

  ylaStepper.setMaxSpeed(1000);
  ylaStepper.setAcceleration(500);
  ylaStepper.setCurrentPosition(0);
}

void loop() {
  int ylaOik = analogRead(A0);
  int ylaVas = analogRead(A1);
  int alaOik = analogRead(A2);
  int alaVas = analogRead(A3);

  Serial.print("ylaOik: ");
  Serial.print(ylaOik);
  Serial.print(" ylaVas: ");
  Serial.print(ylaVas);
  Serial.print(" alaOik: ");
  Serial.print(alaOik);
  Serial.print(" alaVas: ");
  Serial.print(alaVas);
  Serial.println("");

  int avgOik = (ylaOik + alaOik) / 2;
  int avgVas = (ylaVas + alaVas) / 2;
  int avgYla = (ylaOik + ylaVas) / 2;
  int avgAla = (alaOik + alaVas) / 2;

  if ( avgOik > avgVas ) {
    alaStepper.move(5);
    Serial.println("Oikealle");
  }
  else if ( avgVas > avgOik ) {
    alaStepper.move(-5);
    Serial.println("Vasemmalle");
  }
  if ( avgYla > avgAla ) {
    ylaStepper.move(5);
    Serial.println("Ylös");
  }
  else if (avgYla < avgAla ) {
    ylaStepper.move(-5);
    Serial.println("Alas");
  }

  if ( millis() - lastStepTime >= stepDelay) {
    alaStepper.run();
    ylaStepper.run();
    lastStepTime = millis();
  }
}
