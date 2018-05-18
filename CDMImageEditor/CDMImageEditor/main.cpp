
#include "CDMTextInputWindow.h"
#include "CDMTextWindow.h"
#include "CDMMouseInputWindow.h"

int main()
{
	CDMContext* ctx = CDMCreateContext(1, 1);
	CDMSetWindowTitle(L"Image Editor");
	CDMSetFontAndSize(&ctx, L"Terminal", 8, 8);
	CDMChangeWindowSize(&ctx, 150, 80);
	CDMTextInputWindow window(CDMKey::returnK,CDMTextInput::AlphaNum);
	CDMTextWindow text(CDMKey::returnK, false);
	CDMMouseInputWindow mouse;
	mouse.SetTitle(L"Mouse Window");
	mouse.SetupWindow(25, 25, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	mouse.posX = 25;
	mouse.posY = 30;
	text.SetText(L"Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum");
	text.SetScrollKeys(CDMKey::up, CDMKey::down);
	text.SetTitle(L"Text window");
	text.SetupWindow(25, 8, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	text.posX = 70;
	text.posY = 25;
	window.SetupWindow(20, 5, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	window.SetTitle(L"Text Input Window");
	window.posX = 25;
	window.posY = 25;
	while (true)
	{
		CDMPollEvents(ctx, &ctx->events);
		CDMKeepScreenSize(&ctx, &ctx->events);
		CDMClearScreen(&ctx);
		window.Update(ctx);
		window.Draw(ctx);
		text.Update(ctx);
		text.Draw(ctx);
		mouse.Update(ctx);
		mouse.Draw(ctx);
		CDMCoord relative = mouse.GetMousePosition();
		CDMCoord absolute = mouse.GetMousePosition(true);
		CDMPrintf(&ctx, 0, CDMRect{ 0,0,15,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"%d , %d", relative.X, relative.Y);
		CDMPrintf(&ctx, 0, CDMRect{ 0,1,15,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"%d , %d", absolute.X, absolute.Y);
		CDMDraw(&ctx);
		Sleep(16);
	}
	return 0;
}