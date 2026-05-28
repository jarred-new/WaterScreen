#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "WaterScreenDlg.h"

class CWaterScreenDlg;

// CImageTab dialog

class CImageTab : public CDialog
{
	DECLARE_DYNAMIC(CImageTab)

public:
	CImageTab(CWnd* pParent = NULL);   // standard constructor
	virtual ~CImageTab();

// Dialog Data
	enum { IDD = IDD_TAB_IMAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	CEdit m_filePathTextBox;
	CSliderCtrl m_sizeSlider;
	int imageSize;
	CString imagePath;
//	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	CStatic m_imageSizeOutput;
};
