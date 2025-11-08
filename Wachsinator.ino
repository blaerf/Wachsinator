//#define DEBUG

#include <OneWire.h>
#include <DallasTemperature.h>

// ************************************************
// Pins
// ************************************************

// Ausgänge
#define HEIZUNG_L 7
#define HEIZUNG_N 8
#define LAMPE_BEREIT 9
#define LAMPE_BETRIEB 10

// Eingänge
#define SCHALTER_START 3
#define SCHALTER_TAUEN 4
#define SCHALTER_SCHMELZEN 5
#define SCHALTER_ZEIT 6
#define POTI_TEMPERATUR A0
#define TEMPERATUR_SENSOR 2

// ************************************************
// Maschinenstatus
// ************************************************

enum operatingState { BEREIT, BETRIEB, TAUEN, SCHMELZEN};
operatingState opState = BEREIT;

// ************************************************
// Sensor Variablen und Konstanten
// ************************************************

OneWire oneWire(TEMPERATUR_SENSOR);
DallasTemperature sensors(&oneWire);
DeviceAddress tempSensor;
int tempIstWert = 0;
int tempIstWertAlt = 0;
int tempSollWert = 0;
int tempSollWertAlt = 0;
int tempSollWertAnzeige = 0;

volatile boolean buttonState = false;
long debouncing_time = 15; //Debouncing Time in Milliseconds
volatile unsigned long last_micros;

void setup() {
  Serial.begin(9600);
  pinMode(HEIZUNG_L, OUTPUT);
  digitalWrite(HEIZUNG_L, HIGH);
  pinMode(HEIZUNG_N, OUTPUT);
  digitalWrite(HEIZUNG_N, HIGH);
  pinMode(LAMPE_BETRIEB, OUTPUT);
  digitalWrite(LAMPE_BETRIEB, HIGH);
  pinMode(LAMPE_BEREIT, OUTPUT);
  digitalWrite(LAMPE_BEREIT, HIGH);

  pinMode(SCHALTER_START, INPUT_PULLUP);
  pinMode(SCHALTER_TAUEN, INPUT_PULLUP);
  pinMode(SCHALTER_SCHMELZEN, INPUT_PULLUP);
  pinMode(SCHALTER_ZEIT, INPUT_PULLUP);
  pinMode(POTI_TEMPERATUR, INPUT_PULLUP);
  pinMode(TEMPERATUR_SENSOR, INPUT_PULLUP);

  tempSollWertAlt = analogRead(POTI_TEMPERATUR);

  sensors.begin();
  if (!sensors.getAddress(tempSensor, 0))
  {

  }
  sensors.setResolution(tempSensor, 12);
  sensors.setWaitForConversion(false);

  attachInterrupt(digitalPinToInterrupt(SCHALTER_START), buttonStart, LOW);

}

void loop() {

  switch (opState)
  {
    case BEREIT:
      bereitschaft();
      break;
    case TAUEN:
      tauen();
      break;
    case SCHMELZEN:
      schmelzen();
      break;
  }

}

// ************************************************
// Execute the control loop
// ************************************************
void DoControl() {
  // Read the tempIstWert:
  tempIstWert = sensors.getTempC(tempSensor);
  sensors.requestTemperatures(); // prime the pump for the next one - but don't wait
#ifdef DEBUG
  Serial.println(tempIstWert);
#endif
}

void temperatur() {
  tempSollWert = analogRead(POTI_TEMPERATUR);
  tempSollWertAnzeige = map(tempSollWert, 0, 1023, 0, 100);
#ifdef DEBUG
  Serial.println(tempSollWertAnzeige);
#endif
}

void heizen() {
  if (tempIstWert < tempSollWertAnzeige - 5) {
    digitalWrite(HEIZUNG_L, LOW);
    digitalWrite(HEIZUNG_N, LOW);
  }
  else if (tempIstWert >= tempSollWertAnzeige) {
    digitalWrite(HEIZUNG_L, HIGH);
    digitalWrite(HEIZUNG_N, HIGH);
  }
}

void buttonStart() {
  if ((long)(micros() - last_micros) >= debouncing_time * 1000) {
    buttonState = !buttonState;
    last_micros = micros();
  }

}
