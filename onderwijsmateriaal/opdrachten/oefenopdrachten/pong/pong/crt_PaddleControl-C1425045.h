// by Marius Versteegen, 2023

#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Button.h>
#include "crt_SceneDisplayControl.h"
#include "crt_BallControl.h"

// This file contains the code of multiple tasks that run concurrently and notify eachother using flags.

namespace crt
{
	extern ILogger& logger;

	class PaddleControl : public Task, public IButtonListener
	{
	private:
		IButton& buttonLeft;
		IButton& buttonRight;
		ISceneDisplayControl& sceneDisplayControl;
		BallControl& ballControl;
        Flag flagLeftPressed;
		Flag flagRightPressed;
		int screenWidth;
		int paddlePosition;
		int paddleWidth;

	public:
		PaddleControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, IButton& buttonLeft, IButton& buttonRight, ISceneDisplayControl& sceneDisplayControl, BallControl& ballControl) :	
			Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), 
			buttonLeft(buttonLeft),
			buttonRight(buttonRight),
			sceneDisplayControl(sceneDisplayControl),
			ballControl(ballControl),
			flagLeftPressed(this),
			flagRightPressed(this),
			screenWidth(sceneDisplayControl.getWidth()),
			paddlePosition(screenWidth/2),
			paddleWidth(3)
		{
			buttonLeft.addButtonListener(this);
			buttonRight.addButtonListener(this);
			start();
		}

    void buttonPressed(IButton* pButton)
    {
		// logger.logText(pButton->getButtonName());

		if(pButton == &buttonLeft)
		{
        	flagLeftPressed.set();
		}
		else if(pButton == &buttonRight)
		{
			flagLeftPressed.set();
		}
		else
		{
			assert(false);
		}
    }

	// must override pure virtual function
	void buttonReleased(IButton* pButton)
	{
		// do nothing
	};

	private:
		/*override keyword not supported*/
		void main()
		{
			vTaskDelay(1000); // wait for other threads to have started up as well.

			while (true)
			{
				dumpStackHighWaterMarkIfIncreased(); 		// This function call takes about 0.25ms! It should be called while debugging only.

				waitAny(flagLeftPressed + flagRightPressed);
				if(hasFired(flagLeftPressed))
				{
					//logger.logText("Left button press detected by paddleControl");
					if (paddlePosition>(1+(paddleWidth/2)))
					{
						paddlePosition--;
					}
				}
				else if(hasFired(flagRightPressed))
				{
					//logger.logText("Right button press detected by paddleControl");
					if (paddlePosition<(screenWidth-2-paddleWidth/2))
					{
						paddlePosition++;
					}
				}
				else
				{
					assert(false);
				}
				sceneDisplayControl.updatePaddlePosition(paddlePosition);
				ballControl.updatePaddlePosition(paddlePosition);
			}
		}
	}; // end class PaddleControl

};// end namespace crt
