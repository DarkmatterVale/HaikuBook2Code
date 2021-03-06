#ifndef COLOR_WELL_H
#define COLOR_WELL_H


#include <Control.h>


enum
{
	COLORWELL_SQUARE_WELL,
	COLORWELL_ROUND_WELL,
};


class ColorWell : public BControl
{
	public:
		ColorWell(BRect frame, const char *name, BMessage *msg,
			int32 resize = B_FOLLOW_LEFT | B_FOLLOW_TOP,
			int32 flags = B_WILL_DRAW,
			int32 style = COLORWELL_SQUARE_WELL);
		~ColorWell(void);
		
		virtual void SetValue(int32 value);
		virtual void SetValue(const rgb_color &color);
		virtual void SetValue(const uint8 &r, const uint8 &g,
			const uint &b);
		rgb_color ValueAsColor(void) const;
		virtual void SetStyle(const int32 &style);
		int32 Style(void) const;
		virtual void Draw(BRect update);
	private:
		void DrawRound(void);
		void DrawSquare(void);
		
		rgb_color fDisabledColor, fColor;
		int32 fStyle;
};


#endif
