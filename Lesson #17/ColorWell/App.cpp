#include "App.h"
#include "MainWindow.h"

App::App(void)
	: BApplication("application/x-vnd.jy-ColorWellDemo1")
{
	MainWindow *mainwin = new MainWindow();
	mainwin->Show();
}

int main(void)
{
	App *app = new App();
	app->Run();
	delete app;
	return 0;
}
