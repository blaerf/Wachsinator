void tauen() {
#ifdef DEBUG
  Serial.println("Tauen");
  Serial.println ("Start-Stop: " + buttonState);
#endif

  //digitalWrite(HEIZUNG_L, LOW);
  //digitalWrite(HEIZUNG_N, LOW);
  digitalWrite(LAMPE_BETRIEB, LOW);

  DoControl();
  temperatur ();
  heizen();

  if (buttonState == false || digitalRead (SCHALTER_TAUEN) == HIGH) {
    opState = BEREIT;
  }
}
