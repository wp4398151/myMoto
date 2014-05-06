// Win32Robot.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Win32Robot.h"
#include "Robot.h"
#include "Util.h"
#include "TLoginForm.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	TLoginFrom tLoginFrom;
	Robot myRobot(&tLoginFrom);
	myRobot.DoFill();

	return (int)0;
}


