#include <Servo.h>
#include <TimeLib.h>
#include <math.h>

#define pi 3.14159265358979323846

Servo altitudeServo;
Servo azimuthServo;

// Definir pines para los servos
const int ALTITUDE_SERVO_PIN = 9;
const int AZIMUTH_SERVO_PIN = 10;

// Variables globales
float lat, Long;
int a, m, d1, d;

// Declaraciones de funciones
int calcularDiaDelAnio(int year, int month, int day);
float calcularDeclinacionSolar(int d);
float calcularEcuacionTiempo(int d);
float calcularTiempoSolarVerdadero(float hour, float Long, float eot);
float calcularAlturaSolar(float ds, float lat, float tsv);
float calcularAzimut(float ds, float lat, float alt_sol, float tsv);

void setup() {
  Serial.begin(9600);
  
  // Configurar los servos
  altitudeServo.attach(ALTITUDE_SERVO_PIN);
  azimuthServo.attach(AZIMUTH_SERVO_PIN);
  
  // Configurar la fecha y hora inicial (ajusta esto a la fecha y hora actuales)
  setTime(12, 0, 0, 15, 7, 2024);
  
  // Solicitar latitud y longitud
  Serial.println("Ingrese la latitud:");
  while (!Serial.available()) {}
  lat = Serial.parseFloat();
  Serial.print("Latitud: ");
  Serial.println(lat);
  
  Serial.println("Ingrese la longitud:");
  while (!Serial.available()) {}
  Long = Serial.parseFloat();
  Serial.print("Longitud: ");
  Serial.println(Long);
}

void loop() {
  // Obtener la fecha y hora actuales
  a = year();
  m = month();
  d1 = day();
  float currentHour = hour() + minute() / 60.0 + second() / 3600.0;
  
  // Calcular el día del año
  d = calcularDiaDelAnio(a, m, d1);
  
  // Calcular la posición solar
  float ds = calcularDeclinacionSolar(d);
  float eot = calcularEcuacionTiempo(d);
  float tsv = calcularTiempoSolarVerdadero(currentHour, Long, eot);
  float alt_sol_gra = calcularAlturaSolar(ds, lat, tsv);
  float azim = calcularAzimut(ds, lat, alt_sol_gra, tsv);
  
  // Mapear los valores a ángulos de servo (0-180)
  int servo_alt = map(round(alt_sol_gra + 90), 0, 180, 0, 180);
  int servo_azim = map(round(azim), 0, 360, 0, 180);
  
  // Mover los servos
  altitudeServo.write(servo_alt);
  azimuthServo.write(servo_azim);
  
  // Imprimir los resultados
  Serial.print("Altura solar: ");
  Serial.print(alt_sol_gra);
  Serial.print(" grados, Servo: ");
  Serial.println(servo_alt);
  
  Serial.print("Azimut: ");
  Serial.print(azim);
  Serial.print(" grados, Servo: ");
  Serial.println(servo_azim);
  
  delay(60000);  // Esperar 1 minuto antes de la próxima actualización
}

// Implementaciones de las funciones

int calcularDiaDelAnio(int year, int month, int day) {
  const int diasPorMes[] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
  int diaDelAnio = day + diasPorMes[month - 1];
  
  // Ajuste para año bisiesto
  if (month > 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
    diaDelAnio++;
  }
  
  return diaDelAnio;
}

float calcularDeclinacionSolar(int d) {
  return -23.44 * cos((360.0 / 365 * (d + 10) * pi) / 180);
}

float calcularEcuacionTiempo(int d) {
  float b = (360.0 / 365 * (d - 81) * pi) / 180;
  return 9.87 * sin(2 * b) - 7.53 * cos(b) - 1.5 * sin(b);
}

float calcularTiempoSolarVerdadero(float hour, float Long, float eot) {
  float long_zon = floor(Long / 15);
  float long_est = long_zon * 15;
  return hour + ((4 * (Long - long_est)) + eot) / 60;
}

float calcularAlturaSolar(float ds, float lat, float tsv) {
  float h = (15 * (tsv - 12)) * (pi / 180);
  ds *= pi / 180;
  lat *= pi / 180;
  return asin(sin(ds) * sin(lat) + cos(ds) * cos(lat) * cos(h)) * 180 / pi;
}

float calcularAzimut(float ds, float lat, float alt_sol, float tsv) {
  float h = (15 * (tsv - 12)) * (pi / 180);
  ds *= pi / 180;
  lat *= pi / 180;
  alt_sol *= pi / 180;
  float azim = acos((sin(ds) - sin(alt_sol) * sin(lat)) / (cos(alt_sol) * cos(lat)));
  if (h > 0) {
    azim = 2 * pi - azim;
  }
  return azim * 180 / pi;
}