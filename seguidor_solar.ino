#include <RtcDS1302.h>
#include <Servo.h>

ThreeWire myWire(4,5,2); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

Servo servohori; // servo horizontal y limites
int servoh=90;
int servohLimitHigh = 180;
int servohLimitLow = 35;

Servo servoverti; // servo vertical y limites
int servov=90;
int servovLimitHigh = 180;
int servovLimitLow = 35;
unsigned long time;
float tiempo = 200000.50; // CADA 200 SEGUNDOS AVANZA UN GRADO, HASTA LLEGAR A LOS 180°
unsigned long t = 0;

int pos_default = 90;
int pos_default_add = 90;
boolean act_1 = false, act_2 = false;
char DiaSemana[][4] = {"Dom", "Lun", "Mar", "Mie", "Jue", "Vie", "Sab"};


// Pines LDR
int ldrtopr = 3; // pin LDR A3 superior derecho
int ldrtopl = 0; // pin LDR A0 superior izquierdo
int ldrbotr = 2; // pin LDR A2 inferior derecho
int ldrbotl = 1; // pin LDR A1 inferior izquierdo

void setup() 
{
    Serial.begin(9600);
    Rtc.Begin();

    RtcDateTime compiled = RtcDateTime(_DATE, __TIME_);
    if (!Rtc.IsDateTimeValid()) 
    {
        Serial.println("RTC lost confidence in the DateTime!");
        Rtc.SetDateTime(compiled);
    }

    if (Rtc.GetIsWriteProtected())
    {
        Serial.println("RTC was write protected, enabling writing now");
        Rtc.SetIsWriteProtected(false);
    }

    if (!Rtc.GetIsRunning())
    {
        Serial.println("RTC was not actively running, starting now");
        Rtc.SetIsRunning(true);
    }

    RtcDateTime now = Rtc.GetDateTime();
    if (now < compiled) 
    {
        Serial.println("RTC is older than compile time! Updating");
        Rtc.SetDateTime(compiled);
    }
  
    servohori.attach(10);
    servohori.write(90);
    servoverti.attach(9);
    servoverti.write(90);
    delay(5000);
}

void loop() 
{
    int LDR = analogRead(A1);
    Serial.print("SENSOR_LDR ");
    Serial.println(LDR);
 
    RtcDateTime now = Rtc.GetDateTime();
    printDateTime(now);
    delay(1000);

    if (LDR <= 400) {
        servoverti.write(pos_default);
        servohori.write(pos_default);
        act_1 = true; 
    }
    if (now.Hour() >= 7 && now.Hour() < 17) {
        act_1 = true;
    }

    if (act_1 == true) {
        time = millis();
        if (time - t > tiempo) {
            t = time;
            pos_default_add++;
        }
        if (LDR < 600) {
            servoverti.write(pos_default_add);
            Serial.print("GRADOS SERVO");
            Serial.println(pos_default_add);
        } else {
            act_2 = true; // Activar el seguimiento con fotorresistencias cuando la luz es alta
        }
    }

    if (pos_default_add >= 180) {
        act_1 = false;
    }

    if (pos_default_add >= 180 && now.Hour() >= 17) {       
        pos_default_add = 35;
        servoverti.write(pos_default);
    }

    if (act_2 == true) {
        seguimientoFotorresistencias();
    }
}

void seguimientoFotorresistencias() {
    int servoh = servohori.read();
    int servov = servoverti.read();

    int topl = analogRead(ldrtopl);
    int topr = analogRead(ldrtopr);
    int botl = analogRead(ldrbotl);
    int botr = analogRead(ldrbotr);

    int avgtop = (topl + topr) / 2;
    int avgbot = (botl + botr) / 2;
    int avgleft = (topl + botl) / 2;
    int avgright = (topr + botr) / 2;

    if (avgtop > avgbot) {
        servoverti.write(servov - 1);
        if (servov > servovLimitHigh) {
            servov = servovLimitHigh;
        }
        delay(5);
    }
    else if (avgbot > avgtop) {
        servoverti.write(servov + 1);
        if (servov < servovLimitLow) {
            servov = servovLimitLow;
        }
        delay(5);
    } else {
      servoverti.write(servov);
    }

    if (avgleft < avgright) {
        servohori.write(servoh - 1);
        if (servoh > servohLimitHigh) {
            servoh = servohLimitHigh;
        }
        delay(5);
    }
    else if (avgright < avgleft) {
        servohori.write(servoh + 1);
        if (servoh < servohLimitLow) {
            servoh = servohLimitLow;
        }
        delay(5);
    } else {
      servohori.write(servoh);
    }

    delay(50);
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

void printDateTime(const RtcDateTime& dt)
{
    char datestring[20];

    snprintf_P(datestring, 
            countof(datestring),
            PSTR("%04u/%02u/%02u %02u:%02u:%02u %s"),
            dt.Year(),
            dt.Month(),
            dt.Day(),
            dt.Hour(),
            dt.Minute(),
            dt.Second(),
            DiaSemana[dt.DayOfWeek()]);
    Serial.println(datestring);
}
