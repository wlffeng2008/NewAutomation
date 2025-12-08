
// NewAutomationDlg.h : header file
//

#pragma once


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#include "SubDlgMain.h"
#include "SubDlgMaterial.h"
#include "SubDlgProduct.h"
#include "SubDlgVision.h"
#include "SubDlgCalibration.h"
#include "SubDlgConfig.h"
#include "SubDlgWorkinfo.h"

// CNewAutomationDlg dialog
class CNewAutomationDlg : public CDialogEx
{
// Construction
public:
	CNewAutomationDlg(CWnd* pParent = NULL);	// standard constructor

	CSubDlgMain *m_pDlgMn = nullptr;
	CSubDlgMaterial *m_pDlgMt = nullptr;
	CSubDlgProduct *m_pDlgPr= nullptr;
	CSubDlgVision *m_pDlgVi = nullptr;
	CSubDlgCalibration *m_pDlgCl = nullptr;
	CSubDlgConfig *m_pDlgCf = nullptr;
	CSubDlgWorkinfo *m_pDlgWi = nullptr;

	void ShowSubDlg(int nIndex=0);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWAUTOMATION_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void OnTimer(UINT_PTR nIDEvent);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

};
