
// mfctestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfctest.h"
#include "mfctestDlg.h"
#include "afxdialogex.h"
#include <atlImage.h>
#include"CPromotionDlg.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmfctestDlg 대화 상자



CmfctestDlg::CmfctestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCTEST_DIALOG, pParent)
{
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmfctestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmfctestDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CmfctestDlg 메시지 처리기

BOOL CmfctestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	
	
	imgBoard.Load(L"Pieces\\900px-Chess_Board.png");
	imgSelect.Load(L"Pieces\\Select_Green.png");
	imgAttack.Load(L"Pieces\\Attack_Red.png");

	SetWindowPos(NULL, 0, 0, imgBoard.GetWidth() + 400, imgBoard.GetHeight() + 50, SWP_NOZORDER);

	turnsize.CreatePointFont(180,L"굴림");
	turnLable = new CStatic;
	turnLable->Create(_T("Turn"), WS_CHILD | WS_VISIBLE | SS_LEFT,	CRect(650, 10, 800, 40), this);
	turnLable->SetFont(&turnsize, TRUE);

	colorsize.CreatePointFont(240, L"굴림");
	colorLable = new CStatic;
	colorLable->Create(_T("Black"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(750, 50, 1000, 90), this);
	colorLable->SetFont(&colorsize, TRUE);

	replay_Btn.Create(_T("RESTART"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(650, 360, 1000, 460), this, 2501);
	surrender_Btn.Create(_T("SURRENDER"), WS_CHILD | WS_VISIBLE | SS_LEFT, CRect(660, 500, 1000, 600), this, 2502);

	endGame = false;
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmfctestDlg::OnPaint()
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
		//CDialogEx::OnPaint();
		CPaintDC dc(this);
		imgBoard.Draw(dc, 0, 0);
		for (int i = 1; i < 65; i++)
		{
			Piece* ptr = mboard.Get_Piece(mboard.Get_board(),i);
			if (ptr != nullptr)
			{
				ptr->imgsrc.Draw(dc, BoardToXCoordinate(i), BoardToYCoordinate(i));
			}
		}
		cout << endl;
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfctestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CmfctestDlg::BoardToXCoordinate(int boardPos)
{
	if (boardPos % 8 == 0)
		return 560;
	else
		return ((boardPos%8) * 80) - 80;
}

int CmfctestDlg::BoardToYCoordinate(int boardPos)
{
	if (boardPos % 8 == 0)
		return (8 - (boardPos / 8)) * 80;
	else
		return (7 - (boardPos / 8)) * 80;
}

int CmfctestDlg::CoordinateToBoard(int x,int y)
{
	x = (x / 80) + 1;
	y = 8 - (y / 80);
	return ((y - 1) * 8) + x;
}

CString CmfctestDlg::ColorToString(PlayerColor playerColor)
{
	CString res;
	switch (playerColor)
	{
	case PlayerColor::Black:
		res.Format(L"Black");
		return res;
		break;
	case PlayerColor::White:
		res.Format(L"White");
		return res;
		break;
	}
}

CString CmfctestDlg::PieceToString(PieceType pieceType)
{
	CString res;
	switch (pieceType)
	{
	case PieceType::BISHOP:
		res.Format(L"BISHOP");
		return res;
		break;
	case PieceType::KING:
		res.Format(L"KING");
		return res;
		break;
	case PieceType::KNIGHT:
		res.Format(L"KNIGHT");
		return res;
		break;
	case PieceType::PAWN:
		res.Format(L"PAWN");
		return res;
		break;
	case PieceType::QUEEN:
		res.Format(L"QUEEN");
		return res;
		break;
	case PieceType::ROOK:
		res.Format(L"ROOK");
		return res;
		break;
	}
}

void CmfctestDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	vector<int> movable;

	CClientDC dc1(this);

	int x = point.x/80;
	int y = point.y/80;

	x = x * 80;
	y = y * 80;
	if (!endGame)
	{
		if (!mboard.Get_Selected())
		{
			movable = mboard.PieceSelect(mboard.Get_board(), CoordinateToBoard(x, y));
			if (movable[0] != 98)
			{
				imgSelect.AlphaBlend(dc1, x, y, 100);
				for (int i = 0; i < movable.size(); i++)
				{
					imgAttack.AlphaBlend(dc1, BoardToXCoordinate(movable[i]) , BoardToYCoordinate(movable[i]) , 100);
				}
			}
			selectX = x;
			selectY = y;
		}

		else if (mboard.Get_Selected())
		{
			int ch_num;
			int ptr = CoordinateToBoard(x, y);
			int ptr1 = CoordinateToBoard(selectX, selectY);
			ch_num = mboard.PieceMove(mboard.Get_board(), CoordinateToBoard(x, y));
			int save_pos=ptr;

			if (ch_num == 99)
			{
				//상황별 처리 표시
				GameRule();
				Label_Print();
			}
			else if (ch_num == 89 && mboard.Get_promotion())
			{
				int i;
				CPromotionDlg pDlg;
				pDlg.ch = true;
				if (IDOK == pDlg.DoModal())
				{
					i = pDlg.i;
					mboard.Promotion(mboard.Get_board(), save_pos, pDlg.i);
				}
				pDlg.DestroyWindow();
				//상황별 처리 표시
				GameRule();
				Label_Print();
				
			}
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


HBRUSH CmfctestDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  여기서 DC의 특성을 변경합니다.
	if (colorLable == pWnd)
	{
		if (mboard.Get_turn() % 2 == 1)
			pDC->SetTextColor(RGB(208, 211, 212));
		else
			pDC->SetTextColor(RGB(0, 0, 0));
	}
	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.
	return hbr;
}


//BOOL CmfctestDlg::OnCommand(WPARAM wParam, LPARAM lParam)
//{
//	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
//
//	cout << wParam << endl;
//	if (wParam = 2501)
//	{
//		mboard.MakeBoard();
//		this->InvalidateRect(NULL, TRUE);
//	}
//	
//	return CDialogEx::OnCommand(wParam, lParam);
//}


BOOL CmfctestDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	switch (LOWORD(wParam))
	{
	case 2501:
		
		mboard.Restard_Game();
		Label_Print();
		endGame = false;
		break;
	case 2502:
		if (!endGame) 
		{
			CString csrt;
			csrt.Format(L"%s is surrender \n %s WIN!!", mboard.Get_turn() % 2 == 0 ? L"Black" : L"White", mboard.Get_turn() % 2 == 0 ? L"White" : L"Black");
			MessageBox(csrt, _T("Surrender"), MB_ICONINFORMATION);
			endGame = true;
		}
		break;
	}
	return CDialogEx::OnCommand(wParam, lParam);
}

void CmfctestDlg::GameRule()
{
	if (mboard.Get_check())
	{
		mboard.Get_turn() % 2 == 0 ? colorLable->SetWindowTextW(L"Check! Black") : colorLable->SetWindowTextW(L"Check! White");
		cout << "CHECK" << endl;
	}

	else if (mboard.Get_checkmate())
	{
		CString csrt;
		csrt.Format(L"Checkmate \n %s WIN!!", mboard.Get_turn() % 2 == 1 ? L"Black" : L"White");
		MessageBox(csrt, _T("Checkmate"), MB_ICONINFORMATION);
		mboard.Get_turn() % 2 == 1 ? colorLable->SetWindowTextW(L"Checkmate! Black WIN") : colorLable->SetWindowTextW(L"Checkmate! White WIN");
		endGame = true;
	}
	else if (mboard.Get_stalemate())
	{
		CString csrt;
		csrt.Format(L"Stalemate \n!!DRAW!!");
		MessageBox(csrt, _T("Stalemate"), MB_ICONINFORMATION);
		colorLable->SetWindowTextW(L"DRAW");
		endGame = true;
	}
	else if (!mboard.Get_check()) 
	{
		mboard.Get_turn() % 2 == 0 ? colorLable->SetWindowTextW(L"Black") : colorLable->SetWindowTextW(L"White");
		cout << "!CHECK" << endl;
	}
}

void CmfctestDlg::Label_Print()
{
	colorsize.DeleteObject();
	colorsize.CreatePointFont(240, L"굴림");
	colorLable->SetFont(&colorsize);
	this->InvalidateRect(NULL, TRUE);
}