#include "includes.h"

//ÏŞ·ùº¯Êı
u32 LIMIT(u32 yournumber,u32 Upper_Limit,u32 Lower_Limit)
{
	if(yournumber>(Upper_Limit-10))
	{
		yournumber=Upper_Limit-10;
	}
	else if(yournumber<(Lower_Limit+10))
	{
	  yournumber=Lower_Limit+10;
	}
	else
	{
		yournumber=yournumber;
	}
	return yournumber;		
}
