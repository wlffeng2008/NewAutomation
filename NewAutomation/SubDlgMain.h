#pragma once


// CSubDlgMain dialog

class CSubDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgMain)

public:
	CSubDlgMain(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgMain();

	void SaveLoadSetting(BOOL bToSave = false);
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
};
