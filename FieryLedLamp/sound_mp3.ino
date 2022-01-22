#ifdef MP3_TX_PIN
// Воиспроиведение времени используем метод "ADVERT" или объявление

uint32_t mp3_timer = 0;
bool dawnFlagEnd=false;  //окончание рассвета
// задержки в произнощении часов.
//uint16_t clock_delay[25]={0,1200,1176,1080,1320,1152,1296,1200,1248,1368,1488,1488,1632,1560,1584,1440,1560,1584,1656,1680,1416,1752,1656,1656,1056};

/*
// При наступлении ночи NIGHT_HOURS_START MP3 отключается
// При наступлении время будильника - подключаются (включен или нет, не важно)

// Переменные, которые были использованиы в модуле для анализа
// dawnFlag - Идет рассвет
// dawnPosition - Яркость рассвета
// ONflag - включена/выключена лампа
// currentMode - текущий эффект
*/

void mp3_setup()   {
  mp3.begin(9600);
  if (myDFPlayer.begin(mp3)) {                                              // Проверяем, есть ли связь с плеером и, если нет, то
    myDFPlayer.setTimeOut(500);                                             // Указываем время отклика плеера на команды в 500мс  
    myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);                                      // Устанавливаем эквалайзер в положение NORMAL
    myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);                            // Устанавливаем источником SD-карту
    mp3_folder_last=mp3_folder;
    mp3_timer = millis();
    delay(1000);
    myDFPlayer.volume(eff_volume);                                             // Устанавливаем громкость равной 10 (от 0 до 30)
    //eff_volume_tmp = eff_volume;
    mp3_player_connect = true;
    LOG.println (F("mp3 player подключен"));
  }
  else LOG.println (F("mp3 player не подключен"));
}

void play_time_ADVERT()   {
    if (first_entry && advert_hour) {
        advert_flag = true;
        first_entry = false;
        myDFPlayer.volume(0);
        delay(10);
        if (!mp3_play_now) {
           tmp_fold = mp3_folder;
           myDFPlayer.playFolder(99, 1);
           delay(10);
        }
        if (pause_on) myDFPlayer.start();
        delay(10);
        if (day_night) myDFPlayer.volume(day_advert_volume);
        else myDFPlayer.volume(night_advert_volume);
        int pt_h=(uint8_t)((thisTime - thisTime % 60U) / 60U);
        if (pt_h==0) pt_h=24;
        mp3_timer = millis();
        myDFPlayer.advertise(pt_h);
    }
    if (advert_hour && (millis() - mp3_timer > 1700UL)) {
       advert_hour = false;
       int pt_m=(uint8_t)(thisTime % 60U);
       mp3_timer = millis();
       myDFPlayer.advertise(pt_m+100);
    }
    if (millis() - mp3_timer > 1800UL) {
    advert_flag = false;
    myDFPlayer.stopAdvertise();
    if (!mp3_play_now) {
        myDFPlayer.stop (); 
        delay(10);
    }
    if (pause_on) myDFPlayer.pause();
    delay(10);
    myDFPlayer.volume(eff_volume);
    }
}

void play_sound(uint8_t value)   {
    if (!mp3_folder) {
        myDFPlayer.stop ();
        mp3_play_now =false;
    }
    else {
        myDFPlayer.loopFolder(value); // Включить непрерывное воспроизведение указанной папки
        mp3_play_now = true;      // Указывает, играет ли сейчас мелодия
    }
}

void mp3_loop()   {
  if (dawnFlag) {                          // если наступает рассвет
      if (dawnflag_sound ) return;
      myDFPlayer.stop();
      dawnflag_sound = 1;
     if (alarm_sound_on) {
        mp3_folder = 11;
        myDFPlayer.volume(alarm_volume);
        play_sound(mp3_folder);
        mp3_folder_last = mp3_folder;
        alarm_sound_flag = true;
     }
    return;
  }
  else {
      if (dawnflag_sound) {
        myDFPlayer.volume(eff_volume);
        dawnflag_sound = 0;
      }
  }
  if ((ONflag) && (eff_sound_on)) {
    set_mp3_play_now=true;  // Указывает, что надо играть сейчас мелодии  
    }
  else
    {
    set_mp3_play_now=false;  // Указывает, что не надо играть сейчас мелодии      
    }
  
  if ((!set_mp3_play_now)) { //if ((mp3_play_now) && (!set_mp3_play_now)) {
    myDFPlayer.pause(); // Поставить воспроизведение на паузу
    pause_on = true;
    mp3_play_now = false;  
  }   
/*
  if ((!mp3_play_now) && (set_mp3_play_now) && (!pause_on)) {
    play_sound(mp3_folder);
    pause_on = false;
    mp3_folder_last = mp3_folder;
  }
*/  
  if ((set_mp3_play_now) && (pause_on)) { //if ((!mp3_play_now) && (set_mp3_play_now) && (pause_on)) {
    myDFPlayer.start();
    pause_on = false;
    mp3_play_now = true;
  }
  
  
  if ((set_mp3_play_now) && (mp3_folder_last != mp3_folder)) { //if ((mp3_play_now) && (set_mp3_play_now) && (mp3_folder_last != mp3_folder)) {
    if (mp3_play_now || mp3_folder) {
    play_sound(mp3_folder);
    mp3_folder_last = mp3_folder;
   }
  }
  
}

#endif
