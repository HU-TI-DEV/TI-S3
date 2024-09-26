// by Marius Versteegen, 2023

#include <crt_CleanRTOS.h>        // This file includes crt_Config.h  You'll need to change defines there for a release build.
#include <crt_Mutex.h>            // crt_Mutex.h must be included separately.

// All Tasks should be created in this main file.
#include <crt_Logger.h>
#include <crt_Handler.h>
#include <crt_Button.h>
#include "crt_PaddleControl.h"
#include "crt_SceneDisplayControl.h"
#include "crt_GameControl.h"

namespace crt
{
	// Create a "global" logger object withing namespace crt.
	const unsigned int pinButtonDump = 23; // Pressing a button connected to this pin dumps the latest logs to serial monitor.

	Logger<100> theLogger("Logger", 1 /*priority*/, ARDUINO_RUNNING_CORE, pinButtonDump);
	ILogger& logger = theLogger;	// This is the global object. It can be accessed without knowledge of the template parameter of theLogger.

    MainInits mainInits;            // Initialize CleanRTOS.
	Handler<10 /*MAXLISTENERCOUNT*/> buttonHandler("ButtonHandler", 1 /*priority*/, ARDUINO_RUNNING_CORE, 70 /*periodMs*/, 3000 /*batchTimeUs*/); // Don't forget to call its start() member during setup().
	SceneDisplayControl<20,10> sceneDisplayControl("SceneDisplayControl", 1 /*priority*/, 10000 /*stack size*/, ARDUINO_RUNNING_CORE, 1000 /*frameDelayMs*/); 

	// These buttons are shared between multiple controls, so they are created here, rather than being members of the controls.
	Button<5> buttonLeft("ButtonLeft", 25, true, buttonHandler);
	Button<5> buttonRight("ButtonRight", 26, true, buttonHandler);

	BallControl ballControl("BallControl", 1 /*priority*/, 5000 /*stack size*/, ARDUINO_RUNNING_CORE, sceneDisplayControl);
	GameControl gameControl("GameControl", 1 /*priority*/, 5000 /*stack size*/, ARDUINO_RUNNING_CORE, buttonLeft, buttonRight, sceneDisplayControl, ballControl);
	PaddleControl paddleControl("PaddleControl", 1 /*priority*/, 5000 /*stack size*/, ARDUINO_RUNNING_CORE, buttonLeft, buttonLeft, sceneDisplayControl, ballControl); 	
}

void setup()
{
	// initialize serial communication at 115200 bits per second:
	// Serial.begin(115200);    // Only needed when using Serial.print();

	crt::buttonHandler.start();  // IMPORTANT NOTE! a Handler task needs to be started manually,
								// AFTER its listeners have been added or have added themselves to the handler.
	vTaskDelay(10);// allow tasks to initialize.
	ESP_LOGI("checkpoint", "start of main");vTaskDelay(1);
}

void loop()
{
	vTaskDelay(1);// Nothing to do in loop - all example code runs in the 4 threads above.
}