void temperature() {
  if (timeClient.getHours() >= 6 && timeClient.getHours() <= 20) {
    digitalWrite(relayPinLight, HIGH);
    value = HIGH;
    if (therm.getTempAverage() <= 25.99)
    {
      digitalWrite(relayPinStat, HIGH);
      value = HIGH;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(therm.getTempAverage());
      lcd.setCursor(6, 0);
      lcd.print("Temp UP");
      lcd.setCursor(0, 1);
      lcd.print(timeClient.getHours());
      delay(500);
    }
    else if (therm.getTempAverage() >= 26.35)
    {
      digitalWrite(relayPinStat, LOW);
      value = LOW;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(therm.getTempAverage());
      lcd.setCursor(6, 0);
      lcd.print(" Temp DOWN");
      lcd.setCursor(0, 1);
      lcd.print(timeClient.getHours());
      delay(500);
    }
  } else {
    digitalWrite(relayPinLight, LOW);
    digitalWrite(relayPinStat, LOW);
    value = LOW;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(timeClient.getHours());
    lcd.setCursor(0, 1);
    lcd.print("Sensors off");
    delay(2000);
  }
}
