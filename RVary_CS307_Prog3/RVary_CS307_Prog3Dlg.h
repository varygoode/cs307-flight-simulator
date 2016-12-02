
// RVary_CS307_Prog3Dlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "Simulation.h"


// CRVary_CS307_Prog3Dlg dialog
class CRVary_CS307_Prog3Dlg : public CDialogEx
{
// Construction
public:
	CRVary_CS307_Prog3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RVARY_CS307_PROG3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	afx_msg void OnBnClickedRunsim();
	afx_msg void OnBnClickedEndsim();
	afx_msg void OnCbnSelchangeSpeed();
	CComboBox m_SimSpeed;
	afx_msg void OnTimer (UINT TimerVal);
	int m_dSimTimeMin;
	int m_dSimTimeHr;
	int m_dReportTime;
	Simulation *sim;
private:
	int m_iWinWidth;
	int m_iWinHeight;
public:
	CEdit m_SimDataFileTF;
	CButton m_EndSimButton;
	CButton m_RunSimButton;
	CBitmap m_MapBitmap;
	CDC m_DCMemory;
	CRect m_MapRect;
	CEdit m_cityDataFile;
	CEdit m_flightDataFile;
};
