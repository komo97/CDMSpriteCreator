#include "CDMTextInputWindow.h"


CDMTextInputWindow::CDMTextInputWindow(const CDMKey & closeKey, const CDMTextInput::InputType& type) : CDMWindow()
{
	_closeKey = closeKey;
	_type = type;
}

void CDMTextInputWindow::Update(CDMContext* & ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Update(ctx);
	if (CDMGetKeyUp(&ctx->events, _closeKey))
		SetActive(false);
}

void CDMTextInputWindow::Draw(CDMContext *& ctx)
{
	if (!_isActive)
		return;
	CDMWindow::Draw(ctx);
	_inputArea->ReadInput(&ctx->events);
	_inputArea->DisplayText(ctx, CDMRect{ (SHORT)posX + 2, (SHORT)posY + 2, (SHORT)_width - 2, (SHORT)_height - 2 }, _bounds, _background);
}

CDMTextInputWindow::~CDMTextInputWindow()
{
	if (_inputArea)
		delete _inputArea;
}

void CDMTextInputWindow::PostSetup()
{
	_inputArea = new CDMTextInput(_closeKey, (_width - 2) * (_height - 3), _type);
}
