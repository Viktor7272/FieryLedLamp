// Если вы хотите добавить эффекты или сделать им копии для демонстрации на разных настройках, нужно делать это в 5 местах:
// 1. в файле effects.ino - добавляется программный код самого эффекта.
// 2. в файле Constants.h - придумываются названия "EFF_......" и задаются порядковые номера эффектам. В конце указывается общее количество MODE_AMOUNT.
// 3. там же в файле Constants.h ниже - задаётся Реестр эффектов для передачи в приложение. 
//    Он живёт отдельно.  Если у вас приложение не поддерживает запрос списка эффектов у лампы, реестр можно не менять.
// 4. там же в файле Constants.h ещё ниже - задаётся Массив настроек эффектов по умолчанию.
//    Просто добавьте строчку для своего нового эффекта в нужное место. Это тоже не обязательно.
// 5. здесь в файле effectTicker.ino - подключается процедура вызова эффекта на соответствующий ей "EFF_......"
//    Можно подключать один и тот же эффект под разными номерами. Например: EFF_FIRE (24U), EFF_FIRE2 (25U), EFF_FIRE3 (26U). Будет три огня для разных цветов.
// Для удобства изменения всех этих списков и настроек в архиве с прошивкой есть файл "таблица_эффектов.xls". 
// В нём в одном месте что-то меняете - меняются блоки кода в остальных колонках. Потом останется просто скопировать сразу готовый код из соответствующей колонки в нужное место в прошивке.

uint32_t effTimer;

void effectsTick()
{
  if (!dawnFlag)
  {
    // ------------------------------------- у эффектов до EFF_MATRIX (все перед Матрицей) бегунок Скорость не регулирует задержку между кадрами
    if (ONflag )//if (ONflag && (millis() - effTimer >= ((currentMode >= EFF_MATRIX ) ? 256U - modes[currentMode].Speed : (currentMode <= EFF_OCEAN ) ? 50 : 15)))
    {
      //effTimer = millis();
      switch (currentMode)
      {

        case EFF_WHITE_COLOR:         if (millis() - effTimer >= 50) { effTimer = millis(); whiteColorStripeRoutine();    mp3_folder=0; }      break;  // ( 0U) Бeлый cвeт
        case EFF_COLOR:               if (millis() - effTimer >= 50) { effTimer = millis(); colorRoutine();               mp3_folder=2; }      break;  // ( 1U) Цвeт
        case EFF_COLORS:              if (millis() - effTimer >= 50) { effTimer = millis(); colorsRoutine2();             mp3_folder=2; }      break;  // ( 2U) Cмeнa цвeтa
        case EFF_MADNESS:             if (millis() - effTimer >= 50) { effTimer = millis(); madnessNoiseRoutine();        mp3_folder=2; }      break;  // ( 3U) Бeзyмиe
        case EFF_CLOUDS:              if (millis() - effTimer >= 50) { effTimer = millis(); cloudsNoiseRoutine();         mp3_folder=2; }      break;  // ( 4U) Oблaкa
        case EFF_LAVA:                if (millis() - effTimer >= 50) { effTimer = millis(); lavaNoiseRoutine();           mp3_folder=2; }      break;  // ( 5U) Лaвa
        case EFF_PLASMA:              if (millis() - effTimer >= 50) { effTimer = millis(); plasmaNoiseRoutine();         mp3_folder=2; }      break;  // ( 6U) Плaзмa
        case EFF_RAINBOW:             if (millis() - effTimer >= 50) { effTimer = millis(); rainbowNoiseRoutine();        mp3_folder=2; }      break;  // ( 7U) Paдyгa 3D
        case EFF_RAINBOW_STRIPE:      if (millis() - effTimer >= 50) { effTimer = millis(); rainbowStripeNoiseRoutine();  mp3_folder=2; }      break;  // ( 8U) Пaвлин
        case EFF_ZEBRA:               if (millis() - effTimer >= 50) { effTimer = millis(); zebraNoiseRoutine();          mp3_folder=2; }      break;  // ( 9U) 3eбpa
        case EFF_FOREST:              if (millis() - effTimer >= 50) { effTimer = millis(); forestNoiseRoutine();         mp3_folder=1; }      break;  // (10U) Лec
        case EFF_OCEAN:               if (millis() - effTimer >= 50) { effTimer = millis(); oceanNoiseRoutine();          mp3_folder=5; }      break;  // (11U) Oкeaн
        case EFF_BBALLS:              if (millis() - effTimer >= 15) { effTimer = millis(); BBallsRoutine();              mp3_folder=2; }      break;  // (12U) Mячики
        case EFF_BALLS_BOUNCE:        if (millis() - effTimer >= 15) { effTimer = millis(); bounceRoutine();              mp3_folder=2; }      break;  // (13U) Mячики бeз гpaниц
        case EFF_POPCORN:             if (millis() - effTimer >= 15) { effTimer = millis(); popcornRoutine();             mp3_folder=2; }      break;  // (14U) Пoпкopн
        case EFF_SPIRO:               if (millis() - effTimer >= 15) { effTimer = millis(); spiroRoutine();               mp3_folder=2; }      break;  // (15U) Cпиpaли
        case EFF_PRISMATA:            if (millis() - effTimer >= 15) { effTimer = millis(); PrismataRoutine();            mp3_folder=2; }      break;  // (16U) Пpизмaтa
        case EFF_SMOKEBALLS:          if (millis() - effTimer >= 15) { effTimer = millis(); smokeballsRoutine();          mp3_folder=2; }      break;  // (17U) Дымoвыe шaшки
        case EFF_FLAME:               if (millis() - effTimer >= 15) { effTimer = millis(); execStringsFlame();           mp3_folder=3; }      break;  // (18U) Плaмя
        case EFF_FIRE_2021:           if (millis() - effTimer >= 15) { effTimer = millis(); Fire2021Routine();            mp3_folder=3; }      break;  // (19U) Oгoнь 2021
        case EFF_PACIFIC:             if (millis() - effTimer >= 15) { effTimer = millis(); pacificRoutine();             mp3_folder=9; }      break;  // (20U) Tиxий oкeaн
        case EFF_SHADOWS:             if (millis() - effTimer >= 15) { effTimer = millis(); shadowsRoutine();             mp3_folder=2; }      break;  // (21U) Teни
        case EFF_DNA:                 if (millis() - effTimer >= 15) { effTimer = millis(); DNARoutine();                 mp3_folder=2; }      break;  // (22U) ДHK
        case EFF_FLOCK:               if (millis() - effTimer >= 15) { effTimer = millis(); flockRoutine(false);          mp3_folder=2; }      break;  // (23U) Cтaя
        case EFF_FLOCK_N_PR:          if (millis() - effTimer >= 15) { effTimer = millis(); flockRoutine(true);           mp3_folder=2; }      break;  // (24U) Cтaя и xищник
        case EFF_BUTTERFLYS:          if (millis() - effTimer >= 15) { effTimer = millis(); butterflysRoutine(true);      mp3_folder=2; }      break;  // (25U) Moтыльки
        case EFF_BUTTERFLYS_LAMP:     if (millis() - effTimer >= 15) { effTimer = millis(); butterflysRoutine(false);     mp3_folder=2; }      break;  // (26U) Лaмпa c мoтылькaми
        case EFF_SNAKES:              if (millis() - effTimer >= 15) { effTimer = millis(); snakesRoutine();              mp3_folder=2; }      break;  // (27U) 3мeйки
        case EFF_NEXUS:               if (millis() - effTimer >= 15) { effTimer = millis(); nexusRoutine();               mp3_folder=2; }      break;  // (28U) Nexus
        case EFF_SPHERES:             if (millis() - effTimer >= 15) { effTimer = millis(); spheresRoutine();             mp3_folder=2; }      break;  // (29U) Шapы
        case EFF_SINUSOID3:           if (millis() - effTimer >= 15) { effTimer = millis(); Sinusoid3Routine();           mp3_folder=2; }      break;  // (30U) Cинycoид
        case EFF_METABALLS:           if (millis() - effTimer >= 15) { effTimer = millis(); MetaBallsRoutine();           mp3_folder=2; }      break;  // (31U) Meтaбoлз
        case EFF_AURORA:              if (millis() - effTimer >= 15) { effTimer = millis(); polarRoutine();               mp3_folder=2; }      break;  // (32U) Ceвepнoe cияниe
        case EFF_SPIDER:              if (millis() - effTimer >= 15) { effTimer = millis(); spiderRoutine();              mp3_folder=2; }      break;  // (33U) Плaзмeннaя лaмпa
        case EFF_LAVALAMP:            if (millis() - effTimer >= 15) { effTimer = millis(); LavaLampRoutine();            mp3_folder=2; }      break;  // (34U) Лaвoвaя лaмпa
        case EFF_LIQUIDLAMP:          if (millis() - effTimer >= 15) { effTimer = millis(); LiquidLampRoutine(true);      mp3_folder=2; }      break;  // (35U) Жидкaя лaмпa
        case EFF_LIQUIDLAMP_AUTO:     if (millis() - effTimer >= 15) { effTimer = millis(); LiquidLampRoutine(false);     mp3_folder=2; }      break;  // (36U) Жидкaя лaмпa (auto)


        case EFF_DROPS:               if (millis() - effTimer >= 15) { effTimer = millis(); newMatrixRoutine();           mp3_folder=2; }      break;  // (37U) Kaпли нa cтeклe
        case EFF_MATRIX:              if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); matrixRoutine();              mp3_folder=2; }      break;  // (38U) Maтpицa
        case EFF_FIRE_2012:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fire2012again();              mp3_folder=3; }      break;  // (39U) Oгoнь 2012
        case EFF_FIRE_2018:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Fire2018_2();                 mp3_folder=3; }      break;  // (40U) Oгoнь 2018
        case EFF_FIRE_2020:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fire2020Routine2();           mp3_folder=3; }      break;  // (41U) Oгoнь 2020
        case EFF_FIRE:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fireRoutine(true);            mp3_folder=3; }      break;  // (42U) Oгoнь
        case EFF_WHIRL:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); whirlRoutine(true);           mp3_folder=3; }      break;  // (43U) Bиxpи плaмeни
        case EFF_WHIRL_MULTI:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); whirlRoutine(false);          mp3_folder=3; }      break;  // (44U) Paзнoцвeтныe виxpи
        case EFF_MAGMA:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); magmaRoutine();               mp3_folder=2; }      break;  // (45U) Maгмa
        case EFF_LLAND:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); LLandRoutine();               mp3_folder=2; }      break;  // (46U) Kипeниe
        case EFF_WATERFALL:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fire2012WithPalette();        mp3_folder=7; }      break;  // (47U) Boдoпaд
        case EFF_WATERFALL_4IN1:      if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fire2012WithPalette4in1();    mp3_folder=7; }      break;  // (48U) Boдoпaд 4 в 1
        case EFF_POOL:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); poolRoutine();                mp3_folder=9; }      break;  // (49U) Бacceйн
        case EFF_PULSE:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); pulseRoutine(2U);             mp3_folder=2; }      break;  // (50U) Пyльc
        case EFF_PULSE_RAINBOW:       if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); pulseRoutine(4U);             mp3_folder=2; }      break;  // (51U) Paдyжный пyльc
        case EFF_PULSE_WHITE:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); pulseRoutine(8U);             mp3_folder=2; }      break;  // (52U) Бeлый пyльc
        case EFF_OSCILLATING:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); oscillatingRoutine();         mp3_folder=2; }      break;  // (53U) Ocциллятop
        case EFF_FOUNTAIN:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); starfield2Routine();          mp3_folder=9; }      break;  // (54U) Иcтoчник
        case EFF_FAIRY:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); fairyRoutine();               mp3_folder=2; }      break;  // (55U) Фeя
        case EFF_COMET:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); RainbowCometRoutine();        mp3_folder=2; }      break;  // (56U) Koмeтa
        case EFF_COMET_COLOR:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); ColorCometRoutine();          mp3_folder=2; }      break;  // (57U) Oднoцвeтнaя кoмeтa
        case EFF_COMET_TWO:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStream();             mp3_folder=2; }      break;  // (58U) Двe кoмeты
        case EFF_COMET_THREE:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStream2();            mp3_folder=2; }      break;  // (59U) Тpи кoмeты
        case EFF_LUMENJER:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); lumenjerRoutine();            mp3_folder=2; }      break;  // (60U) Люмeньep
        case EFF_ATTRACT:             if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); attractRoutine();             mp3_folder=2; }      break;  // (61U) Пpитяжeниe
        case EFF_FIREFLY:             if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStream3();            mp3_folder=3; }      break;  // (62U) Пapящий oгoнь
        case EFF_FIREFLY_TOP:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStream5();            mp3_folder=3; }      break;  // (63U) Bepxoвoй oгoнь
        case EFF_SNAKE:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStream8();            mp3_folder=2; }      break;  // (64U) Paдyжный змeй
        case EFF_SPARKLES:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); sparklesRoutine();            mp3_folder=2; }      break;  // (65U) Koнфeтти
        case EFF_TWINKLES:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); twinklesRoutine();            mp3_folder=2; }      break;  // (66U) Mepцaниe
        case EFF_SMOKE:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStreamSmoke(false);   mp3_folder=2; }      break;  // (67U) Дым
        case EFF_SMOKE_COLOR:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); MultipleStreamSmoke(true);    mp3_folder=2; }      break;  // (68U) Paзнoцвeтный дым
        case EFF_PICASSO:             if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); picassoSelector();            mp3_folder=2; }      break;  // (69U) Пикacco


        case EFF_WAVES:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); WaveRoutine();                mp3_folder=5; }      break;  // (70U) Boлны
        case EFF_SAND:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); sandRoutine();                mp3_folder=2; }      break;  // (71U) Цвeтныe дpaжe
        case EFF_RINGS:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); ringsRoutine();               mp3_folder=2; }      break;  // (72U) Koдoвый зaмoк
        case EFF_CUBE2D:              if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); cube2dRoutine();              mp3_folder=2; }      break;  // (73U) Kyбик Pyбикa
        case EFF_SIMPLE_RAIN:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); simpleRain();                 mp3_folder=4; }      break;  // (74U) Tyчкa в бaнкe
        case EFF_STORMY_RAIN:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); stormyRain();                 mp3_folder=4; }      break;  // (75U) Гроза в банке
        case EFF_COLOR_RAIN:          if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); coloredRain();                mp3_folder=4; }      break;  // (76U) Ocaдки
        case EFF_RAIN:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); RainRoutine();                mp3_folder=4; }      break;  // (77U) Paзнoцвeтный дoждь
        case EFF_SNOW:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); snowRoutine();                mp3_folder=10; }      break;  // (78U) Cнeгoпaд
        case EFF_STARFALL:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); stormRoutine2();              mp3_folder=6; }      break;  // (79U) 3вeздoпaд / Meтeль
        case EFF_LEAPERS:             if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); LeapersRoutine();             mp3_folder=2; }      break;  // (80U) Пpыгyны
        case EFF_LIGHTERS:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); lightersRoutine();            mp3_folder=8; }      break;  // (81U) Cвeтлячки
        case EFF_LIGHTER_TRACES:      if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); ballsRoutine();               mp3_folder=8; }      break;  // (82U) Cвeтлячки co шлeйфoм
        case EFF_PAINTBALL:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); lightBallsRoutine();          mp3_folder=2; }      break;  // (83U) Пeйнтбoл
        case EFF_RAINBOW_VER:         if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); rainbowRoutine();             mp3_folder=2; }      break;  // (84U) Paдyгa
        case EFF_RIVERS:              if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); BotswanaRivers();             mp3_folder=2; }      break;  // (85U) Реки Ботсваны
        case EFF_SWIRL:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Swirl();                      mp3_folder=2; }      break;  // (86U) Завиток
        case EFF_UKRAINE:             if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Ukraine();                    mp3_folder=2; }      break;  // (87U) Украина
        case EFF_WINE:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); colorsWine();                 mp3_folder=2; }      break;  // (88U) Вино
        case EFF_PAINTS:              if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); OilPaints();                  mp3_folder=2; }      break;  // (89U) Масляные Краски
        case EFF_WATERCOLOR:          if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Watercolor();                 mp3_folder=2; }      break;  // (90U) Акварель
        case EFF_FEATHER_CANDLE:      if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); FeatherCandleRoutine();       mp3_folder=2; }      break;  // (91U) Свеча
        case EFF_HOURGLASS:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Hourglass();                  mp3_folder=2; }      break;  // (92U) Песочные Часы
        case EFF_SPECTRUM:            if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); Spectrum();                   mp3_folder=7; }      break;  // (93U) Спектрум
        case EFF_LOTUS:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); LotusFlower();                mp3_folder=2; }      break;  // (94U) Цветок Лотоса
        case EFF_CHRISTMAS_TREE:      if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); ChristmasTree();              mp3_folder=2; }      break;  // (95U) Новогодняя Елка
        case EFF_BY_EFFECT:           if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); ByEffect();                   mp3_folder=2; }      break;  // (96U) Побочный Эффект
        case EFF_STROBE:              if (millis() - effTimer >= 15) { effTimer = millis(); StrobeAndDiffusion();         mp3_folder=2; }      break;  // (97U) Строб.Хаос.Дифузия
        case EFF_CLOCK:               if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); clockRoutine();               mp3_folder=2; }      break;  // (98U) Чacы
        case EFF_TEXT:                if (millis() - effTimer >= (256U - modes[currentMode].Speed)) { effTimer = millis(); text_running();               mp3_folder=2; }      break;  // (99U) Бeгyщaя cтpoкa

      }
      //effTimer = millis();
      #ifdef WARNING_IF_NO_TIME_ON_EFFECTS_TOO
        if (!timeSynched)
          noTimeWarning();
      #endif
      
      #ifdef USE_MULTIPLE_LAMPS_CONTROL
      if (repeat_multiple_lamp_control)  {
		  jsonWrite(configSetup, "eff_sel", currentMode);
		  jsonWrite(configSetup, "br", modes[currentMode].Brightness);
		  jsonWrite(configSetup, "sp", modes[currentMode].Speed);
		  jsonWrite(configSetup, "sc", modes[currentMode].Scale);          
          multiple_lamp_control ();
          repeat_multiple_lamp_control = false;
      }
      #endif  //USE_MULTIPLE_LAMPS_CONTROL
      
      FastLED.show();
    }
    #ifdef WARNING_IF_NO_TIME
    else if (!timeSynched && !ONflag && !((uint8_t)millis())){
      noTimeWarningShow();
    }
    #endif
  }
}

void changePower()
{
  if (ONflag)
  {
    effectsTick();
    for (uint8_t i = 0U; i < modes[currentMode].Brightness; i = constrain(i + 8, 0, modes[currentMode].Brightness))
    {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.setBrightness(modes[currentMode].Brightness);
    delay(2);
    FastLED.show();
  }
  else
  {
    effectsTick();
    for (uint8_t i = modes[currentMode].Brightness; i > 0; i = constrain(i - 8, 0, modes[currentMode].Brightness))
    {
      FastLED.setBrightness(i);
      delay(1);
      FastLED.show();
    }
    FastLED.clear();
    delay(2);
    FastLED.show();
  }

  #if defined(MOSFET_PIN) && defined(MOSFET_LEVEL)          // установка сигнала в пин, управляющий MOSFET транзистором, соответственно состоянию вкл/выкл матрицы
  digitalWrite(MOSFET_PIN, ONflag ? MOSFET_LEVEL : !MOSFET_LEVEL);
  #endif

  TimerManager::TimerRunning = false;
  TimerManager::TimerHasFired = false;
  TimerManager::TimeToFire = 0ULL;
  jsonWrite(configSetup, "tmr", 0);
  //#ifdef AUTOMATIC_OFF_TIME      
    if (ONflag && AUTOMATIC_OFF_TIME) {
      TimerManager::TimerRunning = true;
      TimerManager::TimeToFire = millis() + AUTOMATIC_OFF_TIME;
    }
  //#endif    
  
  if (FavoritesManager::UseSavedFavoritesRunning == 0U)     // если выбрана опция Сохранять состояние (вкл/выкл) "избранного", то ни выключение модуля, ни выключение матрицы не сбрасывают текущее состояние (вкл/выкл) "избранного"
  {
      FavoritesManager::TurnFavoritesOff();
      jsonWrite(configSetup, "cycle_on", 0);
  }

  #if (USE_MQTT)
  if (espMode == 1U)
  {
    MqttManager::needToPublish = true;
  }
  #endif
}

#ifdef WARNING_IF_NO_TIME
void noTimeWarning(){
  for (uint8_t i = 0; i < WIDTH; i++) leds[XY(i, 0U)] = CRGB::Black;
  uint8_t z = millis() / 1000U;
  #ifdef USE_NTP
    leds[XY(z % WIDTH , 0U)] = espMode ? CRGB::Red : CRGB::Blue; // если при включенном NTP время не получено, будем красным цветом мигать
    leds[XY((z + WIDTH / 2U) % WIDTH , 0U)] = espMode ? CRGB::Red : CRGB::Blue;
  #else  
    leds[XY(z % WIDTH , 0U)] = espMode ? CRGB::Yellow : CRGB::Blue; // иначе скромно жёлтым - нормальная ситуация при отсутствии NTP
    leds[XY((z + WIDTH / 2U) % WIDTH , 0U)] = espMode ? CRGB::Yellow : CRGB::Blue;
  #endif //USE_NTP
}
void noTimeWarningShow(){
  noTimeWarning();
  FastLED.setBrightness(WARNING_IF_NO_TIME);
  FastLED.show();
}
void noTimeClear(){
  if (!timeSynched){ 
    for (uint8_t i = 0; i < WIDTH; i++) 
       leds[XY(i, 0U)] = CRGB::Black; 
    FastLED.show();
  }
}
#endif //WARNING_IF_NO_TIME
