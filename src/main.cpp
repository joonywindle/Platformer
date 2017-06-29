#include <stdio.h>
#include <iostream>
#include "MainGame.h"
#include "WindowManager.h"
#include "Test.h"
#include <fstream>
int main(int argc, char **argv)
{
  WindowManager wm;
	MainGame mg;
  wm.initSystems();
	mg.run();
	return 0;
}
