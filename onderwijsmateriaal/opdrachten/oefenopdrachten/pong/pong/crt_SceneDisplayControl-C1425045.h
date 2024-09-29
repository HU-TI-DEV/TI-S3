// by Marius Versteegen, 2023

#pragma once
#include <crt_CleanRTOS.h>
#include <crt_CharMatrix.h>

// This file contains the code of multiple tasks that run concurrently and notify eachother using flags.

namespace crt
{
	extern ILogger& logger;

	struct TwoNumbers
	{
		TwoNumbers():number1(0),number2(0){}
		TwoNumbers(int number1, int number2):number1(number1),number2(number2){}
		
		int number1;
		int number2;
	};

	class ISceneDisplayControl
	{
		public:
			virtual int getWidth() = 0;
			virtual int getHeight() = 0;
			virtual void updateBallPosition(int x, int y) = 0;
			virtual void updatePaddlePosition(int x) = 0;
			virtual void enable() = 0;
			virtual void disable() = 0;
	};

	template <int WIDTH, int HEIGHT>
	class SceneDisplayControl : public Task, public ISceneDisplayControl
	{
		enum State
		{
			STATE_ENABLED,
			STATE_DISABLED
		};

	private:
		int width;
		int height;
		int frameDelayMs;
		CharMatrix<WIDTH,HEIGHT> charMatrix;
		Pool<TwoNumbers> poolBallPosition;
		Pool<int> poolPaddlePosition;
		Flag flagEnable;
		Flag flagDisable;
		Flag flagPositionUpdated;
		State state;

	public:
		SceneDisplayControl(const char *taskName, unsigned int taskPriority, unsigned int taskSizeBytes, unsigned int taskCoreNumber, int frameDelayMs) :
			Task(taskName, taskPriority, taskSizeBytes, taskCoreNumber),
			width(WIDTH),
			height(HEIGHT),
			frameDelayMs(frameDelayMs),
			flagEnable(this),
			flagDisable(this),
			flagPositionUpdated(this),
			state (STATE_DISABLED)
		{
			poolBallPosition.write(TwoNumbers(width/2,1));
			poolPaddlePosition.write(width/2);
			start();
		}

    int getWidth()
    {
		return width;
    }

	int getHeight()
	{
		return height;
	}

	void updateBallPosition(int x, int y)
	{
		poolBallPosition.write(TwoNumbers(x,y));
		flagPositionUpdated.set();
	}

	void updatePaddlePosition(int x)
	{
		poolPaddlePosition.write(x);
		flagPositionUpdated.set();
	}

	void enable()
	{
	}

	void disable()
	{
		flagDisable.set();
	}

	private:
		void clearConsole()
		{
			ESP_LOGI("","%s","\x1b[2J\x1b[H");
		}

		void markCorners()
		{
			charMatrix.setChar(0,0,'X');
			charMatrix.setChar(width-1,0,'Y');
			charMatrix.setChar(width-1,height-1,'Z');
			charMatrix.setChar(0,height-1,'W');
		}

		void drawTopBorder()
		{
			for(int i = 0; i < width; i++)
			{
				charMatrix.setChar(i,height-1,'-');
			}
		}

		void drawLeftBorder()
		{
			for(int i = 0; i < height; i++)
			{
				charMatrix.setChar(0,i,'|');
			}
		}

		void drawRightBorder()
		{
			for(int i = 0; i < height; i++)
			{
				charMatrix.setChar(width-1,i,'|');
			}
		}

		void drawPaddle()
		{
			int paddlePosition=0;
			poolPaddlePosition.read(paddlePosition);
			charMatrix.setChar(paddlePosition-1,0,'@');
			charMatrix.setChar(paddlePosition,0,'@');
			charMatrix.setChar(paddlePosition+1,0,'@');
		}

		void drawBall()
		{
			TwoNumbers ballPosition;
			poolBallPosition.read(ballPosition);
			charMatrix.setChar(ballPosition.number1,ballPosition.number2,'O');
		}

		void displayScene()
		{
			charMatrix.clearMatrix();
			drawTopBorder();
			drawLeftBorder();
			drawRightBorder();
			//markCorners(); // just for initial debugging.
			drawPaddle();
			drawBall();

			clearConsole(); // comment out for debugging (otherwise the debug output is cleared as well).
			charMatrix.printMatrix();
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
					case STATE_ENABLED:
						displayScene();
						waitAny(flagDisable+flagPositionUpdated);
						if(hasFired(flagDisable))
						{
							state = STATE_DISABLED;
						}
						else if(hasFired(flagPositionUpdated))
						{
							// state blijft STATE_ENABLED
							state = STATE_ENABLED;
						}
						break;

					case STATE_DISABLED:
						wait(flagEnable);
						flagDisable.clear();
						state = STATE_ENABLED;
						break;
					default:
						assert(false);
				}
			}
		}
	}; // end class SceneDisplayControl

};// end namespace crt
