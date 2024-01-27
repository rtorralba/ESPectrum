/*
	Author: bitluni 2019
	License: 
	Creative Commons Attribution ShareAlike 4.0
	https://creativecommons.org/licenses/by-sa/4.0/
	
	For further details check out: 
		https://youtube.com/bitlunislab
		https://github.com/bitluni
		http://bitluni.net
*/
#pragma once

#include "../I2S/I2S.h"

enum vmodeproperties {
	hFront,
	hSync,
	hBack,
	hRes,
	vFront,
	vSync,
	vBack,
	vRes,
	vDiv,
	hSyncPolarity,
	vSyncPolarity,
	r1sdm0,
	r1sdm1,
	r1sdm2,
	r1odiv,
	r0sdm2,
	r0odiv
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VGA STANDARD MODES (IN STANDARD MODE TIMING DEPENDS ON PWM_AUDIO SO 48K MODES = 128K MODES)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define VgaMode_320x240 { 8, 48, 24, 320, 10, 2, 33, 480, 2, 1, 1, 41,84,7,7,6,6 } // 31469 / 59.94 INDUSTRY STANDARD
#define VgaMode_360x200 { 9, 54, 27, 360, 12, 2, 35, 400, 2, 1, 0, 48,84,7,6,6,5 } // 31469 / 70.087 TAKEN FROM SAMSUNG S22C450 MANUAL

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// VGA 50HZ MODES
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 48K

// 48K 50hz VGA, SYNC @ 19968 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_50_48 { 8, 42, 50, 320, 27, 6, 53, 720, 3, 1, 1, 0,44,6,4,8,5 } // 40365 / 50.0801282
#define VgaMode_360x200_50_48 { 18, 36, 54, 360, 31, 3, 33, 600, 3, 1, 1, 51,97,5,4,7,5 } // 33403 / 50.0801282

// 128K

// 128K 50hz VGA, SYNC @ 19992 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_50_128 { 8, 42, 50, 320, 27, 6, 53, 720, 3, 1, 1, 224,40,6,4,8,5 } // 40316 / 50.020008
#define VgaMode_360x200_50_128 { 18, 36, 54, 360, 31, 3, 33, 600, 3, 1, 1, 194,125,8,6,7,5 } // 33363 / 50.020008

// PENTAGON 128K

// PENTAGON 128K 50hz VGA, SYNC @ 20480 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_50_PENTAGON { 8, 42, 50, 320, 27, 6, 53, 720, 3, 1, 1, 13,146,7,5,6,4 } // 39355 / 48.838125
#define VgaMode_360x200_50_PENTAGON { 18, 36, 54, 360, 31, 3, 33, 600, 3, 1, 1, 143,49,8,6,5,4 } // 32568 / 48.838125

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TV MODES
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 48K

// ¡PENDING FINE TUNE SYNC TESTS! -> 48K 50hz CRT, SYNC @ 19968 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_TV_48 { 42, 32, 62, 320, 28, 3, 40, 240, 1, 1, 1, 59,167,6,13,6,12 } // 15575 / 50.0801282
#define VgaMode_360x200_TV_48 { 22, 32, 42, 360, 48, 3, 60, 200, 1, 1, 1, 59,167,6,13,6,12 } // 15575 / 50.0801282

// 128K

// ¡PENDING FINE TUNE SYNC TESTS! -> 128K 50hz CRT, SYNC @ 19992 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_TV_128 { 42, 32, 62, 320, 28, 3, 40, 240, 1, 1, 1, 245,163,6,13,8,15 } // 15556 / 50.020008
#define VgaMode_360x200_TV_128 { 22, 32, 42, 360, 48, 3, 60, 200, 1, 1, 1, 245,163,6,13,8,15 } // 15556 / 50.020008

// PENTAGON 128K

// ¡PENDING FINE TUNE SYNC TESTS! -> PENTAGON 128K 50hz CRT, SYNC @ 20480 micros, DAPR AUDIO LAG TEST -> CLEAN TONE
#define VgaMode_320x240_TV_PENTAGON { 42, 32, 62, 320, 28, 3, 40, 240, 1, 1, 1, 151,197,7,15,5,11 } // 15186 / 48.838125
#define VgaMode_360x200_TV_PENTAGON { 22, 32, 42, 360, 48, 3, 60, 200, 1, 1, 1, 151,197,7,15,5,11 } // 15186 / 48.838125

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const unsigned short int vidmodes[14][17]={ 
	VgaMode_320x240, VgaMode_360x200,
	VgaMode_320x240_50_48, VgaMode_360x200_50_48, VgaMode_320x240_50_128, VgaMode_360x200_50_128, VgaMode_320x240_50_PENTAGON , VgaMode_360x200_50_PENTAGON,
	VgaMode_320x240_TV_48, VgaMode_360x200_TV_48, VgaMode_320x240_TV_128, VgaMode_360x200_TV_128, VgaMode_320x240_TV_PENTAGON , VgaMode_360x200_TV_PENTAGON		
};

class VGA : public I2S {

  public:

	VGA(const int i2sIndex = 0);
	
	bool init(int mode, const int *pinMap, const int bitCount, const int clockPin = -1);

	int mode;

	int CenterH = 0;
	int CenterV = 0;

  protected:
	
	virtual void initSyncBits() = 0;
	virtual long syncBits(bool h, bool v) = 0;
 
	long vsyncBit;
	long hsyncBit;
	long vsyncBitI;
	long hsyncBitI;

	virtual void allocateLineBuffers();
	virtual void allocateLineBuffers(void **frameBuffer);
	virtual void propagateResolution(const int xres, const int yres) = 0;

};
