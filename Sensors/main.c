#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "thread.h"
#include "ztimer.h"
#include "shell.h"

#include "mutex.h"

#include "lpsxxx.h"
#include "lpsxxx_params.h"

#include "isl29020.h"
#include "isl29020_params.h"
#include "isl29020-internal.h"



/* Declaration of variables for the lps331ap sensor*/
static lpsxxx_t lpsxxx;

/* Declaration of variables for the isl29020 sensor*/
static isl29020_t isl29020;


int main(void)
{
        
    // Initialization the lps331ap sensor 
    lpsxxx_init(&lpsxxx, &lpsxxx_params[0]);
    //Initialization the isl29020 sensor  
    isl29020_init (&isl29020, &isl29020_params[0]);
    int16_t light = 0;
    int16_t temp = 0;
    uint16_t pres = 0;
    int i=0;
    int nb_value=100;
        while(i<nb_value){
            printf("Id: %d\n",i);
            light=isl29020_read(&isl29020);
            printf("Luminosity: %i.%ulx\n", (light / 100), (light % 100));
            lpsxxx_read_temp(&lpsxxx, &temp);
            printf("Temperature: %i.%u°C\n", (temp /100), (temp % 100));
            lpsxxx_read_pres(&lpsxxx, &pres);
            printf("Pressure: %uhPa\n", pres);
            ztimer_sleep(ZTIMER_SEC, 5);
        i=i+1;
        }

    return 0;
}


