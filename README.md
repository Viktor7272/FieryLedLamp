# FieryLedLamp

Led lamp with web interface

Распакуйте содержимое архива в корневую папку на диске (не на рабочий стол, пожалуйста)
и делайте всё так же, как показал Алекс Гайвер в своём видео https://youtu.be/771-Okf0dYs?t=525 . В архиве есть файл "ПРОЧТИ МЕНЯ!!.txt. Его нужно внимательно прочитать. Для загрузки файлов из папки data в файловую систему контролера нужно установить Uploader. Видео тут https://esp8266-arduinoide.ru/esp8266fs/
Версию Ядра в "Менеджере плат" выбирайте 2.7.4. При первом запуске лампа создаст свою WiFi сеть с именем LedLamp пароль у этой сети при первом запуске будет 31415926. После подключения к сети LedLamp наберите в браузере 192.168.4.1 и зайдите на web страницу лампы. Там можно изменить имя лампы (если их несколько в сети), настроить подключение к Вашей домашней WiFi сети часовой пояс и переход на летнее время. Так же можно сменить пароль точки доступа (рекомендуется) и имя точки доступа. Перезагрузить лампу.
Все настройки прошивки находятся на вкладке Constants.h (там по-русски, без проблем разберётесь) и в файле data/config.json (там можно ничего не менять, всё меняется потом с web страницы лампы).

В данной прошивке режим работы ESP_MODE 1 (с роутером) или ESP_MODE 0 (без) .
В любой момент его можно будет поменять, либо он сам изменится.
