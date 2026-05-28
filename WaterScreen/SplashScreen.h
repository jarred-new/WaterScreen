#pragma once
#include "stdafx.h"

#define TIMER_SPLASH 1003

// CSplashScreen dialog

class CSplashScreen : public CDialogEx
{
	DECLARE_DYNAMIC(CSplashScreen)

public:
	CSplashScreen(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSplashScreen();

// Dialog Data
	enum { IDD = IDD_SPLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	UINT_PTR m_timer;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
};
