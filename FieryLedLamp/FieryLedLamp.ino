//
// ======================= ВНИМАНИЕ !!! =============================
//  Все настройки делаются на вкладке Constants.h
//  Почитайте там то, что на русском языке написано.
//  Либо ничего не трогайте, если собирали, как в оригинальном видео.
//  В любом случае ВНИМАТЕЛЬНО прочитайте файл ПРОЧТИ МЕНЯ!!!.txt 
//
//  решение проблем можно поискать тут под спойлерами:
//  https://community.alexgyver.ru/goto/post?id=33652
// ==================================================================

// Ссылка для менеджера плат:
// https://arduino.esp8266.com/stable/package_esp8266com_index.json

/*
  Скетч к проекту "Многофункциональный RGB светильник"
  Страница проекта (схемы, описания): https://alexgyver.ru/GyverLamp/
  Исходники авторской (старой) прошивки на GitHub: https://github.com/AlexGyver/GyverLamp/
  исходники новой версии: https://community.alexgyver.ru/threads/wifi-lampa-budilnik-obsuzhdenie-proshivki-ot-gunner47.2418/post-73929
  Нравится лампа? Поддержи автора! https://alexgyver.ru/support_alex/
  Автор идеи и первой реализации: AlexGyver, AlexGyver Technologies, 2019
  https://AlexGyver.ru/
*/

/*
  Версия 2.1 beta 86² эффектов в 1
  - Добавлен web updater. Теперь можно загружать прошивку по ОТА через любой браузер из bin файла. Нет необходимости устанавливать Arduino IDE. Удобно для поддержки конечных польэователей.
  - Добавлен web интерфейс для настройки  лампы. Можно менять имя лампы, имя и пароль точки доступа, имя и пароль WiFi сети, часовой пояс и переход на летнее время, а так же управлять режимами Random, переход Кнопкой-только по выбранным эффектам или по всем, Вкл/Выкл кнопки, управление выводом времени бегущей строкой.
  - Теперь лампу можно включить примерно через секунду после подачи питания не дожидаясь подключения к WIFi сети.
  - Исправлены мелкие ошибки.

  Версия 2.86² эффектов в 1
  - Если удерживать кнопку на выключенной лампе, включится сразу режим "Белый свет".
  - Если включился режим "Белый свет" (не важно, каким способом) и при этом данный режим не добавлен в список для автоматического переключения эффектов, тогда он сам не переключится.
  - Можно сделать, чтобы кнопкой переключались только те режимы, которые добавлены в избранное для режима Цикл. Настройка #define BUTTON_CHANGE_FAVORITES_MODES_ONLY
  - Лампа будет пытаться соединиться с роутером целых 60 секунд, а не 7, как раньше было. Это чтобы лампа могла дождаться загрузки роутера, если электричество в доме отключалось. Настройка #define ESP_CONN_TIMEOUT (60U)
  - Лампа будет проверять появление на роутере интернета через каждые 15 секунд, а не раз в 5 минут, как раньше было. Это чтобы время в лампе поскорее синхронизировалось с NTP-сервером. Настройка #define RESOLVE_INTERVAL (15UL * 1000UL)
  - Лампа будет забывать пароль к роутеру, если её переключили в режим работы "без роутера" кнопкой или по истечении 60 секунд ожидания. Это чтобы приложение не теряло связь с лампой в режиме "без роутера". Настройка #define RESET_WIFI_ON_ESP_MODE_CHANGE
  - Прошивку не удастся загрузить, если актуальные библиотеки из архива с прошивкой не положены в папку с библиотеками.
  - Лампа не будет реагировать на "фантомные нажатия" сенсорной кнопки, если вы забыли её подключить перед включением лампы в розетку. Настройка #define BUTTON_LOCK_ON_START
  - Убран в отдельную настройку сигнал лампы "про проблему со временем" во время работы эффектов. По умолчанию мигать двумя светодиодами во время работы эффектов лампа не будет.  
  - В режиме Цикл эффекты теперь запускаются на случайных, но удачных настройках. Можно это отключить, если не требуется.
  - Добавлены эффекты Цветные драже, Плазменная лампа, Северное сияние, Шары, Магма.
  - Удалён эффект Блуждающий кубик (версию прошивки повышаем, теперь больше нет оправданий, что этот эффект должен быть вместе со всеми 26ю изначальными).
  - Собраны воедино надоевшие эффекты Радуга вертикальная+горизонтальная+диагональная, Звездопад+Метель.
  - Убран запрет на установку времени ожидания подключения к роутеру более 7 секунл (для этого нужно брать библиотеки из архива с прошивкой).
  - В эффекте Белый свет добавлен вертикальный вариант ("направленный свет") для бегунка Масштаб от 50 и выше.
  - Исправлен режим Часы для узких матриц от 11 до 14 пикселей в высоту (не работал).
  - Появилась поддержка команд "RND_" от приложения для управления режимом случайных настроек и возврату к настройкам по умолчанию (а приложение такое пока ещё не появилось).
  
  Версия 1.5.85 эффектов в 1
  - Добавлены эффекты Фея, Источник.
  - Удалён эффект Мячики со шлейфом (это была просто копия Мячиков для демонстрации на других настройках бегунка Скорость).
  - Добавлена возможность автоматической синхронизации времени лампы со смартфоном. Приложение должно поддерживать данную функцию.
  - Добавлена индикация о том, что лампа не знает время (если по низу лампы по кругу бегут 2 цветные точки, значит, не знает).
  - Исправлен баг в библиотеке FastLed в реализации функции blur2d. Рекомендуется положить библиотеки из архива с прошивкой в папку библиотек программы Arduino IDE.
  - Убран запрет поиска ip-адреса лампы, когда лампа работает в виде точки доступа без роутера (в режиме ESP_MODE = 0).
  - Добавлена возможность передать приложению имя лампы (на случай, когда у вас в домашней сети несколько ламп). Приложение должно поддерживать данную функцию.
  
  Версия 1.5.84 эффекта в 1
  - Добавлены эффекты Кипение, Притяжение, Капли на стекле, Дымовые шашки, Тихий океан, Nexus.
  - Убраны эффекты Белый огонь, Цветной огонь, Бeлый вoдoпaд, Быстрый пульс, Пульсирующая кoмeтa (копии и похожие эффекты уже не интересны даже в режиме Цикл, и так эффектов многовато).
  - Убран запрет обновления прошивки "по воздуху", когда лампа работает в виде точки доступа без роутера (в режиме ESP_MODE = 0).
  - Исправления в эффектах ДНК (добавлено управление бегунком Масштаб), Мячики без границ, Вихри, Разноцветные вихри, Стая, Стая и хищник (сглаживание).

  Версия 1.5.83 эффекта в 1
  - Добавлен эффект Огонь 2020.
  - Возвращён эффект Пульсирующая комета.
  - Устранены проблемы "хищник умер", "время бегущей строкой дёргается".
  - Убрано затухание лампы в момент смены эффектов. Убрана предварительная очистка изображения предыдущего эффекта, где было возможно.
  - Добавлены "секретные команды" для установки Будильника Рассвет и Таймера выключения из приложения Blynk (вдруг кому очень надо).

  Версия 1.5.81 эффект в 1
  - Удалён эффект Белая комета.
  - Временно удалён эффект Пульсирующая комета.
  - Временно? добавлен эффект Осциллятор.
  - Обновлена поддержка приложения Blynk для управления текстом бегущей строки и передачи "секретных команд".
  - Эффекты Дым лучше адаптированы для ламп с плохим рассеивателем.
  - Найдена и убрана причина того, что в режиме Цикл лампа полностью гасла между эффектами.
  
  Версия 1.5.82 эффекта в 1
  - Удалён эффект Салют.
  - Добавлены эффекты Жидкая лампа и эффект Попкорн.
  - Реализована возможность установки времени на лампе без подключения к интернету (через приложение для Андроид от @Koteyka - оно есть в архиве с прошивкой).
  - Добавлена поддержка секретных команд reset=wifi, reset=effects, esp_mode=.. (через приложение для Андроид от @Koteyka - оно есть в архиве с прошивкой).
  
  Версия 1.5.80 эффектов в 1
  - В эффекте Цвет добавлена возможность выбора насыщенности бегунком Скорость.
  - Добавлены эффекты Тени, Мотыльки, Лампа с мотыльками, ДНК, Змейки, Салют.
  - Добавлена поддержка приложения Blynk (для iOS и Android) для ламп, имеющих постоянный доступ в Интернет. Если включить, будет всё немного подтормаживать.
  
  Версия 1.5.74 эффекта в 1
  - Добавлен эффект Лавовая лампа.
  
  Версия 1.5.73 эффекта в 1
  - Добавлены эффекты Пикассо.
  - Добавлен эффект Прыгуны.
  
  Версия 1.5.69 эффектов в 1 proper
  - В эффекте Белый свет сделано более плавное изменение площади свечения бегунком Масштаб (может, и зря).
  - В эффекте Метаболз наконец-то исправлена проблема перезагрузки лампы при длительной работе.

  Версия 1.5.69 эффектов в 1
  - Добавлены эффекты Дым и Разноцветный дым.

  Версия 1.5.67 эффектов в 1
  - Добавлен отдельный режим Часы. Просто как обычный предпоследний эффект. "Скорость" регулирует местоположение цифр. Чем лучше рассеивание на лампе, тем бесполезнее этот режим.
    Минимальная необходимая для Часов высота матрицы 11 пикселей. И 7 пикселей по ширине должно быть видно на одной стороне лампы, иначе часть циферблата уползёт на бок.
  - Исправлены баги в эффектах Кометы, вызывающие перезагрузку лампы при отличающихся друг от друга высоте и ширине матрицы, и при матрице высотой менее 14 пикселей.

  Версия 1.5.66 эффектов в 1
  - Все сложные настройки в Constants.h убраны вниз, чтобы не отвлекали.
  - Добавлены эффекты Мячики без границ (Прыжки), Кодовый замок и Кубик Рубика. Скрыт эффект Белые мячики (можно выбрать белый цвет обычным).
  - Добавлена возможность установить автоматическое выключение лампы после нескольких часов непрерывной работы (на случай, если кто-то забыл её выключить). 
    В приложении время выключения будет отображаться неверно, пока не исправят в будущих версиях.

  Версия 1.5.64 эффекта в 1
  - Добавлен эффект Мерцание.
  - Эффект Смена цвета теперь работает медленнее. На масштабах >10 переключение цвета будет через выбранное количество секунд (1 секунда для Скорости = 255 / 2 секунды для Скорости = 254 и т.д.)
  - В эффекте Метаболз добавлена возможность выбора палитры бегунком Масштаб
  - Обновлены эффекты Метель и Звездопад на версию от @Palpalych.
  - Добавлена возможность включить "очередь показов" выбранных эффектов для режима Цикл (чтобы не было повторов слишком часто). Это нужно включать в Constants.h.
  - Добавлена возможность выключить функцию "продолжить демонстрацию последнего эффекта после обесточивания лампы". Это нужно делать в Constants.h.
  - Исправлена размерность переменной currentMode. Возможно, теперь максимальное количество эффектов может быть больше 127 штук. Но это не точно.
  
  Версия 1.5.63 эффекта в 1
  - Добавлены эффекты Тучка в банке, Гроза в банке, Осадки, Огонь 2012.
  - Добавлена регулировка оттенка у эффекта Огонь 2018.
  - В Constants.h добавлен параметр для поддержки более свежей версии приложения от @Koteyka.
  - Оптимизированы функции parsing.h
  - Исправлена функция XY(). Это был аналог getPixelNumber(), но почему-то криво написанный.

  Версия 1.5.60 эффектов в 1
  - Добавлен эффект Огонь 2018.
  - Добавлена регулировка Масштаба у эффектов 2 кометы, 3 кометы, Парящий огонь, Верховой огонь.
  - Возможно, исправлена совместимость прошивки с матрицами, где способ подключения светодиодов отличается от "змейки".

  Версия 1.5.59 эффектов в 1
  - Создан массив настроек всех эффектов по умолчанию. Настройки выбраны с небольшой яркостью для работы в режиме ночника (для себя делал). Можете поставить яркость побольше.
  - Добавлен сброс настроек всех эффектов на значения по умолчанию при поступлении запроса от приложения ("загрузить список эффектов из лампы"). Можно отключить это в Constants.h.
  - Добавлены эффекты Вихри пламени и Разноцветные вихри.
  - В эффекте Светлячки со шлейфом теперь можно выбрать им цвета бегунком Масштаб.

  Версия 1.5.57 эффектов в 1
  - Объединено использование многих переменных в разных эффектах для небольшой экономии памяти.
  - Эффект Цвет тоже вынесен наверх в эффекты с принудительной задержкой в 50 мс, чтобы не травмировать контроллер платы.
  - Добавлены эффекты Стая, Стая и хищник, Призмата, Волны.
  - Увеличен размер буфера для приёма настроек Избранного от приложения в лампу. Теперь максимальное количество эффектов где-то в районе 117.
    (но это уже предел для текущей реализации функций FavoritesManager.h. дальше придётся менять там типы переменных).
  
  Версия 1.5.53 эффекта в 1
  - Изменён способ отправки списка эффектов в лампу. Теперь он не ограничен размером буфера, а ограничен хз чем.
  - Список эффектов расширен до 53 штук.
  - Добавлены новые функции, поддерживаемые приложением от @Koteyka (рисование, бегущая строка).
  
  Версия 1.5: 
    этот же список с гиперссылками: https://community.alexgyver.ru/threads/wifi-lampa-budilnik-obsuzhdenie-proshivki-ot-gunner47.2418/post-30883
  - Исправлен баг в условии процедуры вызова эффектов (у двух эффектов регулятор скорость не работал)
  - Инвертирована регулировка Скорости у всех эффектов, где она работала задом наперёд
  - Из всех эффектов убраны обращения к их порядковым номерам. Теперь любой эффект можно устанавливать на любое место (кроме номеров с 7 по 15), а также делать копии эффектов
  - Переработано распределение флеш-памяти EepromManager.h Теперь можно добавлять новые эффекты и делать копии (копии - для демонстрации одного эффекта на разных настройках).
  - В библиотеке FastLED исправлены коэффициенты расчёта потребления тока
  - Эффект Огонь заменён на "Ламповый огонь", при максимальном Масштабе он же будет эффект Белый огонь
  - Эффект Белый огонь заменён на эффект Водопад, при максимальном Масштабе цвет воды будет белым
  - Внесены исправления эффектов Пейнтбол и Радуга диагональная от @Palpalych (выставляйте Пейнтболу Скорость побольше, чтобы выглядело хорошо)
  - К эффекту Цвет добавлен эффект Бассейн (при максимальной Скорости блики воды исчезают, работает эффект Цвет)
  - К эффекту Смена цвета добавлен эффект Пульс (при минимальном Масштабе будет работать эффект Смена цвета)
  - Внесены исправления эффектов Метель и Звездопад от @Rampart
  - У эффекта Матрица изменена цветовая палитра и алгоритм работы (Нестыдная Матрица)
  - Эффект Светлячки со шлейфом заменён на эффект Кометы (в коде оставлены старый эффект, а также дополнительный Кометы мини, но они не подключены)
  - С прошивкой в архиве поставляется 2 приложения. Стандартное может работать только с 26 эффектами. При увеличении количества эффектов будет работать только приложение от @Koteyka
  - В архив с прошивкой добавлен файл с инструкцией в формате книжки. Правда, там уже устарели все ссылки.
  - Добавлен обработчик команды "GBR" для изменения яркости всех эффектов сразу без сохранения в энергонезависимую память. Приложение должно поддерживать данную функцию.
  - Добавлен обработчик команды "LIST" для отправки в приложение количества и реестра установленных эффектов. Приложение должно поддерживать данную функцию.

  Версия 1.4:
  - Исправлен баг при смене режимов
  - Исправлены тормоза в режиме точки доступа
  --- 08.07.2019
  - Исправлены параметры и процесс подключения к WiFi сети (таймаут 7 секунд) и развёртываия WiFi точки доступа (параметры имени/пароля)
  - Добавлено "#define USE_NTP" - позволяет запретить обращаться в интернет
  - Добавлено "#define ESP_USE_BUTTON - позволяет собирать лампу без физической кнопки, иначе яркость эффектов самопроизвольно растёт до максимальной
  - Переработаны параметры IP адресов, STA_STATIC_IP теперь пустой по умолчанию - избавляет от путаницы с IP адресами из неправильных диапазонов
  - Добавлено "#define GENERAL_DEBUG" - выводит в Serial/Telnet некоторые отладочные сообщения
  - Добавлено "#define WIFIMAN_DEBUG (true)" - выводит в Serial/Telnet отладочные сообщения библиотеки WiFiManager
  - Добавлена таблица с тест кейсами
  - Форматирование кода, комментарии
  --- 11.07.2019
  - Исправлена ошибка невыключения матрицы после срабатывания будильника, если до будильника матрица была выключенной
  - Дополнена таблица с тест кейсами
  --- 14.07.2019
  - Исправлена ошибка выключения будильника, если перед его срабатыванием был активен эффект "матрица" (или другой эффект, где задействовано мало светодиодов)
  - Добавлено управление по воздуху:
  -- работает только в режиме WiFi клиента
  -- работает при подключенной кнопке (потому что режим прошивки активируется кнопкой)
  --- 16.07.2019
  - Исправлено регулярное подвисание матрицы на 1-2 секунды при отсутствии подключения к интернету (но при успешном подключении к WiFi)
  --- 28.07.2019
  - Доработано взаимодействие с android приложением (отправка состояния после каждой операции)
  --- 01.08.2019
  - Возврат к стандартной библиотеке GyverButton (изменениё из неё перенесено в button.ino
  - Добавлены 2 эффекта: Светлячки со шлейфом и Белый свет
  - При запросе обновления по воздуху (2 четверных касания к кнопке) лампа переключается в режим "Матрица" для визуального подтверждения готовности к прошивке
  - В android приложение добавлена функция сканирования сети и добавления ламп с помощью multicast пакетов, доработка прошивки под это
  --- 03.08.2019
  - Исправлены ошибки взаимодействия android приложения с лампой, в вывод команды CURR добавлено текущее время (или millis(), если время не синхронизировано)
  --- 10.08.2019
  - Добавлена точная настройка яркости, скорости и масштаба эффектов
  - Добавлено взаимодействие с android приложением по управлению будильниками
  --- 14.08.2019
  - Добавлена функция таймера отключения
  --- 26.08.2019
  - Добавлен режим автоматического переключения избранных эффектов
  - Реорганизован код, исправлены ошибки
  --- 28.08.2019
  - Добавлен вызов режима обновления модуля esp из android приложения
  --- 30.08.2019
  - Эффект "Светлячки со шлейфами" переименован в "Угасающие пиксели"
  - Добавлены 5 новых эффекта: "Радуга диагональная", "Метель", "Звездопад", "Светлячки со шлейфами" (новый) и "Блуждающий кубик"
  - Исправлены ошибки
  --- 04.09.2019
  - Большая часть определений (констант) перенесена в файл Constants.h
  - Большая оптимизация использования памяти
  - Исправлена ошибка невключения эффекта "Белый свет" приложением и кнопкой
  - Исправлена ошибка неправильного выбора интервала в режиме Избранное в android приложении
  --- 16.09.2019
  - Добавлено сохранение состояния (вкл/выкл) лампы в EEPROM память
  - Добавлен новый эффект белого света (с горизонтальной полосой)
  - Реорганизован код, исправлены ошибки
  --- 20.09.2019
  - Добавлена возможность сохранять состояние (вкл/выкл) режима "Избранное"; не сбрасывается выключением матрицы, не сбрасывается перезапуском модуля esp
  - Убрана очистка параметров WiFi при старте с зажатой кнопкой; регулируется директивой ESP_RESET_ON_START, которая определена как false по умолчанию
  --- 24.09.2019
  - Добавлены изменения из прошивка от Alex Gyver v1.5: бегущая строка с IP адресом лампы по пятикратному клику на кнопку
  --- 29.09.2019
  - Добавлена опция вывода отладочных сообщений по пртоколу telnet вместо serial для удалённой отладки
  - Исправлена ошибка регулировки яркости кнопкой
  --- 05.10.2019
  - Добавлено управление по протоколу MQTT
  - Исправлена ошибка выключения будильника кнопкой
  - Добавлена задержка в 1 секунду сразу после старта, в течение которой нужно нажать кнопку, чтобы очистить сохранённые параметры WiFi (если ESP_RESET_ON_START == true)
  --- 12.10.2019
  - Добавлена возможность сменить рабочий режим лампы (ESP_MODE) без необходимости перепрошивки; вызывается по семикратному клику по кнопке при включенной матрице; сохраняется в EEPROM
  - Изменён алгоритм работы будильника:
  -  * обновление его оттенка/яркости происходит 1 раз в 3 секунды вместо 1 раза в минуту
  -  * диоды разбиты на 6 групп, первой из которых назначается новый оттенок/яркость 1 раз в 3 секунды, вторая "отстаёт" на 1 шаг, третья - на 2 шага и т.д. (для большей плавности)
  - Добавлена визуальная сигнализация о некоторых важных действиях/состояниях лампы:
  -  * при запуске в режиме WiFi клиента и ещё не настроенных параметрах WiFi сети (когда их нужно ввести)                                                     - 1 вспышка жёлтым
  -  * если лампа стартовала в режиме WiFi клиента с ненастроенными параметрами WiFi сети, и они не были введены за отведённый таймаут (перед перезагрузкой)   - 1 вспышка красным
  -  * при переходе лампы в режим обновления по воздуху (OTA) по двум четырёхкратным кликам по кнопке или по кнопке OTA из android приложения                  - 2 вспышки жёлтым
  -  * если лампа была переведена в режим OTA, но не дождалась прошивки за отведённый таймаут (перед перезагрузкой)                                            - 2 вспышки красным
  -  * при переключении рабочего режима лампы WiFi точка доступа/WiFi клиент семикратным кликом по кнопке (перед перезагрузкой)                                - 3 вспышки красным
  -  * при запросе вывода времени бегущей строкой, если время не синхронизировано                                                                              - 4 вспышки красным
  - Уменьшен таймаут подключения к WiFi сети до 6 секунд; вызвано увеличившейся продолжительностью работы функции setup(), она в сумме должна быть меньше 8 секунд
  - Оптимизирован код
  --- 14.10.2019
  - Если при первом старте в режиме WiFi клиента запрашиваемые имя и пароль WiFi сети не введены за отведённый таймаут (5 минут), лампа перезагрузится в режиме точки доступа
  - Добавлен вывод времени бегущей строкой:
  -  * по запросу - шестикратному клику - текущее время белым цветом;
  -  * периодически - определяется константой PRINT_TIME в Constants.h - от раза в час (красным цветом) до раза в минуту (синим цветом) с яркостью текущего эффекта как при включенной, так и при выключенной матрице
  --- 19.10.2019
  - Добавлены "ночные часы" (от NIGHT_HOURS_START до NIGHT_HOURS_STOP включительно) и "дневные часы" (всё остальное время), для которых доступна регулировка яркости для вывода времени бегущей строкой - NIGHT_HOURS_BRIGHTNESS и DAY_HOURS_BRIGHTNESS
  --- 20.10.2019
  - Добавлена блокировка кнопки на лампе из android приложения; сохраняется в EEPROM память
  --- 24.10.2019
  - Добавлен вывод сигнала (HIGH/LOW - настраивается константой MOSFET_LEVEL) синхронно с включением матрицы на пин MOSFET транзистора (настраивается константой MOSFET_PIN)
  - Добавлен вывод сигнала (HIGH/LOW - настраивается константой ALARM_LEVEL) на пин будильника (настраивается константой ALARM_PIN); сигнал подаётся в течение одной минуты, начиная со времени, на которое заведён будильник
  --- 02.11.2019
  - Добавлен переход на летнее/зимнее время (изменены настройки часового пояса, см. Constants.h); добавлена библиотека Timezone
  - Добавлен эффект Белый огонь
  - Исправлена ошибка сброса сигнала на пине ALARM_PIN при отключении будильника вручную
  - Добавлена сигнализация (4 вспышки красным) при запросе вывода времени шестикратным кликом, если время не синхронизировано
  --- 04.11.2019
  - Исправлена ошибка невключения MOSFET'а матрицы при срабатывании "рассвета"
  - Исправлена ошибка невключения MOSFET'а матрицы при выводе времени и IP адреса
  --- 08.11.2019
  - Исправлены ошибки назначения статического IP адреса
  - Добавлен набросок WiFiManager Captive Portal для ввода пользовательских параметров и настроек
*/

// Ссылка для менеджера плат:
// https://arduino.esp8266.com/stable/package_esp8266com_index.json

#define FASTLED_USE_PROGMEM 1 // просим библиотеку FASTLED экономить память контроллера на свои палитры

#include "pgmspace.h"
#include "Constants.h"
#include <FastLED.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <EEPROM.h>
#include "Types.h"
#include "timerMinim.h"
#ifdef ESP_USE_BUTTON
#include <GyverButton.h>
#endif
#include "fonts.h"
#ifdef USE_NTP
#include <NTPClient.h>
#include <Timezone.h>
#endif
#include <TimeLib.h>
#ifdef OTA
#include "OtaManager.h"
#endif
#if USE_MQTT
#include "MqttManager.h"
#endif
#include "TimerManager.h"
#include "FavoritesManager.h"
#include "EepromManager.h"
#ifdef USE_BLYNK
#include <BlynkSimpleEsp8266.h>
#endif
#include <ESP8266SSDP.h>        
#include <ArduinoJson.h>        //Установить из менеджера библиотек версию 5.13.5 !!!. https://arduinojson.org/
#include <ESP8266HTTPUpdateServer.h>    // Обновление с web страницы
#ifdef USE_LittleFS
#include <LittleFS.h>    
#define SPIFFS LittleFS  
#endif
// --- ИНИЦИАЛИЗАЦИЯ ОБЪЕКТОВ ----------
CRGB leds[NUM_LEDS];
//WiFiManager wifiManager;
//WiFiServer wifiServer(ESP_HTTP_PORT);
WiFiUDP Udp;

#ifdef USE_NTP
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, NTP_ADDRESS, 0, NTP_INTERVAL); // объект, запрашивающий время с ntp сервера; в нём смещение часового пояса не используется (перенесено в объект localTimeZone); здесь всегда должно быть время UTC
   TimeChangeRule summerTime  = { SUMMER_TIMEZONE_NAME, SUMMER_WEEK_NUM, SUMMER_WEEKDAY, SUMMER_MONTH, SUMMER_HOUR, 0 };
   TimeChangeRule winterTime  = { WINTER_TIMEZONE_NAME, WINTER_WEEK_NUM, WINTER_WEEKDAY, WINTER_MONTH, WINTER_HOUR, 0 };
   Timezone localTimeZone(summerTime, winterTime);
  #ifdef PHONE_N_MANUAL_TIME_PRIORITY
    bool stillUseNTP = true;
  #endif    
#endif

timerMinim timeTimer(3000);
bool ntpServerAddressResolved = false;
bool timeSynched = false;
uint32_t lastTimePrinted = 0U;

#if defined(USE_MANUAL_TIME_SETTING) || defined(GET_TIME_FROM_PHONE)
time_t manualTimeShift;
#endif

#ifdef GET_TIME_FROM_PHONE
time_t phoneTimeLastSync;
#endif

uint8_t selectedSettings = 0U;

#ifdef ESP_USE_BUTTON
#if (BUTTON_IS_SENSORY == 1)
GButton touch(BTN_PIN, LOW_PULL, NORM_OPEN);  // для сенсорной кнопки LOW_PULL
#else
GButton touch(BTN_PIN, HIGH_PULL, NORM_OPEN); // для физической (не сенсорной) кнопки HIGH_PULL. ну и кнопку нужно ставить без резистора в разрыв между пинами D2 и GND
#endif
#endif

#ifdef OTA
OtaManager otaManager(&showWarning);
OtaPhase OtaManager::OtaFlag = OtaPhase::None;
#endif

#if USE_MQTT
AsyncMqttClient* mqttClient = NULL;
AsyncMqttClient* MqttManager::mqttClient = NULL;
char* MqttManager::mqttServer = NULL;
char* MqttManager::mqttUser = NULL;
char* MqttManager::mqttPassword = NULL;
char* MqttManager::clientId = NULL;
char* MqttManager::lampInputBuffer = NULL;
char* MqttManager::topicInput = NULL;
char* MqttManager::topicOutput = NULL;
bool MqttManager::needToPublish = false;
char MqttManager::mqttBuffer[] = {};
uint32_t MqttManager::mqttLastConnectingAttempt = 0;
SendCurrentDelegate MqttManager::sendCurrentDelegate = NULL;
#endif

ESP8266HTTPUpdateServer httpUpdater;  // Объект для обнавления с web страницы
ESP8266WebServer HTTP (ESP_HTTP_PORT);//ESP8266WebServer HTTP;  // Web интерфейс для устройства
File fsUploadFile;  // Для файловой системы



// --- ИНИЦИАЛИЗАЦИЯ ПЕРЕМЕННЫХ -------
uint16_t localPort = ESP_UDP_PORT;
char packetBuffer[MAX_UDP_BUFFER_SIZE];                     // buffer to hold incoming packet
char inputBuffer[MAX_UDP_BUFFER_SIZE];
static const uint8_t maxDim = max(WIDTH, HEIGHT);

ModeType modes[MODE_AMOUNT];
AlarmType alarms[7];

static const uint8_t dawnOffsets[] PROGMEM = {5, 10, 15, 20, 25, 30, 40, 50, 60};   // опции для выпадающего списка параметра "время перед 'рассветом'" (будильник); синхронизировано с android приложением
uint8_t dawnMode;
bool dawnFlag = false;
uint32_t thisTime;
bool manualOff = false;

uint8_t currentMode = 0;
bool loadingFlag = true;
bool ONflag = false;
uint32_t eepromTimeout;
bool settChanged = false;
bool buttonEnabled = true; // это важное первоначальное значение. нельзя делать false по умолчанию

unsigned char matrixValue[8][16]; //это массив для эффекта Огонь

bool TimerManager::TimerRunning = false;
bool TimerManager::TimerHasFired = false;
uint8_t TimerManager::TimerOption = 1U;
uint64_t TimerManager::TimeToFire = 0ULL;

uint8_t FavoritesManager::FavoritesRunning = 0;
uint16_t FavoritesManager::Interval = DEFAULT_FAVORITES_INTERVAL;
uint16_t FavoritesManager::Dispersion = DEFAULT_FAVORITES_DISPERSION;
uint8_t FavoritesManager::UseSavedFavoritesRunning = 0;
uint8_t FavoritesManager::FavoriteModes[MODE_AMOUNT] = {0};
uint32_t FavoritesManager::nextModeAt = 0UL;

//bool CaptivePortalManager::captivePortalCalled = false;

char TextTicker [43];
int Painting = 0; CRGB DriwingColor = CRGB(255, 255, 255);

uint8_t espMode ;
uint8_t random_on;
uint8_t Favorit_only;
//uint32_t my_time;
uint32_t my_timer;
uint8_t time_always;
bool connect = false;
uint32_t lastResolveTryMoment = 0xFFFFFFFFUL;
uint8_t ESP_CONN_TIMEOUT;
uint8_t PRINT_TIME ; 




void setup()
{
  Serial.begin(115200);
  Serial.println();
  ESP.wdtEnable(WDTO_8S);


  // ПИНЫ
  #ifdef MOSFET_PIN                                         // инициализация пина, управляющего MOSFET транзистором в состояние "выключен"
  pinMode(MOSFET_PIN, OUTPUT);
  #ifdef MOSFET_LEVEL
  digitalWrite(MOSFET_PIN, !MOSFET_LEVEL);
  #endif
  #endif

  #ifdef ALARM_PIN                                          // инициализация пина, управляющего будильником в состояние "выключен"
  pinMode(ALARM_PIN, OUTPUT);
  #ifdef ALARM_LEVEL
  digitalWrite(ALARM_PIN, !ALARM_LEVEL);
  #endif
  #endif
  
   //HTTP
  User_setings (); 
  LOG.print(F("\nСтарт файловой системы\n"));
  FS_init();  //Запускаем файловую систему
  LOG.print(F("Чтение файла конфигурации\n"));
  configSetup = readFile("config.json", 768);   
  LOG.println(configSetup);
  //Настраиваем и запускаем SSDP интерфейс
  LOG.print(F("Старт SSDP\n"));
  SSDP_init();
  //Настраиваем и запускаем HTTP интерфейс
  LOG.print (F("Старт WebServer\n"));
  HTTP_init();

  
//-----------Инициализируем переменные, хранящиеся в файле config.json--------------
  LAMP_NAME = jsonRead(configSetup, "SSDP");
  AP_NAME = jsonRead(configSetup, "ssidAP");
  AP_PASS = jsonRead(configSetup, "passwordAP");
  Favorit_only = jsonReadtoInt(configSetup, "favorit");
  random_on = jsonReadtoInt(configSetup, "random_on");
  espMode = jsonReadtoInt(configSetup, "ESP_mode");
  PRINT_TIME = jsonReadtoInt(configSetup, "print_time");
  buttonEnabled = jsonReadtoInt(configSetup, "button_on");
  ESP_CONN_TIMEOUT = jsonReadtoInt(configSetup, "TimeOut");
  time_always = jsonReadtoInt(configSetup, "time_always");
  (jsonRead(configSetup, "run_text")).toCharArray (TextTicker, (jsonRead(configSetup, "run_text")).length()+1);
  NIGHT_HOURS_START = 60U * jsonReadtoInt(configSetup, "night_time");
  NIGHT_HOURS_BRIGHTNESS = jsonReadtoInt(configSetup, "night_bright");
  NIGHT_HOURS_STOP = 60U * jsonReadtoInt(configSetup, "day_time");
  DAY_HOURS_BRIGHTNESS = jsonReadtoInt(configSetup, "day_bright");
  DONT_TURN_ON_AFTER_SHUTDOWN = jsonReadtoInt(configSetup, "effect_always"); 
  AUTOMATIC_OFF_TIME = (5 * 60UL * 60UL * 1000UL) * ( uint32_t )(jsonReadtoInt(configSetup, "timer5h"));
  #ifdef USE_NTP
  (jsonRead(configSetup, "ntp")).toCharArray (NTP_ADDRESS, (jsonRead(configSetup, "ntp")).length()+1);
  #endif
  jsonWrite(configSetup, "Power", ONflag);
  //aveConfig(); 
  Serial.print ("TextTicker = ");
  Serial.println (TextTicker);
  #ifdef USE_NTP
  winterTime.offset = jsonReadtoInt(configSetup, "timezone") * 60;
  summerTime.offset = winterTime.offset + jsonReadtoInt(configSetup, "Summer_Time") *60;
  localTimeZone.setRules (summerTime, winterTime);
  #endif


  // TELNET
  #if defined(GENERAL_DEBUG) && GENERAL_DEBUG_TELNET
  telnetServer.begin();
  for (uint8_t i = 0; i < 100; i++)                         // пауза 10 секунд в отладочном режиме, чтобы успеть подключиться по протоколу telnet до вывода первых сообщений
  {
    handleTelnetClient();
    delay(100);
    ESP.wdtFeed();
  }
  #endif


  // КНОПКА
  #if defined(ESP_USE_BUTTON)
  touch.setStepTimeout(BUTTON_STEP_TIMEOUT);
  touch.setClickTimeout(BUTTON_CLICK_TIMEOUT);
  touch.setDebounce(BUTTON_SET_DEBOUNCE);
    #if ESP_RESET_ON_START
    delay(500);                                            // ожидание инициализации модуля кнопки ttp223 (по спецификации 250мс)
    if (digitalRead(BTN_PIN))
    {
     // wifiManager.resetSettings();                          
      LOG.println(F("Настройки WiFiManager сброшены"));
      //buttonEnabled = true;                                   // при сбросе параметров WiFi сразу после старта с зажатой кнопкой, также разблокируется кнопка, если была заблокирована раньше
	jsonWrite(configSetup, "ssid", "");                          // сброс сохранённых SSID и пароля при старте с зажатой кнопкой, если разрешено
	jsonWrite(configSetup, "password", "");
	saveConfig();                                       // Функция сохранения данных во Flash
    }
    ESP.wdtFeed();
    #elif defined(BUTTON_LOCK_ON_START)
    delay(500);                                            // ожидание инициализации модуля кнопки ttp223 (по спецификации 250мс)
    if (digitalRead(BTN_PIN))
      buttonEnabled = false;
    ESP.wdtFeed();
    #endif
  #endif


  // ЛЕНТА/МАТРИЦА
  FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)/*.setCorrection(TypicalLEDStrip)*/;
  //FastLED.addLeds<WS2812B, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(0xFFB0F0); // по предложению @kostyamat добавлена такая цветокоррекция "теперь можно получить практически чистый желтый цвет" и получилось плохо
  FastLED.setBrightness(BRIGHTNESS);
  if (CURRENT_LIMIT > 0)
  {
    FastLED.setMaxPowerInVoltsAndMilliamps(5, CURRENT_LIMIT);
  }
  FastLED.clear();
  FastLED.show();

#ifdef USE_SHUFFLE_FAVORITES // первоначальная очередь избранного до перемешивания
    for (uint8_t i = 0; i < MODE_AMOUNT; i++)
      shuffleFavoriteModes[i] = i;
#endif

  // EEPROM
  EepromManager::InitEepromSettings(                        // инициализация EEPROM; запись начального состояния настроек, если их там ещё нет; инициализация настроек лампы значениями из EEPROM
    modes, alarms, &ONflag, &dawnMode, &currentMode,
    &(FavoritesManager::ReadFavoritesFromEeprom),
    &(FavoritesManager::SaveFavoritesToEeprom),
    &(restoreSettings)); // не придумал ничего лучше, чем делать восстановление настроек по умолчанию в обработчике инициализации EepromManager


  // WI-FI
  
  LOG.printf_P(PSTR("Рабочий режим лампы: ESP_MODE = %d\n"), espMode);
  //Запускаем WIFI
  LOG.println(F("Старуем WIFI"));
  
  WiFi.persistent(false);   // Побережём EEPROM
 
  if (espMode == 0U)                                        // режим WiFi точки доступа
  {
	// Отключаем WIFI
	WiFi.disconnect();
	// Меняем режим на режим точки доступа
	WiFi.mode(WIFI_AP);
	// Задаем настройки сети
    if (sizeof(AP_STATIC_IP))
    {
      WiFi.softAPConfig(                      
        IPAddress(AP_STATIC_IP[0], AP_STATIC_IP[1], AP_STATIC_IP[2], AP_STATIC_IP[3]),      // IP адрес WiFi точки доступа
        IPAddress(AP_STATIC_IP[0], AP_STATIC_IP[1], AP_STATIC_IP[2], 1),                    // первый доступный IP адрес сети
        IPAddress(255, 255, 255, 0));                                                       // маска подсети
    }
	// Включаем WIFI в режиме точки доступа с именем и паролем
	// хронящихся в переменных _ssidAP _passwordAP в фвйле config.json
	WiFi.softAP(AP_NAME, AP_PASS);
    LOG.print(F("Старт WiFi в режиме точки доступа\n"));
    LOG.print(F("IP адрес: "));
    LOG.println(WiFi.softAPIP());
   #ifdef GENERAL_DEBUG
    LOG.println ("*******************************************");
    LOG.print ("Heap Size after connection AP mode = ");
    LOG.println(system_get_free_heap_size());
    LOG.println ("*******************************************");
    #endif    
	connect = true;
    delay (100);    
  }
  else                                                      // режим WiFi клиента. Подключаемся к роутеру
  {
    LOG.println(F("Старт WiFi в режиме клиента (подключение к роутеру)"));
//	WIFI_start_station_mode (); 
	
   
   WiFi.persistent(false);

  // Попытка подключения к Роутеру
  WiFi.mode(WIFI_STA);
  String _ssid = jsonRead(configSetup, "ssid");
  String _password = jsonRead(configSetup, "password");
  if (_ssid == "" && _password == "") {
   espMode = 0;
   jsonWrite(configSetup, "ESP_mode", (int)espMode);
   saveConfig(); 
   ESP.restart();
  }
  else {
    WiFi.begin(_ssid.c_str(), _password.c_str());
  }
		
	delay (100);	  
    #ifdef USE_BLYNK
    Blynk.config(USE_BLYNK);
    #endif
  }     //if (espMode == 0U) {...} else {...
  
  ESP.wdtFeed();

  LOG.printf_P(PSTR("Порт UDP сервера: %u\n"), localPort);
  Udp.begin(localPort);


  // NTP
  #ifdef USE_NTP
  timeClient.begin();
  ESP.wdtFeed();
  #endif

  // MQTT
  #if (USE_MQTT)
  if (espMode == 1U)
  {
    mqttClient = new AsyncMqttClient();
    MqttManager::setupMqtt(mqttClient, inputBuffer, &sendCurrent);    // создание экземпляров объектов для работы с MQTT, их инициализация и подключение к MQTT брокеру
  }
  ESP.wdtFeed();
  #endif

  // ОСТАЛЬНОЕ
  memset(matrixValue, 0, sizeof(matrixValue)); //это массив для эффекта Огонь. странно, что его нужно залить нулями
  randomSeed(micros());
  changePower();
  loadingFlag = true;

  //TextTicker = RUNNING_TEXT_DEFAULT;
  delay (100);
  
  my_timer=millis();
}


void loop()
{
 if (espMode) {
  if (WiFi.status() != WL_CONNECTED) {
	if ((millis()-my_timer) >= 1000UL) {	
	  my_timer=millis();
	  if (ESP_CONN_TIMEOUT--) {
		LOG.print(F("."));
		ESP.wdtFeed();
	  }
	  else {
		// Если не удалось подключиться запускаем в режиме AP
		espMode = 0;
		jsonWrite(configSetup, "ESP_mode", (int)espMode);
		saveConfig(); 
		ESP.restart();
		//StartAPMode();
	  }
	}
  }
	else {
		// Иначе удалось подключиться отправляем сообщение
		// о подключении и выводим адрес IP
		LOG.print(F("\nПодключение к роутеру установлено\n"));
		LOG.print(F("IP адрес: "));
		LOG.println(WiFi.localIP());
		long rssi = WiFi.RSSI();
		LOG.print(F("Уровень сигнала сети RSSI = "));
		LOG.print(rssi);
		LOG.println(F(" dbm"));
		connect = true;
		//ESP_CONN_TIMEOUT = 0;
		lastResolveTryMoment = 0;
   #ifdef GENERAL_DEBUG
    LOG.println ("***********************************************");
    LOG.print ("Heap Size after connection Station mode = ");
    LOG.println(system_get_free_heap_size());
    LOG.println ("***********************************************");
    #endif
		delay (100);	  
	}
 }
 
 if (connect || !espMode)  { my_timer = millis(); }
  
do {	
  
  //delay (10);   //Для одной из плат(NodeMCU v3 без металлического экрана над ESP и Flash памятью) пришлось ставить задержку. Остальные работали нормально.
  
	if ((connect || !espMode)&&((millis() - my_timer) >= 10UL)) //Пришлось уменьшить частоту обращений к обработчику запросов web страницы, чтобы не использовать delay (10);.
	{
	HTTP.handleClient(); // Обработка запросов web страницы. 
	my_timer = millis();
	}

  parseUDP();
 if (Painting == 0) {

  effectsTick();

  EepromManager::HandleEepromTick(&settChanged, &eepromTimeout, &ONflag, 
    &currentMode, modes, &(FavoritesManager::SaveFavoritesToEeprom));

  //#ifdef USE_NTP
  #if defined(USE_NTP) || defined(USE_MANUAL_TIME_SETTING) || defined(GET_TIME_FROM_PHONE)
  //if (millis() > 30 * 1000U) можно попытаться оттянуть срок первой попытки синхронизации времени на 30 секунд, чтобы роутер успел не только загрузиться, но и соединиться с интернетом
    timeTick();
  #endif

  #ifdef ESP_USE_BUTTON
  //if (buttonEnabled) в процедуре ведь есть эта проверка
    buttonTick();
  #endif

  #ifdef OTA
  otaManager.HandleOtaUpdate();                             // ожидание и обработка команды на обновление прошивки по воздуху
  #endif

  TimerManager::HandleTimer(&ONflag, &settChanged,          // обработка событий таймера отключения лампы
    &eepromTimeout, &changePower);

  if (FavoritesManager::HandleFavorites(                    // обработка режима избранных эффектов
      &ONflag,
      &currentMode,
      &loadingFlag
      //#ifdef USE_NTP
      #if defined(USE_NTP) || defined(USE_MANUAL_TIME_SETTING) || defined(GET_TIME_FROM_PHONE)
      , &dawnFlag
      #endif
      , &random_on
      , &selectedSettings
      ))
  {
    #ifdef USE_BLYNK
    updateRemoteBlynkParams();
    #endif
    FastLED.setBrightness(modes[currentMode].Brightness);
  }

  #if USE_MQTT
  if (espMode == 1U && mqttClient && WiFi.isConnected() && !mqttClient->connected())
  {
    MqttManager::mqttConnect();                             // библиотека не умеет восстанавливать соединение в случае потери подключения к MQTT брокеру, нужно управлять этим явно
    MqttManager::needToPublish = true;
  }

  if (MqttManager::needToPublish)
  {
    if (strlen(inputBuffer) > 0)                            // проверка входящего MQTT сообщения; если оно не пустое - выполнение команды из него и формирование MQTT ответа
    {
      processInputBuffer(inputBuffer, MqttManager::mqttBuffer, true);
    }
    
    MqttManager::publishState();
  }
  #endif

  #ifdef USE_BLYNK
  if (espMode == 1U && WiFi.isConnected())
    Blynk.run();
  #endif

  #if defined(GENERAL_DEBUG) && GENERAL_DEBUG_TELNET
  handleTelnetClient();
  #endif
 }//if (Painting == 0)
  ESP.wdtFeed();
} while (connect);
}
