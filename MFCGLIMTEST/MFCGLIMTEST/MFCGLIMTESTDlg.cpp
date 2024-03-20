
// MFCGLIMTESTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCGLIMTEST.h"
#include "MFCGLIMTESTDlg.h"
#include "afxdialogex.h"
#include <iostream>

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


// CMFCGLIMTESTDlg 대화 상자



CMFCGLIMTESTDlg::CMFCGLIMTESTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCGLIMTEST_DIALOG, pParent)
	, m_nPosX(0)
	, m_nPosY(0)
	, m_nHalfRadius(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCGLIMTESTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XPOS, m_nPosX);
	DDX_Text(pDX, IDC_EDIT_YPOS, m_nPosY);
	DDX_Text(pDX, IDC_EDIT_HR, m_nHalfRadius);
}

BEGIN_MESSAGE_MAP(CMFCGLIMTESTDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BOARD, &CMFCGLIMTESTDlg::OnBnClickedBtnBoard)
	ON_BN_CLICKED(IDC_BTN_DRAWCIRCLE, &CMFCGLIMTESTDlg::OnBnClickedBtnDrawcircle)
	ON_BN_CLICKED(IDC_BTN_ACT1, &CMFCGLIMTESTDlg::OnBnClickedBtnAct1)
	ON_BN_CLICKED(IDC_BTN_LOAD, &CMFCGLIMTESTDlg::OnBnClickedBtnLoad)
END_MESSAGE_MAP()


// CMFCGLIMTESTDlg 메시지 처리기

BOOL CMFCGLIMTESTDlg::OnInitDialog()
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


	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMFCGLIMTESTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCGLIMTESTDlg::OnPaint()
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
HCURSOR CMFCGLIMTESTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCGLIMTESTDlg::updateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}


void CMFCGLIMTESTDlg::OnBnClickedBtnBoard()
{
	int nWidth = 1200;
	int nHeight = 800;
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


void CMFCGLIMTESTDlg::OnBnClickedBtnDrawcircle()
{
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	memset(fm, 0xff, nWidth * nHeight);
	UpdateData(true);
	int nCenterX = m_nPosX;
	int nCenterY = m_nPosY;
	m_nWidth = m_nPosX;
	m_nHeight = m_nPosY;
	m_nHR = m_nHalfRadius;
	int nPitch = m_Image.GetPitch();

	for (int j = nCenterY - m_nHalfRadius; j < nCenterY + m_nHalfRadius * 2; j++)
	{
		for (int i = nCenterX - m_nHalfRadius; i < nCenterX + m_nHalfRadius * 2; i++)
		{
			if (isInCircle(i, j))
				fm[j * nPitch + i] = 0;
		}
	}
	UpdateData(false);

	updateDisplay();
}

bool CMFCGLIMTESTDlg::isInCircle(int i, int j)
{
	bool bRet = false;

	double dx = i - m_nWidth;
	double dy = j - m_nHeight;
	double dDist = dx * dx + dy * dy;

	if (dDist < m_nHR * m_nHR)
		bRet = true;

	return bRet;
}

void CMFCGLIMTESTDlg::moveCircle()
{
	int nWidth = m_Image.GetWidth();	
	int nHeight = m_Image.GetHeight();
	int nBpp = m_Image.GetPitch();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);

	drawCircle(++m_nWidth,++m_nHeight);

}

void CMFCGLIMTESTDlg::drawCircle(int nSttX, int nSttY)
{
	unsigned char* fm = (unsigned char*)m_Image.GetBits();
	int nPitch = m_Image.GetPitch();
	for (int j = nSttX - m_nHR; j < nSttY + m_nHR * 2; j++)
	{
		for (int i = nSttY - m_nHR; i < nSttX + m_nHR * 2; i++)
		{
			if (isInCircle(i, j))
				fm[j * nPitch + i] = 0;
		}
	}
	updateDisplay();
}


void CMFCGLIMTESTDlg::OnBnClickedBtnAct1()
{
	for (int i = 0; i < 200; i++)
	{
		moveCircle();
		if (i % 20 == 0)
		{
			m_Image.Save(g_strFileimage);
			nsaveCount++;
			g_strFileimage.Format(_T("C:\\Users\\IOT\\source\repos\\mfcExam\\GLIMIMAGE\\save%d.bmp"),nsaveCount);
		}
		Sleep(10);
	}
}

void CMFCGLIMTESTDlg::OnBnClickedBtnLoad()
{
	int nRandnum = rand() % nsaveCount;
	g_strFileimage.Format(_T("C:\\Users\\IOT\\source\\repos\\mfcExam\\GLIMIMAGE\\save%d.bmp"), nRandnum);
	if (m_Image != NULL)
	{
		m_Image.Destroy();
	}
	m_Image.Load(g_strFileimage);

	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	int nWidth = m_Image.GetWidth();
	int nHeight = m_Image.GetHeight();
	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	CRect rect(0, 0, nWidth, nHeight);
	for (int j = rect.top; j < rect.bottom; j++)
	{
		for (int i = rect.left; i < rect.right; i++)
		{
			if (fm[j * nPitch + i] == 0)
			{
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = nSumX / nCount;
	double dCenterY = nSumY / nCount;

	std::cout << "중심값 (x,y) :" << dCenterX << "\t" << dCenterY << std::endl;
	updateDisplay();
}
