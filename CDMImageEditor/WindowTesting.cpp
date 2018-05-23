
#include "CDMTextInputWindow.h"
#include "CDMTextWindow.h"
#include "CDMMouseInputWindow.h"
#include "CDMMenuWindow.h"
#include "CDMButton.h"

void testFunc(CDMMenuWindow& callingWindow, void** parameter)
{
	callingWindow.SetActive(false);
}

void buttonFunc(CDMButton& button, void** parameter)
{
	CDMPrintf((CDMContext**)parameter, 0, CDMRect{ 100,79,2,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"%d", 3 + 7);
}

int main()
{
	CDMContext* ctx = CDMCreateContext(1, 1);
	CDMSetWindowTitle(L"Image Editor");
	CDMSetFontAndSize(&ctx, L"Terminal", 8, 8);
	CDMChangeWindowSize(&ctx, 150, 80);
	CDMActivateMouseInput(&ctx);
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
	CDMMenuWindow menu(CDMKey::up, CDMKey::down, CDMKey::esc, CDMKey::returnK);
	CDMButton button(L"Testerino", buttonFunc, (void**)&ctx);
	button.posX = 70;
	button.posY = 0;
	button.SetupWindow(15, 5, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	menu.SetTitle(L"Menu Window");
	menu.SetupWindow(10, 15, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	menu.posX = 25;
	menu.posY = 25;
	menu.AddItem(L"Testerino malabrino 1", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 2", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 3", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 4", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 5", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 6", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 7", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 8", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 9", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 10", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 11", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 12", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 13", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 14", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 15", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 16", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 17", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 18", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 19", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 20", testFunc, nullptr);
	menu.AddItem(L"Testerino malabrino 21", testFunc, nullptr);
	menu.cursorType = CDMMenuWindow::CursorType::arrow;
	while (true)
	{
		CDMPollEvents(ctx, &ctx->events);
		CDMKeepScreenSize(&ctx, &ctx->events);
		CDMClearScreen(&ctx);
		menu.Update(ctx);
		menu.Draw(ctx);
		button.Update(ctx);
		button.Draw(ctx);
		window.Update(ctx);
		window.Draw(ctx);
		text.Update(ctx);
		text.Draw(ctx);
		mouse.Update(ctx);
		mouse.Draw(ctx);
		CDMCoord relative = mouse.GetMousePosition();
		CDMCoord absolute = mouse.GetMousePosition(true);
		CDMPrintf(&ctx, 0, CDMRect{ 0,0,40,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"Mouse position relative: %d , %d", relative.X, relative.Y);
		CDMPrintf(&ctx, 0, CDMRect{ 0,1,40,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"Mouse position absolute: %d , %d", absolute.X, absolute.Y);
		CDMPrintf(&ctx, 0, { 0,0,15,1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK, L"%d", CDMGetKeyPressed(&ctx->events, CDMKey::mbleft));
		CDMDraw(&ctx);
		Sleep(16);
	}
	return 0;
}