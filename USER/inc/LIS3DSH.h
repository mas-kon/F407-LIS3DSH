#ifndef LIS3DSH_H_
#define LIS3DSH_H_

/* ============================================ INCLUDES ===================================================== */
#include "main.h"

/* ============================================ DEFINES ===================================================== */
#define LIS3DSH_ID				0x3F
#define	HYSTERESIS				1500


/* ============================================ FUCTIONS ==================================================== */
void InitLIS3DSH(void);
void TestLIS3DSH(void);
void Identity_LIS3DSH(void);
	
#endif /* LIS3DSH_H_ */
