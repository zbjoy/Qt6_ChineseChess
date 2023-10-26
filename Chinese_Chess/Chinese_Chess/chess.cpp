#include "chess.h"

Chess::Chess()
{
    type = 0;
    Select = false;
}

ChessMap::ChessMap()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (((i == 0 || i == ROW - 1) && j == 0) || ((i == 0 || i == ROW - 1) && j == COL - 1))
            {
                if (i == 0)
                {
                    chess[i][j].type = 3;
                }
                else
                {
                    chess[i][j].type = 10;
                }
            }
            else if (((i == 0 || i == ROW - 1) && j == 1) || ((i == 0 || i == ROW - 1) && j == COL - 2))
            {
                if (i == 0)
                {
                    chess[i][j].type = 4;
                }
                else
                {
                    chess[i][j].type = 11;
                }

            }
            else if (((i == 0 || i == ROW - 1) && j == 2) || ((i == 0 || i == ROW - 1) && j == COL - 3))
            {
                if (i == 0)
                {
                    chess[i][j].type = 5;
                }
                else
                {
                    chess[i][j].type = 12;
                }
            }
            else if (((i == 0 || i == ROW - 1) && j == 3) || ((i == 0 || i == ROW - 1) && j == COL - 4))
            {
                if (i == 0)
                {
                    chess[i][j].type = 6;
                }
                else
                {
                    chess[i][j].type = 13;
                }
            }
            else if (((i == 0 || i == ROW - 1) && j == 4))
            {
                if (i == 0)
                {
                    chess[i][j].type = 7;
                }
                else
                {
                    chess[i][j].type = 14;
                }
            }
            else if ((i == 3 || i == ROW - 4) && (j == 0 || j == 2 || j == 4 || j == 6 || j == 8 || j == 10))
            {
                if (i == 3)
                {
                    chess[i][j].type = 1;
                }
                else
                {
                    chess[i][j].type = 8;
                }
            }
            else if ((i == 2 || i == ROW - 3) && (j == 1 || j == COL - 2))
            {
                if (i == 2)
                {
                    chess[i][j].type = 2;
                }
                else
                {
                    chess[i][j].type = 9;
                }
            }
            else
            {
                chess[i][j].type = 0;
            }

        }
    }
}
