#pragma once


// CPromotionDlg 대화 상자

class CPromotionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPromotionDlg)

public:
	CPromotionDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPromotionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PromotionDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	int i;
	CFont promotionFont;
	CStatic* promotionLable;
	bool ch;
	afx_msg void OnClickedQueenbtn();
	afx_msg void OnClickedBishopbtn();
	afx_msg void OnClickedKnightbtn();
	afx_msg void OnClickedRookbtn();
//	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
