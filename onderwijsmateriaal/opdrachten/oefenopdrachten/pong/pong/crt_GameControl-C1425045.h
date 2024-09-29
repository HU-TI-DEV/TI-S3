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

	enum State
	{
		STATE_INITIAL,
		STATE_KLIK_OM_TE_STARTEN,
		STATE_GAME_RUNNING,
		STATE_GAME_OVER
	};

	class GameControl : public Task, public IButtonListener, public IBallControlListener
	{
	private:
	    State state;
		IButton& buttonLeft;
		IButton& buttonRight;
        Flag flagLeftPressed;
		Flag flagRightPressed;
		Flag flagBallMissedByPaddle;
		ISceneDisplayControl& sceneDisplayControl;
		BallControl& ballControl;

	public:
		GameControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, IButton& buttonLeft, IButton& buttonRight, ISceneDisplayControl& sceneDisplayControl, BallControl& ballControl) :	
			Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), 
			state(STATE_INITIAL),
			buttonLeft(buttonLeft),
			buttonRight(buttonRight),
			flagLeftPressed(this),
			flagRightPressed(this),
			flagBallMissedByPaddle(this),
			sceneDisplayControl(sceneDisplayControl),
			ballControl(ballControl)
		{
			buttonLeft.addButtonListener(this);
			buttonRight.addButtonListener(this);
			ballControl.setBallControlListener(this);
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
			flagRightPressed.set();
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

	void ballMissedByPaddle()
	{
		flagBallMissedByPaddle.set();
	}

	private:
		void waitForButtonPress()
		{
			waitAny(flagLeftPressed + flagRightPressed);
			if(hasFired(flagLeftPressed))
			{
				//ESP_LOGI("PaddleControl", "Left button was pressed");
				logger.logText("Left button was pressed");
			}
			else if(hasFired(flagRightPressed))
			{
				//ESP_LOGI("PaddleControl", "Right button was pressed");
				logger.logText("Right button was pressed");
			}
			else
			{
				assert(false);
			}
		}

		/*override keyword not supported*/
		void main()
		{
			vTaskDelay(1000); // wait for other threads to have started up as well.

			while (true)
			{
				dumpStackHighWaterMarkIfIncreased(); 		// This function call takes about 0.25ms! It should be called while debugging only.

				switch(state)
				{
					case STATE_INITIAL:
						logger.logText("STATE_INITIAL");
						vTaskDelay(200);
						ESP_LOGI("", "\n\n\nKlik op de linker of rechter knop om te starten.");
						break;

					case STATE_KLIK_OM_TE_STARTEN:
						logger.logText("STATE_KLIK_OM_TE_STARTEN");
						vTaskDelay(200);
						flagLeftPressed.clear();  // clear any pending button presses still meant to controll the paddle.
						flagRightPressed.clear();
						waitForButtonPress();
						ballControl.startBall();
						sceneDisplayControl.enable();
						state = STATE_GAME_RUNNING;
						break;
						
					case STATE_GAME_RUNNING:
						logger.logText("STATE_GAME_RUNNING");
						wait(flagBallMissedByPaddle);
						state = STATE_GAME_OVER;
						break;

					case STATE_GAME_OVER:
						sceneDisplayControl.disable();
						vTaskDelay(200); // wacht op evt parallel afrenderen van scene.
						logger.logText("STATE_GAME_OVER");

						ESP_LOGI("Game Over", "\n"
						"  _____                         ____                  \n"
						" / ____|                       / __ \\                 \n"
						"| |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __  \n"
						"| | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__| \n"
						"| |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |    \n"
						" \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|    \n"
						"\n"
						"Klik op de linker of rechter knop om opnieuw te starten.");

						state = STATE_KLIK_OM_TE_STARTEN;
						break;

					default:
						assert(false);
				}

				vTaskDelay(1);
			}
		}
	}; // end class PaddleControl

};// end namespace crt
