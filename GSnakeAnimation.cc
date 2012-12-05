/*
 * GSnakeAnimation.cc
 *
 *  Created on: 26 nov 2012
 *      Author: Nima
 */

#include "GSnakeAnimation.h"

GSnakeAnimation::GSnakeAnimation() {
	CurrentFrame    = 0;
	MaxFrames       = 0;
	FrameInc        = 1;
	FrameRate       = 100; //[ms]
	OldTime         = 0;
	Oscillate       = false;
}

void GSnakeAnimation::OnAnimate() {
	if(OldTime + FrameRate > SDL_GetTicks()) {
		return;
	}

	OldTime = SDL_GetTicks();
	CurrentFrame += FrameInc;

	if(Oscillate) {
		if(FrameInc > 0) {
			if(CurrentFrame >= MaxFrames) {
				FrameInc = -FrameInc;
			}
		}else{
			if(CurrentFrame <= 0) {
				FrameInc = -FrameInc;
			}
		}
	}else{
		if(CurrentFrame >= MaxFrames) {
			CurrentFrame = 0;
		}
	}
}

void GSnakeAnimation::SetFrameRate(unsigned int Rate)
{
	FrameRate = Rate;
}

void GSnakeAnimation::SetCurrentFrame(int Frame) {
	if(Frame < 0 || Frame >= MaxFrames) return;
	CurrentFrame = Frame;
}

int GSnakeAnimation::GetCurrentFrame() {
	return CurrentFrame;
}
