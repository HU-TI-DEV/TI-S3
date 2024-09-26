// by Marius Versteegen, 2024

#pragma once
#include <crt_CleanRTOS.h>
#include <crt_Button.h>
#include "crt_SceneDisplayControl.h"

// This file contains the code of multiple tasks that run concurrently and notify eachother using flags.

namespace crt
{
	extern ILogger& logger;

    class IBallControlListener
    {
    public:
        virtual void ballMissedByPaddle() = 0;
    };

	class BallControl : public Task
	{
        enum State
        {
            STATE_STOPPED,
            STATE_RUNNING
        };

	private:
        Flag flagStart;
        Pool<int> poolPaddlePosition;
        ISceneDisplayControl& sceneDisplayControl;
        IBallControlListener* pBallControlListener;
        int screenWidth;
        int screenHeigth;
        int posX;
        int posY;
        int vX;
        int vY;
        State state;

	public:
		BallControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, ISceneDisplayControl& sceneDisplayControl) :	
			Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber), 
            flagStart(this),
            sceneDisplayControl(sceneDisplayControl),
            pBallControlListener(nullptr),
			screenWidth(sceneDisplayControl.getWidth()),
            screenHeigth(sceneDisplayControl.getHeight()),
            posX(screenWidth/2),
            posY(screenHeigth/2),
            vX(1),
            vY(1),
            state(STATE_STOPPED)
		{
			start();
		}

        void setBallControlListener(IBallControlListener* pBallControlListener)
        {
            this->pBallControlListener = pBallControlListener;
        }

        void startBall()
        {
            flagStart.set();
        }

        void updatePaddlePosition(int x)
        {
            poolPaddlePosition.write(x);
        }

	private:
        void initialiseRandomStartPos()
        {
            posX = screenWidth/2;
            posY = screenHeigth/2;
            vX = (rand()%2)*2-1;
            vY = 1;
        }

        void updateBallPosition()
        {
            if (posX==1 || posX==screenWidth-2)
            {
                vX = -vX;
            }
            if (posY==screenHeigth-2)
            {
                vY = -vY;
            }
            int paddlePosition(0);
            poolPaddlePosition.read(paddlePosition);
            if(posY==1 && (posX+vX)>=paddlePosition-1 && (posX+vX)<=paddlePosition+1)
            {
                vY = -vY;
            }
            posX += vX;
            posY += vY;
            sceneDisplayControl.updateBallPosition(posX, posY);
        }

		/*override keyword not supported*/
		void main()
		{
			vTaskDelay(1000); // wait for other threads to have started up as well.

			while (true)
			{
				dumpStackHighWaterMarkIfIncreased(); 		// This function call takes about 0.25ms! It should be called while debugging only.

				switch (state)
                {
                case STATE_STOPPED:
                    wait(flagStart);
                    initialiseRandomStartPos();
                    state = STATE_RUNNING;
                    break;

                case STATE_RUNNING:
                    if (posY<=0)
                    {
                        assert(pBallControlListener!=nullptr);
                        pBallControlListener->ballMissedByPaddle();
                        state = STATE_STOPPED;
                    }
                    else
                    {
                        updateBallPosition();
                    }
                    break;
                
                default:
                    break;
                }

                vTaskDelay(500);    // Determines the speed of the ball.
                                    // feasibility depends on the console speed of your machine.
			}
		}
	}; // end class BallControl

};// end namespace crt
