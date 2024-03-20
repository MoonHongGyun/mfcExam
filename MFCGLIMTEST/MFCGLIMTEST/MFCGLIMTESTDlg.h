
// MFCGLIMTESTDlg.h: 헤더 파일
//

#pragma once


// CMFCGLIMTESTDlg 대화 상자
class CMFCGLIMTESTDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCGLIMTESTDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGLIMTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


private:
	CImage m_Image;
	void updateDisplay();
	bool isInCircle(int i, int j);
	int m_nWidth = 0;
	int m_nHeight = 0;
	int m_nHR = 0;
	int nsaveCount = 1;
	CString g_strFileimage = _T("C:\\Users\\IOT\\Desktop\\GLIMIMAGE\\save0.bmp");
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
	afx_msg void OnBnClickedBtnBoard();
	afx_msg void OnBnClickedBtnDrawcircle();
	int m_nPosX = 0;
	int m_nPosY = 0;
	int m_nHalfRadius = 0;

	void moveCircle();
	void drawCircle(int nSttX,int nSttY);
	afx_msg void OnBnClickedBtnAct1();
	afx_msg void OnBnClickedBtnLoad();
};
