# Laboratorio 4. STM32: GPIO, ADC, comunicaciones, Iot

Este proyecto corresponde al cuarto laboratorio del curso Laboratorio de Microcontroladores de la Universidad de Costa Rica. Realizado por Sofia Fonseca Munoz.

Este proyecto consiste en la creacion de un sismografo por medio del microcontrolador STM32f429 Discovery kit. Este kit esta conformado por el microcontrolador ARM STM32F429, varios botones, una pantalla LCD tactil, varios leds y otros componentes que permiten la creacion de proyectos gracias a su integralidad. 

El sismografo utiliza el acelerometro interno que posee el kit para detectar movimiento. Las aceleraciones dadas se muestran en la pantalla junto con el nivel de bateria con el que esta funcionando y si se estan transimitiendo datos. Este sismografo utiliza el protocolo USART para enviar datos a la computadora, la cual se encarga de enviar esta informacion a ThingsBoard. 

ThingsBoard es una plataforma IoT que permite manipular y desplegar datos para diferentes funcionalidades. En este caso muestra los datos e indica si el sismografo a detectado un temblor. 

Para correr este programa se debe instalar:
 sudo apt install gcc-arm-none-eabi
 sudo apt install stlink-tools
 sudo apt install openocd
 pip3 install paho-mqtt

Para correr este codigo que se encuentra basado en la biblioteca de libopencm3, se debe descargar primero el repositorio de ejemplos que se encuentra en https://github.com/libopencm3/libopencm3-examples y seguir los pasos para su adecuado uso. Cuando se completa, se agrega la carpeta de seismo debajo de /../libopencm3-examples/examples/stm32/f4/stm32f429i-discovery.

Una vez que se encuentra corriendo el programa en la tarjeta, se puede ejecutar el script de python para ver los valores el ThingsBoard.
[//]: <> (![Sismografo en ThingsBoard.](informe/images/TemblorTrue.png))

