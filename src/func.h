#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <random>
#include <ctime>

class BLACKJACK {
private:
    std::mt19937 generator;
    std::random_device::result_type SEED;

public:
    BLACKJACK();

    std::vector<std::string> CARD_DECK = {
        "10C", "10D", "10H", "10S", 
        "2C", "2D", "2H", "2S", 
        "3C", "3D", "3H", "3S", 
        "4C", "4D", "4H", "4S", 
        "5C", "5D", "5H", "5S", 
        "6C", "6D", "6H", "6S", 
        "7C", "7D", "7H", "7S", 
        "8C", "8D", "8H", "8S", 
        "9C", "9D", "9H", "9S", 
        "AC", "AD", "AH", "AS", 
        "JC", "JD", "JH", "JS", 
        "KC", "KD", "KH", "KS", 
        "QC", "QD", "QH", "QS"
    };
    std::vector<std::string> CARDS_LEFT = {
        "10C", "10D", "10H", "10S", 
        "2C", "2D", "2H", "2S", 
        "3C", "3D", "3H", "3S", 
        "4C", "4D", "4H", "4S", 
        "5C", "5D", "5H", "5S", 
        "6C", "6D", "6H", "6S", 
        "7C", "7D", "7H", "7S", 
        "8C", "8D", "8H", "8S", 
        "9C", "9D", "9H", "9S", 
        "AC", "AD", "AH", "AS", 
        "JC", "JD", "JH", "JS", 
        "KC", "KD", "KH", "KS", 
        "QC", "QD", "QH", "QS"
    };

    std::unordered_map<std::string, std::pair<std::string, int>> DECK = {
        {"10C", {"10C.png", 10}}, {"10D", {"10D.png", 10}}, 
        {"10H", {"10H.png", 10}}, {"10S", {"10S.png", 10}},
        {"2C", {"2C.png", 2}}, {"2D", {"2D.png", 2}}, 
        {"2H", {"2H.png", 2}}, {"2S", {"2S.png", 2}},
        {"3C", {"3C.png", 3}}, {"3D", {"3D.png", 3}}, 
        {"3H", {"3H.png", 3}}, {"3S", {"3S.png", 3}},
        {"4C", {"4C.png", 4}}, {"4D", {"4D.png", 4}}, 
        {"4H", {"4H.png", 4}}, {"4S", {"4S.png", 4}},
        {"5C", {"5C.png", 5}}, {"5D", {"5D.png", 5}}, 
        {"5H", {"5H.png", 5}}, {"5S", {"5S.png", 5}},
        {"6C", {"6C.png", 6}}, {"6D", {"6D.png", 6}}, 
        {"6H", {"6H.png", 6}}, {"6S", {"6S.png", 6}},
        {"7C", {"7C.png", 7}}, {"7D", {"7D.png", 7}}, 
        {"7H", {"7H.png", 7}}, {"7S", {"7S.png", 7}},
        {"8C", {"8C.png", 8}}, {"8D", {"8D.png", 8}}, 
        {"8H", {"8H.png", 8}}, {"8S", {"8S.png", 8}},
        {"9C", {"9C.png", 9}}, {"9D", {"9D.png", 9}}, 
        {"9H", {"9H.png", 9}}, {"9S", {"9S.png", 9}},
        {"AC", {"AC.png", 11}}, {"AD", {"AD.png", 11}}, 
        {"AH", {"AH.png", 11}}, {"AS", {"AS.png", 11}},
        {"JC", {"JC.png", 10}}, {"JD", {"JD.png", 10}}, 
        {"JH", {"JH.png", 10}}, {"JS", {"JS.png", 10}},
        {"KC", {"KC.png", 10}}, {"KD", {"KD.png", 10}}, 
        {"KH", {"KH.png", 10}}, {"KS", {"KS.png", 10}},
        {"QC", {"QC.png", 10}}, {"QD", {"QD.png", 10}}, 
        {"QH", {"QH.png", 10}}, {"QS", {"QS.png", 10}}
    };

    std::vector<std::string> PC_CARDS;
    int PC_CARDS_COUNT = 0;
    int PC_POINTS = 0;

    std::vector<std::string> PLAYER_CARDS;
    int PLAYER_CARDS_COUNT = 0;
    int PLAYER_POINTS = 0;

    //int WON_AMOUNT = 0;
    int LAST_BET = 0;
    int BET_AMOUNT = 0;
    int YOU_HAVE = 1000;

    std::random_device::result_type get_SEED();
    int get_random_index(int size);
    void GAME_RESET(bool new_game);
    //int CHECK_PC_POINTS();
    //int CHECK_PLAYER_POINTS();
    int CHECK_POINTS(std::vector<std::string>& CARDS);
    int CHECK_FOR_WIN();
    void START_GAME(int &bet);
    int HIT();
    int STAND();
};
