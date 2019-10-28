
// mfctestDlg.h: 헤더 파일
//

#pragma once

// CmfctestDlg 대화 상자
class CmfctestDlg : public CDialogEx
{
// 생성입니다.
public:
	CmfctestDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	
// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	int selectX;
	int selectY;
	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	CImage imgBoard;
	CImage imgSelect;
	CImage imgAttack;
	CFont turnsize;
	CFont colorsize;
	CFont statussize;
	CFont notationsize;
	CString notationString;
	CStatic* turnLable;
	CStatic* colorLable;
	CStatic* statusLable;
	CStatic* notationLable;
	Board mboard;
	PlayerColor pColor;
	int BoardToXCoordinate(int boardPos);
	int BoardToYCoordinate(int boardPos);
	int CoordinateToBoard(int x, int y);
	CString ColorToString(PlayerColor playerColor);
	CString PieceToString(PieceType pieceType);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
