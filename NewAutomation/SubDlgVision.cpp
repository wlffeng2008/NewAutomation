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
END_MESSAGE_MAP()


// CSubDlgVision message handlers
BOOL CSubDlgVision::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 200, 100));
	return TRUE;
}