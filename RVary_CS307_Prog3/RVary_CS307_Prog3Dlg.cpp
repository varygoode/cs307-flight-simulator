
// RVary_CS307_Prog3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "RVary_CS307_Prog3.h"
#include "RVary_CS307_Prog3Dlg.h"
#include "afxdialogex.h"
#include <fstream>

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


// CRVary_CS307_Prog3Dlg dialog




CRVary_CS307_Prog3Dlg::CRVary_CS307_Prog3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRVary_CS307_Prog3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	sim = new Simulation();
}

void CRVary_CS307_Prog3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SPEED, m_SimSpeed);
	DDX_Control(pDX, IDC_EDIT1, m_SimDataFileTF);
	DDX_Control(pDX, IDC_ENDSIM, m_EndSimButton);
	DDX_Control(pDX, IDC_RUNSIM, m_RunSimButton);
	DDX_Control(pDX, IDC_EDIT2, m_cityDataFile);
	DDX_Control(pDX, IDC_EDIT3, m_flightDataFile);
}

BEGIN_MESSAGE_MAP(CRVary_CS307_Prog3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RUNSIM, &CRVary_CS307_Prog3Dlg::OnBnClickedRunsim)
	ON_BN_CLICKED(IDC_ENDSIM, &CRVary_CS307_Prog3Dlg::OnBnClickedEndsim)
	ON_CBN_SELCHANGE(IDC_SPEED, &CRVary_CS307_Prog3Dlg::OnCbnSelchangeSpeed)
	ON_WM_TIMER (&CRVary_CS307_Prog3Dlg::OnTimer)
END_MESSAGE_MAP()


// CRVary_CS307_Prog3Dlg message handlers

BOOL CRVary_CS307_Prog3Dlg::OnInitDialog()
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

	// TODO: Add extra initialization here
	m_SimSpeed.AddString("1X");
	m_SimSpeed.AddString("2X");
	m_SimSpeed.AddString("3X");
	m_SimSpeed.SetCurSel(0);

	m_SimDataFileTF.SetWindowTextA("FlightSim03.txt");

	// Resize and reposition the window
	m_iWinWidth = 1024;
	m_iWinHeight = 1024;
	this->SetWindowPos(NULL, 10, 10, m_iWinWidth, m_iWinHeight, 0); // Move and resize window
	// Move all the widgets
	m_EndSimButton.SetWindowPos(NULL, m_iWinWidth-990, m_iWinHeight-435, 340, 20, 0);
	m_RunSimButton.SetWindowPos(NULL, m_iWinWidth-840, m_iWinHeight-960, 180, 20, 0); 
	m_SimSpeed.SetWindowPos(NULL, m_iWinWidth-900, m_iWinHeight-960, 50, 20, 0); 
	m_SimDataFileTF.SetWindowPos(NULL, m_iWinWidth-900, m_iWinHeight-990, 230, 20, 0);
	m_cityDataFile.SetWindowPos(NULL, m_iWinWidth - 900, m_iWinHeight - 910, 230, 20, 0);
	m_flightDataFile.SetWindowPos(NULL, m_iWinWidth - 900, m_iWinHeight - 880, 230, 20, 0);
	// Move the sim speed label
	CStatic *label = (CStatic *)GetDlgItem(IDC_STATIC1);
	label->SetWindowPos(NULL, m_iWinWidth-985, m_iWinHeight-960, 200, 20, 0);
	// Move the data file label
	label = (CStatic *)GetDlgItem(IDC_STATIC2);
	label->SetWindowPos(NULL, m_iWinWidth-990, m_iWinHeight-990, 200, 20, 0);
	// Move the city data file label
	label = (CStatic *)GetDlgItem(IDC_STATIC3);
	label->SetWindowPos(NULL, m_iWinWidth - 990, m_iWinHeight - 880, 200, 20, 0);
	// Move the flight data file label
	label = (CStatic *)GetDlgItem(IDC_STATIC4);
	label->SetWindowPos(NULL, m_iWinWidth - 990, m_iWinHeight - 910, 200, 20, 0);
	// Move the flight status report label
	label = (CStatic *)GetDlgItem(IDC_STATIC5);
	label->SetWindowPos(NULL, m_iWinWidth - 875, m_iWinHeight - 835, 200, 20, 0);
	// Move the arrivals & departures label
	label = (CStatic *)GetDlgItem(IDC_STATIC6);
	label->SetWindowPos(NULL, m_iWinWidth - 880, m_iWinHeight - 530, 200, 20, 0);
	// Move the current clock time label
	label = (CStatic *)GetDlgItem(IDC_STATIC7);
	label->SetWindowPos(NULL, m_iWinWidth - 625, m_iWinHeight - 430, 200, 15, 0);
	// Move the group box 1
	label = (CStatic *)GetDlgItem(IDC_GROUP1);
	label->SetWindowPos(NULL, m_iWinWidth - 995, m_iWinHeight - 1010, 350, 80, 0);
	// Move the group box 2
	label = (CStatic *)GetDlgItem(IDC_GROUP2);
	label->SetWindowPos(NULL, m_iWinWidth - 995, m_iWinHeight - 925, 350, 80, 0);
	// Move the group box 3
	label = (CStatic *)GetDlgItem(IDC_GROUP3);
	label->SetWindowPos(NULL, m_iWinWidth - 995, m_iWinHeight - 845, 350, 435, 0);
	// Move the group box 4
	label = (CStatic *)GetDlgItem(IDC_GROUP4);
	label->SetWindowPos(NULL, m_iWinWidth - 630, m_iWinHeight - 1010, 600, 600, 0);

	// Set up the bitmap map image
	CDC *thisDC = this->GetDC();
	m_MapBitmap.LoadBitmapA(IDB_BITMAP1);
	m_DCMemory.CreateCompatibleDC(thisDC);
	m_DCMemory.SelectObject(&m_MapBitmap);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRVary_CS307_Prog3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CRVary_CS307_Prog3Dlg::OnPaint()
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
		CDC *cdc = this->GetDC(); // Add this line to get a CDC for drawing

		// Add your code to draw the FlightSim here
		//   Note: This can simply be a call such as:
		//   theFlightSim->drawFlightSim(cdc);
		// Where theFlightSim is a pointer to your FlightSim 
		//   class.  The FlightSim, however, will have to be
		//   told the size of the window and possibly other
		//   parameters so it will know the limits of the
		//   content pane it will be drawing into using the
		//   device context (cdc) passed in.

		//========= Do Painting here ==============
		CDC *thisDC = this->GetDC();	// Get the window DC

		// Draw the map bitmap
		int height, width;
		sim->getMapImageSize(&width, &height);
		m_MapRect.SetRect(415, 25, width + 425, height + 25);
		thisDC->BitBlt(m_MapRect.left, m_MapRect.top,
			m_MapRect.Width(), m_MapRect.Height(),
			&m_DCMemory, 0, 0, SRCCOPY);

		// Have the flight sim draw all cities on top of the bitmap
		sim->drawCities(thisDC, 415, 25);

		//draw the report
		sim->drawClock(thisDC, 480, 575, 40, 20);
		if (m_dReportTime == m_dSimTimeMin || sim->simDone())
		{
			sim->drawReport(thisDC, 25, 190, 335, 290);
			
			char speedStr[10];
			m_SimSpeed.GetLBText(m_SimSpeed.GetCurSel(), speedStr);
			
			if (strcmp(speedStr, "1X") == 0) m_dReportTime = m_dSimTimeMin + 5;
			else if (strcmp(speedStr, "2X") == 0) m_dReportTime = m_dSimTimeMin + 10;
			else m_dReportTime = m_dSimTimeMin + 15;			

			if (m_dReportTime >= 60)
				m_dReportTime -= 60;
		}

		sim->drawArrDep(thisDC, 25, 495, 335, 80);

		// Have the flight sim draw all routes and planes on top of the bitmap
		sim->drawRoutesAndPlanes(thisDC, 415, 25);
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRVary_CS307_Prog3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}






void CRVary_CS307_Prog3Dlg::OnBnClickedRunsim()
{
	// TODO: Add your control notification handler code here
	char datafile[64];
	char speedStr[10];
	char cityXML[64];
	char flightXML[64];
	
	m_SimDataFileTF.GetWindowText(datafile, 63);

	ifstream inFile;
	inFile.open(datafile);
	
	inFile >> cityXML;
	inFile >> flightXML;

	inFile.close();
	
	m_cityDataFile.SetWindowTextA(cityXML);
	m_flightDataFile.SetWindowTextA(flightXML);
	
	// Get the speed to run
	m_SimSpeed.GetLBText(m_SimSpeed.GetCurSel(), speedStr);
	if(strcmp(speedStr, "1X") == 0) CWnd::SetTimer(1, 1000, 0);
	else if(strcmp(speedStr, "2X") == 0) CWnd::SetTimer(1, 500, 0);
	else CWnd::SetTimer(1, 333, 0);
	sim->initialize(datafile);	// Give it the name of the data file
	m_dSimTimeHr = 0;		// Init sim time-this is a member variable defined in Prog3Dlg.h
	m_dSimTimeMin = 0;	// Init sim time-this is a member variable defined in Prog3Dlg.h
	sim->fdp->getStartTime(&m_dSimTimeHr, &m_dSimTimeMin);
	
	if (strcmp(speedStr, "1X") == 0) m_dReportTime = m_dSimTimeMin + 5;
	else if (strcmp(speedStr, "2X") == 0) m_dReportTime = m_dSimTimeMin + 10;
	else m_dReportTime = m_dSimTimeMin + 15;

	if (m_dReportTime >= 60)
		m_dReportTime -= 60;

	m_RunSimButton.EnableWindow(false); // Disable the run sim button so the user can't click it again
	sim->update(m_dSimTimeHr, m_dSimTimeMin);	// It's kickoff time
}


void CRVary_CS307_Prog3Dlg::OnBnClickedEndsim()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
}


void CRVary_CS307_Prog3Dlg::OnCbnSelchangeSpeed()
{
	// TODO: Add your control notification handler code here
	
}

void CRVary_CS307_Prog3Dlg::OnTimer(UINT nIDEvent)
{
	// Perform any updates to the FlightSim state here before calling OnPaint
	m_dSimTimeMin += 1.0; // Update sim time - this is a member variable defined in programNameDlg.h 
	if (m_dSimTimeMin == 60)
	{
		m_dSimTimeHr++;
		m_dSimTimeMin = 0;
	}
	sim->update(m_dSimTimeHr, m_dSimTimeMin);
	OnPaint();  // Call the paint function to update the display

	if (sim->simDone())
	{
		CWnd::KillTimer(nIDEvent);
		OnPaint();  // Call the paint function to update the display
	}

	CDialog::OnTimer(nIDEvent); // Pass on to super
}