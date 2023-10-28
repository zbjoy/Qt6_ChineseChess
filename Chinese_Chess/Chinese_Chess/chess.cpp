#include "chess.h"

#include <iostream>

Chess::Chess()
{
    type = 0;
    Select = false;
}

ChessMap::ChessMap()
{
    iniChessMap();

}

void ChessMap::iniChessMap()
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

    Player = true;

    isWin = 0;
}

void ChessMap::saveChessMap()
{
    QFile file("ChessMap.txt");
    if(!file.open(QFile::WriteOnly))
    {
        return;
    }

    QTextStream out(&file);

    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0;  j < COL; ++j)
        {
            out << chess[i][j].type << ' ';
        }
    }
    //out << "hello world";
    out << Player;

    file.close();
}

void ChessMap::infoChessMap()
{
    QFile file("ChessMap.txt");
    if(!file.open(QFile::ReadOnly))
    {
        return;
    }
    QTextStream in(&file);

    for(int i = 0; i < ROW * COL; ++i)
    {
        in >> debug[i];
    }

    QString temp;
    in >> temp;
    Player = temp.toInt();

    //std::cout << Player << std::endl;

    file.close();



    //std::cout << chessInfo << std::endl;

    for(int i = 0; i < ROW; ++i)
    {
        for(int j = 0; j < COL; ++j)
        {
            //            QByteArray temp = debug[i * COL + j].toLatin1();

            //            char* chessInfo = temp.data();
            chess[i][j].type = debug[i * COL + j].toInt();//(chessInfo[i * COL + j] - '0');
            //std::cout << chessMap.chess[i][j].type << " ";
        }
        //std::cout << std::endl;
    }
}
