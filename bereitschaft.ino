void bereitschaft() {

  digitalWrite(LAMPE_BEREIT, LOW);
  digitalWrite(HEIZUNG_L, HIGH);
  digitalWrite(HEIZUNG_N, HIGH);
  digitalWrite(LAMPE_BETRIEB, HIGH);

  DoControl();
  temperatur ();

  if (buttonState == true && digitalRead (SCHALTER_TAUEN) == LOW) {
    opState = TAUEN;
#ifdef DEBUG
    Serial.println("Tauen");
#endif

  }

  else if (buttonState == true && digitalRead (SCHALTER_SCHMELZEN) == LOW && digitalRead (SCHALTER_ZEIT) == LOW) {
    opState = SCHMELZEN;
#ifdef DEBUG
    Serial.println("Schmelzen");
#endif
  }

  else {
#ifdef DEBUG
    Serial.println("Bereitschaft");
    Serial.print ("Start-Stop: ");
    Serial.print(buttonState);
    Serial.print("\n");
#endif
    opState = BEREIT;

  }

}
