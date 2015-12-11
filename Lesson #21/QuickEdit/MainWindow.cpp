#include "MainWindow.h"

#include <Alert.h>
#include <Application.h>
#include <Directory.h>
#include <File.h>
#include <Menu.h>
#include <MenuItem.h>
#include <Messenger.h>
#include <NodeInfo.h>
#include <Path.h>
#include <ScrollView.h>
#include <String.h>
#include <TranslationUtils.h>

enum
{
	M_FILE_NEW = 'flnw',
	M_SHOW_OPEN = 'shop',
	M_SAVE = 'save',
	M_SAVE_AS = 'svas',
	M_PRINT_SETUP = 'ptcf',
	M_PRINT = 'prin'
};

MainWindow::MainWindow(void)
	: BWindow(BRect(100,100,500,400), "QuickEdit", B_TITLED_WINDOW,
		B_ASYNCHRONOUS_CONTROLS)
{
	BRect r(Bounds());
	r.bottom = 20;
	
	fMenuBar = new BMenuBar(r, "menubar");
	AddChild(fMenuBar);
	
	BMenu *menu = new BMenu("File");
	fMenuBar->AddItem(menu);
	
	menu->AddItem(new BMenuItem("New", new BMessage(M_FILE_NEW), 'N'));
	menu->AddItem(new BMenuItem("Open", new BMessage(M_SHOW_OPEN), 'O'));
	menu->AddItem(new BMenuItem("Save", new BMessage(M_SAVE), 'S'));
	menu->AddItem(new BMenuItem("Save As", new BMessage(M_SAVE_AS), 'S',
		B_COMMAND_KEY | B_SHIFT_KEY));
	
	r = Bounds();
	r.top = fMenuBar->Frame().bottom + 1;
	r.right -= B_V_SCROLL_BAR_WIDTH;

	BRect textRect = r;
	textRect.OffsetTo(0,0);
	textRect.InsetBy(5,5);
	fTextView = new BTextView(r, "textview", textRect, B_FOLLOW_ALL);
	
	fTextView->SetStylable(true);
	
	BScrollView *scrollView = new BScrollView("scrollview", fTextView,
		B_FOLLOW_ALL, 0, false, true);
	AddChild(scrollView);
	
	BMessenger msgr(NULL, this);
	fOpenPanel = new BFilePanel(B_OPEN_PANEL, &msgr, NULL, 0, false);
	fSavePanel = new BFilePanel(B_SAVE_PANEL, &msgr, NULL, 0, false);
	
	fTextView->MakeFocus(true);
}

MainWindow::~MainWindow(void)
{
	delete fOpenPanel;
	delete fSavePanel;
}

void MainWindow::MessageReceived(BMessage *msg)
{
	switch (msg->what)
	{
		case M_FILE_NEW:
		{
			fTextView->SetText("");
			fFilePath = "";
			break;
		}
		case M_SHOW_OPEN:
		{
			fOpenPanel->Show();
			break;
		}
		case B_REFS_RECEIVED:
		{
			entry_ref ref;
			if (msg->FindRef("refs", &ref) != B_OK)
				break;
			OpenFile(ref); 
			break;
		}
		case M_SAVE:
		{
			if (fFilePath.CountChars() < 1)
				fSavePanel->Show();
			else
				SaveFile(fFilePath.String());
			break;
		}
		case M_SAVE_AS:
		{
			fSavePanel->Show();
			break;
		}
		case B_SAVE_REQUESTED:
		{
			entry_ref dir;
			BString name;
			if (msg->FindRef("directory", &dir) == B_OK &&
				msg->FindString("name", &name) == B_OK)
			{
				BPath path(&dir);
				path.Append(name);
				SaveFile(path.Path());
			}
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

void MainWindow::OpenFile(const entry_ref &ref)
{
	BEntry entry(&ref, true);
	entry_ref realRef;
	entry.GetRef(&realRef);
	
	BFile file(&realRef, B_READ_ONLY);
	if (file.InitCheck() != B_OK)
		return;
	
	if (BTranslationUtils::GetStyledText(&file, fTextView) == B_OK)
	{
		BPath path(&realRef);
		fFilePath = path.Path();
		SetTitle(path.Leaf());
	}
}

void MainWindow::SaveFile(const char *path)
{
	BFile file;
	if (file.SetTo(path, B_READ_WRITE | B_CREATE_FILE | B_ERASE_FILE)
		!= B_OK)
		return;
	
	if (BTranslationUtils::PutStyledText(fTextView, &file) == B_OK)
	{
		fFilePath = path;
		
		BNodeInfo nodeInfo(&file);
		nodeInfo.SetType("text/plain");
	}
}

void MainWindow::FrameResized(float w, float h)
{
	UpdateTextRect();
}


void MainWindow::UpdateTextRect(void)
{
	BRect r(fTextView->Bounds());
	r.InsetBy(5, 5);
	fTextView->SetTextRect(r);
}
