
// MFCGLIMDlg.h: 헤더 파일
//

#pragma once


#include "IMAGELISTDlg.h"

// CMFCGLIMDlg 대화 상자
class CMFCGLIMDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCGLIMDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCGLIM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.

private:
	CImage m_Image;
	void updateDisplay();
	void drawCircle(int nX, int nY, int nRadius);
	bool isInCircle(int i, int j, int nXpos, int nYpos, int nRadius);
	bool validImagePosition(int i, int j);
	int repeatBig(int x, int y);
	void saveImage(int i, int count);
	IMAGELISTDlg* m_ImageListDlg;

protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	int m_nX1;
	int m_nY1;
	int m_nX2;
	int m_nY2;
	int ImageCount = NULL;
	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnOpen();
	afx_msg void OnBnClickedBtnDraw();
	afx_msg void OnDestroy();
};
