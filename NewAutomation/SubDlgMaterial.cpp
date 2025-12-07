// SubDlgMaterial.cpp : implementation file
//

#include "stdafx.h"
#include "NewAutomation.h"
#include "SubDlgMaterial.h"
#include "afxdialogex.h"


// CSubDlgMaterial dialog

IMPLEMENT_DYNAMIC(CSubDlgMaterial, CDialogEx)

CSubDlgMaterial::CSubDlgMaterial(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_MATERIAL, pParent)
{

}

CSubDlgMaterial::~CSubDlgMaterial()
{
}

void CSubDlgMaterial::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSubDlgMaterial, CDialogEx)
END_MESSAGE_MAP()


// CSubDlgMaterial message handlers

BOOL CSubDlgMaterial::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	SetDlgBKColor(RGB(0, 100, 0));
	return TRUE;
}