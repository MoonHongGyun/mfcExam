#pragma once


// IMAGELISTDlg 대화 상자

class IMAGELISTDlg : public CDialogEx
{
	DECLARE_DYNAMIC(IMAGELISTDlg)

public:
	IMAGELISTDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~IMAGELISTDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMAGELISTDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_imageList;
	void ListInsertCount(int nCount);
	afx_msg void OnLbnSelchangeListImage();

private:
	CImage m_Image;
	void updateDisplay();
public:
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
};
