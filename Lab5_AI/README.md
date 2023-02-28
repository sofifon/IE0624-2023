# Laboratorio 4. STM32: GPIO, ADC, comunicaciones, Iot

Este proyecto consiste en el aprendizaje y utilización de Machine Learning para microcontrola-
dores. Para ello se utilizó el microcontrolador STM32F429i Discovery kit y algunas herramientas
digitales como TensorFlow Lite, Google Colab, Python.

Los datos para alimentar la red neuronal fueron tomados por medio del microcontrolador, ya que
es ahí donde se quiere ver el sistema funcionando. Se grabaron 3 movimientos por 15 segundos cada
uno: brazo arriba abajo, extensión de codo y círculos con el brazo.

La red neronal fue entrenada através de Google Colab, se utilizó 60 % de los datos para entre-
namiento, 20 % para comprobación y 20 % para validación. Una vez hecha se exportó para utilizarla
como una biblioteca en un programa para el microcontrolador STM. 

Para correr este programa se debe instalar:
 sudo apt install gcc-arm-none-eabi
 sudo apt install stlink-tools
 sudo apt install openocd


Para correr este codigo que se encuentra basado en la biblioteca de libopencm3, se debe descargar primero el repositorio de ejemplos que se encuentra en https://github.com/libopencm3/libopencm3-examples y seguir los pasos para su adecuado uso. Cuando se completa, se agrega la carpeta de measurements debajo de /../libopencm3-examples/examples/stm32/f4/stm32f429i-discovery, si se quieren grabar los datos, o la carpeta de detection si se desea detectar los movimientos.

En el caso de grabar los datos, una vez que measurements se encuentra corriendo el programa en la tarjeta, se puede ejecutar el script de python recorder.py para crear el documento de datos.


