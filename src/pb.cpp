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

#include "pb.h"


Ball::Ball(int i) { number = i; }

int   Ball::getNumber() { return number; }
bool  Ball::isRed()     { return Red; }

bool Ball::operator == (int i) const { return number == i; }
bool Ball::operator == (Ball &rhs) const { return number == rhs.number; }
bool Ball::operator <  (Ball &rhs) const { return number < rhs.number;  }
bool Ball::operator >  (Ball &rhs) const { return number > rhs.number;  }

WhiteBall::WhiteBall(int i) : Ball(i) { Red = false; }

RedBall::RedBall(int i) : Ball(i) { Red = true; }

RandomNumbers::RandomNumbers(int min, int max, int amount)
{
    std::random_device rd;
    std::default_random_engine re(rd());
    std::uniform_int_distribution<int> uid(min, max);

    for (int i = 0; i < amount; i++)
    {
        int num = uid(re);

        for (int n : numbers)
        {
            if (n == num)
                num = uid(re);
        }

        numbers.push_back(num);
    }
}

std::vector<int> RandomNumbers::getNumbers() { return numbers; }

Ticket::Ticket()
{
    RandomNumbers ticketNums(1, 58, 6);
    numbers = ticketNums.getNumbers();
    std::sort(numbers.begin(), numbers.end());
}

void Ticket::display()
{
    std::cout << "Ticket:  ";
    for (int i : numbers)
    {
        std::cout << std::setw(2) << i << " ";
    }
    std::cout << std::endl;
}

std::vector<int> Ticket::getNumbers()  { return numbers; }

Lottery::Lottery()
{
    RandomNumbers RandomWhite(1, 58, 5);
    RandomNumbers RandomRed(1, 34, 1);

    for (int n : RandomWhite.getNumbers())
    {
        balls.push_back(new WhiteBall(n));
    }

    std::sort(balls.begin(), balls.end(), [](Ball* a, Ball* b){ return *a < *b; });

    balls.push_back(new RedBall(RandomRed.getNumbers()[0]));
}

Lottery::~Lottery()
{
    for (auto ball : balls)
    {
        delete ball;
    }
}

void Lottery::display()
{
    std::cout << "Lottery: ";

    for (auto ball : balls)
    {
        if (ball->isRed())
            std::cout << "Red number: " << ball->getNumber() << std::endl;
        else
            std::cout << std::setw(2) << ball->getNumber() << " ";
    }
}

std::vector<Ball*> Lottery::getBalls() { return balls; }

Winning::Winning(std::vector<Ticket*> tickets, std::vector<Ball*> balls)
{
    for (auto ticket : tickets)
    {
        int matches = 0;
        bool hasRed = false;

        for (int number : ticket->getNumbers())
        {
            for (auto ball : balls)
            {
                if (*ball == number)
                {
                    matches++;

                    if (ball->isRed())
                        hasRed = true;
                }
            }
        }

        winnsPerTicket.push_back(matches);
        hasRedTicket.push_back(hasRed);
    }
}

int Winning::getWinnings()
{
    for (size_t i = 0; i < winnsPerTicket.size(); i++)
    {
        std::cout << "Got " << winnsPerTicket[i] << " matches.";

        if (hasRedTicket[i])
            std::cout << " And has got the red ball!" << std::endl;
        else
            std::cout << " But has not got the red ball." << std::endl;
    }

    return 0;
}

Game::~Game()
{
    for (auto ticket : tickets)
    {
        delete ticket;
    }
}

void Game::Menu()
{
    int numTic = 0;
    std::cout << "Welcome to the PowerBall Lottery!" << std::endl;
    std::cout << "To play you need to purchase a ticket at $2. More tickets increase the odds to win." << std::endl;
    std::cout << "How many tickets would you like? " << std::endl;

    do
    {
        std::cout << "Enter amount of tickets you would like to purchase: ";
        std::cin >> numTic;
        std::cin.sync();

        if ((numTic < 1) || (numTic > 100))
        {
            std::cout << "Input invalid. Needs to be a number between 1 and 100. Please try again" << std::endl;
        }
    } while ((numTic < 1) || (numTic > 100));

    createTickets(numTic);
    std::cout << "Your tickets are registered. Thank you for playing the PowerBall lottery!" << std::endl;
}

void Game::Play()
{
    std::cout << "Let\'s see this weeks PowerBall lottery numbers!" << std::endl;
    lotto.display();

    for (auto ticket : tickets)
    {
        ticket->display();
    }

    Winning w(tickets, lotto.getBalls());
    w.getWinnings();
}

void Game::createTickets(int numTic)
{
    for (int i = 0; i < numTic; i++)
    {
        tickets.push_back(new Ticket);
    }
}
