/*
 * GFPS.h
 *
 *  Created on: 28 nov 2012
 *      Author: Nima
 */

#ifndef GFPS_H_
#define GFPS_H_

#include <SDL/SDL.h>

class GFPS {
	public:
		GFPS();
		float GetSpeedFactor();
		int GetFPS();
		void OnLoop();

		static GFPS FPSControl;

	private:
		unsigned int OldTime;
		unsigned int LastTime;

		float SpeedFactor;

		unsigned int NumFrames;
		unsigned int Frames;
};

#endif
