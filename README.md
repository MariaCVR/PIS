## Descripción del Proyecto
Este proyecto tiene la finalidad de diseñar y construir un cargador solar automatizado que mejore la eficiencia de captación de energía solar mediante la orientación óptima hacia el sol. Para ello se creó un código, con el cual se programará un software de control que integre los algoritmos de seguimiento solar y gestión de energía, asegurando que el sistema sea eficiente, fácil de usar y mantenible, y que esté adecuadamente documentado para futuras referencias y mejoras. La implementación del cargador solar se debe a que el mundo actual está sintiendo los efectos del cambio climático y el calentamiento global, generados en parte por la quema de combustibles fósiles para la generación de energía eléctrica. Por ello nos vemos obligados a generar fuentes limpias de energía.
##Requisitos
Para ejecutar el programa:
- Tener un dispositivo tecnológico. 
- Tener instalado o instalar VisualStudioCode.
- Descargar Arduino IDE junto con los controladores de Arduino uno.
- Descargar el archivo [Seguidor Solar]
- Tener el microcontrolador de Arduino uno.
- Seleccionar el tipo de placa de arduino que se esta utilizando en la opcion de placa
## Instrucciones de Instalacion
A continuacion, se detallan los pasos a seguir para poder ejecutar el programa en un seguidor solar:
- Abra VisualStudioCode y cree una carpeta para guardar el codigo
- Descargue el archivo [Calculo Azimut](https://github.com/MariaCVR/PIS/blob/main/calculo_azimut.c) y guardelo en la carpeta
- Descargue Arduino IDE junto con los controladores de Arduino uno, los cuales se los puede descargar mientras se descarga Arduino IDE
- Abra el archivo [Seguidor Solar](https://github.com/MariaCVR/PIS/commit/3fcef5f2689e61b4c51ab52df61bb7fa25235b4f) y guardelo dentro de la carpeta predeterminada de Arduino IDE
- Conecte el microcontrolador a la computadora via USB
- En Arduino IDE, Dirijirse a la pertaña Herramientas y seleccionar la occion del puerto donde se encuentra el arduino
- Seleccionar el tipo de placa de arduino que se esta utilizando en la opcion de placa
- Compile el programa para verificar que no haya errores de sintaxis
- Seleccione la opcion de subir, la cual se encuentra al lado de la opcion para compilar
- Desconectar cuidadosamente el arduino para colocarlo en el seguidor solar
## Uso
Después de seguir con los pasos de instalación, solo queda implementar el programa para el seguimiento solar, en el cual proporcionaremos las variables de latitud y longitud, para obtener las coordenadas del sol.
