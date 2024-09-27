/*
 * Light weight library to convert Gregorian date to Jalali (Shamsi)
 * with leap year support. Please reffer to Github page formore information
 * By: Payam Sabouri <paysab@gmail.com> 
 * Modified By: Hamed Zakeri Rad 
 * https://github.com/HamedZakeriRad/Arduino-Gregorian-to-Jalali-Date
 */

#ifndef JalaliDateConverter_h
#define JalaliDateConverter_h

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif
#include <RTClib.h>  // Include RTC for DateTime object

class JalaliDateConverter {
	public:
		void ToShamsi(uint16_t,uint16_t,uint16_t);
		void ToGregorian(uint16_t,uint16_t,uint16_t);
		uint16_t global_year, global_month, global_day;
		String convertToJalali(DateTime now);  // Add the function prototype
	private:
		const uint16_t grgSumOfDays[2][13]={
			{0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
			{0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366}};
		const uint16_t hshSumOfDays[2][13]={
			{0, 31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 365}, 
			{0, 31, 62, 93, 124, 155, 186, 216, 246, 276, 306, 336, 366}};
		boolean grgIsLeap (uint16_t);
		boolean hshIsLeap (uint16_t);
};

#endif

