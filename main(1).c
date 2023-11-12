#include <stdio.h>
#include "ztimer.h"
#include "isl29020.h"
#include "isl29020_params.h"

isl29020_params_t *param;
isl29020_t *dev;
int light;


int main(void)
{
    puts("Hello from RIOT!");
    isl29020_init (dev, param);
    //while(1){
    light = isl29020_read (dev);
    printf("light%d", light);
    ztimer_sleep(ZTIMER_SEC, 30);
    
    return 0;
}
