
// MFCGLIMDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCGLIM.h"
#include "MFCGLIMDlg.h"
#include "afxdialogex.h"
#include <iostream>

#define CIRCLE_RADIUS 10

#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#define new DEBUG_NEW
#endif


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
public:
//	afx_msg void OnLbnDblclkListImage();
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


// CMFCGLIMDlg 대화 상자



CMFCGLIMDlg::CMFCGLIMDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGLIM_DIALOG, pParent)
	, m_nX1(0)
	, m_nY1(0)
	, m_nX2(0)
	, m_nY2(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGLIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_X1, m_nX1);
	DDX_Text(pDX, IDC_EDIT_Y1, m_nY1);
	DDX_Text(pDX, IDC_EDIT_X2, m_nX2);
	DDX_Text(pDX, IDC_EDIT_Y2, m_nY2);
}

BEGIN_MESSAGE_MAP(CMFCGLIMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ACTION, &CMFCGLIMDlg::OnBnClickedBtnAction)
	ON_BN_CLICKED(IDC_BTN_OPEN, &CMFCGLIMDlg::OnBnClickedBtnOpen)
	ON_BN_CLICKED(IDC_BTN_DRAW, &CMFCGLIMDlg::OnBnClickedBtnDraw)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMFCGLIMDlg 메시지 처리기

BOOL CMFCGLIMDlg::OnInitDialog()
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
	m_ImageListDlg = new IMAGELISTDlg;
	m_ImageListDlg->Create(IDD_IMAGELISTDlg, this);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGLIMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCGLIMDlg::OnPaint()
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

	int nWidth = 800;
	int nHeight = 600;
	int nBpp = 8;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8)
	{
		static RGBQUAD rgb[256];

		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	updateDisplay();
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCGLIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCGLIMDlg::updateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

bool CMFCGLIMDlg::validImagePosition(int i, int j)
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	CRect rect(0, 0, nWidth, nHeight);

	return rect.PtInRect(CPoint(i, j));
}

void CMFCGLIMDlg::drawCircle(int nX, int nY, int nRadius)
{
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nPitch = m_Image.GetPitch();
	for (int j = nY - nRadius; j < nY + nRadius * 2; j++)
	{
		for (int i = nX - nRadius; i < nX+ nRadius * 2; i++)
		{
			if (isInCircle(i, j, nX, nY, nRadius))
				if (validImagePosition(i, j))
					fm[j * nPitch + i] = 0;
		}
	}
	updateDisplay();
}

bool CMFCGLIMDlg::isInCircle(int i, int j, int nXpos, int nYpos, int nRadius)
{
	bool bRet = false;

	double dx = i - nXpos;
	double dy = j - nYpos;
	double dDist = dx * dx + dy * dy;

	if (dDist < nRadius * nRadius)
		bRet = true;

	return bRet;
}

int CMFCGLIMDlg::repeatBig(int x ,int y)
{
	if (x < 0)
		x *= -1;
	if (y < 0)
		y *= -1;

	if (x < y)
		return y;
	else
		return y;
}

void CMFCGLIMDlg::OnBnClickedBtnAction()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	int nCenterX = m_nX1;
	int nCenterY = m_nY1;
	int f_nCenterX = m_nX2;
	int f_nCenterY = m_nY2;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	int nPitch = m_Image.GetPitch();
	int r_nXcount = -(nCenterX - f_nCenterX);
	int r_nYcount = nCenterY - f_nCenterY;
	int r_nCount = repeatBig(r_nXcount, r_nYcount);

	if (ImageCount == NULL)
		ImageCount = 1;


	for (int i = 0; i < r_nCount; i++)
	{
		memset(fm, 0xff, nWidth * nHeight);
		drawCircle(nCenterX, nCenterY, CIRCLE_RADIUS);
		if (r_nXcount < 0)
		{
			if (i < -(r_nXcount)-1)
				nCenterX--;
		}
		else
		{
			if (i < r_nXcount - 1)
				nCenterX++;
		}

		if (r_nYcount < 0)
		{
			if (i < -(r_nYcount)-1)
				nCenterY++;
		}
		else
		{
			if (i < r_nYcount - 1)
				nCenterY--;
		}
		saveImage(i, r_nCount);
		Sleep(1);
		

	}

	UpdateData(false);

}

void CMFCGLIMDlg::saveImage(int i, int count)
{
	CString ImagePath;
	if (count >= 10)
	{
		if (i % 10 == 0)
		{
			m_ImageListDlg->ListInsertCount(ImageCount);
			ImagePath.Format(_T("%d.bmp"), ImageCount++);
			m_Image.Save(ImagePath);
		}
	}
	else if (count >= 3)
	{
		if (i % 3 == 0)
		{
			m_ImageListDlg->ListInsertCount(ImageCount);
			ImagePath.Format(_T("%d.bmp"), ImageCount++);
			m_Image.Save(ImagePath);
		}
	}
	else
	{
		m_ImageListDlg->ListInsertCount(ImageCount);
		ImagePath.Format(_T("%d.bmp"), ImageCount++);
		m_Image.Save(ImagePath);
	}
}

void CMFCGLIMDlg::OnBnClickedBtnOpen()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ImageListDlg->ShowWindow(SW_SHOW);
}


void CMFCGLIMDlg::OnBnClickedBtnDraw()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	int nCenterX = m_nX1;
	int nCenterY = m_nY1;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	drawCircle(nCenterX, nCenterY, CIRCLE_RADIUS);
	UpdateData(false);
}




void CMFCGLIMDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	delete m_ImageListDlg;
}
