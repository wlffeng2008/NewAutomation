// CubDlgConfig.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgConfig.h"
#include "afxdialogex.h"


// CubDlgConfig dialog

IMPLEMENT_DYNAMIC(CSubDlgConfig, CDialogEx)

CSubDlgConfig::CSubDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CONFIG, pParent)
{

}

CSubDlgConfig::~CSubDlgConfig()
{
}

void CSubDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgConfig, CDialogEx)
END_MESSAGE_MAP()


// CubDlgConfig message handlers
BOOL CSubDlgConfig::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 200, 0));
	return TRUE;
}