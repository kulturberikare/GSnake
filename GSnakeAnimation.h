/*
 * GSnakeAnimation.h
 *
 *  Created on: 26 nov 2012
 *      Author: Nima
 */

#ifndef GSNAKEANIMATION_H_
#define GSNAKEANIMATION_H_

#include <SDL/SDL.h>

class GSnakeAnimation {
	public:
		GSnakeAnimation();
		int GetCurrentFrame();
		void OnAnimate();
		void SetFrameRate(unsigned int);
		void SetCurrentFrame(int);

		bool Oscillate;
		unsigned int MaxFrames;

	private:
		unsigned int CurrentFrame;
		unsigned int FrameInc;
		unsigned int FrameRate; //[ms]
		unsigned long OldTime;
};

#endif
