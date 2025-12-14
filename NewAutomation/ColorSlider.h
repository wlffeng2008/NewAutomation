#pragma once


#include <gdiplus.h>
using namespace Gdiplus;

Gdiplus::Color RGB2Color(COLORREF rgb,BYTE alpha=255);
Gdiplus::Rect  Rect2RectF(CRect rect);


class CColorSlider : public CMySliderCtrl
{
	DECLARE_DYNAMIC(CColorSlider)

public:
	CColorSlider();
	virtual ~CColorSlider();

	void SetColor(COLORREF clrBK, COLORREF clrPG0, COLORREF clrPG1, COLORREF clrTH0, COLORREF clrTH1=0xFFFFFF);
	COLORREF m_clrTH1= 0xFFFFFF;

	COLORREF m_clrBK = RGB(192, 192, 192);
	COLORREF m_clrPG = 0xBADFFD;// 
	COLORREF m_clrPG1 = 0x3CA7FF;
	COLORREF m_clrTH = 0x3CA7FF;

protected:
	afx_msg void OnPaint();
protected:
	DECLARE_MESSAGE_MAP()
};


