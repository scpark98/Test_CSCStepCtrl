
// Test_CSCStepCtrlDlg.h: 헤더 파일
//

#pragma once

#include "../../Common/ResizeCtrl.h"
#include "../../Common/CStatic/CSCStepCtrl/SCStepCtrl.h"

// CTestCSCStepCtrlDlg 대화 상자
class CTestCSCStepCtrlDlg : public CDialogEx
{
// 생성입니다.
public:
	CTestCSCStepCtrlDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	CResizeCtrl		m_resize;

	enum TIMER_ID
	{
		timer_test_step = 0,
	};

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TEST_CSCSTEPCTRL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CSCStepCtrl m_steph;
	CSCStepCtrl m_stepv;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnWindowPosChanged(WINDOWPOS* lpwndpos);
	CButton m_check_test_timer;
	afx_msg void OnBnClickedCheckTestTimer();
};
