
#include "CDMTextInputWindow.h"
#include "CDMTextWindow.h"
#include "CDMMouseInputWindow.h"
#include "CDMMenuWindow.h"
#include "CDMButton.h"
#include <string>
#include <locale>
#include <codecvt>

#define WIDTH 180
#define HEIGHT 110
void SetupImage();
void DrawImage();
void SaveImage();

CDMSurface* image = nullptr;
CDMContext* ctx = nullptr;
CDMColorScheme scheme;
CDMColorSets currentSet = CDMColorSets::Set1;
std::wstring iName;
int imageWidth = 0;
int imageHeight = 0;

int main()
{
	ctx = CDMCreateContext(20, 20);
	CDMSetFontAndSize(&ctx, L"Terminal", 8, 8);
	CDMSetWindowTitle(L"CDM Image Editor");
	CDMChangeWindowSize(&ctx, WIDTH, HEIGHT);
	CDMActivateMouseInput(&ctx);
	SetupImage();
	DrawImage();
	SaveImage();
	return 0;
}

void LoadImageCallback(CDMButton& button, void* param)
{	
	if (iName == L"")
		return;
	memset(param, true, sizeof(bool));
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string converted_str = converter.to_bytes(iName);
	image = CDMReadImg((converted_str + std::string(".cdi")).data(), &scheme);
	imageHeight = image->rect.Bottom;
	imageWidth = image->rect.Right;
}

void EditCallback(CDMButton& button, void* param)
{
	if (iName == L"" || imageHeight == 0 || imageWidth == 0)
		return;
	memset(param, true, sizeof(bool));
	image = CDMCreateSurface((WIDTH / 2) - (imageWidth/2), (HEIGHT / 2) - (imageHeight/2), imageWidth, imageHeight);
	CDMSetCharacters(&image, L'C', L'D', L'G', L'I');
	CDMSetBackgroundColor(&image, CDMBackgroundColor::BWHITE, CDMBackgroundColor::BWHITE, CDMBackgroundColor::BWHITE, CDMBackgroundColor::BWHITE);
	CDMSetForegroundColor(&image, CDMLetterColor::BLACK, CDMLetterColor::BLACK, CDMLetterColor::BLACK, CDMLetterColor::BLACK);
}

void SetCallback(CDMButton& button, void* param)
{
	currentSet = *(CDMColorSets*)param;
}

void ForegroundCallback(CDMButton& button, void* param)
{
	switch (currentSet)
	{
	case Set1:
		image->pallete.p1.frontColor = *(CDMLetterColor*)param;
		break;
	case Set2:
		image->pallete.p2.frontColor = *(CDMLetterColor*)param;
		break;
	case Set3:
		image->pallete.p3.frontColor = *(CDMLetterColor*)param;
		break;
	case Set4:
		image->pallete.p4.frontColor = *(CDMLetterColor*)param;
		break;
	}
}

void BackgroundCallback(CDMButton& button, void* param)
{
	switch (currentSet)
	{
	case Set1:
		image->pallete.p1.backColor = *(CDMLetterColor*)param;
		break;
	case Set2:
		image->pallete.p2.backColor = *(CDMLetterColor*)param;
		break;
	case Set3:
		image->pallete.p3.backColor = *(CDMLetterColor*)param;
		break;
	case Set4:
		image->pallete.p4.backColor = *(CDMLetterColor*)param;
		break;
	}
}

void SaveCallback(CDMButton& button, void* param)
{
	memset(param, true, sizeof(bool));
	using convert_type = std::codecvt_utf8<wchar_t>;
	std::wstring_convert<convert_type, wchar_t> converter;
	std::string converted_str = converter.to_bytes(iName);
	CDMExportSrfcToImg(ctx, image, converted_str.data(), converted_str.size());
}

void SetupImage()
{
	bool endCycle = false;
	CDMButton loadImageButton(L"Load Image", LoadImageCallback, (void*)&endCycle);
	CDMButton parametersReady(L"Start editing", EditCallback, (void*)&endCycle);
	CDMTextInputWindow width(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMTextInputWindow height(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMTextInputWindow imageName(CDMKey::KeysEnd, CDMTextInput::InputType::Text);
	width.SetTitle(L"Image Width");
	width.posX = 15;
	width.posY = 15;
	width.SetupWindow(8, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	height.SetTitle(L"Image Height");
	height.posX = 15;
	height.posY = 21;
	height.SetupWindow(8, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	imageName.SetTitle(L"Image Name");
	imageName.posX = (WIDTH / 2) - 15;
	imageName.posY = (HEIGHT / 2) - 2;
	imageName.SetupWindow(30, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	loadImageButton.SetupWindow(12, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	loadImageButton.posX = WIDTH - 50;
	loadImageButton.posY = 10;
	parametersReady.SetupWindow(15, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	parametersReady.posX = (WIDTH / 2) - 7;
	parametersReady.posY = HEIGHT - 10;
	while (!(endCycle))
	{
		CDMPollEvents(ctx, &ctx->events);
		CDMKeepScreenSize(&ctx, &ctx->events);
		CDMClearScreen(&ctx);
		loadImageButton.Update(ctx);
		loadImageButton.Draw(ctx);
		parametersReady.Update(ctx);
		parametersReady.Draw(ctx);
		width.Update(ctx);
		width.Draw(ctx);
		height.Update(ctx);
		height.Draw(ctx);
		imageName.Update(ctx);
		imageName.Draw(ctx);
		iName = imageName.GetText();
		if(width.GetText().size() > 0)
			imageWidth = std::stoi(width.GetText());
		if(height.GetText().size() > 0)
			imageHeight = std::stoi(height.GetText());
		CDMDraw(&ctx);
		Sleep(16);
	}
}

void DrawImage()
{
#pragma region variable declaration
	bool endCycle = false;
	CDMColorSets set1 = Set1, set2 = Set2, set3 = Set3, set4 = Set4;
	CDMLetterColor l1 = LCOLOR1, l2 = LCOLOR2, l3 = LCOLOR3, l4 = LCOLOR4, l5 = LCOLOR5,
		l6 = LCOLOR6, l7 = LCOLOR7, l8 = LCOLOR8, l9 = LCOLOR9, l10 = LCOLOR10,
		l11 = LCOLOR11, l12 = LCOLOR12, l13 = LCOLOR13, l14 = LCOLOR14, l15 = LCOLOR15, l16 = LCOLOR16;
	CDMBackgroundColor b1 = BCOLOR1, b2 = BCOLOR2, b3 = BCOLOR3, b4 = BCOLOR4, b5 = BCOLOR5, b6 = BCOLOR6,
		b7 = BCOLOR7, b8 = BCOLOR8, b9 = BCOLOR9, b10 = BCOLOR10, b11 = BCOLOR11, b12 = BCOLOR12, b13 = BCOLOR13,
		b14 = BCOLOR14, b15 = BCOLOR15, b16 = BCOLOR16;
	CDMMouseInputWindow canvas;
	CDMButton set1B(L"1",SetCallback,(void*)&set1), set2B(L"2", SetCallback, (void*)&set2),
		set3B(L"3", SetCallback, (void*)&set3), set4B(L"4", SetCallback, (void*)&set4);
	CDMTextInputWindow	set1C(CDMKey::KeysEnd,CDMTextInput::InputType::Numeric), 
						set2C(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						set3C(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						set4C(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMTextInputWindow	rc1(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc2(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc3(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc4(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc5(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc6(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc7(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc8(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc9(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc10(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc11(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc12(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc13(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc14(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						rc15(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						rc16(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMTextInputWindow	gc1(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						gc2(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc3(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc4(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc5(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc6(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc7(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc8(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc9(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc10(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc11(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc12(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc13(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc14(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc15(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						gc16(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMTextInputWindow	bc1(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						bc2(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						bc3(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						bc4(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						bc5(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric),
						bc6(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc7(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc8(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc9(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc10(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc11(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc12(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc13(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc14(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc15(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric), 
						bc16(CDMKey::KeysEnd, CDMTextInput::InputType::Numeric);
	CDMButton	lcs1(L"L1",ForegroundCallback,(void*)&l1), 
				lcs2(L"L2", ForegroundCallback, (void*)&l2), 
				lcs3(L"L3", ForegroundCallback, (void*)&l3),
				lcs4(L"L4", ForegroundCallback, (void*)&l4), 
				lcs5(L"L5", ForegroundCallback, (void*)&l5),
				lcs6(L"L6", ForegroundCallback, (void*)&l6), 
				lcs7(L"L7", ForegroundCallback, (void*)&l7), 
				lcs8(L"L8", ForegroundCallback, (void*)&l8), 
				lcs9(L"L9", ForegroundCallback, (void*)&l9), 
				lcs10(L"L10", ForegroundCallback, (void*)&l10), 
				lcs11(L"L11", ForegroundCallback, (void*)&l11), 
				lcs12(L"L12", ForegroundCallback, (void*)&l12), 
				lcs13(L"L13", ForegroundCallback, (void*)&l13), 
				lcs14(L"L14", ForegroundCallback, (void*)&l14), 
				lcs15(L"L15", ForegroundCallback, (void*)&l15), 
				lcs16(L"L16", ForegroundCallback, (void*)&l16);
	CDMButton	bcs1(L"B1", BackgroundCallback, (void*)&b1),
				bcs2(L"B2", BackgroundCallback, (void*)&b2), 
				bcs3(L"B3", BackgroundCallback, (void*)&b3), 
				bcs4(L"B4", BackgroundCallback, (void*)&b4), 
				bcs5(L"B5", BackgroundCallback, (void*)&b5), 
				bcs6(L"B6", BackgroundCallback, (void*)&b6), 
				bcs7(L"B7", BackgroundCallback, (void*)&b7), 
				bcs8(L"B8", BackgroundCallback, (void*)&b8), 
				bcs9(L"B9", BackgroundCallback, (void*)&b9), 
				bcs10(L"B10", BackgroundCallback, (void*)&b10), 
				bcs11(L"B11", BackgroundCallback, (void*)&b11), 
				bcs12(L"B12", BackgroundCallback, (void*)&b12), 
				bcs13(L"B13", BackgroundCallback, (void*)&b13), 
				bcs14(L"B14", BackgroundCallback, (void*)&b14), 
				bcs15(L"B15", BackgroundCallback, (void*)&b15), 
				bcs16(L"B16", BackgroundCallback, (void*)&b16);
	CDMButton endDrawing(L"Exit and save", SaveCallback, (void*)&endCycle);
#pragma endregion

#pragma region setup
	set1B.posX = 10;
	set1B.posY = HEIGHT - 5;
	set1B.SetupWindow(3, 3, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	set2B.posX = 15;
	set2B.posY = HEIGHT - 5;
	set2B.SetupWindow(3, 3, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	set3B.posX = 20;
	set3B.posY = HEIGHT - 5;
	set3B.SetupWindow(3, 3, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	set4B.posX = 25;
	set4B.posY = HEIGHT - 5;
	set4B.SetupWindow(3, 3, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	CDMCoord relativeMousePos = { 0,0 };
	canvas.posX = (WIDTH / 2) - (imageWidth/2) - 1;
	canvas.posY = (HEIGHT / 2) - (imageHeight/2) - 1;
	canvas.ShouldDrag(false);
	canvas.SetTitle(iName);
	canvas.SetupWindow(imageWidth + 1, imageHeight + 1, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	set1C.posX = 10;
	set1C.posY = HEIGHT - 13;
	set1C.ShouldDrag(false);
	set1C.SetTitle(L"C1");
	set1C.SetupWindow(7, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	set1C.SetText(std::to_wstring(image->pallete.p1.character));

	set2C.posX = 17;
	set2C.posY = HEIGHT - 13;
	set2C.ShouldDrag(false);
	set2C.SetTitle(L"C2");
	set2C.SetupWindow(7, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	set2C.SetText(std::to_wstring(image->pallete.p2.character));

	set3C.posX = 24;
	set3C.posY = HEIGHT - 13;
	set3C.ShouldDrag(false);
	set3C.SetTitle(L"C3");
	set3C.SetupWindow(7, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	set3C.SetText(std::to_wstring(image->pallete.p3.character));

	set4C.posX = 31;
	set4C.posY = HEIGHT - 13;
	set4C.ShouldDrag(false);
	set4C.SetTitle(L"C4");
	set4C.SetupWindow(7, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	set4C.SetText(std::to_wstring(image->pallete.p4.character));

	rc1.posX = WIDTH - 17;
	rc1.posY = 10; 
	rc1.ShouldDrag(false); 
	rc1.SetTitle(L"r1"); 
	rc1.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK); 
	rc1.SetText(std::to_wstring(CDMGetR(&scheme, 0)));
	
	rc2.posX = WIDTH - 17;
	rc2.posY = 15;
	rc2.ShouldDrag(false);
	rc2.SetTitle(L"r2");
	rc2.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc2.SetText(std::to_wstring(CDMGetR(&scheme, 1)));

	rc3.posX = WIDTH - 17;
	rc3.posY = 20;
	rc3.ShouldDrag(false);
	rc3.SetTitle(L"r3");
	rc3.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc3.SetText(std::to_wstring(CDMGetR(&scheme, 2)));

	rc4.posX = WIDTH - 17;
	rc4.posY = 25;
	rc4.ShouldDrag(false);
	rc4.SetTitle(L"r4");
	rc4.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc4.SetText(std::to_wstring(CDMGetR(&scheme, 3)));

	rc5.posX = WIDTH - 17;
	rc5.posY = 30;
	rc5.ShouldDrag(false);
	rc5.SetTitle(L"r5");
	rc5.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc5.SetText(std::to_wstring(CDMGetR(&scheme, 4)));

	rc6.posX = WIDTH - 17;
	rc6.posY = 35;
	rc6.ShouldDrag(false);
	rc6.SetTitle(L"r6");
	rc6.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc6.SetText(std::to_wstring(CDMGetR(&scheme, 5)));

	rc7.posX = WIDTH - 17;
	rc7.posY = 40;
	rc7.ShouldDrag(false);
	rc7.SetTitle(L"r7");
	rc7.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc7.SetText(std::to_wstring(CDMGetR(&scheme, 6)));

	rc8.posX = WIDTH - 17;
	rc8.posY = 45;
	rc8.ShouldDrag(false);
	rc8.SetTitle(L"r8");
	rc8.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc8.SetText(std::to_wstring(CDMGetR(&scheme, 7)));

	rc9.posX = WIDTH - 17;
	rc9.posY = 50;
	rc9.ShouldDrag(false);
	rc9.SetTitle(L"r9");
	rc9.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc9.SetText(std::to_wstring(CDMGetR(&scheme, 8)));

	rc10.posX = WIDTH - 17;
	rc10.posY = 55;
	rc10.ShouldDrag(false);
	rc10.SetTitle(L"r10");
	rc10.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc10.SetText(std::to_wstring(CDMGetR(&scheme, 9)));

	rc11.posX = WIDTH - 17;
	rc11.posY = 60;
	rc11.ShouldDrag(false);
	rc11.SetTitle(L"r11");
	rc11.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc11.SetText(std::to_wstring(CDMGetR(&scheme, 10)));

	rc12.posX = WIDTH - 17;
	rc12.posY = 65;
	rc12.ShouldDrag(false);
	rc12.SetTitle(L"r12");
	rc12.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc12.SetText(std::to_wstring(CDMGetR(&scheme, 11)));

	rc13.posX = WIDTH - 17;
	rc13.posY = 70;
	rc13.ShouldDrag(false);
	rc13.SetTitle(L"r13");
	rc13.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc13.SetText(std::to_wstring(CDMGetR(&scheme, 12)));

	rc14.posX = WIDTH - 17;
	rc14.posY = 75;
	rc14.ShouldDrag(false);
	rc14.SetTitle(L"r14");
	rc14.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc14.SetText(std::to_wstring(CDMGetR(&scheme, 13)));

	rc15.posX = WIDTH - 17;
	rc15.posY = 80;
	rc15.ShouldDrag(false);
	rc15.SetTitle(L"r15");
	rc15.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc15.SetText(std::to_wstring(CDMGetR(&scheme, 14)));

	rc16.posX = WIDTH - 17;
	rc16.posY = 85;
	rc16.ShouldDrag(false);
	rc16.SetTitle(L"r16");
	rc16.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	rc16.SetText(std::to_wstring(CDMGetR(&scheme, 15)));

	gc1.posX = WIDTH - 12;
	gc1.posY = 10;
	gc1.ShouldDrag(false);
	gc1.SetTitle(L"g1");
	gc1.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc1.SetText(std::to_wstring(CDMGetG(&scheme, 0)));

	gc2.posX = WIDTH - 12;
	gc2.posY = 15;
	gc2.ShouldDrag(false);
	gc2.SetTitle(L"g2");
	gc2.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc2.SetText(std::to_wstring(CDMGetG(&scheme, 1)));

	gc3.posX = WIDTH - 12;
	gc3.posY = 20;
	gc3.ShouldDrag(false);
	gc3.SetTitle(L"g3");
	gc3.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc3.SetText(std::to_wstring(CDMGetG(&scheme, 2)));

	gc4.posX = WIDTH - 12;
	gc4.posY = 25;
	gc4.ShouldDrag(false);
	gc4.SetTitle(L"g4");
	gc4.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc4.SetText(std::to_wstring(CDMGetG(&scheme, 3)));

	gc5.posX = WIDTH - 12;
	gc5.posY = 30;
	gc5.ShouldDrag(false);
	gc5.SetTitle(L"g5");
	gc5.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc5.SetText(std::to_wstring(CDMGetG(&scheme, 4)));

	gc6.posX = WIDTH - 12;
	gc6.posY = 35;
	gc6.ShouldDrag(false);
	gc6.SetTitle(L"g6");
	gc6.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc6.SetText(std::to_wstring(CDMGetG(&scheme, 5)));

	gc7.posX = WIDTH - 12;
	gc7.posY = 40;
	gc7.ShouldDrag(false);
	gc7.SetTitle(L"g7");
	gc7.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc7.SetText(std::to_wstring(CDMGetG(&scheme, 6)));

	gc8.posX = WIDTH - 12;
	gc8.posY = 45;
	gc8.ShouldDrag(false);
	gc8.SetTitle(L"g8");
	gc8.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc8.SetText(std::to_wstring(CDMGetG(&scheme, 7)));

	gc9.posX = WIDTH - 12;
	gc9.posY = 50;
	gc9.ShouldDrag(false);
	gc9.SetTitle(L"g9");
	gc9.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc9.SetText(std::to_wstring(CDMGetG(&scheme, 8)));

	gc10.posX = WIDTH - 12;
	gc10.posY = 55;
	gc10.ShouldDrag(false);
	gc10.SetTitle(L"g10");
	gc10.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc10.SetText(std::to_wstring(CDMGetG(&scheme, 9)));

	gc11.posX = WIDTH - 12;
	gc11.posY = 60;
	gc11.ShouldDrag(false);
	gc11.SetTitle(L"g11");
	gc11.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc11.SetText(std::to_wstring(CDMGetG(&scheme, 10)));

	gc12.posX = WIDTH - 12;
	gc12.posY = 65;
	gc12.ShouldDrag(false);
	gc12.SetTitle(L"g12");
	gc12.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc12.SetText(std::to_wstring(CDMGetG(&scheme, 11)));

	gc13.posX = WIDTH - 12;
	gc13.posY = 70;
	gc13.ShouldDrag(false);
	gc13.SetTitle(L"g13");
	gc13.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc13.SetText(std::to_wstring(CDMGetG(&scheme, 12)));

	gc14.posX = WIDTH - 12;
	gc14.posY = 75;
	gc14.ShouldDrag(false);
	gc14.SetTitle(L"g14");
	gc14.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc14.SetText(std::to_wstring(CDMGetG(&scheme, 13)));
	
	gc15.posX = WIDTH - 12;
	gc15.posY = 80;
	gc15.ShouldDrag(false);
	gc15.SetTitle(L"g15");
	gc15.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc15.SetText(std::to_wstring(CDMGetG(&scheme, 14)));

	gc16.posX = WIDTH - 12;
	gc16.posY = 85;
	gc16.ShouldDrag(false);
	gc16.SetTitle(L"g16");
	gc16.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	gc16.SetText(std::to_wstring(CDMGetG(&scheme, 15)));

	bc1.posX = WIDTH - 7;
	bc1.posY = 10;
	bc1.ShouldDrag(false);
	bc1.SetTitle(L"b1");
	bc1.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc1.SetText(std::to_wstring(CDMGetB(&scheme, 0)));

	bc2.posX = WIDTH - 7;
	bc2.posY = 15;
	bc2.ShouldDrag(false);
	bc2.SetTitle(L"b2");
	bc2.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc2.SetText(std::to_wstring(CDMGetB(&scheme, 1)));

	bc3.posX = WIDTH - 7;
	bc3.posY = 20;
	bc3.ShouldDrag(false);
	bc3.SetTitle(L"b3");
	bc3.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc3.SetText(std::to_wstring(CDMGetB(&scheme, 2)));

	bc4.posX = WIDTH - 7;
	bc4.posY = 25;
	bc4.ShouldDrag(false);
	bc4.SetTitle(L"b4");
	bc4.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc4.SetText(std::to_wstring(CDMGetB(&scheme, 3)));

	bc5.posX = WIDTH - 7;
	bc5.posY = 30;
	bc5.ShouldDrag(false);
	bc5.SetTitle(L"b5");
	bc5.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc5.SetText(std::to_wstring(CDMGetB(&scheme, 4)));

	bc6.posX = WIDTH - 7;
	bc6.posY = 35;
	bc6.ShouldDrag(false);
	bc6.SetTitle(L"b6");
	bc6.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc6.SetText(std::to_wstring(CDMGetB(&scheme, 5)));

	bc7.posX = WIDTH - 7;
	bc7.posY = 40;
	bc7.ShouldDrag(false);
	bc7.SetTitle(L"b7");
	bc7.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc7.SetText(std::to_wstring(CDMGetB(&scheme, 6)));

	bc8.posX = WIDTH - 7;
	bc8.posY = 45;
	bc8.ShouldDrag(false);
	bc8.SetTitle(L"b8");
	bc8.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc8.SetText(std::to_wstring(CDMGetB(&scheme, 7)));

	bc9.posX = WIDTH - 7;
	bc9.posY = 50;
	bc9.ShouldDrag(false);
	bc9.SetTitle(L"b9");
	bc9.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc9.SetText(std::to_wstring(CDMGetB(&scheme, 8)));

	bc10.posX = WIDTH - 7;
	bc10.posY = 55;
	bc10.ShouldDrag(false);
	bc10.SetTitle(L"b10");
	bc10.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc10.SetText(std::to_wstring(CDMGetB(&scheme, 9)));

	bc11.posX = WIDTH - 7;
	bc11.posY = 60;
	bc11.ShouldDrag(false);
	bc11.SetTitle(L"b11");
	bc11.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc11.SetText(std::to_wstring(CDMGetB(&scheme, 10)));

	bc12.posX = WIDTH - 7;
	bc12.posY = 65;
	bc12.ShouldDrag(false);
	bc12.SetTitle(L"b12");
	bc12.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc12.SetText(std::to_wstring(CDMGetB(&scheme, 11)));

	bc13.posX = WIDTH - 7;
	bc13.posY = 70;
	bc13.ShouldDrag(false);
	bc13.SetTitle(L"b13");
	bc13.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc13.SetText(std::to_wstring(CDMGetB(&scheme, 12)));

	bc14.posX = WIDTH - 7;
	bc14.posY = 75;
	bc14.ShouldDrag(false);
	bc14.SetTitle(L"b14");
	bc14.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc14.SetText(std::to_wstring(CDMGetB(&scheme, 13)));

	bc15.posX = WIDTH - 7;
	bc15.posY = 80;
	bc15.ShouldDrag(false);
	bc15.SetTitle(L"b15");
	bc15.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc15.SetText(std::to_wstring(CDMGetB(&scheme, 14)));

	bc16.posX = WIDTH - 7;
	bc16.posY = 85;
	bc16.ShouldDrag(false);
	bc16.SetTitle(L"b16");
	bc16.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
	bc16.SetText(std::to_wstring(CDMGetB(&scheme, 15)));

	lcs1.posX = 1;
	lcs1.posY = 10;
	lcs1.SetTitle(L"LC1");
	lcs1.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs2.posX = 1;
	lcs2.posY = 15;
	lcs2.SetTitle(L"LC2");
	lcs2.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs3.posX = 1;
	lcs3.posY = 20;
	lcs3.SetTitle(L"LC3");
	lcs3.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs4.posX = 1;
	lcs4.posY = 25;
	lcs4.SetTitle(L"LC4");
	lcs4.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs5.posX = 1;
	lcs5.posY = 30;
	lcs5.SetTitle(L"LC5");
	lcs5.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs6.posX = 1;
	lcs6.posY = 35;
	lcs6.SetTitle(L"LC6");
	lcs6.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs7.posX = 1;
	lcs7.posY = 40;
	lcs7.SetTitle(L"LC7");
	lcs7.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs8.posX = 1;
	lcs8.posY = 45;
	lcs8.SetTitle(L"LC8");
	lcs8.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs9.posX = 1;
	lcs9.posY = 50;
	lcs9.SetTitle(L"LC9");
	lcs9.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs10.posX = 1;
	lcs10.posY = 55;
	lcs10.SetTitle(L"LC10");
	lcs10.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs11.posX = 1;
	lcs11.posY = 60;
	lcs11.SetTitle(L"LC11");
	lcs11.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs12.posX = 1;
	lcs12.posY = 65;
	lcs12.SetTitle(L"LC12");
	lcs12.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs13.posX = 1;
	lcs13.posY = 70;
	lcs13.SetTitle(L"LC13");
	lcs13.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs14.posX = 1;
	lcs14.posY = 75;
	lcs14.SetTitle(L"LC14");
	lcs14.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs15.posX = 1;
	lcs15.posY = 80;
	lcs15.SetTitle(L"LC15");
	lcs15.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	lcs16.posX = 1;
	lcs16.posY = 85;
	lcs16.SetTitle(L"LC16");
	lcs16.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs1.posX = 7;
	bcs1.posY = 10;
	bcs1.SetTitle(L"BC1");
	bcs1.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs2.posX = 7;
	bcs2.posY = 15;
	bcs2.SetTitle(L"BC2");
	bcs2.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs3.posX = 7;
	bcs3.posY = 20;
	bcs3.SetTitle(L"BC3");
	bcs3.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs4.posX = 7;
	bcs4.posY = 25;
	bcs4.SetTitle(L"BC4");
	bcs4.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs5.posX = 7;
	bcs5.posY = 30;
	bcs5.SetTitle(L"BC5");
	bcs5.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs6.posX = 7;
	bcs6.posY = 35;
	bcs6.SetTitle(L"BC6");
	bcs6.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs7.posX = 7;
	bcs7.posY = 40;
	bcs7.SetTitle(L"BC7");
	bcs7.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs8.posX = 7;
	bcs8.posY = 45;
	bcs8.SetTitle(L"BC8");
	bcs8.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs9.posX = 7;
	bcs9.posY = 50;
	bcs9.SetTitle(L"BC9");
	bcs9.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs10.posX = 7;
	bcs10.posY = 55;
	bcs10.SetTitle(L"BC10");
	bcs10.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs11.posX = 7;
	bcs11.posY = 60;
	bcs11.SetTitle(L"BC11");
	bcs11.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs12.posX = 7;
	bcs12.posY = 65;
	bcs12.SetTitle(L"BC12");
	bcs12.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs13.posX = 7;
	bcs13.posY = 70;
	bcs13.SetTitle(L"BC13");
	bcs13.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs14.posX = 7;
	bcs14.posY = 75;
	bcs14.SetTitle(L"BC14");
	bcs14.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs15.posX = 7;
	bcs15.posY = 80;
	bcs15.SetTitle(L"BC15");
	bcs15.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	bcs16.posX = 7;
	bcs16.posY = 85;
	bcs16.SetTitle(L"BC16");
	bcs16.SetupWindow(5, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);

	endDrawing.posX = (WIDTH / 2) - 8;
	endDrawing.posY = HEIGHT - 10;
	endDrawing.SetupWindow(15, 4, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK);
#pragma endregion

	while (!(endCycle))
	{
		CDMPollEvents(ctx, &ctx->events);
		CDMKeepScreenSize(&ctx, &ctx->events);
		CDMClearScreen(&ctx);
		canvas.Update(ctx);
		canvas.Draw(ctx);
		relativeMousePos = canvas.GetMousePosition();
		if (relativeMousePos.X >= -1 && relativeMousePos.Y >= -1 &&
			relativeMousePos.X + 1 < imageWidth && relativeMousePos.Y + 1 < imageHeight &&
			canvas.IsClicking(ctx))
			CDMSetPixel(&image, relativeMousePos.X + 1, relativeMousePos.Y + 1, currentSet);
		CDMPrepareSurface(&image);
		CDMAddSurfaceToContext(&ctx, image);

#pragma region Drawing and updating canvas items
		set1B.Update(ctx);
		set1B.Draw(ctx);

		set2B.Update(ctx);
		set2B.Draw(ctx);

		set3B.Update(ctx);
		set3B.Draw(ctx);

		set4B.Update(ctx);
		set4B.Draw(ctx);

		set1C.Update(ctx);
		set1C.Draw(ctx);

		set2C.Update(ctx);
		set2C.Draw(ctx);

		set3C.Update(ctx);
		set3C.Draw(ctx);

		set4C.Update(ctx);
		set4C.Draw(ctx);

		if (set1C.GetText().size() > 0)
			image->pallete.p1.character = std::stoi(set1C.GetText());
		if (set2C.GetText().size() > 0)
			image->pallete.p2.character = std::stoi(set2C.GetText());
		if (set3C.GetText().size() > 0)
			image->pallete.p3.character = std::stoi(set3C.GetText());
		if (set4C.GetText().size() > 0)
			image->pallete.p4.character = std::stoi(set4C.GetText());

		CDMPoke(&ctx, CDMCoord{ (SHORT)set1B.posX, (SHORT)set1B.posY - 2 },
			image->pallete.p1.character, (CDMLetterColor)image->pallete.p1.frontColor, (CDMBackgroundColor)image->pallete.p1.backColor);
		CDMPoke(&ctx, CDMCoord{ (SHORT)set2B.posX, (SHORT)set2B.posY - 2 },
			image->pallete.p2.character, (CDMLetterColor)image->pallete.p2.frontColor, (CDMBackgroundColor)image->pallete.p2.backColor);
		CDMPoke(&ctx, CDMCoord{ (SHORT)set3B.posX, (SHORT)set3B.posY - 2 },
			image->pallete.p3.character, (CDMLetterColor)image->pallete.p3.frontColor, (CDMBackgroundColor)image->pallete.p3.backColor);
		CDMPoke(&ctx, CDMCoord{ (SHORT)set4B.posX, (SHORT)set4B.posY - 2 },
			image->pallete.p4.character, (CDMLetterColor)image->pallete.p4.frontColor, (CDMBackgroundColor)image->pallete.p4.backColor);

		rc1.Update(ctx);
		rc1.Draw(ctx);

		rc2.Update(ctx);
		rc2.Draw(ctx);

		rc3.Update(ctx);
		rc3.Draw(ctx);

		rc4.Update(ctx);
		rc4.Draw(ctx);

		rc5.Update(ctx);
		rc5.Draw(ctx);

		rc6.Update(ctx);
		rc6.Draw(ctx);

		rc7.Update(ctx);
		rc7.Draw(ctx);

		rc8.Update(ctx);
		rc8.Draw(ctx);

		rc9.Update(ctx);
		rc9.Draw(ctx);

		rc10.Update(ctx);
		rc10.Draw(ctx);

		rc11.Update(ctx);
		rc11.Draw(ctx);

		rc12.Update(ctx);
		rc12.Draw(ctx);

		rc13.Update(ctx);
		rc13.Draw(ctx);

		rc14.Update(ctx);
		rc14.Draw(ctx);

		rc15.Update(ctx);
		rc15.Draw(ctx);

		rc16.Update(ctx);
		rc16.Draw(ctx);


		gc1.Update(ctx);
		gc1.Draw(ctx);

		gc2.Update(ctx);
		gc2.Draw(ctx);

		gc3.Update(ctx);
		gc3.Draw(ctx);

		gc4.Update(ctx);
		gc4.Draw(ctx);

		gc5.Update(ctx);
		gc5.Draw(ctx);

		gc6.Update(ctx);
		gc6.Draw(ctx);

		gc7.Update(ctx);
		gc7.Draw(ctx);

		gc8.Update(ctx);
		gc8.Draw(ctx);

		gc9.Update(ctx);
		gc9.Draw(ctx);

		gc10.Update(ctx);
		gc10.Draw(ctx);

		gc11.Update(ctx);
		gc11.Draw(ctx);

		gc12.Update(ctx);
		gc12.Draw(ctx);

		gc13.Update(ctx);
		gc13.Draw(ctx);

		gc14.Update(ctx);
		gc14.Draw(ctx);

		gc15.Update(ctx);
		gc15.Draw(ctx);

		gc16.Update(ctx);
		gc16.Draw(ctx);

		bc1.Update(ctx);
		bc1.Draw(ctx);

		bc2.Update(ctx);
		bc2.Draw(ctx);

		bc3.Update(ctx);
		bc3.Draw(ctx);

		bc4.Update(ctx);
		bc4.Draw(ctx);

		bc5.Update(ctx);
		bc5.Draw(ctx);

		bc6.Update(ctx);
		bc6.Draw(ctx);

		bc7.Update(ctx);
		bc7.Draw(ctx);

		bc8.Update(ctx);
		bc8.Draw(ctx);

		bc9.Update(ctx);
		bc9.Draw(ctx);

		bc10.Update(ctx);
		bc10.Draw(ctx);

		bc11.Update(ctx);
		bc11.Draw(ctx);

		bc12.Update(ctx);
		bc12.Draw(ctx);

		bc13.Update(ctx);
		bc13.Draw(ctx);

		bc14.Update(ctx);
		bc14.Draw(ctx);

		bc15.Update(ctx);
		bc15.Draw(ctx);

		bc16.Update(ctx);
		bc16.Draw(ctx);

		CDMPoke(&ctx, CDMCoord{ (SHORT)rc1.posX - 2, (SHORT)rc1.posY }, L' ', LCOLOR1, BCOLOR1);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc2.posX - 2, (SHORT)rc2.posY }, L' ', LCOLOR2, BCOLOR2);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc3.posX - 2, (SHORT)rc3.posY }, L' ', LCOLOR3, BCOLOR3);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc4.posX - 2, (SHORT)rc4.posY }, L' ', LCOLOR4, BCOLOR4);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc5.posX - 2, (SHORT)rc5.posY }, L' ', LCOLOR5, BCOLOR5);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc6.posX - 2, (SHORT)rc6.posY }, L' ', LCOLOR6, BCOLOR6);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc7.posX - 2, (SHORT)rc7.posY }, L' ', LCOLOR7, BCOLOR7);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc8.posX - 2, (SHORT)rc8.posY }, L' ', LCOLOR8, BCOLOR8);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc9.posX - 2, (SHORT)rc9.posY }, L' ', LCOLOR9, BCOLOR9);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc10.posX - 2, (SHORT)rc10.posY }, L' ', LCOLOR10, BCOLOR10);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc11.posX - 2, (SHORT)rc11.posY }, L' ', LCOLOR11, BCOLOR11);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc12.posX - 2, (SHORT)rc12.posY }, L' ', LCOLOR12, BCOLOR12);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc13.posX - 2, (SHORT)rc13.posY }, L' ', LCOLOR13, BCOLOR13);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc14.posX - 2, (SHORT)rc14.posY }, L' ', LCOLOR14, BCOLOR14);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc15.posX - 2, (SHORT)rc15.posY }, L' ', LCOLOR15, BCOLOR15);
		CDMPoke(&ctx, CDMCoord{ (SHORT)rc16.posX - 2, (SHORT)rc16.posY }, L' ', LCOLOR16, BCOLOR16);

		lcs1.Update(ctx);
		lcs1.Draw(ctx);

		lcs2.Update(ctx);
		lcs2.Draw(ctx);

		lcs3.Update(ctx);
		lcs3.Draw(ctx);

		lcs4.Update(ctx);
		lcs4.Draw(ctx);

		lcs5.Update(ctx);
		lcs5.Draw(ctx);

		lcs6.Update(ctx);
		lcs6.Draw(ctx);

		lcs7.Update(ctx);
		lcs7.Draw(ctx);

		lcs8.Update(ctx);
		lcs8.Draw(ctx);

		lcs9.Update(ctx);
		lcs9.Draw(ctx);

		lcs10.Update(ctx);
		lcs10.Draw(ctx);

		lcs11.Update(ctx);
		lcs11.Draw(ctx);

		lcs12.Update(ctx);
		lcs12.Draw(ctx);

		lcs13.Update(ctx);
		lcs13.Draw(ctx);

		lcs14.Update(ctx);
		lcs14.Draw(ctx);

		lcs15.Update(ctx);
		lcs15.Draw(ctx);

		lcs16.Update(ctx);
		lcs16.Draw(ctx);

		bcs1.Update(ctx);
		bcs1.Draw(ctx);

		bcs2.Update(ctx);
		bcs2.Draw(ctx);

		bcs3.Update(ctx);
		bcs3.Draw(ctx);

		bcs4.Update(ctx);
		bcs4.Draw(ctx);

		bcs5.Update(ctx);
		bcs5.Draw(ctx);

		bcs6.Update(ctx);
		bcs6.Draw(ctx);

		bcs7.Update(ctx);
		bcs7.Draw(ctx);

		bcs8.Update(ctx);
		bcs8.Draw(ctx);

		bcs9.Update(ctx);
		bcs9.Draw(ctx);

		bcs10.Update(ctx);
		bcs10.Draw(ctx);

		bcs11.Update(ctx);
		bcs11.Draw(ctx);

		bcs12.Update(ctx);
		bcs12.Draw(ctx);

		bcs13.Update(ctx);
		bcs13.Draw(ctx);

		bcs14.Update(ctx);
		bcs14.Draw(ctx);

		bcs15.Update(ctx);
		bcs15.Draw(ctx);

		bcs16.Update(ctx);
		bcs16.Draw(ctx);

		endDrawing.Update(ctx);
		endDrawing.Draw(ctx);

		CDMPrintf(&ctx, 0, CDMRect{ (SHORT)bcs1.posX + 7, (SHORT)bcs1.posY, 15, 1 }, CDMLetterColor::WHITE, CDMBackgroundColor::BBLACK,
			L"Current set: %d", currentSet == Set1 ? 1 : currentSet == Set2 ? 2 : currentSet == Set3 ? 3 : 4);
#pragma endregion

		CDMDraw(&ctx);
		Sleep(16);
	}
}

void SaveImage()
{
}
