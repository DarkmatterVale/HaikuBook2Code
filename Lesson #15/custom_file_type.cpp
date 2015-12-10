#include <Mime.h>

int main(void)
{
	BMimeType customType;
	
	customType.SetType("text/MyWrite");
	customType.SetShortDescription("My Write text document");
	customType.SetLongDescription("My Write text document");
	
	BMessage extMsg;
	extMsg.AddString("extensions", "mywr");
	customType.SetFileExtensions(&extMsg);
	
	customType.SetPreferredApp("application/x-vnd.test.MyWrite");
}
