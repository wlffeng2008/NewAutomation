// ColorSlider.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "ColorSlider.h"
using namespace Gdiplus;
// CColorSlider

Gdiplus::Color RGB2Color(COLORREF rgb, BYTE alpha)
{
	return Gdiplus::Color(alpha,rgb&0x0000FF, (rgb&0x00FF00)>>8,(rgb&0xFF0000)>>16);
}

Gdiplus::Rect  Rect2RectF(CRect rect)
{
	return Gdiplus::Rect(rect.left, rect.top, rect.Width(), rect.Height());
}


IMPLEMENT_DYNAMIC(CColorSlider, CMySliderCtrl)

CColorSlider::CColorSlider()
{
	m_clrBK = RGB(192, 192, 192);
	m_clrPG = 0xBADFFD;// 
	m_clrPG1 = 0x3CA7FF;
	m_clrTH = 0x3CA7FF;
	m_clrTH1 = RGB(255,255,255);
}

CColorSlider::~CColorSlider()
{
}


BEGIN_MESSAGE_MAP(CColorSlider, CMySliderCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CColorSlider::SetColor(COLORREF clrBK, COLORREF clrPG0, COLORREF clrPG1, COLORREF clrTH0, COLORREF clrTH1)
{
	if (clrBK != ~0) m_clrBK = clrBK;
	if (clrPG0 != ~0) m_clrPG = clrPG0;
	if (clrPG1 != ~0) m_clrPG1 = clrPG1;
	if (clrTH0 != ~0) m_clrTH = clrTH0;
	if (clrTH1 != ~0) m_clrTH1 = clrTH1;
}

// CColorSlider message handlers

void CColorSlider::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);

	int nW = rc.Width();
	int nH = rc.Height();

	BOOL bHMode = nW > nH;

	int nBarH = 10;

	if (nBarH>nH)
		nBarH = nH;

	if (bHMode)
		rc.InflateRect(-nBarH, 0, -nBarH, 0);
	else
		rc.InflateRect(0, -nBarH, 0, -nBarH);

	CRect rcBkBar(rc);
	if (bHMode)
	{
		rcBkBar.top += (nH - nBarH) / 2 -1;
		rcBkBar.bottom = rcBkBar.top + nBarH +1;
	}
	else
	{
		rcBkBar.left += (nW - nBarH) / 2 - 1;
		rcBkBar.right = rcBkBar.left + nBarH + 1;
	}

	CRgn clipRgn;
	clipRgn.CreateRoundRectRgn(rcBkBar.left, rcBkBar.top, rcBkBar.right, rcBkBar.bottom, 7, 7); 

	Gdiplus::Bitmap bmp(nW, nH, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(&bmp);
	graphics.Clear(Color(0, 0, 0, 0));
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	graphics.SetClip((HRGN)clipRgn.GetSafeHandle());
	Gdiplus::SolidBrush br(RGB2Color(m_clrBK));
	graphics.FillRectangle(&br, Rect2RectF(rcBkBar));

	{
		CRect rcPgBar(rcBkBar);
		int nMin = 0;
		int nMax = 0;
		GetRange(nMin, nMax);
		if (nMax == nMin)
			nMax++;
		int nCurPos = CSliderCtrl::GetPos();
		rcPgBar.left--;
		if (bHMode)
			rcPgBar.right = rcPgBar.left + nCurPos * rc.Width() / (nMax - nMin);
		else
			rcPgBar.top = rcPgBar.top + nCurPos * rc.Height() / (nMax - nMin);

		rcPgBar.top --;
		rcPgBar.bottom ++;
		if (bHMode)
		{
			Gdiplus::LinearGradientBrush brPg(Rect2RectF(rcPgBar), RGB2Color(m_clrPG), RGB2Color(m_clrPG1), Gdiplus::LinearGradientModeHorizontal);
			graphics.FillRectangle(&brPg, Rect2RectF(rcPgBar));
		}
		else
		{
			Gdiplus::LinearGradientBrush brPg(Rect2RectF(rcPgBar), RGB2Color(m_clrPG1), RGB2Color(m_clrPG), Gdiplus::LinearGradientModeVertical);
			graphics.FillRectangle(&brPg,Rect2RectF(rcPgBar));
		}
	}

	GetClientRect(&rc);
	CRgn All;
	All.CreateRectRgn(0, 0, rc.right+5, rc.bottom+5);
	graphics.SetClip((HRGN)All.GetSafeHandle());

	{
		int nRD = nBarH;

		CRect rcThumb;
		GetThumbRect(&rcThumb); //得到滑块的位置
		CPoint pt = rcThumb.CenterPoint();
		CRect rcRnd(pt.x - nRD, rc.Height()/2 - nRD, pt.x + nRD, rc.Height() / 2 + nRD);

		if (bHMode)
		{
			rcRnd.top -= 1;
			rcRnd.bottom -= 1;
		}
		else
		{
			rcRnd = CRect(rc.Width() / 2 - nRD, pt.y - nRD, rc.Width() / 2 + nRD, pt.y + nRD);
			rcRnd.left-=2;
			rcRnd.right-=2;
		}

		Rect rcTh=Rect2RectF(rcRnd);

		Gdiplus::SolidBrush brTh(RGB2Color(m_clrTH1));
		graphics.FillEllipse(&brTh, rcTh);
		Pen pen(RGB2Color(m_clrTH), 2);
		graphics.DrawEllipse(&pen, rcTh);
	}

	{
		Gdiplus::Graphics graphics(dc.GetSafeHdc());
		graphics.DrawImage(&bmp, 0, 0);
	}
	All.DeleteObject();
	clipRgn.DeleteObject();
}
