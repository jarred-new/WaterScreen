
// WaterScreenDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WaterScreen.h"
#include "WaterScreenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CWaterScreenDlg dialog



CWaterScreenDlg::CWaterScreenDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CWaterScreenDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaterScreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
	isTabInit = true;
}

BEGIN_MESSAGE_MAP(CWaterScreenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CWaterScreenDlg::OnTcnSelchangeTab1)
//	ON_WM_SIZING()
ON_WM_SIZE()
END_MESSAGE_MAP()


// CWaterScreenDlg message handlers

BOOL CWaterScreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// StatusBar Creation
	if (!m_statusBarCtrl.Create(WS_CHILD | WS_VISIBLE | CCS_BOTTOM | CCS_ADJUSTABLE,
		CRect(0, 0, 0, 0), this, (UINT)IDC_STATUSBAR) ) {
		AfxMessageBox(L"Status Bar Failed!");
		exit(0);
	}

	// 2. Define widths for your panes (e.g., first pane takes 150px, second takes the rest)
	int paneWidths[m_nNumPanes] = { 150, -1 };
	m_statusBarCtrl.SetParts(m_nNumPanes, paneWidths);

	// 3. Set default text for the panes
	m_statusBarCtrl.SetText(_T(" Ready"), 0, 0);       // Pane index 0
	m_statusBarCtrl.SetText(_T(" "), 1, 0);  // Pane index 1

	// Creating and initializing the tab control

	// 1. Insert tabs
	m_tabCtrl.InsertItem(TEXTTAB, _T("Text Watermark"));
	m_tabCtrl.InsertItem(IMAGETAB, _T("Image Watermark"));
	m_tabCtrl.InsertItem(DISPLAYTAB, _T("Display"));

	// 2. Create the dialog pages
	m_textTab = new CTextTab();
	m_textTab->Create(IDD_TAB_TEXT, &m_tabCtrl);
	m_imageTab = new CImageTab();
	m_imageTab->Create(IDD_TAB_IMAGE, &m_tabCtrl);
	m_displayTab = new CDisplayTab();
	m_displayTab->Create(IDD_TAB_DISPLAY, &m_tabCtrl);

	// 3. Define the display area for the pages inside the tab control
	CRect tabRect;
	m_tabCtrl.GetClientRect(&tabRect);
	m_tabCtrl.AdjustRect(FALSE, &tabRect);

	// 4. Move pages to the tab control area and hide them initially
	m_textTab->MoveWindow(tabRect);
	m_imageTab->MoveWindow(tabRect);
	m_displayTab->MoveWindow(tabRect);

	m_textTab->ShowWindow(SW_SHOW);
	m_imageTab->ShowWindow(SW_HIDE);
	m_displayTab->ShowWindow(SW_HIDE);

	cp = 0;

	CWnd* cancelButton = GetDlgItem(IDCANCEL);
	if (cancelButton != nullptr && ::IsWindow(cancelButton->GetSafeHwnd())) {
		CRect clientRect;
		GetClientRect(&clientRect); // Get new parent window size

		// Define your constant margins from the bottom and right edges
		int marginRight = 15;
		int marginBottom = 26;

		// Define your control's fixed dimensions
		int controlWidth = 100;
		int controlHeight = 20;
		// Calculate the new X and Y positions based on the new client size
		int newX = clientRect.Width() - controlWidth - marginRight;
		int newY = clientRect.Height() - controlHeight - marginBottom;

		// Apply the new position without changing the size
		cancelButton->MoveWindow(newX, newY, controlWidth, controlHeight, TRUE);
	}
	else {
		// Save Memory
		delete m_textTab;
		delete m_imageTab;
		delete m_displayTab;
		exit(0);
	}

	if (!isTabInit) {
		// Save Memory
		delete m_textTab;
		delete m_imageTab;
		delete m_displayTab;
		exit(0);
	}
	else {
		CRect clientRect;
		GetClientRect(&clientRect);

		int padding = 0;      // Set to 0 for true edge-to-edge docking
		int controlHeight = clientRect.Height() - 50; // Define your desired fixed height

		// Calculate dimensions: Full width, fixed height, pinned to top
		int x = padding;
		int y = padding;
		int width = clientRect.Width() - (padding * 2);
		int height = controlHeight;

		// Apply the new layout
		m_tabCtrl.MoveWindow(x, y, width, height);

		CRect tabRect;
		m_tabCtrl.GetClientRect(&tabRect);
		m_tabCtrl.AdjustRect(FALSE, &tabRect);
		if (m_textTab->GetSafeHwnd() != NULL) {
			m_textTab->MoveWindow(tabRect);
		}
		if (m_imageTab->GetSafeHwnd() != NULL) {
			m_imageTab->MoveWindow(tabRect);
		}
		if (m_displayTab->GetSafeHwnd() != NULL) {
			m_displayTab->MoveWindow(tabRect);
		}
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWaterScreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWaterScreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWaterScreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CWaterScreenDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;
	cp = m_tabCtrl.GetCurSel();
	switch (cp)
	{
	case 0: // Text Tab
		m_textTab->ShowWindow(SW_SHOW);
		m_imageTab->ShowWindow(SW_HIDE);
		m_displayTab->ShowWindow(SW_HIDE);
		break;
	case 1: // Image Tab
		m_textTab->ShowWindow(SW_HIDE);
		m_imageTab->ShowWindow(SW_SHOW);
		m_displayTab->ShowWindow(SW_HIDE);
		break;
	case 2: // Display Tab
		m_textTab->ShowWindow(SW_HIDE);
		m_imageTab->ShowWindow(SW_HIDE);
		m_displayTab->ShowWindow(SW_SHOW);
		break;
	default:
		*pResult = 0;
		break;
	}
}


BOOL CWaterScreenDlg::DestroyWindow()
{
	// Save Memory
	delete m_textTab;
	delete m_imageTab;
	delete m_displayTab;

	return CDialogEx::DestroyWindow();
}


//void CWaterScreenDlg::OnSizing(UINT fwSide, LPRECT pRect)
//{
//	CDialogEx::OnSizing(fwSide, pRect);
//
//	// TODO: Add your message handler code here
//}


void CWaterScreenDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	
	CWnd* cancelButton = GetDlgItem(IDCANCEL);
	if (cancelButton != nullptr && ::IsWindow(cancelButton->GetSafeHwnd())) {
		CRect clientRect;
		GetClientRect(&clientRect); // Get new parent window size

		// Define your constant margins from the bottom and right edges
		int marginRight = 15;
		int marginBottom = 26;

		// Define your control's fixed dimensions
		int controlWidth = 100;
		int controlHeight = 20;
		// Calculate the new X and Y positions based on the new client size
		int newX = clientRect.Width() - controlWidth - marginRight;
		int newY = clientRect.Height() - controlHeight - marginBottom;

		// Apply the new position without changing the size
		cancelButton->MoveWindow(newX, newY, controlWidth, controlHeight, TRUE);
	}
	else {
		return;
	}

	if (!isTabInit) {
		return;
	}
	else {
		CRect clientRect;
		GetClientRect(&clientRect);

		int padding = 0;      // Set to 0 for true edge-to-edge docking
		int controlHeight = clientRect.Height() - 50; // Define your desired fixed height

		// Calculate dimensions: Full width, fixed height, pinned to top
		int x = padding;
		int y = padding;
		int width = clientRect.Width() - (padding * 2);
		int height = controlHeight;

		// Apply the new layout
		m_tabCtrl.MoveWindow(x, y, width, height);

		CRect tabRect;
		m_tabCtrl.GetClientRect(&tabRect);
		m_tabCtrl.AdjustRect(FALSE, &tabRect);
		if (m_textTab->GetSafeHwnd() != NULL) {
			m_textTab->MoveWindow(tabRect);
		}
		if (m_imageTab->GetSafeHwnd() != NULL) {
			m_imageTab->MoveWindow(tabRect);
		}
		if (m_displayTab->GetSafeHwnd() != NULL) {
			m_displayTab->MoveWindow(tabRect);
		}
	}

	if (m_statusBarCtrl.GetSafeHwnd())
	{
		// Force the status bar to automatically adjust to the bottom border
		m_statusBarCtrl.SendMessage(WM_SIZE, nType, MAKELPARAM(cx, cy));

		// Optional: Re-adjust internal widths dynamically if needed
		int paneWidths[m_nNumPanes] = { cx / 2, -1 }; // Splits sections evenly 50/50
		m_statusBarCtrl.SetParts(m_nNumPanes, paneWidths);
	}
}

void CWaterScreenDlg::CopyValuesFromTextToDisplay() {
	try {
		if (m_textTab != nullptr && m_displayTab != nullptr)
		{
			// 1. Force Tab 1 UI values into variables
			m_textTab->UpdateData(TRUE);

			// 2. Direct assignment transfer
			m_displayTab->text = m_textTab->text;
			if (m_textTab->text.IsEmpty()) {
				m_displayTab->text = L"There is no text!";
			}
			m_displayTab->fontSize = m_textTab->fontSize;
			m_displayTab->fontName = m_textTab->fontName;
			m_displayTab->strHtmlHex = m_textTab->strHtmlHex;

			// 3. Force Tab 3 variables into its UI controls
			m_displayTab->UpdateData(FALSE);
		}
	}
	catch (CMemoryException* e) {
		if (MessageBox(L"Out of Memory, cannot display...\nThis app will quit", L"Error!", MB_OK | MB_ICONERROR) == IDOK) {
			e->Delete();	
			exit(0);
		}
	}
}

void CWaterScreenDlg::CopyValuesFromImageToDisplay() {
	try {
		if (m_imageTab != nullptr && m_displayTab != nullptr)
		{
			// 1. Force Tab 1 UI values into variables
			m_imageTab->UpdateData(TRUE);

			// 2. Direct assignment transfer
			m_displayTab->imagePath = m_imageTab->imagePath;
			m_displayTab->imageSize = m_imageTab->imageSize;

			// 3. Force Tab 3 variables into its UI controls
			m_displayTab->UpdateData(FALSE);
		}
	}
	catch (CMemoryException* e) {
		if (MessageBox(L"Out of Memory, cannot display...\nThis app will quit", L"Error!", MB_OK | MB_ICONERROR) == IDOK) {
			e->Delete();
			exit(0);
		}
	}
}

void CWaterScreenDlg::SetStatusBarText(CString pane1Text, CString pane2Text) {
	this->m_statusBarCtrl.SetText(L" " + pane1Text, 0, 0);       // Pane index 0
	this->m_statusBarCtrl.SetText(L" " + pane2Text, 1, 0);  // Pane index 1
	this->UpdateData(TRUE);
}
