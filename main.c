#include <stdio.h>
#include "verion.h"

int main()
{

char ver[128] = {0};
sprintf(ver, "%s%s.%s", ___MODULE___, ___VERSION___,___BUILD___);
printf("ver = %s\n", ver);
return 0;

}

