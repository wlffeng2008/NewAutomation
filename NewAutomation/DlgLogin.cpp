// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "DlgLogin.h"
#include "afxdialogex.h"


// CDlgLogin dialog

IMPLEMENT_DYNAMIC(CDlgLogin, CDialogEx)

CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DIALOG, pParent)
{

}

CDlgLogin::~CDlgLogin()
{
}

void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialogEx)
END_MESSAGE_MAP()


// CDlgLogin message handlers
