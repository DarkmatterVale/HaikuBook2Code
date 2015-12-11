#include "MainWindow.h"

#include <Application.h>
#include <Menu.h>
#include <MenuItem.h>
#include <View.h>
#include <MenuBar.h>

#include "ColorWell1.h"

enum
{
	M_SET_COLOR = 'stcl',
	M_COLOR_UPDATED = 'mcup',
	M_SET_SHAPE_CIRCLE = 'sscr',
	M_SET_SHAPE_SQUARE = 'sssq',
};

MainWindow::MainWindow(void)
	: BWindow(BRect(100,100,500,400), "ColorWell Demo", B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS)
{
	BRect r(Bounds());
	r.bottom = 20;
	fMenuBar = new BMenuBar(r, "menubar");
	AddChild(fMenuBar);
	
	r = Bounds();
	r.top = 20;
	BView *background = new BView(r, "Background", B_FOLLOW_ALL,
		B_WILL_DRAW);
		
	background->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	AddChild(background);
	
	fColorWell = new ColorWell(BRect(15,15,165,165), "color well",
		new BMessage(M_COLOR_UPDATED));
	
	background->AddChild(fColorWell);
	
	BMenu *menu = new BMenu("Color");
	fMenuBar->AddItem(menu);
	
	BMessage *msg = new BMessage(M_SET_COLOR);
	msg->AddInt8("red", 160);
	msg->AddInt8("green", 0);
	msg->AddInt8("blue", 0);
	menu->AddItem(new BMenuItem("Red", msg, 'R', B_COMMAND_KEY));
	msg = new BMessage(M_SET_COLOR);
	msg->AddInt8("red", 0);
	msg->AddInt8("green", 160);
	msg->AddInt8("blue", 0);
	menu->AddItem(new BMenuItem("Green", msg, 'G', B_COMMAND_KEY));
	msg = new BMessage(M_SET_COLOR);
	msg->AddInt8("red", 0);
	msg->AddInt8("green", 0);
	msg->AddInt8("blue", 160);
	menu->AddItem(new BMenuItem("Blue", msg, 'B', B_COMMAND_KEY));
	
	menu = new BMenu("Shape");
	fMenuBar->AddItem(menu);
	
	menu->AddItem(new BMenuItem("Square", new BMessage(M_SET_SHAPE_SQUARE),
		'S', B_COMMAND_KEY));
	menu->AddItem(new BMenuItem("Circle", new BMessage(M_SET_SHAPE_CIRCLE),
		'C', B_COMMAND_KEY));
}

void MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case M_SET_COLOR:
		{
			int8 red, green, blue;
			msg->FindInt8("red", &red);
			msg->FindInt8("green", &green);
			msg->FindInt8("blue", &blue);
			
			fColorWell->SetValue(red, green, blue);
			break;
		}
		case M_SET_SHAPE_CIRCLE:
		{
			fColorWell->SetStyle(COLORWELL_ROUND_WELL);
			break;
		}
		case M_SET_SHAPE_SQUARE:
		{
			fColorWell->SetStyle(COLORWELL_SQUARE_WELL);
			break;
		}
		default:
		{
			BWindow::MessageReceived(msg);
			break;
		}
	}
}

bool MainWindow::QuitRequested(void)
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}
