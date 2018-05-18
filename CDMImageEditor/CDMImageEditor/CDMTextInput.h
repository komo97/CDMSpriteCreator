#pragma once
#include "CDM.h"
#include <string>

class CDMTextInput
{
public:
	enum InputType
	{
		Text = 0x001,
		Numeric = 0x002,
		AlphaNum = 0x003,
		AcceptNewline = 0x010,
	}inputType;
	CDMTextInput() = delete;
	CDMTextInput(const CDMKey& closeKey, const size_t& maxInput, const InputType& type);
	void ReadInput(CDMEvent* const& events);
	void SetActive(const bool& status);
	void DisplayText(CDMContext *& ctx, const CDMRect& displayArea, CDMLetterColor let, CDMBackgroundColor bg);
	bool IsActive() const;
	std::wstring GetText() const;
	~CDMTextInput();
private:
	bool _isActive,
		 _caps;
	std::wstring _text;
	size_t	_maxInput,
			_cursor;
	CDMKey _closeKey;
	bool _blink;
};

