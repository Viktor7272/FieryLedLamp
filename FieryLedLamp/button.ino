#ifdef ESP_USE_BUTTON

bool brightDirection;
static bool startButtonHolding = false;                     // флаг: кнопка удерживается для изменения яркости/скорости/масштаба лампы кнопкой
static bool Button_Holding = false;


void buttonTick()
{
  if (!buttonEnabled)                                       // события кнопки не обрабатываются, если она заблокирована
  {
    return;
  }

  touch.tick();
  uint8_t clickCount = touch.hasClicks() ? touch.getClicks() : 0U;


  // однократное нажатие
  if (clickCount == 1U)
  {
    if (dawnFlag)
    {
      manualOff = true;
      dawnFlag = false;
      #ifdef TM1637_USE
      clockTicker_blink();
      #endif
      FastLED.setBrightness(modes[currentMode].Brightness);
      changePower();
    }
    else
    {
      ONflag = !ONflag;
	  jsonWrite(configSetup, "Power", ONflag);
      changePower();
    }
    settChanged = true;
    if (ONflag)   eepromTimeout = millis();
    else    eepromTimeout = millis() + EEPROM_WRITE_DELAY;
    loadingFlag = true;

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    #ifdef USE_MULTIPLE_LAMPS_CONTROL
    multiple_lamp_control ();
    #endif  //USE_MULTIPLE_LAMPS_CONTROL
  }


  // двухкратное нажатие
  if (ONflag && clickCount == 2U)
  {
    if (Favorit_only)
	{
      uint8_t lastMode = currentMode;
      do {
        if (++currentMode >= MODE_AMOUNT) currentMode = 0;
      } while (FavoritesManager::FavoriteModes[currentMode] == 0 && currentMode != lastMode);
      if (currentMode == lastMode) // если ни один режим не добавлен в избранное, всё равно куда-нибудь переключимся
        if (++currentMode >= MODE_AMOUNT) currentMode = 0;
	}
    else
      if (++currentMode >= MODE_AMOUNT) currentMode = 0;
    
	jsonWrite(configSetup, "eff_sel", currentMode);
	jsonWrite(configSetup, "br", modes[currentMode].Brightness);
    jsonWrite(configSetup, "sp", modes[currentMode].Speed);
    jsonWrite(configSetup, "sc", modes[currentMode].Scale);
    FastLED.setBrightness(modes[currentMode].Brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();
    //FastLED.clear();
    //delay(1);

      if (random_on && FavoritesManager::FavoritesRunning)
        selectedSettings = 1U;

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    #ifdef USE_MULTIPLE_LAMPS_CONTROL
    multiple_lamp_control ();
    #endif  //USE_MULTIPLE_LAMPS_CONTROL
  }


  // трёхкратное нажатие
  if (ONflag && clickCount == 3U)
  {
	if (Favorit_only) 
	{
      uint8_t lastMode = currentMode;
      do {
        if (--currentMode >= MODE_AMOUNT) currentMode = MODE_AMOUNT - 1;
      } while (FavoritesManager::FavoriteModes[currentMode] == 0 && currentMode != lastMode);
      if (currentMode == lastMode) // если ни один режим не добавлен в избранное, всё равно куда-нибудь переключимся
        if (--currentMode >= MODE_AMOUNT) currentMode = MODE_AMOUNT - 1;
	}
	else 
	  if (--currentMode >= MODE_AMOUNT) currentMode = MODE_AMOUNT - 1;
    
	jsonWrite(configSetup, "eff_sel", currentMode);
	jsonWrite(configSetup, "br", modes[currentMode].Brightness);
    jsonWrite(configSetup, "sp", modes[currentMode].Speed);
    jsonWrite(configSetup, "sc", modes[currentMode].Scale);
    FastLED.setBrightness(modes[currentMode].Brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimeout = millis();
    //FastLED.clear();
    //delay(1);

      if (random_on && FavoritesManager::FavoritesRunning)
        selectedSettings = 1U;

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    #ifdef USE_MULTIPLE_LAMPS_CONTROL
    multiple_lamp_control ();
    #endif  //USE_MULTIPLE_LAMPS_CONTROL
  }


  // четырёхкратное нажатие
  if (clickCount == 4U)
  {
  
	//bool ota = false;
    #ifdef OTA
    if (otaManager.RequestOtaUpdate())
    {
      ONflag = true;
	  jsonWrite(configSetup, "Power", ONflag);
      currentMode = EFF_MATRIX;                             // принудительное включение режима "Матрица" для индикации перехода в режим обновления по воздуху
	  jsonWrite(configSetup, "eff_sel", currentMode);
	  jsonWrite(configSetup, "br", modes[currentMode].Brightness);
      jsonWrite(configSetup, "sp", modes[currentMode].Speed);
      jsonWrite(configSetup, "sc", modes[currentMode].Scale);
      //FastLED.clear();
      //delay(1);
      changePower();
	  //ota = true;
    }
    else
    #endif
	
	#ifdef BUTTON_CAN_SET_SLEEP_TIMER
	//if (!ota)
	{
    // мигать об успехе операции лучше до вызова changePower(), иначе сперва мелькнут кадры текущего эффекта
    showWarning(CRGB::Blue, 1000, 250U);                    // мигание синим цветом 1 секунду
    ONflag = true;
    changePower();
	jsonWrite(configSetup, "Power", ONflag);
    settChanged = true;
    eepromTimeout = millis();
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    TimerManager::TimeToFire = millis() + BUTTON_SET_SLEEP_TIMER1 * 60UL * 1000UL;
    TimerManager::TimerRunning = true;
	}
    #endif //BUTTON_CAN_SET_SLEEP_TIMER	
    ;
  }


  // пятикратное нажатие
  if (clickCount == 5U)                                     // вывод IP на лампу
  {
    if (espMode == 1U)
    {
      loadingFlag = true;
      
      #if defined(MOSFET_PIN) && defined(MOSFET_LEVEL)      // установка сигнала в пин, управляющий MOSFET транзистором, матрица должна быть включена на время вывода текста
      digitalWrite(MOSFET_PIN, MOSFET_LEVEL);
      #endif

      while(!fillString(WiFi.localIP().toString().c_str(), CRGB::White, false)) { delay(1); ESP.wdtFeed(); }

      #if defined(MOSFET_PIN) && defined(MOSFET_LEVEL)      // установка сигнала в пин, управляющий MOSFET транзистором, соответственно состоянию вкл/выкл матрицы или будильника
      digitalWrite(MOSFET_PIN, ONflag || (dawnFlag && !manualOff) ? MOSFET_LEVEL : !MOSFET_LEVEL);
      #endif

      loadingFlag = true;
    }
  }


  // шестикратное нажатие
  if (clickCount == 6U)                                     // вывод текущего времени бегущей строкой
  {
    printTime(thisTime, true, ONflag);
  }


  // семикратное нажатие
  if (clickCount == 7U)  // if (ONflag &&                   // смена рабочего режима лампы: с WiFi точки доступа на WiFi клиент или наоборот
  {
    #ifdef RESET_WIFI_ON_ESP_MODE_CHANGE
      if (espMode) wifiManager.resetSettings();                             // сброс сохранённых SSID и пароля (сброс настроек подключения к роутеру)
    #endif
    espMode = (espMode == 0U) ? 1U : 0U;
	jsonWrite(configSetup, "ESP_mode", (int)espMode);
	saveConfig();  

    #ifdef GENERAL_DEBUG
    LOG.printf_P(PSTR("Рабочий режим лампы изменён и сохранён в энергонезависимую память\nНовый рабочий режим: ESP_MODE = %d, %s\nРестарт...\n"),
      espMode, espMode == 0U ? F("WiFi точка доступа") : F("WiFi клиент (подключение к роутеру)"));
    delay(1000);
    #endif

    showWarning(CRGB::Red, 3000U, 500U);                    // мигание красным цветом 3 секунды - смена рабочего режима лампы, перезагрузка
    ESP.restart();
  }


  // кнопка только начала удерживаться
  //if (ONflag && touch.isHolded())
  if (touch.isHolded()) // пускай для выключенной лампы удержание кнопки включает белую лампу
  {
    brightDirection = !brightDirection;
    startButtonHolding = true;
  }


  // кнопка нажата и удерживается
//  if (ONflag && touch.isStep())
if (touch.isStep())
  if (ONflag && !Button_Holding)
  {

    int8_t but = touch.getHoldClicks();
        //Serial.println (but);

    switch (but )
    {
      case 0U:                                              // просто удержание (до удержания кнопки кликов не было) - изменение яркости
      {
        uint8_t delta = modes[currentMode].Brightness < 10U // определение шага изменения яркости: при яркости [1..10] шаг = 1, при [11..16] шаг = 3, при [17..255] шаг = 15
          ? 1U
          : 5U;
        modes[currentMode].Brightness =
          constrain(brightDirection
            ? modes[currentMode].Brightness + delta
            : modes[currentMode].Brightness - delta,
          1, 255);
		jsonWrite(configSetup, "br", modes[currentMode].Brightness);
        FastLED.setBrightness(modes[currentMode].Brightness);

        #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение яркости: %d\n"), modes[currentMode].Brightness);
        #endif
        #ifdef USE_MULTIPLE_LAMPS_CONTROL
        multiple_lamp_control ();
        #endif  //USE_MULTIPLE_LAMPS_CONTROL

        break;
      }

      case 1U:                                              // удержание после одного клика - изменение скорости
      {
        modes[currentMode].Speed = constrain(brightDirection ? modes[currentMode].Speed + 1 : modes[currentMode].Speed - 1, 1, 255);
		jsonWrite(configSetup, "sp", modes[currentMode].Speed);
        loadingFlag = true; // без перезапуска эффекта ничего и не увидишь

        #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение скорости: %d\n"), modes[currentMode].Speed);
        #endif
        #ifdef USE_MULTIPLE_LAMPS_CONTROL
        multiple_lamp_control ();
        #endif  //USE_MULTIPLE_LAMPS_CONTROL

        break;
      }

      case 2U:                                              // удержание после двух кликов - изменение масштаба
      {
        modes[currentMode].Scale = constrain(brightDirection ? modes[currentMode].Scale + 1 : modes[currentMode].Scale - 1, 1, 100);
		jsonWrite(configSetup, "sc", modes[currentMode].Scale);
        loadingFlag = true; // без перезапуска эффекта ничего и не увидишь

        #ifdef GENERAL_DEBUG
        LOG.printf_P(PSTR("Новое значение масштаба: %d\n"), modes[currentMode].Scale);
        #endif
        #ifdef USE_MULTIPLE_LAMPS_CONTROL
        multiple_lamp_control ();
        #endif  //USE_MULTIPLE_LAMPS_CONTROL

        break;
      }
	  
	    #ifdef BUTTON_CAN_SET_SLEEP_TIMER
	  case 3U:
	  {
		Button_Holding = true;
		// мигать об успехе операции лучше до вызова changePower(), иначе сперва мелькнут кадры текущего эффекта
		showWarning(CRGB::Blue, 1500U, 250U);                    // мигание синим цветом 1 секунду
		ONflag = true;
		changePower();
		jsonWrite(configSetup, "Power", ONflag);
		settChanged = true;
		eepromTimeout = millis();
		#ifdef USE_BLYNK
		updateRemoteBlynkParams();
		#endif
		TimerManager::TimeToFire = millis() + BUTTON_SET_SLEEP_TIMER2 * 60UL * 1000UL;
		TimerManager::TimerRunning = true;
		break;
	  }
		#endif //BUTTON_CAN_SET_SLEEP_TIMER

      default:
        break;
    }		

    settChanged = true;
    eepromTimeout = millis();
  }
  else
  {
  if (!Button_Holding ) {
    int8_t but = touch.getHoldClicks();
        //Serial.println (but);

    switch (but )
    {
      case 0U:                                              // просто удержание (до удержания кнопки кликов не было) - белый свет
	  {
		Button_Holding = true;
		currentMode = EFF_WHITE_COLOR;
		jsonWrite(configSetup, "eff_sel", currentMode);
		jsonWrite(configSetup, "br", modes[currentMode].Brightness);
		jsonWrite(configSetup, "sp", modes[currentMode].Speed);
		jsonWrite(configSetup, "sc", modes[currentMode].Scale);
		ONflag = true;
		jsonWrite(configSetup, "Power", ONflag);
		changePower();
		settChanged = true;
		eepromTimeout = millis();
		#ifdef USE_BLYNK
		updateRemoteBlynkParams();
		#endif
		break;
	  }
	    #ifdef BUTTON_CAN_SET_SLEEP_TIMER	  
	  case 3U:
	  {
		Button_Holding = true;
		// мигать об успехе операции лучше до вызова changePower(), иначе сперва мелькнут кадры текущего эффекта
		showWarning(CRGB::Blue, 1500U, 250U);                    // мигание синим цветом 1 секунду
		ONflag = true;
		changePower();
		jsonWrite(configSetup, "Power", ONflag);
		settChanged = true;
		eepromTimeout = millis();
		#ifdef USE_BLYNK
		updateRemoteBlynkParams();
		#endif
		TimerManager::TimeToFire = millis() + BUTTON_SET_SLEEP_TIMER2 * 60UL * 1000UL;
		TimerManager::TimerRunning = true;
		break;		
	  }
		#endif //BUTTON_CAN_SET_SLEEP_TIMER	  
	}
   }
  }

  // кнопка отпущена после удерживания
  if (ONflag && !touch.isHold() && startButtonHolding)      // кнопка отпущена после удерживания, нужно отправить MQTT сообщение об изменении яркости лампы
  {
    startButtonHolding = false;
    Button_Holding = false;
    loadingFlag = true;

    #if (USE_MQTT)
    if (espMode == 1U)
    {
      MqttManager::needToPublish = true;
    }
    #endif
    
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    
  }
}
#endif
