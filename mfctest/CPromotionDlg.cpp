// CPromotionDlg.cpp: 구현 파일
//

#include "pch.h"
#include "mfctest.h"
#include "CPromotionDlg.h"
#include "afxdialogex.h"


// CPromotionDlg 대화 상자

IMPLEMENT_DYNAMIC(CPromotionDlg, CDialogEx)

CPromotionDlg::CPromotionDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PromotionDlg, pParent)
{
	
}

CPromotionDlg::~CPromotionDlg()
{
}

void CPromotionDlg::DoDataExchange(CDataExchange* pDX)
{
	if (ch)
	{
		promotionFont.CreatePointFont(280, L"굴림");
		promotionLable = new CStatic;
		promotionLable->Create(_T("Promotion"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(150, 5, 400, 50), this);
		promotionLable->SetFont(&promotionFont, TRUE);
		ch = false;
	}
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPromotionDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPromotionDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_QueenBtn, &CPromotionDlg::OnClickedQueenbtn)
	ON_BN_CLICKED(IDC_BishopBtn, &CPromotionDlg::OnClickedBishopbtn)
	ON_BN_CLICKED(IDC_KnightBtn, &CPromotionDlg::OnClickedKnightbtn)
	ON_BN_CLICKED(IDC_RookBtn, &CPromotionDlg::OnClickedRookbtn)
END_MESSAGE_MAP()


// CPromotionDlg 메시지 처리기


void CPromotionDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//MessageBox(_T("OKOKOK"));
	i = 100;

	CDialogEx::OnOK();
}


void CPromotionDlg::OnClickedQueenbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = 4;
	CDialogEx::OnOK();
}


void CPromotionDlg::OnClickedBishopbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = 3;
	CDialogEx::OnOK();
}


void CPromotionDlg::OnClickedKnightbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = 2;
	CDialogEx::OnOK();
}


void CPromotionDlg::OnClickedRookbtn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	i = 1;
	CDialogEx::OnOK();
}


//BOOL CPromotionDlg::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//	if (wParam = 101)
//	{
//
//	}
//
//	else if (wParam = 102)
//	{
//
//	}
//	return CDialogEx::OnCommand(wParam, lParam);
//}
