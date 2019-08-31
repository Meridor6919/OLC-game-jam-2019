#include "GameApp.h"

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prev_instace, LPSTR cmd_line, int show_cmd)
{
	try
	{
		GameApp xd(instance);
		xd.Run();
	}
	catch (HRESULT h)
	{
		MessageBox(0, "Critical error", "Critical error", 0);
		exit(0);
	}
}