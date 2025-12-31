// SubDlgWorkinfo.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgWorkinfo.h"
#include "afxdialogex.h"


CSubDlgWorkinfo *pWDlg = nullptr;

// CSubDlgWorkinfo dialog

IMPLEMENT_DYNAMIC(CSubDlgWorkinfo, CDialogEx)

CSubDlgWorkinfo::CSubDlgWorkinfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_WORKINFO, pParent)
{
	pWDlg = this;
}

CSubDlgWorkinfo::~CSubDlgWorkinfo()
{
}

void CSubDlgWorkinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgWorkinfo, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

void CSubDlgWorkinfo::DrawCurv(const float *data, int nCount)
{
	for (int i = 0; i < 960; i++)
	{
		m_data[i] = data[i];
	}
	RedrawWindow();
}

void CSubDlgWorkinfo::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetClientRect(rc);
	int nW = rc.Width();
	int nH = rc.Height();

	Gdiplus::Bitmap bmp(nW, nH, PixelFormat32bppARGB);
	Gdiplus::Graphics graphics(&bmp);
	graphics.Clear(Color(255, 255, 255, 255));
	graphics.SetSmoothingMode(Gdiplus::SmoothingModeHighQuality);

	SolidBrush br(Color::Aqua);
	graphics.FillRectangle(&br,Rect(0, nH / 2 - 200, nW, 400));

	Pen pen1(Color(255, 0, 0), 1);
	Pen pen2(Color(0, 0, 255), 1);
	float xStep = nW*1.0 / 480; 
	int x0 = 0;
	int y0 = m_data[0] * 200 + nH / 2;
	int y2 = m_data[1] * 200 + nH / 2;

	for (int i = 1; i < 960; i+=2)
	{
		int x1 = i*xStep;
		int y1 = m_data[i+0] * 200 + nH / 2;
		int y3 = m_data[i+1] * 200 + nH / 2;
		graphics.DrawLine(&pen1, x0, y0, x1, y1);
		graphics.DrawLine(&pen2, x0, y2, x1, y3);

		x0 = x1;
		y0 = y1;
		y2 = y3;
	}

	Pen pen(Color(0,255,0), 2);
	graphics.DrawLine(&pen,0,nH/2,nW,nH/2);

	Gdiplus::Graphics Out(dc.GetSafeHdc());
	//Out.Clear(Color(255, 255, 255));
	Out.DrawImage(&bmp,0, 0);
}

// CSubDlgWorkinfo message handlers
BOOL CSubDlgWorkinfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 250, 0));
	return TRUE;
}