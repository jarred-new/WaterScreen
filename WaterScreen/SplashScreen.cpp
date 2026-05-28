// SplashScreen.cpp : implementation file
//

#include "stdafx.h"
#include "WaterScreen.h"
#include "SplashScreen.h"
#include "afxdialogex.h"


// CSplashScreen dialog

IMPLEMENT_DYNAMIC(CSplashScreen, CDialogEx)

CSplashScreen::CSplashScreen(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSplashScreen::IDD, pParent)
{

}

CSplashScreen::~CSplashScreen()
{
}

void CSplashScreen::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplashScreen, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSplashScreen message handlers


void CSplashScreen::OnPaint()
{
	CPaintDC dc(this); // Device context for painting

	// 1. Load the bitmap (IDC_MY_BITMAP could be loaded from resources)
	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(),
		MAKEINTRESOURCE(IDB_BITMAP2), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

	if (hBmp)
	{
		// 2. Create a memory DC compatible with the paint DC
		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		// 3. Select the bitmap into the memory DC
		HBITMAP hOldBmp = (HBITMAP)memDC.SelectObject(hBmp);

		// 4. Get the destination dialog client rectangle
		CRect rect;
		GetClientRect(&rect);

		// 5. Get original bitmap dimensions
		BITMAP bm;
		::GetObject(hBmp, sizeof(bm), &bm);

		// 6. Stretch the bitmap to fit the entire dialog
		dc.SetStretchBltMode(HALFTONE); // For smoother scaling
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(),
			&memDC, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

		// 7. Clean up
		memDC.SelectObject(hOldBmp);
		::DeleteObject(hBmp);
	}
}


void CSplashScreen::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == m_timer) {
		KillTimer(m_timer);
		this->DestroyWindow();
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CSplashScreen::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_timer = SetTimer(TIMER_SPLASH, 2000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
