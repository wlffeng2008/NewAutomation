#pragma once

#include "OutsideLoad.h"

class CSubDlgMain;
class COutloadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COutloadDlg)

public:
	COutloadDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~COutloadDlg();

	COutsideLoad *m_pLoader = nullptr;
	CSubDlgMain *m_pMain = nullptr;

	int OnSimpleThreadLoopRun(int nID);

	BOOL m_bSendAll = FALSE;
	CString m_strFile;
	CString &MakeScript(int nIndex = 0);

	void SaveLoadConfig(BOOL bToSave);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_OUTLOAD };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
