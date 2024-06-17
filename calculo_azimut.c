#include <stdio.h>
#include <math.h> // Libreria para las operaciones matematicas
#include <time.h> // Libreria para las funciones de fecha y hora

#define pi 3.14159265358979323846 // Definimos pi como un valor aproximado a "Pí"

int main() {
    int a, m, d1, cont = 0, d, db = 0; // Declaramos las variables enteras de: año, mes y dia actuales, asi como un contador y el numero de dias desde el 1 de enero
    float hour, min, hor_loc; // Declaramos las variables de la hora, minutos y hora local
    /*Declaramos las variables de longitud, latitud, declinacion solar, la ecuacion del
    tiempo, el tiempo solar verdadero, la altura solar y el azimuto direccion solar*/
    float Long, lat, ds, b, eot, long_zon, long_est, tsv, h, alt_sol, alt_sol_gra, azim;

    // Obtener la fecha y hora actuales

    time_t now; // Variable para almacenar el tiempo en segundos
    struct tm *local; // Estructura que 
    time(&now);
    local = localtime(&now);

    // Determinación de la fecha actual
    a = local->tm_year + 1900; // tm_year devuelve años desde 1900
    m = local->tm_mon + 1;     // tm_mon devuelve meses desde 0
    d1 = local->tm_mday;       // tm_mday devuelve el día del mes

    // Determinación de la hora local
    hour = local->tm_hour;
    min = local->tm_min;
    hor_loc = hour + (min / 60);

    // Conteo de los días transcurridos desde que inicio el año
    d = 0;
    cont = 0;
    do {
        if (cont == 1 || cont == 3 || cont == 5 || cont == 7 || cont == 8 || cont == 10 || cont == 12) {
            d = d + 31;
        } else if (cont == 4 || cont == 6 || cont == 9 || cont == 11) {
            d = d + 30;
        } else if (cont == 2) {
            if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
                d = d + 29; // Año bisiesto
            } else {
                d = d + 28; // Año no bisiesto
            }
        }
        cont++;
    } while (cont < m);

    // Ajuste para el día actual
    d = d - (31 - d1);

    // Determinación si el año actual es bisiesto
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
        db = 1;
    } else {
        db = 0;
    }
    d = d + d1 + db;

    // Recibir datos de latitud y longitud
    printf("-------------------------------------------------\n");
    printf("Escriba la latitud: ");
    scanf("%f", &lat);
    printf("-------------------------------------------------\n");
    printf("Escriba la longitud: ");
    scanf("%f", &Long);

    // Cálculo de la declinación solar
    ds = -23.44 * cos((((360.0 / 365) * (d + 10)) * pi) / 180);
    printf("-------------------------------------------------\n");
    printf("El angulo de declinacion solar es de %.2f grados\n", ds);

    // Fórmula de la ecuación del tiempo
    b = (((360.0 / 365) * (d - 81)) * pi) / 180;
    eot = 9.87 * sin(2 * b) - 7.53 * cos(b) - 1.5 * sin(b);

    // Cálculo del tiempo solar verdadero
    long_zon = trunc(Long / 15);
    long_est = long_zon * 15;
    tsv = hor_loc + (((4 * (Long - long_est)) + eot) / 60);

    // Cálculo de la altura solar
    h = (15 * (tsv - 12)) * (pi / 180);
    ds = ds * (pi / 180);
    lat = lat * (pi / 180);
    alt_sol = asin(sin(ds) * sin(lat) + cos(ds) * cos(lat) * cos(h));
    alt_sol_gra = alt_sol * (180 / pi);
    printf("-------------------------------------------------\n");
    printf("La altura solar es de %.2f grados\n", alt_sol_gra);

    // Cálculo del azimut
    printf("-------------------------------------------------\n");
    azim = acos((sin(ds) - sin(alt_sol) * sin(lat)) / (cos(alt_sol) * cos(lat)));
    if (h > 0) {
        azim = 2 * pi - azim;
    }
    azim = azim * (180 / pi);
    printf("El azimut o direccion solar es de %.2f grados\n", azim);

    return 0;
}