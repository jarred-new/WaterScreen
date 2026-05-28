
// WaterScreenDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "PreHeaderTab.h"

#define IDC_STATUSBAR 1001

class CTextTab;
class CImageTab;
class CDisplayTab;

// CWaterScreenDlg dialog
class CWaterScreenDlg : public CDialogEx
{
// Construction
public:
	CWaterScreenDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_WATERSCREEN_DIALOG };

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
	CTabCtrl m_tabCtrl;
	int cp; // current page
	CTextTab* m_textTab;
	CImageTab* m_imageTab;
	CDisplayTab* m_displayTab;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL DestroyWindow();
//	afx_msg void OnSizing(UINT fwSide, LPRECT pRect);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void CopyValuesFromTextToDisplay();
	void CopyValuesFromImageToDisplay();
	void SetStatusBarText(CString pane1Text, CString pane2Text);

	CStatusBarCtrl m_statusBarCtrl;
	static const int m_nNumPanes = 2;

private:
	bool isTabInit = false;
	//void resize();
};
