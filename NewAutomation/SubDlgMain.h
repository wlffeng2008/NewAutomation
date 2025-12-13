#pragma once


// CSubDlgMain dialog
#include "DlgPSOEdit.h"

class CSubDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgMain)

public:
	CSubDlgMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgMain();

	void SaveLoadSetting(BOOL bToSave = false);
	double m_dbXPos = 0;
	double m_dbYPos = 0;

	CDlgPSOEdit *m_pDlgPSO=nullptr;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MAIN };
#endif

protected:
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	virtual void OnTimer(UINT_PTR nIDEvent);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
};
