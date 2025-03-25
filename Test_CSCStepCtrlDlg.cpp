
// Test_CSCStepCtrlDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Test_CSCStepCtrl.h"
#include "Test_CSCStepCtrlDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "../../Common/Functions.h"


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestCSCStepCtrlDlg 대화 상자



CTestCSCStepCtrlDlg::CTestCSCStepCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TEST_CSCSTEPCTRL_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestCSCStepCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_STEPH, m_steph);
	DDX_Control(pDX, IDC_STATIC_STEPV, m_stepv);
	DDX_Control(pDX, IDC_CHECK_TEST_TIMER, m_check_test_timer);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_combo_style);
	DDX_Control(pDX, IDC_EDIT_SIZE, m_edit_size);
	DDX_Control(pDX, IDC_SPIN_SIZE, m_spin_size);
}

BEGIN_MESSAGE_MAP(CTestCSCStepCtrlDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTestCSCStepCtrlDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTestCSCStepCtrlDlg::OnBnClickedCancel)
	ON_WM_TIMER()
	ON_WM_WINDOWPOSCHANGED()
	ON_BN_CLICKED(IDC_CHECK_TEST_TIMER, &CTestCSCStepCtrlDlg::OnBnClickedCheckTestTimer)
	ON_CBN_SELCHANGE(IDC_COMBO_STYLE, &CTestCSCStepCtrlDlg::OnCbnSelchangeComboStyle)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIZE, &CTestCSCStepCtrlDlg::OnDeltaposSpinSize)
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// CTestCSCStepCtrlDlg 메시지 처리기

BOOL CTestCSCStepCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_resize.Create(this);
	m_resize.Add(IDC_STATIC_STEPH, 0, 0, 100, 0);
	m_resize.Add(IDC_STATIC_STEPV, 0, 0, 100, 100);

	/*
	thumb_style_circle,
	thumb_style_circle_with_num,
	thumb_style_rect,
	thumb_style_rect_round,
	thumb_style_diamond,
	thumb_style_arrow,
	*/
	m_combo_style.AddString(_T("thumb_style_circle"));
	m_combo_style.AddString(_T("thumb_style_circle_with_num"));
	m_combo_style.AddString(_T("thumb_style_rect"));
	m_combo_style.AddString(_T("thumb_style_rect_round"));
	m_combo_style.AddString(_T("thumb_style_diamond"));
	m_combo_style.AddString(_T("thumb_style_arrow"));

	int style = theApp.GetProfileInt(_T("setting"), _T("style"), thumb_style_circle);
	Clamp(style, 0, 5);
	m_combo_style.SetCurSel(style);


	int size = theApp.GetProfileInt(_T("setting"), _T("size"), 18);
	m_edit_size.SetWindowText(i2S(size));
	m_spin_size.SetRange(10, 40);
	m_spin_size.SetPos(size);


	m_steph.set_style(true, style);
	m_steph.set_thumb_size(size);
	m_steph.set_step_count(6);
	m_steph.set_margin(24, 8, 24, 8);
	m_steph.set_texts(_T("step 0"), _T("스텝 1"), _T("step 2"), _T("스텝 3"), _T("step 4"), _T("스텝 5"));
	m_steph.set_pos(2);
	m_steph.set_step_color(1, Gdiplus::Color::Red);

	m_stepv.set_style(false, style);
	m_stepv.set_thumb_size(size);
	m_stepv.set_step_count(6);
	m_stepv.set_texts(_T("step 0"), _T("스텝 1"), _T("step 2"), _T("스텝 3"), _T("step 4"), _T("스텝 5"));
	m_stepv.set_pos(2);
	m_stepv.set_step_color(1, Gdiplus::Color::Red);

	m_check_test_timer.SetCheck(BST_CHECKED);
	OnBnClickedCheckTestTimer();

	RestoreWindowPosition(&theApp, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTestCSCStepCtrlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTestCSCStepCtrlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTestCSCStepCtrlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestCSCStepCtrlDlg::OnBnClickedOk()
{
	m_steph.reset_step_color();
	m_stepv.reset_step_color();
}

void CTestCSCStepCtrlDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CTestCSCStepCtrlDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == timer_test_step)
	{
		int pos = m_steph.get_pos() + 1;
		if (pos > m_steph.get_step_count())
			m_steph.set_pos(-1);
		else
			m_steph.step();

		pos = m_stepv.get_pos() + 1;
		if (pos > m_stepv.get_step_count())
			m_stepv.set_pos(-1);
		else
			m_stepv.step();

	}

	CDialogEx::OnTimer(nIDEvent);
}

void CTestCSCStepCtrlDlg::OnWindowPosChanged(WINDOWPOS* lpwndpos)
{
	CDialogEx::OnWindowPosChanged(lpwndpos);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SaveWindowPosition(&theApp, this);
}

void CTestCSCStepCtrlDlg::OnBnClickedCheckTestTimer()
{
	int state = m_check_test_timer.GetCheck();

	if (state == BST_CHECKED)
		SetTimer(timer_test_step, 1000, NULL);
	else
		KillTimer(timer_test_step);
}

void CTestCSCStepCtrlDlg::OnCbnSelchangeComboStyle()
{
	int style = m_combo_style.GetCurSel();
	if (style < 0 || style >= m_combo_style.GetCount())
		return;

	m_steph.set_thumb_style(-1, style);
	m_stepv.set_thumb_style(-1, style);
}

void CTestCSCStepCtrlDlg::OnDeltaposSpinSize(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
}

void CTestCSCStepCtrlDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (pScrollBar == (CScrollBar*)&m_spin_size)
	{
		int size = m_spin_size.GetPos();

		m_steph.set_thumb_size(size);
		m_stepv.set_thumb_size(size);
	}

	CDialogEx::OnVScroll(nSBCode, nPos, pScrollBar);
}
