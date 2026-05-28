#pragma once
#include "afxwin.h"
#include "afxcolorbutton.h"
#include "afxfontcombobox.h"
#include "afxcmn.h"
#include "WaterScreenDlg.h"

class CWaterScreenDlg;

// CTextTab dialog

class CTextTab : public CDialog
{
	DECLARE_DYNAMIC(CTextTab)

public:
	CTextTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTextTab();

// Dialog Data
	enum { IDD = IDD_TAB_TEXT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_TextInput;
	CMFCColorButton m_TextColor;
	CMFCFontComboBox m_TextFont;
	afx_msg void OnEnChangeEdit1();
	virtual BOOL OnInitDialog();
	CSliderCtrl m_fontSizeBar;
//	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CString text;
	int fontSize;
	CStatic m_textSizeOutput;
	afx_msg void OnCbnSelchangeMfcfontcombo1();
	CString fontName;
	afx_msg void OnBnClickedMfccolorbutton1();
	CString strHtmlHex;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
