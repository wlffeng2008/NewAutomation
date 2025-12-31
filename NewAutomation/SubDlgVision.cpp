// SubDlgVision.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgVision.h"
#include "afxdialogex.h"


// CSubDlgVision dialog

IMPLEMENT_DYNAMIC(CSubDlgVision, CDialogEx)

CSubDlgVision::CSubDlgVision(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_VISION, pParent)
{

}

CSubDlgVision::~CSubDlgVision()
{
}

void CSubDlgVision::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgVision, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


BOOL CSubDlgVision::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(255, 255, 255));

	return TRUE;
}

BOOL CSubDlgVision::OnCommand(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
	default:
		break;
	}

	return CDialogEx::OnCommand(wParam, lParam);
}


void CSubDlgVision::OnPaint()
{
	CPaintDC dc(this);

	CRect rc;
	GetClientRect(&rc);

	DrawDialog(&dc);
}


