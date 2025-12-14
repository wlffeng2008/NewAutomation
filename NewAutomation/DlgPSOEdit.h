#pragma once

// CDlgPSOEdit dialog
class CSubDlgMain;
class CDlgPSOEdit : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPSOEdit)

public:
	CDlgPSOEdit(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlgPSOEdit();
	CMyListCtrl *m_pList = nullptr;
	CSubDlgMain *m_pMain = nullptr;
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PSOSCRIPT };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
