/* ============================================================
   File: Program_Structure.c
   Purpose: Show complete "Program Structure" in C
   ============================================================ */

/* 1) HEADERS / INCLUDES */
#include <stdio.h>
#include <string.h>

/* 2) MACROS / DEFINES */
#define APP_NAME       "StructureDemo"
#define MAX_BUF        64
#define LIMIT_TEMP     30

/* 3) GLOBAL DECLARATIONS (global variables) */
int g_system_on = 1;          // visible everywhere in this file
static int g_error_count = 0; // static global: visible only inside this .c file

/* 4) USER-DEFINED TYPES (struct) */
typedef struct
{
    int id;
    int temperature;
    char status[16];
} Sensor;

/* 5) FUNCTION PROTOTYPES (declare before use) */
static void print_banner(void);
static int  read_temperature_fake(void);
static void update_sensor(Sensor *s, int temp);
static void print_sensor(const Sensor *s);
static int  clamp(int x, int min, int max);

/* 6) main() ENTRY POINT */
int main(void)
{
    /* Local variables (block scope) */
    Sensor s1;
    s1.id = 1;

    print_banner();

    /* Example flow: read -> process -> print (structured steps) */
    int raw_temp = read_temperature_fake();
    int safe_temp = clamp(raw_temp, -20, 120);

    update_sensor(&s1, safe_temp);
    print_sensor(&s1);

    /* Simple control decision using global flags */
    if (s1.temperature > LIMIT_TEMP)
    {
        printf("Action: Temperature high -> FAN ON\n");
    }
    else
    {
        printf("Action: Temperature normal -> FAN OFF\n");
    }

    printf("Error count = %d\n", g_error_count);

    return 0;  // program ends
}

/* ============================================================
   7) FUNCTION DEFINITIONS (actual implementations)
   ============================================================ */

/* static function: visible only inside this file */
static void print_banner(void)
{
    printf("=== %s ===\n", APP_NAME);
}

/* Fake temperature reading (simulating a sensor read) */
static int read_temperature_fake(void)
{
    /* static local: keeps value between calls */
    static int t = 25;
    t += 3;  // changes each call

    return t;
}

/* Function using pointer parameter (can modify original struct) */
static void update_sensor(Sensor *s, int temp)
{
    if (s == NULL)
    {
        g_error_count++;
        return;
    }

    s->temperature = temp;

    if (temp > LIMIT_TEMP)
        strcpy(s->status, "HIGH");
    else
        strcpy(s->status, "OK");
}

/* Function using const pointer (read-only access) */
static void print_sensor(const Sensor *s)
{
    if (s == NULL)
    {
        g_error_count++;
        return;
    }

    printf("Sensor ID: %d\n", s->id);
    printf("Temp     : %d C\n", s->temperature);
    printf("Status   : %s\n", s->status);
}

/* Utility function returns a value */
static int clamp(int x, int min, int max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
