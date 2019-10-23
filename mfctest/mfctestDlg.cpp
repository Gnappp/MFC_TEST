
// mfctestDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "mfctest.h"
#include "mfctestDlg.h"
#include "afxdialogex.h"

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
	
	CString str;
	str.Format(L"C:\\Users\\진화\\Desktop\\공부하는중\\mfctest\\MFC_TEST\\mfctest\\Pieces\\900px-Chess_Board.png");
	imgBoard.Load(str);
	SetWindowPos(NULL, 0, 0, imgBoard.GetWidth()+50, imgBoard.GetHeight()+50, SWP_NOZORDER);
	board = MakeBoard();
	for (int c = 0; c < 2; c++)
	{
		CString color;
		color = ColorToString(PlayerColor(c));
		for (int p = 0; p < 6; p++)
		{
			CString fileName;
			CString piece;
			piece = PieceToString(PieceType(p));
			fileName.Format(L"C:\\Users\\진화\\Desktop\\공부하는중\\mfctest\\MFC_TEST\\mfctest\\Pieces\\%s_%s.png", color, piece);
			imgPiece[c][p].Load(fileName);
		}
	}

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
		//mPiece[1][5].Draw(dc, 0, 560);
		for (int i = 1; i < 65; i++)
		{
			Piece* ptr = board[i].get();
			if (ptr != NULL)
			{
				imgPiece[ptr->get_PlayerColor()][ptr->get_PieceType()].Draw(dc, BoardToXCoordinate(i), BoardToYCoordinate(i));
			}
		}
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmfctestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

unique_ptr<Piece>* CmfctestDlg::MakeBoard()
{
	unique_ptr<Piece>* board = new unique_ptr < Piece>[65];
	board[1] = std::make_unique<Rook>(PlayerColor::White, 1);
	board[2] = std::make_unique<Knight>(PlayerColor::White, 2);
	board[3] = std::make_unique<Bishop>(PlayerColor::White, 3);
	board[4] = std::make_unique<Queen>(PlayerColor::White, 4);
	board[5] = std::make_unique<King>(PlayerColor::White, 5);
	board[6] = std::make_unique<Bishop>(PlayerColor::White, 6);
	board[7] = std::make_unique<Knight>(PlayerColor::White, 7);
	board[8] = std::make_unique<Rook>(PlayerColor::White, 8);
	board[9] = std::make_unique<Pawn>(PlayerColor::White, 9);
	board[10] = std::make_unique<Pawn>(PlayerColor::White, 10);
	board[11] = std::make_unique<Pawn>(PlayerColor::White, 11);
	board[12] = std::make_unique<Pawn>(PlayerColor::White, 12);
	board[13] = std::make_unique<Pawn>(PlayerColor::White, 13);
	board[14] = std::make_unique<Pawn>(PlayerColor::White, 14);
	board[15] = std::make_unique<Pawn>(PlayerColor::White, 15);
	board[16] = std::make_unique<Pawn>(PlayerColor::White, 16);

	board[57] = std::make_unique<Rook>(PlayerColor::Black, 57);
	board[58] = std::make_unique<Knight>(PlayerColor::Black, 58);
	board[59] = std::make_unique<Bishop>(PlayerColor::Black, 59);
	board[60] = std::make_unique<Queen>(PlayerColor::Black, 60);
	board[61] = std::make_unique<King>(PlayerColor::Black, 61);
	board[62] = std::make_unique<Bishop>(PlayerColor::Black, 62);
	board[63] = std::make_unique<Knight>(PlayerColor::Black, 63);
	board[64] = std::make_unique<Rook>(PlayerColor::Black, 64);
	board[49] = std::make_unique<Pawn>(PlayerColor::Black, 49);
	board[50] = std::make_unique<Pawn>(PlayerColor::Black, 50);
	board[51] = std::make_unique<Pawn>(PlayerColor::Black, 51);
	board[52] = std::make_unique<Pawn>(PlayerColor::Black, 52);
	board[53] = std::make_unique<Pawn>(PlayerColor::Black, 53);
	board[54] = std::make_unique<Pawn>(PlayerColor::Black, 54);
	board[55] = std::make_unique<Pawn>(PlayerColor::Black, 55);
	board[56] = std::make_unique<Pawn>(PlayerColor::Black, 56);

	return board;
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

	CClientDC dc(this);

	int x = point.x/80;
	int y = point.y/80;

	x = x * 80;
	y = y * 80;

	if (!mboard.Get_Selected())
	{
		movable=mboard.PieceSelect(board,CoordinateToBoard(x, y));
	}
	else if (mboard.Get_Selected())
	{
		mboard.PieceMove(board, CoordinateToBoard(x, y));
		int ptr = CoordinateToBoard(x, y);
		imgPiece[board[ptr]->get_PlayerColor()][board[ptr]->get_PieceType()].Draw(dc, x, y);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
