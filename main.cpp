#include <iostream>

#include "engine.h"

int main(int argc, char** argv)
{
	// Start an engine and run it then cleanup after

	
	// Create the engine
	Engine* engine = new Engine("Tutorial Window Name", 1200, 1000);

	// Engine initialization

	// this checks to see if the program initialized itself properly, if it didnt, clean up and exit(1).

	if (!engine->Initialize()) {
		printf("The engine failed to start.\n");
		delete engine;
		engine = NULL;
		return 1;
	}

	//this runs the window program

	// Run the engine
	engine->Run();

	//This is memory cleanup for when our program is done running.

	// Destroy the engine
	delete engine;
	engine = NULL;

	return 0;
}
