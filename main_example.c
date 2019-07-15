
#include <stdio.h>
#include <fps220_d10h.h>

/* Private variable */
int32_t real_p, real_t, altitude;
//float real_press, real_temp;
volatile uint32_t TMR0_Ticks = 0; //one tick per millisecond(ms)
volatile uint32_t fps220_update_rdy = 0;

/**
 * @brief      A timer generate an interrupt every millisecond
 */
void TMR0_IRQHandler(void)
{
	if (TIMER_GetIntFlag(TIMER0) == 1)
	{
		/* Clear Timer0 time-out interrupt flag */
		TIMER_ClearIntFlag(TIMER0);

		TMR0_Ticks++;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{

	fps220_init();//fps220 initiation

	while (1)
	{
		fps220_update_data();//Updating fps220 data
		if (fps220_update_rdy) {
			// real_press = fps220_read_pressure();//If you need the pressure value read is in uint of Pa, use this function.
			// real_temp = fps220_read_temperature();//If you need the temperature value read is in unit of degree Celsius, use this function.

			/* This function read pressure and temperature values. Pressure uint:0.01 Pa, Temperature unit:0.01 degree Celsius */
			fps220_read_data(&real_p, &real_t);
			fps220_update_rdy = 0;
		}
	}
}
