#include "ColorWell1.h"

ColorWell::ColorWell(BRect frame, const char *name, BMessage *message,
	int32 resize, int32 flags, int32 style)
	: BControl(frame, name, NULL, message, resize, flags)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
	SetLowColor(0,0,0);
	
	fColor.red = 0;
	fColor.green = 0;
	fColor.blue = 0;
	fColor.alpha = 255;
	
	fDisabledColor.red = 190;
	fDisabledColor.green = 190;
	fDisabledColor.blue = 190;
	fDisabledColor.alpha = 255;
}

ColorWell::~ColorWell(void)
{
}

void ColorWell::SetValue(int32 value)
{
	BControl::SetValue(value);
	
	fColor.red = (value & 0xFF000000) >> 24;
	fColor.green = (value & 0x00FF0000) >> 16;
	fColor.blue = (value & 0x0000FF00) >> 8;
	fColor.alpha = 255;
	
	SetHighColor(fColor);
	Draw(Bounds());
}

void ColorWell::SetValue(const rgb_color &col)
{
	fColor = col;
	fColor.alpha = 255;
	
	BControl::SetValue((fColor.red << 24) + (fColor.green << 16) +
		(fColor.blue << 8) + 255);
	SetHighColor(col);
	Draw(Bounds());
}

void ColorWell::SetValue(const uint8 &r, const uint8 &g, const uint &b)
{
	fColor.red = r;
	fColor.green = g;
	fColor.blue = b;
	fColor.alpha = 255;
	
	BControl::SetValue((fColor.red << 24) + (fColor.green << 16) +
		(fColor.blue << 8) + 255);
	SetHighColor(r,g,b);
	Draw(Bounds());
}

void ColorWell::SetStyle(const int32 &style)
{
	if (style != fStyle)
	{
		fStyle = style;
		Invalidate();
	}
}

int32 ColorWell::Style(void) const
{
	return fStyle;
}

void ColorWell::Draw(BRect update)
{
	if (fStyle == COLORWELL_SQUARE_WELL)
		DrawSquare();
	else
		DrawRound();
}

rgb_color ColorWell::ValueAsColor(void) const
{
	return fColor;
}

void ColorWell::DrawRound(void)
{
	if (IsEnabled())
		SetHighColor(fColor);
	else
		SetHighColor(fDisabledColor);
		
	FillEllipse(Bounds());
	
	SetHighColor(0,0,0);
	StrokeEllipse(Bounds());
}

void ColorWell::DrawSquare(void)
{
	if (IsEnabled())
		SetHighColor(fColor);
	else
		SetHighColor(fDisabledColor);
	
	FillRect(Bounds());
	
	SetHighColor(0,0,0);
	StrokeRect(Bounds());
}
