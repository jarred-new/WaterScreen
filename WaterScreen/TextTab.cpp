// TextTab.cpp : implementation file
//

#include "stdafx.h"
#include "WaterScreen.h"
#include "TextTab.h"
#include "afxdialogex.h"


// CTextTab dialog

IMPLEMENT_DYNAMIC(CTextTab, CDialog)

CTextTab::CTextTab(CWnd* pParent /*=NULL*/)
	: CDialog(CTextTab::IDD, pParent)
{

	fontSize = 12;
	fontName = _T("");
}

CTextTab::~CTextTab()
{
}

void CTextTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_TextInput);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_TextColor);
	DDX_Control(pDX, IDC_MFCFONTCOMBO1, m_TextFont);
	DDX_Control(pDX, IDC_SLIDER1, m_fontSizeBar);
	DDX_Control(pDX, IDC_STATIC_TEXTSIZE, m_textSizeOutput);
}


BEGIN_MESSAGE_MAP(CTextTab, CDialog)
	ON_EN_CHANGE(IDC_EDIT1, &CTextTab::OnEnChangeEdit1)
//	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CTextTab::OnNMCustomdrawSlider1)
//	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CTextTab::OnTRBNThumbPosChangingSlider1)
ON_WM_HSCROLL()
ON_CBN_SELCHANGE(IDC_MFCFONTCOMBO1, &CTextTab::OnCbnSelchangeMfcfontcombo1)
ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CTextTab::OnBnClickedMfccolorbutton1)
END_MESSAGE_MAP()


// CTextTab message handlers


void CTextTab::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CString str;
	m_TextInput.GetWindowText(str);
	text = str;
	this->UpdateData();
	if (str.IsEmpty()) {
		MessageBeep(MB_ICONERROR);
		m_TextInput.ShowBalloonTip(L"This is empty!",
			L"Type your desired text here!",
			TTI_ERROR_LARGE);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(_T(" Error:"), 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(_T(" Type your text!"), 1, 0);  // Pane index 1
			}
		}
	}
}


BOOL CTextTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->EnableToolTips();
	
	m_TextInput.SetCueBanner(L"Enter your text here...");
	m_fontSizeBar.SetRange(12, 1000);
	m_fontSizeBar.SetTicFreq(4); // Find the GCF between 12 and 1000, so the answer is 4

	fontName = "Segoe UI"; // default font
	COLORREF color = m_TextColor.GetColor();
	strHtmlHex.Format(_T("#%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color)); // get default color
	this->UpdateData();
	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


//void CTextTab::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


//void CTextTab::OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	// This feature requires Windows Vista or greater.
//	// The symbol _WIN32_WINNT must be >= 0x0600.
//	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


void CTextTab::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar != NULL && pScrollBar->GetSafeHwnd() == m_fontSizeBar.GetSafeHwnd())
	{
		fontSize = m_fontSizeBar.GetPos();
		CString fontSizeOutput;
		fontSizeOutput.Format(L"Text Size: %d", fontSize);
		m_textSizeOutput.SetWindowText(fontSizeOutput);
		m_textSizeOutput.UpdateData(TRUE);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(fontSizeOutput, 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
			}
		}

		this->UpdateData();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CTextTab::OnCbnSelchangeMfcfontcombo1()
{
	CMFCFontInfo* fontInfo = m_TextFont.GetSelFont();

	if (fontInfo != NULL) {
		fontName = fontInfo->m_strName;
		this->UpdateData();

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(_T(" Font Selected:"), 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(fontName, 1, 0);  // Pane index 1
			}
		}
	}
	else {
		MessageBox(L"No font found", L"Error", MB_ICONERROR | MB_OK);
	}
}


void CTextTab::OnBnClickedMfccolorbutton1()
{
	COLORREF color = m_TextColor.GetColor();
	CString hexOutput;
	hexOutput.Format(_T("#%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color));
	strHtmlHex = hexOutput;

	CWnd* pTabCtrl = GetParent();
	if (pTabCtrl)
	{
		CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
		if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
		{
			pParent->m_statusBarCtrl.SetText(_T(" Text Color:"), 0, 0);       // Pane index 0
			pParent->m_statusBarCtrl.SetText(strHtmlHex, 1, 0);  // Pane index 1
		}
	}
	this->UpdateData();
}


BOOL CTextTab::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}
