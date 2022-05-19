void telegramMSG() {
  // Send an echo message back
  if (strncmp(Bot.received_msg.text, "on", strlen("on")) == 0 && status == 0) {
    Bot.sendMessage(Bot.received_msg.chat.id, "Сеесекундно маховики информации будут запущенны!");
    status = 1;

    // set cursor to first column, first row
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PC Status:");
    lcd.setCursor(0, 1);
    lcd.print("Now its run");
    delay(1000);
    // clears the display to print new message

    digitalWrite(relayPin, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(relayPin, HIGH);
    value = HIGH;
  }
  else if (strncmp(Bot.received_msg.text, "off", strlen("off")) == 0 && status == 1) {
    Bot.sendMessage(Bot.received_msg.chat.id, "Пару секунд и выключюсь!");
    status = 0;

    // set cursor to first column, first row
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PC Status:");
    lcd.setCursor(0, 1);
    lcd.print("Shutdown");
    delay(1000);
    // clears the display to print new message

    digitalWrite(relayPin, LOW);
    value = LOW;

    delay(1000);

    digitalWrite(relayPin, HIGH);
    value = HIGH;
  }
  else if (strncmp(Bot.received_msg.text, "stat", strlen("stat")) == 0) {
    String str1 = String(therm.getTempAverage());
    Bot.sendMessage(Bot.received_msg.chat.id, "Фигня");

    // set cursor to first column, first row
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temperature:");
    lcd.setCursor(0, 1);
    lcd.print(therm.getTempAverage() + ' C');
    delay(1000);
    // clears the display to print new message
  }
  //        else {
  //          Bot.sendMessage(Bot.received_msg.chat.id, "Ты или вспомни или не вспомни! Что то не так.");
  //        }

  if (strncmp(Bot.received_msg.text, "test", strlen("test")) == 0) {
    Bot.sendMessage(Bot.received_msg.chat.id, "Проверяем ответ платы!");

    // set cursor to first column, first row
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Its u look it");
    lcd.setCursor(0, 1);
    lcd.print("All GOOD");
    delay(1000);
  }
}
