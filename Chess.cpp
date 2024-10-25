#include<iostream>
#include<string>

#include<fstream>    
#include<windows.h>
#include<conio.h>
using namespace std;
#define white 0
#define black 1
#define dim 8
#define gap 12
#define mul 5
#define c1 12
#define c2 6
#define kill 4
#define move 10
#define slfchk 5
#define promotion 11

struct position
{
	int pri, pci;
};
struct pieces
{
	position pos;
	int color;
	char sym;

};
//print box


void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}


void printbox(int sr, int sc, int color)
{
	char sym = -37;
	SetClr(color);
	for (int ri = sr - 1; ri < sr + mul - 1; ri++)
	{
		for (int i = sc - 1; i < sc + mul - 1; i++)
		{
			gotoRowCol(ri, i);
			cout << sym;
		}
	}
	SetClr(7);
}
//move validating function
bool validsourcemove(pieces* b[][dim], int sr, int sc, int turn)
{
	if (b[sr][sc] == nullptr)
		return false;
	if (b[sr][sc]->color == turn)
		return true;
	else return false;
}
bool validdestinationmove(pieces* b[][dim], int dr, int dc, int turn)
{
	return ((dr < dim && dc < dim) && ((b[dr][dc] == nullptr) || (b[dr][dc]->color != turn)));

}
//board & turn function
void printhori(int ri, int sc, int ec)
{
	char sym = -37;
	for (int ci = mul * (gap + sc) - 2; ci < mul * (gap + ec) - 1; ci++)
	{
		gotoRowCol(ri - 2, ci);
		cout << sym;
	}
}
void printverti(int ri, int sc, int ec)
{
	char sym = -37;
	for (int ci = mul * (gap + sc) - 2; ci < mul * (gap + ec) - 1; ci++)
	{
		gotoRowCol(ci, ri - 2);
		cout << sym;
	}
}
void printgrid()
{
	char sym = -37;
	for (int ri = 0; ri <= dim; ri++)
	{
		int rt = mul * (gap + ri);
		printhori(rt, 0, dim);
		printverti(rt, 0, dim);
	}
}
void init(pieces* b[][dim])
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (ri > 1 && ri < dim - 2)
			{
				b[ri][ci] = nullptr;

			}
			else if (ri == 1)
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'p';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if (ri == dim - 2)
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'P';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == 0 && ci == 0) || ri == 0 && ci == dim - 1)
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'r';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == dim - 1 && ci == 0) || ri == dim - 1 && ci == dim - 1)
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'R';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == 0 && ci == 1) || (ri == 0 && ci == dim - 2))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'h';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == dim - 1 && ci == 1) || (ri == dim - 1 && ci == dim - 2))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'H';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == 0 && ci == 2) || (ri == 0 && ci == dim - 3))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'b';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == dim - 1 && ci == 2) || (ri == dim - 1 && ci == dim - 3))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'B';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == 0 && ci == 4))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'k';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == dim - 1 && ci == 4))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'K';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == 0 && ci == 3))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'q';
				b[ri][ci]->color = white;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
			else if ((ri == dim - 1 && ci == 3))
			{
				b[ri][ci] = new pieces[1];
				b[ri][ci]->sym = 'Q';
				b[ri][ci]->color = black;
				b[ri][ci]->pos.pri = ri;
				b[ri][ci]->pos.pci = ci;
			}
		}
	}
}
void displayboard(pieces* b[][dim])
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			int r = mul * (gap + ri);
			int c = mul * (gap + ci);

			int color;
			{
				if ((ri + ci) % 2 == 0)
					color = c1;
				else
					color = c2;
			}
			if (b[ri][ci] == nullptr)
			{
				printbox(r, c, color);
				continue;
			}
			else
			{
				printbox(r, c, color);
				gotoRowCol(r, c);
				cout << b[ri][ci]->sym;
			}
		}
	}
}
//load
void load(pieces* b[][dim], int& turn)
{
	ifstream rdr("chesss.txt");
	rdr >> turn;
	turn++;
	turn %= 2;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			char g;

			rdr >> g;
			if (g == '-')
			{
				b[ri][ci] = nullptr;
			}
			else
			{
				b[ri][ci] = new pieces[1];
				rdr >> b[ri][ci]->color;
				rdr >> b[ri][ci]->pos.pci;
				rdr >> b[ri][ci]->pos.pri;
				b[ri][ci]->sym = g;
			}
		}
	}
}
void initt(pieces* b[][dim], int& turn)
{
	int choice;
	gotoRowCol(88 / 2, 166 / 6);
	cout << "\t\t\t\t\t\t 1. NEW GAME " << endl;
	gotoRowCol(88 / 2 + 1, 166 / 6);
	cout << "\t\t\t\t\t\t 2. LOAD PREVIOUS GAME" << endl;
	gotoRowCol(88 / 2 + 2, 166 / 6);
	cout << "\t\t\t\t\t\t 0. EXIT " << endl;
	cout << " enter choice ";
	cin >> choice;
	switch (choice)
	{
	case 1:
		init(b);
		break;
	case 2:
		load(b, turn);
		break;
	case 3:
		exit(1);
	default:
		exit(1);
	}
	system("cls");
}
//turn
void turnchange(int& turn)
{
	turn++;
	turn %= 2;
}
//valid piece move
bool validcastling(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	if (sc == dc - 1)
		return false;
	if (sc == dc + 1)
		return false;
	bool tu = (b[sr][sc]->pos.pri != sr || b[sr][sc]->pos.pci != sc);
	if (b[sr][0] == nullptr)
		return false;
	if (b[sr][7] == nullptr)
		return false;
	if (sr == 0)
	{
		if (b[sr][sc]->sym != 'k')
			return false;
		bool fg = ((b[sr][dim - 1]->sym != 'r' && b[sr][0]->sym != 'r'));
		if ((b[sr][sc]->pos.pri != sr || b[sr][sc]->pos.pci != sc) || ((b[sr][dim - 1]->sym != 'r' && b[sr][0]->sym != 'r') || sr != dr))
			return false;
	}
	else
	{
		if (b[sr][sc]->sym != 'K')
			return false;
		bool fj = ((b[sr][dim - 1]->sym != 'R' && b[sr][0]->sym != 'R'));
		if ((b[sr][sc]->pos.pri != sr || b[sr][sc]->pos.pci != sc) || (b[sr][dim - 1]->sym != 'R' && b[sr][0]->sym != 'R') || (sr != dr))
			return false;
	}
	if (sc == dc - 2)
	{
		if (b[sr][dim - 1]->pos.pri != sr || b[sr][dim - 1]->pos.pci != dim - 1)
			return false;
		for (int i = sc + 1; i < dim - 1; i++)
		{
			if (b[sr][i] != nullptr)
			{
				return false;
			}
		}
		return(sc == dc - 2);
	}
	else if (sc == dc + 2)
	{

		if (b[sr][0]->pos.pri != sr || b[sr][0]->pos.pci != 0)
			return false;
		for (int i = 1; i < sc; i++)
		{
			if (b[sr][i] != nullptr)
			{
				return false;
			}
		}
		return (sc == dc + 2);
	}
	return false;
}


void pawnPromotion(pieces* b[][dim], int& sr, int sc, int dr, int dc)
{

	if (b[sr][sc]->sym == 'p' && dr == 7 && sr == 6)
	{
		char pcs[4];
		pcs[0] = 'q';
		pcs[1] = 'r';
		pcs[2] = 'b';
		pcs[3] = 'h';
		int dcc = dc;
		int k = 0;
		for (dcc; dcc < dc + 4; dcc++)
		{
			printbox(mul * (gap + dr + 1), mul * (gap + dcc - 1), promotion);
			gotoRowCol(mul * (gap + dr + 1), mul * (gap + dcc - 1));
			cout << pcs[k];
			k++;
		}
		int drr, dccc = 0;
		do
		{
			getRowColbyLeftClick(drr, dccc);
			drr /= mul;
			dccc /= mul;
			drr -= gap;
			dccc -= gap;
		} while ((drr != dr + 1) || dccc < dc || dccc >= dc + 4);
		if (dccc == dc)
		{
			b[sr][sc]->sym = 'q';
		}
		else if (dccc == dc + 1)
		{
			b[sr][sc]->sym = 'r';
		}
		else if (dccc == dc + 2)
		{
			b[sr][sc]->sym = 'b';
		}
		else if (dccc == dc + 3)
		{
			b[sr][sc]->sym = 'h';
		}
		system("cls");


	}
	else if (b[sr][sc]->sym == 'P' && dr == 0 && sr == 1)
	{
		char pcs[4];
		pcs[0] = 'Q';
		pcs[1] = 'R';
		pcs[2] = 'B';
		pcs[3] = 'H';
		int dcc = dc;
		int k = 0;
		for (dcc; dcc < dc + 4; dcc++)
		{
			printbox(mul * (gap + dr - 1), mul * (gap + dcc - 1), promotion);
			gotoRowCol(mul * (gap + dr - 1), mul * (gap + dcc - 1));
			cout << pcs[k];
			k++;
		}
		int drr, dccc = 0;
		do
		{
			getRowColbyLeftClick(drr, dccc);
			drr /= mul;
			dccc /= mul;
			drr -= gap;
			dccc -= gap;
		} while ((drr != dr - 1) || dccc < dc || dccc >= dc + 4);
		if (dccc == dc)
		{
			b[sr][sc]->sym = 'Q';
		}
		else if (dccc == dc + 1)
		{
			b[sr][sc]->sym = 'R';
		}
		else if (dccc == dc + 2)
		{
			b[sr][sc]->sym = 'B';
		}
		else if (dccc == dc + 3)
		{
			b[sr][sc]->sym = 'H';
		}
		system("cls");


	}


}
bool checkHorizontalmove(int sr, int sc, int dr, int dc)
{
	return(sr == dr && sc != dc);
}
bool checkVerticalmove(int sr, int sc, int dr, int dc)
{
	return(sc == dc && dr != sr);
}
bool checkTWOdiagonalmove(int sr, int sc, int dr, int dc)
{
	return((sr - sc == dr - dc) || (sr + sc == dr + dc));
}
bool checkrook(int sr, int sc, int dr, int dc)
{

	return(checkHorizontalmove(sr, sc, dr, dc) || checkVerticalmove(sr, sc, dr, dc));
}
bool checkbishop(int sr, int sc, int dr, int dc)
{
	return((checkTWOdiagonalmove(sr, sc, dr, dc)));
}
bool checkKing(int sr, int sc, int dr, int dc)
{
	if (sr == dr && sc == dc)
		return false;
	for (int i = -1; i < 2; i++)
	{
		for (int t = -1; t < 2; t++)
		{
			if (sr + i == dr && sc + t == dc)
			{
				return true;
			}
		}
	}
	return false;
}
bool checkpawn(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	if (b[dr][dc] != nullptr)
	{
		if (b[dr][dc]->color != b[sr][sc]->color)
		{

			if (b[sr][sc]->sym == 'p')
			{
				return(((sr == dr - 1) && ((sc == dc - 1) || (sc == dc + 1))));
			}
			else if (b[sr][sc]->sym == 'P')
			{
				return(((sr == dr + 1) && ((sc == dc - 1) || (sc == dc + 1))));
			}

		}
	}
	else if (b[sr][sc]->pos.pci == sc && b[sr][sc]->pos.pri == sr)
	{
		if (b[sr][sc]->sym == 'p')
		{
			return(((sr == dr - 1) || (sr == dr - 2)) && (sc == dc)) && (b[sr + 1][dc] == nullptr);
		}
		else if (b[sr][sc]->sym == 'P')
		{
			return(((sr == dr + 1) || (sr == dr + 2)) && (sc == dc)) && (b[sr - 1][dc] == nullptr);
		}
	}
	else if (b[sr][sc]->sym == 'p')
	{
		return(((sr == dr - 1)) && (sc == dc));
	}
	else if (b[sr][sc]->sym == 'P')
	{
		return(((sr == dr + 1)) && (sc == dc));
	}

	return false;

}
bool pathISclearhorizontal(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	int i;
	if (dc == sc)
		return false;
	if (dc > sc)
	{
		i = 1;
		for (i += sc; i < dc; i++)
		{
			if (b[sr][i] != nullptr)
			{
				return false;
			}
		}
		return true;
	}

	else
	{
		i = -1;
		for (i += sc; i >= dc + 1; i--)
		{
			if (b[sr][i] != nullptr)
			{
				return false;

			}
		}
		return true;

	}
}
bool pathISclearvertical(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	if (dr == sr)
		return false;
	if (dr > sr)
	{
		for (int i = 1 + sr; i < dr; i++)
		{
			if (b[i][sc] != nullptr)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (int i = -1 + sr; i > dr; i--)
		{
			if (b[i][sc] != nullptr)
			{
				return false;
			}
		}
		return true;
	}
}
bool Rightdiagonalpathclr(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	int deltaR = dr - sr;
	int deltaC = dc - sc;
	int rt = 1, ct = 1;
	if (deltaR < 0)
	{
		rt = -1;
	}
	if (deltaC < 0)
	{
		ct = -1;
	}
	for (int i = 1; i < deltaR * rt; i++)
	{
		int mr = (sr)+(i * rt), mc = (sc)+(i * ct);
		if (b[mr][mc] != nullptr)
		{
			return false;
		}
	}
	return true;
}
bool checkhorse(pieces* b[][dim], int sr, int sc, int dr, int dc)
{

	return  ((sr == dr - 2 || sr == dr + 2) && (sc == dc - 1 || sc == dc + 1)) || ((sc == dc - 2 || sc == dc + 2) && (sr == dr - 1 || sr == dr + 1));

}
void castling(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	if (sc == dc - 2)
	{
		b[sr][dc - 1] = new pieces[1];
		b[sr][dc - 1]->color = b[sr][dim - 1]->color;
		b[sr][dc - 1]->sym = b[sr][dim - 1]->sym;
		b[sr][dc - 1]->pos.pci = b[sr][dim - 1]->pos.pci;
		b[sr][dc - 1]->pos.pri = b[sr][dim - 1]->pos.pri;
		b[sr][dim - 1] = nullptr;

	}
	else if (sc == dc + 2)
	{
		b[sr][dc + 1] = new pieces[1];
		b[sr][dc + 1]->color = b[sr][0]->color;
		b[sr][dc + 1]->sym = b[sr][0]->sym;
		b[sr][dc + 1]->pos.pci = b[sr][0]->pos.pci;
		b[sr][dc + 1]->pos.pri = b[sr][0]->pos.pri;
		b[sr][0] = nullptr;
	}
}
bool destination(pieces* b[][dim], int sr, int sc, int dr, int dc)
{
	char t = b[sr][sc]->sym;
	switch (t)
	{
	case 'r':
		return ((checkrook(sr, sc, dr, dc)) && (pathISclearvertical(b, sr, sc, dr, dc) || pathISclearhorizontal(b, sr, sc, dr, dc)));
		break;
	case 'R':
		return (checkrook(sr, sc, dr, dc) && (pathISclearvertical(b, sr, sc, dr, dc) || pathISclearhorizontal(b, sr, sc, dr, dc)));
		break;
	case 'b':
		return ((checkbishop(sr, sc, dr, dc)) && Rightdiagonalpathclr(b, sr, sc, dr, dc));
		break;
	case 'B':
		return ((checkbishop(sr, sc, dr, dc)) && (Rightdiagonalpathclr(b, sr, sc, dr, dc)));
		break;
	case 'q':
		return ((checkrook(sr, sc, dr, dc) && (pathISclearhorizontal(b, sr, sc, dr, dc) || pathISclearvertical(b, sr, sc, dr, dc))) || (checkbishop(sr, sc, dr, dc) && Rightdiagonalpathclr(b, sr, sc, dr, dc)));
		break;
	case 'Q':
		return ((checkrook(sr, sc, dr, dc) && (pathISclearhorizontal(b, sr, sc, dr, dc) || pathISclearvertical(b, sr, sc, dr, dc))) || (checkbishop(sr, sc, dr, dc) && Rightdiagonalpathclr(b, sr, sc, dr, dc)));
		break;
	case'k':
		if (validcastling(b, sr, sc, dr, dc))
		{
			//castling(b, sr, sc, dr, dc);
			return true;
		}
		return checkKing(sr, sc, dr, dc);
		break;
	case'K':
		if (validcastling(b, sr, sc, dr, dc))
		{
			//castling(b, sr, sc, dr, dc);
			return true;
		}
		return checkKing(sr, sc, dr, dc);
		break;
	case'p':
		return checkpawn(b, sr, sc, dr, dc);
		break;
	case'P':
		return checkpawn(b, sr, sc, dr, dc);
		break;
	case 'h':
		return checkhorse(b, sr, sc, dr, dc);
		break;
	case'H':
		return checkhorse(b, sr, sc, dr, dc);
		break;
	}


}
//highltight funtion
void highlight(pieces* b[][dim], int sr, int sc)
{
	bool board[dim][dim];
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			board[ri][ci] = destination(b, sr, sc, ri, ci) && (b[ri][ci] == nullptr || b[sr][sc]->color != b[ri][ci]->color);
			if (board[ri][ci])
			{
				int r = mul * (gap + ri);
				int c = mul * (gap + ci);
				if (validcastling(b, sr, sc, ri, ci))
				{
					gotoRowCol(r, c);
					printbox(r, c, slfchk);
				}
				else if (b[ri][ci] == nullptr)
				{
					gotoRowCol(r, c);
					printbox(r, c, move);
				}
				else if (b[ri][ci] != nullptr)
				{

					gotoRowCol(r, c);
					printbox(r, c, kill);
					gotoRowCol(r, c);
					cout << b[ri][ci]->sym;
				}
			}
		}
	}

}

void updateboard(pieces* b[][dim], int sr, int sc, int dr, int dc)
{

	if (validcastling(b, sr, sc, dr, dc))
	{

		castling(b, sr, sc, dr, dc);
	}

	if (b[dr][dc] != nullptr)
		delete[]b[dr][dc];
	b[dr][dc] = new pieces[1];
	b[dr][dc]->color = b[sr][sc]->color;
	b[dr][dc]->pos = b[sr][sc]->pos;
	b[dr][dc]->sym = b[sr][sc]->sym;
	delete[]b[sr][sc];
	b[sr][sc] = nullptr;
}
//check
void findKing(pieces* b[][dim], position& k, int turn)
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (b[ri][ci] == nullptr)
			{
				continue;
			}
			if (b[ri][ci]->color != turn)
			{
				continue;
			}
			if (b[ri][ci]->sym == 'k' || b[ri][ci]->sym == 'K')
			{
				k.pci = ci;
				k.pri = ri;
				return;
			}
		}
	}
}
void copyboard(pieces* b[][dim], pieces* ccb[][dim])
{
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (b[ri][ci] == nullptr)
			{
				ccb[ri][ci] = nullptr;
				continue;
			}
			else
				ccb[ri][ci] = new pieces[1];
			ccb[ri][ci]->color = b[ri][ci]->color;
			ccb[ri][ci]->pos = b[ri][ci]->pos;
			ccb[ri][ci]->sym = b[ri][ci]->sym;
		}
	}
}
bool check(pieces* b[][dim], int turn, int sr, int sc, int dr, int dc)
{
	position k, cck;
	pieces* ccb[dim][dim];
	copyboard(b, ccb);
	updateboard(ccb, sr, sc, dr, dc);
	findKing(b, k, turn);
	findKing(ccb, cck, turn);
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (b[ri][ci] == nullptr)
			{
				continue;
			}
			if (b[ri][ci]->color == turn)
			{
				continue;
			}
			else
			{
				if (destination(b, ri, ci, k.pri, k.pci))
				{
					if (destination(ccb, ri, ci, cck.pri, cck.pci))
					{
						int r = mul * (gap + k.pri);
						int c = mul * (gap + k.pci);
						gotoRowCol(r, c);

						return true;
					}
				}
			}

		}
	}
	return false;
}
bool selfcheck(pieces* b[][dim], int turn, int sr, int sc, int dr, int dc)
{
	position k, cck;
	pieces* ccb[dim][dim];
	copyboard(b, ccb);
	updateboard(ccb, sr, sc, dr, dc);
	findKing(b, k, turn);
	findKing(ccb, cck, turn);
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (b[ri][ci] == nullptr)
			{
				continue;
			}
			if (b[ri][ci]->color == turn)
			{
				continue;
			}
			else
			{

				if (destination(ccb, ri, ci, cck.pri, cck.pci))
				{
					int r = mul * (gap + k.pri);
					int c = mul * (gap + k.pci);
					gotoRowCol(r, c);
					printbox(r, c, slfchk);
					Sleep(100);
					return true;
				}

			}

		}
	}
	return false;
}
bool checkmate(pieces* b[][dim], int turn)
{
	int sr, sc;
	bool board[dim][dim];
	for (int rii = 0; rii < dim; rii++)
	{
		for (int cii = 0; cii < dim; cii++)
		{
			if (b[rii][cii] == nullptr)
			{
				continue;
			}
			if (b[rii][cii]->color != turn)
			{
				continue;
			}
			else if (b[rii][cii] == nullptr || b[rii][cii]->color == turn)
			{
				sr = rii;
				sc = cii;

				for (int ri = 0; ri < dim; ri++)
				{
					for (int ci = 0; ci < dim; ci++)
					{
						if (destination(b, sr, sc, ri, ci) && ((b[ri][ci] == nullptr || b[sr][sc]->color != b[ri][ci]->color)))
						{
							if (!check(b, turn, sr, sc, ri, ci) && !selfcheck(b, turn, sr, sc, ri, ci))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
bool stalemate(pieces* b[][dim], int turn)
{
	int sr, sc;
	bool board[dim][dim];
	for (int rii = 0; rii < dim; rii++)
	{
		for (int cii = 0; cii < dim; cii++)
		{
			if (b[rii][cii] == nullptr)
			{
				continue;
			}
			if (b[rii][cii]->color != turn)
			{
				continue;
			}
			else if (b[rii][cii] == nullptr || b[rii][cii]->color == turn)
			{
				sr = rii;
				sc = cii;

				for (int ri = 0; ri < dim; ri++)
				{
					for (int ci = 0; ci < dim; ci++)
					{
						if (destination(b, sr, sc, ri, ci) && ((b[ri][ci] == nullptr || b[sr][sc]->color != b[ri][ci]->color)) && (b[sr][sc]->sym != 'k' || b[sr][sc]->sym != 'K'))
						{

							return false;

						}
						else if (destination(b, sr, sc, ri, ci) && ((b[ri][ci] == nullptr || b[sr][sc]->color == b[ri][ci]->color)) && (b[sr][sc]->sym == 'k' || b[sr][sc]->sym == 'K'))
						{

							if (!check(b, turn, sr, sc, ri, ci))
							{
								return false;
							}
						}
					}
				}
			}
		}
	}
	return true;
}
//move function

void selectmove(pieces* b[][dim], int& sr, int& sc, int& dr, int& dc, int turn)
{


	if (turn == white)
	{
		gotoRowCol(mul * (gap - mul + 2), (mul * (gap - mul)) + 7 * mul);
		cout << " player 1's turn ";
	}
	else
	{
		gotoRowCol(mul * (gap - mul + 2), (mul * (gap - mul)) + 7 * mul);
		cout << " player 2's turn ";
	}
	do {
		do
		{

			displayboard(b);
			if (checkmate(b, turn))
			{
				return;
			}
			getRowColbyLeftClick(sr, sc);
			sr += 1;
			sc += 1;
			sr /= mul;
			sc /= mul;
			sr -= gap;
			sc -= gap;
		} while (!(validsourcemove(b, sr, sc, turn)));
		highlight(b, sr, sc);
		getRowColbyLeftClick(dr, dc);
		dr += 1;
		dc += 1;
		dr /= mul;
		dc /= mul;
		dr -= gap;
		dc -= gap;
	} while (!(validdestinationmove(b, dr, dc, turn) && destination(b, sr, sc, dr, dc)) || (selfcheck(b, turn, sr, sc, dr, dc)) || (check(b, turn, sr, sc, dr, dc)));

	if (checkpawn(b, sr, sc, dr, dc))
		pawnPromotion(b, sr, sc, dr, dc);
}
void writefile(pieces* b[][dim], int turn)
{
	ofstream writer("chesss.txt");
	writer << turn << endl;
	for (int ri = 0; ri < dim; ri++)
	{
		for (int ci = 0; ci < dim; ci++)
		{
			if (b[ri][ci] == nullptr)
			{
				writer << '-';
			}
			else
			{
				writer << b[ri][ci]->sym << " ";
				writer << b[ri][ci]->color << " ";
				writer << b[ri][ci]->pos.pci << " ";
				writer << b[ri][ci]->pos.pri << " ";
			}
			writer << endl;
		}
	}
}

int main()
{
	int sr, sc, dr, dc;
	int turn = 0;
	pieces* board[dim][dim];
	initt(board, turn);
	displayboard(board);
	do
	{
		selectmove(board, sr, sc, dr, dc, turn);
		updateboard(board, sr, sc, dr, dc);
		displayboard(board);
		writefile(board, turn);
		turnchange(turn);
	} while (!(checkmate(board, turn) || stalemate(board, turn)));
}