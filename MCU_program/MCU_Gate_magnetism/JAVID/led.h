#ifndef __LED_H
#define __LED_H
#include "sys.h"

void LED_Init(void);
#define LED_safe PBout(0)//°²È«µÆ
#define LED_danger PBout(1)//Î£ÏÕµÆ

#define ON 1
#define OFF 0

#endif

