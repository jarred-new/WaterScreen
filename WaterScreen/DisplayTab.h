#pragma once
#include "afxwin.h"
#include "PreHeaderTab.h"
#include "WaterScreenDlg.h"
#include <shlwapi.h>
#include "afxcolorbutton.h"
#pragma comment(lib, "shlwapi.lib")
#define TIMER_HIDE_TIMER 101

class CWaterScreenDlg;

// CDisplayTab dialog
class CDisplayTab : public CDialog
{
	DECLARE_DYNAMIC(CDisplayTab)

public:
	CDisplayTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDisplayTab();

// Dialog Data
	enum { IDD = IDD_TAB_DISPLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_comboDisplaySelection;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnCbnSelchangeCombo1();
	int displaySelection;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CToolTipCtrl toolTipMessage;
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	// from text tab
	CString text;
	int fontSize;
	CString fontName;
	CString strHtmlHex;

	// from image tab
	CString imagePath;
	int imageSize;

	CComboBox m_cornerLocation;
	CMFCColorButton m_transparencyKey;
	afx_msg void OnBnClickedMfccolorbutton1();
protected:
	CString tk;
	CString locationCorner;
	int locationCornerSelection;
private:
	void GetLocationSelection();
	void DisplayNow(int screen);
public:
	afx_msg void OnCbnSelchangeCombo2();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	int displayType;
};
