// IMAGELISTDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MFCGLIM.h"
#include "IMAGELISTDlg.h"
#include "afxdialogex.h"
#include <iostream>

// IMAGELISTDlg 대화 상자

IMPLEMENT_DYNAMIC(IMAGELISTDlg, CDialogEx)

IMAGELISTDlg::IMAGELISTDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_IMAGELISTDlg, pParent)
{

}

IMAGELISTDlg::~IMAGELISTDlg()
{
}

void IMAGELISTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_IMAGE, m_imageList);
}


BEGIN_MESSAGE_MAP(IMAGELISTDlg, CDialogEx)
	ON_LBN_SELCHANGE(IDC_LIST_IMAGE, &IMAGELISTDlg::OnLbnSelchangeListImage)
	ON_WM_PAINT()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

void IMAGELISTDlg::ListInsertCount(int nCount)
{
	CString ImagePath;
	m_imageList.ResetContent();
	for (int i = 1; i < nCount+1; i++)
	{
		ImagePath.Format(_T("%d.bmp"), i);
		m_imageList.AddString(ImagePath);
	}


}

// IMAGELISTDlg 메시지 처리기


void IMAGELISTDlg::OnLbnSelchangeListImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString ImagePath;
	int nIndex = m_imageList.GetCurSel();

	m_imageList.GetText(nIndex, ImagePath);
	if (m_Image != NULL)
	{
		m_Image.Destroy();
	}
	m_Image.Load(ImagePath);

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

	for (int i = 0; i < 5; i++)
	{
		fm[((int)dCenterY-2+i) * nPitch + (int)dCenterX-2+i] = 0xff;
		fm[((int)dCenterY-2+i) * nPitch + (int)dCenterX+2-i] = 0xff;
	}


	std::cout << "중심값 (x,y) :" << dCenterX << "\t" << dCenterY << std::endl;
	updateDisplay();
}

void IMAGELISTDlg::updateDisplay()
{
	CClientDC dc(this);
	m_Image.Draw(dc, 0, 0);
}

void IMAGELISTDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
				   // 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_Image != NULL)
	{
		m_Image.Destroy();
	}
	int nWidth = 800;
	int nHeight = 600;
	int nBpp = 8;
	if (m_Image == NULL)
	{
		m_Image.Create(nWidth, -nHeight, nBpp);
		if (nBpp == 8)
		{
			static RGBQUAD rgb[256];

			for (int i = 0; i < 256; i++)
				rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;

			m_Image.SetColorTable(0, 256, rgb);
		}
		unsigned char* fm = (unsigned char*)m_Image.GetBits();
		memset(fm, 0xff, nWidth * nHeight);
	}

	updateDisplay();
}


void IMAGELISTDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
