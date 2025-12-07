
// NewAutomationDlg.h : header file
//

#pragma once


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "Automation1.h"

// CNewAutomationDlg dialog
class CNewAutomationDlg : public CDialogEx
{
// Construction
public:
	CNewAutomationDlg(CWnd* pParent = NULL);	// standard constructor

	void SaveLoadSetting(BOOL bToSave=false);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NEWAUTOMATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
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

public:
	afx_msg void OnBnClickedButtonJogx2();
};
