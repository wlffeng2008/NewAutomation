// SubDlgWorkinfo.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgWorkinfo.h"
#include "afxdialogex.h"


// CSubDlgWorkinfo dialog

IMPLEMENT_DYNAMIC(CSubDlgWorkinfo, CDialogEx)

CSubDlgWorkinfo::CSubDlgWorkinfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_WORKINFO, pParent)
{

}

CSubDlgWorkinfo::~CSubDlgWorkinfo()
{
}

void CSubDlgWorkinfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgWorkinfo, CDialogEx)
END_MESSAGE_MAP()


// CSubDlgWorkinfo message handlers
BOOL CSubDlgWorkinfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 250, 0));
	return TRUE;
}