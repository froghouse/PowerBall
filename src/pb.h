/**
 *  Poweball, a simple game that generates random numbers
 *  Copyright (C) 2017  Tomas Landberg
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <iostream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>

#ifndef __PB_H__
#define __PB_H__ 1

class Ball
{
    public:
        Ball() = default;
        Ball(int i);
        int   getNumber();
        bool  isRed();
        bool operator == (int i) const;
        bool operator == (Ball &rhs) const;
        bool operator <  (Ball &rhs) const;
        bool operator >  (Ball &rhs) const;
    protected:
        int number;
        bool Red;
};

class WhiteBall : public Ball
{
    public:
        WhiteBall(int i);
};

class RedBall : public Ball
{
    public:
        RedBall(int i);
};

class RandomNumbers
{
    public:
        RandomNumbers(int min, int max, int amount);
        std::vector<int> getNumbers();
    private:    
        std::vector<int> numbers;
};

class Ticket
{
    public:
        Ticket();
        void display();
        std::vector<int> getNumbers();
    private:
        std::vector<int> numbers;
};

class Lottery
{
    public:
        Lottery();
        ~Lottery();
        void display();
        std::vector<Ball*> getBalls();
    private:
        std::vector<Ball*> balls;
};

class Winning
{
    public:
        Winning(std::vector<Ticket*> tickets, std::vector<Ball*> balls);
        int getWinnings();
    private:
        std::vector<int> winnsPerTicket;
        std::vector<bool> hasRedTicket;
};

class Game
{
    public:
        Game();
        ~Game();
        void Menu();
        void Play();
    private:
        std::vector<Ticket*> tickets;
        Lottery lotto;
        void createTickets(int numTic);
};

#endif
