#pragma once


// CSubDlgWorkinfo dialog

class CSubDlgWorkinfo : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgWorkinfo)

public:
	CSubDlgWorkinfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgWorkinfo();
	float m_data[1920];
	void DrawCurv(const float *data,int nCount=480);
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_WORKINFO };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
};
