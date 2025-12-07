#pragma once


// CSubDlgCalibration dialog

class CSubDlgCalibration : public CDialogEx
{
	DECLARE_DYNAMIC(CSubDlgCalibration)

public:
	CSubDlgCalibration(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSubDlgCalibration();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CALIBRATION };
#endif

protected:
	BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
