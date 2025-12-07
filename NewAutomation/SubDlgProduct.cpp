// SubDlgProduct.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgProduct.h"
#include "afxdialogex.h"


// CSubDlgProduct dialog

IMPLEMENT_DYNAMIC(CSubDlgProduct, CDialogEx)

CSubDlgProduct::CSubDlgProduct(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_PRODUCT, pParent)
{

}

CSubDlgProduct::~CSubDlgProduct()
{
}

void CSubDlgProduct::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgProduct, CDialogEx)
END_MESSAGE_MAP()


// CSubDlgProduct message handlers
BOOL CSubDlgProduct::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 150, 0));
	return TRUE;
}