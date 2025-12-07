#pragma once


// CSubDlgWorkinfo dialog

class CSubDlgWorkinfo : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgWorkinfo)

public:
	CSubDlgWorkinfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgWorkinfo();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORKINFO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
