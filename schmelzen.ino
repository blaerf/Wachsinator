void schmelzen() {
#ifdef DEBUG
  Serial.println("Schmelzen");
  Serial.println ("Start-Stop: " + buttonState);
#endif

  //digitalWrite(HEIZUNG_L, LOW);
  //digitalWrite(HEIZUNG_N, LOW);
  digitalWrite(LAMPE_BETRIEB, LOW);

  DoControl();
  temperatur ();
  heizen();

  if (buttonState == false || digitalRead (SCHALTER_SCHMELZEN) == HIGH || digitalRead (SCHALTER_ZEIT) == HIGH) {
    opState = BEREIT;
  }
}
