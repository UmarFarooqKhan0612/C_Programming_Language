/* ============================================================
   File: 1_Program_Structure.c
   ============================================================ */

/* 1) HEADERS / INCLUDES */
#include <stdio.h>
#include <string.h>

/* 2) MACROS / DEFINES */
#define LIMIT_TEMP 30
#define NAME_LEN   16

/* 3) USER-DEFINED TYPES (struct) */
typedef struct
{
    int id;
    int temp;
    char status[NAME_LEN];
} Sensor;

/* 4) GLOBAL DECLARATIONS (global variables) */
static int g_error_count = 0;

/* 5) FUNCTION PROTOTYPES (declare before use) */
static int  read_temp_fake(void);
static void update_sensor(Sensor *s, int temp);
static void print_sensor(const Sensor *s);

/* 6) main() ENTRY POINT */
int main(void)
{
    Sensor s = { .id = 1, .temp = 0, .status = "INIT" };

    for (int i = 0; i < 5; i++)
    {
        int t = read_temp_fake();
        update_sensor(&s, t);
        print_sensor(&s);
    }

    printf("Errors: %d\n", g_error_count);
    return 0;
}

/* ============================================================
   7) FUNCTION DEFINITIONS (actual implementations)
   ============================================================ */

static int read_temp_fake(void)
{
    static int t = 25;
    t += 3;            /* 28, 31, 34, ... */
    return t;
}

static void update_sensor(Sensor *s, int temp)
{
    if (!s) { g_error_count++; return; }

    s->temp = temp;
    if (temp > LIMIT_TEMP) strncpy(s->status, "HIGH", NAME_LEN);
    else                   strncpy(s->status, "OK",   NAME_LEN);
}

static void print_sensor(const Sensor *s)
{
    if (!s) { g_error_count++; return; }
    printf("ID=%d Temp=%d Status=%s\n", s->id, s->temp, s->status);
}
