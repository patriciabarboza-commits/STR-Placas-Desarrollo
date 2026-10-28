STR en placas de desarrollo

Este repositorio contiene los códigos modificados de la actividad de evaluación continua sobre Sistemas de Tiempo Real (STR), utilizando FreeRTOS en las placas Arduino UNO y ESP32.

Implementaciones:

Arduino UNO (ArduinoUNO_RTOS.ino)
Se incorporó una tercera tarea al código original, permitiendo controlar tres LEDs conectados a los pines digitales 8, 9 y 10, con diferentes prioridades e intervalos de ejecución.

ESP32 (ESP32_RTOS.ino)
Se agregó una tercera tarea para controlar un LED externo conectado al GPIO 18. Se mantuvieron las dos tareas originales: el control del LED integrado y el envío de mensajes de telemetría mediante el monitor serie.

Resultados: En ambas plataformas se comprobó el funcionamiento de las tres tareas implementadas mediante pruebas físicas.
