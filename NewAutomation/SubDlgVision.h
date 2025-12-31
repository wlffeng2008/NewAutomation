#pragma once


// CSubDlgVision dialog

class CSubDlgVision : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgVision)

public:
	CSubDlgVision(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgVision();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_VISION };
#endif

protected:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
