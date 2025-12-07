// SubDlgCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgCalibration.h"
#include "afxdialogex.h"


// CSubDlgCalibration dialog

IMPLEMENT_DYNAMIC(CSubDlgCalibration, CDialogEx)

CSubDlgCalibration::CSubDlgCalibration(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_CALIBRATION, pParent)
{

}

CSubDlgCalibration::~CSubDlgCalibration()
{
}

void CSubDlgCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgCalibration, CDialogEx)
END_MESSAGE_MAP()


// CSubDlgCalibration message handlers
BOOL CSubDlgCalibration::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 200, 200));
	return TRUE;
}