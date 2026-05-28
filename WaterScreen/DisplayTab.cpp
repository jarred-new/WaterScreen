// DisplayTab.cpp : implementation file
//

#include "stdafx.h"
#include "WaterScreen.h"
#include "DisplayTab.h"
#include "afxdialogex.h"


// CDisplayTab dialog

IMPLEMENT_DYNAMIC(CDisplayTab, CDialog)

CDisplayTab::CDisplayTab(CWnd* pParent /*=NULL*/)
	: CDialog(CDisplayTab::IDD, pParent)
{

	displaySelection = 0;
	tk = _T("");
	locationCorner = _T("TopLeft");
	displayType = 0;
}

CDisplayTab::~CDisplayTab()
{
}

void CDisplayTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboDisplaySelection);
	DDX_Control(pDX, IDC_COMBO2, m_cornerLocation);
	DDX_Control(pDX, IDC_MFCCOLORBUTTON1, m_transparencyKey);
}


BEGIN_MESSAGE_MAP(CDisplayTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CDisplayTab::OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CDisplayTab::OnCbnSelchangeCombo1)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MFCCOLORBUTTON1, &CDisplayTab::OnBnClickedMfccolorbutton1)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CDisplayTab::OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_RADIO1, &CDisplayTab::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CDisplayTab::OnBnClickedRadio2)
END_MESSAGE_MAP()


// CDisplayTab message handlers


BOOL CDisplayTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->EnableToolTips();

	m_comboDisplaySelection.AddString(L"Primary Monitor (Main Display)");
	m_comboDisplaySelection.AddString(L"Second Display (HDMI Extend Display Mode)");
	m_comboDisplaySelection.SetCueBanner(L"Select your display here...");

	displaySelection = m_comboDisplaySelection.GetCurSel();

	/*  TopLeft, TopCenter, TopRight,
		CenterLeft, Center, CenterRight,
		BottomLeft, BottomCenter, BottomRight
	*/
	m_cornerLocation.AddString(L"TopLeft");
	m_cornerLocation.AddString(L"TopCenter");
	m_cornerLocation.AddString(L"TopRight");
	m_cornerLocation.AddString(L"CenterLeft");
	m_cornerLocation.AddString(L"Center");
	m_cornerLocation.AddString(L"CenterRight");
	m_cornerLocation.AddString(L"BottomLeft");
	m_cornerLocation.AddString(L"BottomCenter");
	m_cornerLocation.AddString(L"BottomRight");
	m_cornerLocation.SetCurSel(0);

	locationCornerSelection = m_cornerLocation.GetCurSel();

	COLORREF color = m_transparencyKey.GetColor();
	tk.Format(_T("#%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color)); // get default color
	this->UpdateData();

	toolTipMessage.Create(this, TTS_ALWAYSTIP | TTS_BALLOON);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(TOOLINFO);
	ti.hwnd = this->m_hWnd;
	ti.uId = (INT_PTR)m_comboDisplaySelection.m_hWnd;
	ti.uFlags = TTF_TRACK | TTF_IDISHWND;
	ti.lpszText = L"You need to select your display!";

	/*if (toolTipMessage.SendMessage(TTM_GETTOOLINFO,
		0,
		(LPARAM)&ti) != NULL) {
		ti.uFlags |= TTF_TRACK;
		toolTipMessage.SendMessage(TTM_SETTOOLINFO,
			0,
			(LPARAM)&ti);
	}*/

	toolTipMessage.SendMessage(TTM_ADDTOOL, 0, (LPARAM)&ti);

	toolTipMessage.Activate(TRUE);

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CDisplayTab::OnBnClickedButton1()
{
	/*CString str;
	str.Format(L"Selection: %d", displaySelection);
	AfxMessageBox(str);*/
	if (displaySelection == -1) {
		CRect rect;
		m_comboDisplaySelection.GetWindowRect(&rect);
		int posX = rect.left + (rect.Width() / 2);
		int posY = rect.bottom;
		::SendMessage(toolTipMessage.m_hWnd,
			TTM_TRACKPOSITION,
			0,
			MAKELPARAM(posX, posY));

		TOOLINFO ti = { 0 };
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = this->m_hWnd;
		ti.uId = (INT_PTR)m_comboDisplaySelection.m_hWnd;
		ti.uFlags = TTF_TRACK | TTF_IDISHWND;

		::SendMessage(toolTipMessage.m_hWnd,
			TTM_TRACKACTIVATE, FALSE,
			(LPARAM)&ti);

		::SendMessage(toolTipMessage.m_hWnd,
			TTM_SETTITLE,
			TTI_ERROR_LARGE,
			(LPARAM)L"This is important!");

		MessageBeep(MB_ICONERROR);
		::SendMessage(toolTipMessage.m_hWnd,
			TTM_TRACKACTIVATE, TRUE,
			(LPARAM)&ti);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(_T(" Error:"), 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(_T(" Display is null"), 1, 0);  // Pane index 1
			}
		}

		SetTimer(TIMER_HIDE_TIMER, 5000, NULL);
	}
	else if (displaySelection == 0) {
		this->DisplayNow(0);
	}
	else if (displaySelection == 1) {
		this->DisplayNow(1);
	}
}


void CDisplayTab::OnCbnSelchangeCombo1()
{
	displaySelection = m_comboDisplaySelection.GetCurSel();
	
	switch (displaySelection)
	{
	case 0: {
				CWnd* pTabCtrl = GetParent();
				if (pTabCtrl)
				{
					CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
					if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
					{
						pParent->SetStatusBarText(L"Display Selected:", L"1");
					}
				}
	}
		break;
	case 1: {
				CWnd* pTabCtrl = GetParent();
				if (pTabCtrl)
				{
					CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
					if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
					{
						pParent->SetStatusBarText(L"Display Selected:", L"2");
					}
				}
	}
		break;
	default:
		break;
	}
}


BOOL CDisplayTab::PreTranslateMessage(MSG* pMsg)
{
	if (toolTipMessage.GetSafeHwnd() != NULL && ::IsWindow(toolTipMessage)) {
		toolTipMessage.RelayEvent(pMsg);
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}


void CDisplayTab::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == TIMER_HIDE_TIMER) {
		TOOLINFO ti = { 0 };
		ti.cbSize = sizeof(TOOLINFO);
		ti.hwnd = this->m_hWnd;
		ti.uId = (INT_PTR)m_comboDisplaySelection.m_hWnd;
		ti.uFlags = TTF_TRACK | TTF_IDISHWND;

		::SendMessage(toolTipMessage.m_hWnd,
			TTM_TRACKACTIVATE, FALSE,
			(LPARAM)&ti);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(_T(" Ready"), 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
			}
		}

		KillTimer(TIMER_HIDE_TIMER);
	}

	CDialog::OnTimer(nIDEvent);
}


void CDisplayTab::OnBnClickedMfccolorbutton1()
{
	COLORREF color = m_transparencyKey.GetColor();
	tk.Format(_T("#%02X%02X%02X"), GetRValue(color), GetGValue(color), GetBValue(color)); // get default color
	
	CWnd* pTabCtrl = GetParent();
	if (pTabCtrl)
	{
		CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
		if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
		{
			pParent->m_statusBarCtrl.SetText(_T(" TransparencyKey Color:"), 0, 0);       // Pane index 0
			pParent->m_statusBarCtrl.SetText(tk, 1, 0);  // Pane index 1
		}
	}

	this->UpdateData();
}

void CDisplayTab::GetLocationSelection() {
	if (locationCornerSelection != CB_ERR)
	{
		CString lb;
		m_cornerLocation.GetLBText(locationCornerSelection, lb);
		locationCorner = lb;
		this->UpdateData(TRUE);
	}
}

void CDisplayTab::OnCbnSelchangeCombo2()
{
	locationCornerSelection = m_cornerLocation.GetCurSel();
	this->UpdateData(TRUE);
}


void CDisplayTab::OnBnClickedRadio1()
{
	displayType = 0;
	CWnd* pTabCtrl = GetParent();
	if (pTabCtrl)
	{
		CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
		if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
		{
			pParent->m_statusBarCtrl.SetText(_T(" Display Selected:"), 0, 0);       // Pane index 0
			pParent->m_statusBarCtrl.SetText(_T(" Text Display"), 1, 0);  // Pane index 1
		}
	}
}


void CDisplayTab::OnBnClickedRadio2()
{
	displayType = 1;
	CWnd* pTabCtrl = GetParent();
	if (pTabCtrl)
	{
		CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
		if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
		{
			pParent->m_statusBarCtrl.SetText(_T(" Display Selected:"), 0, 0);       // Pane index 0
			pParent->m_statusBarCtrl.SetText(_T(" Image Display"), 1, 0);  // Pane index 1
		}
	}
}

void CDisplayTab::DisplayNow(int screen) {
	// Text Display
	if (displayType == 0) {
		TCHAR szExePath[MAX_PATH];
		::GetModuleFileName(NULL, szExePath, MAX_PATH);
		::PathRemoveFileSpec(szExePath);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				// Ask parent to orchestrate the copy operation
				pParent->CopyValuesFromTextToDisplay();

				this->UpdateData(TRUE);

				/*AfxMessageBox(text);
				AfxMessageBox(fontName);*/

				/*CString fsz;
				fsz.Format(L"%d", fontSize);*/

				/*AfxMessageBox(fsz);
				AfxMessageBox(strHtmlHex);*/

				GetLocationSelection();

				CString strSource;
				strSource.Format(L"%s\\displaycmd\\TextDisplay.exe",
					szExePath);

				CString args;
				args.Format(L"\"%s\" \"%s\" %d \"%s\" \"%s\" %d %s",
					text, fontName, fontSize, strHtmlHex, tk, screen, locationCorner);

				CWnd* pTabCtrl = GetParent();
				if (pTabCtrl)
				{
					CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
					if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
					{
						pParent->m_statusBarCtrl.SetText(_T(" Ready"), 0, 0);       // Pane index 0
						pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
					}
				}

				::ShellExecute(NULL, L"open", strSource, args, NULL, SW_SHOW);
			}
		}
	}
	// Image Display
	else if (displayType == 1) {
		TCHAR szExePath[MAX_PATH];
		::GetModuleFileName(NULL, szExePath, MAX_PATH);
		::PathRemoveFileSpec(szExePath);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				// Ask parent to orchestrate the copy operation
				pParent->CopyValuesFromImageToDisplay();

				this->UpdateData(TRUE);

				GetLocationSelection();

				CString strSource;
				strSource.Format(L"%s\\displaycmd\\ImageDisplay.exe",
					szExePath);

				CString args;
				args.Format(L"\"%s\" \"%s\" %d %s %d",
					imagePath, tk, screen, locationCorner, imageSize);

				CWnd* pTabCtrl = GetParent();
				if (pTabCtrl)
				{
					CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
					if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
					{
						pParent->m_statusBarCtrl.SetText(_T(" Ready"), 0, 0);       // Pane index 0
						pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
					}
				}

				::ShellExecute(NULL, L"open", strSource, args, NULL, SW_SHOW);
			}
		}
	}
}