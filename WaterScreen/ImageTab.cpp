// ImageTab.cpp : implementation file
//

#include "stdafx.h"
#include "WaterScreen.h"
#include "ImageTab.h"
#include "afxdialogex.h"


// CImageTab dialog

IMPLEMENT_DYNAMIC(CImageTab, CDialog)

CImageTab::CImageTab(CWnd* pParent /*=NULL*/)
	: CDialog(CImageTab::IDD, pParent)
{

	imageSize = 0;
	imagePath = _T("");
}

CImageTab::~CImageTab()
{
}

void CImageTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_filePathTextBox);
	DDX_Control(pDX, IDC_SLIDER1, m_sizeSlider);
	DDX_Control(pDX, IDC_STATIC_IMAGESIZE, m_imageSizeOutput);
}


BEGIN_MESSAGE_MAP(CImageTab, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CImageTab::OnBnClickedButton1)
	//ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CImageTab::OnNMCustomdrawSlider1)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CImageTab message handlers
BOOL CImageTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_filePathTextBox.SetCueBanner(L"Click on three dots or type the path manually here...");
	
	m_sizeSlider.SetRange(5, 350);
	m_sizeSlider.SetTicFreq(5);

	return FALSE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CImageTab::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	return CDialog::PreTranslateMessage(pMsg);
}

void CImageTab::OnBnClickedButton1()
{
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_HIDEREADONLY,
		_TEXT("JPG Files (*.jpg; *.jpeg)|*.jpg; *.jpeg|PNG Files (*.png)|*.png|GIF Files (*.gif)|*.gif|All Files (*.*)|*.*||"), this);

	CWnd* pTabCtrl = GetParent();
	if (pTabCtrl)
	{
		CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
		if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
		{
			pParent->m_statusBarCtrl.SetText(_T(" Open"), 0, 0);       // Pane index 0
			pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
		}
	}

	if (fileDlg.DoModal()) {
		imagePath = fileDlg.GetPathName();
		m_filePathTextBox.SetWindowText(imagePath);
		m_filePathTextBox.UpdateData(TRUE);
		this->UpdateData(TRUE);
	}
}

//void CImageTab::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
//{
//	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
//	// TODO: Add your control notification handler code here
//	*pResult = 0;
//}


void CImageTab::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	if (pScrollBar != NULL && pScrollBar->GetSafeHwnd() == m_sizeSlider.GetSafeHwnd())
	{
		imageSize = m_sizeSlider.GetPos();
		CString imageSizeOutput;
		imageSizeOutput.Format(L"Image Size: %d", imageSize);
		m_imageSizeOutput.SetWindowText(imageSizeOutput);
		m_imageSizeOutput.UpdateData(TRUE);

		CWnd* pTabCtrl = GetParent();
		if (pTabCtrl)
		{
			CWaterScreenDlg* pParent = (CWaterScreenDlg*)pTabCtrl->GetParent();
			if (pParent && ::IsWindow(pParent->GetSafeHwnd()))
			{
				pParent->m_statusBarCtrl.SetText(imageSizeOutput, 0, 0);       // Pane index 0
				pParent->m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1
			}
		}
		this->UpdateData();
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
