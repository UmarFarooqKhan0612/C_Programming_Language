/* ============================================================
   File: Program_Structure.c
   Purpose: Show complete "Program Structure" in C
   ============================================================ */

/* 1) HEADERS / INCLUDES */
#include <stdio.h>
#include <string.h>

/* 2) MACROS / DEFINES */
#define APP_NAME       "StructureDemo"
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
    Sensor s1;
    s1.id = 1;

    print_banner();

    /* FOR LOOP demo: multiple reads so you see OK -> HIGH transition */
    for (int i = 0; i < 5; i++)
    {
        int raw_temp  = read_temperature_fake();
        int safe_temp = clamp(raw_temp, -20, 120);

        update_sensor(&s1, safe_temp);
        print_sensor(&s1);

        if (s1.temperature > LIMIT_TEMP)
            printf("Action: Temperature high -> FAN ON\n\n");
        else
            printf("Action: Temperature normal -> FAN OFF\n\n");
    }

    printf("Error count = %d\n", g_error_count);

    return 0;
}

/* ============================================================
   7) FUNCTION DEFINITIONS (actual implementations)
   ============================================================ */

static void print_banner(void)
{
    printf("=== %s ===\n", APP_NAME);
}

static int read_temperature_fake(void)
{
    /* static local: keeps value between calls */
    static int t = 25;
    t += 3;              /* 28, 31, 34, 37, 40 ... */
    return t;
}

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

static int clamp(int x, int min, int max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
