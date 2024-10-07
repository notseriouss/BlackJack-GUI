#include "func.h"

BLACKJACK::BLACKJACK() {
    std::random_device rd;
    SEED = rd();
    generator = std::mt19937(SEED);
}

std::random_device::result_type BLACKJACK::get_SEED() {
    return SEED;
}

int BLACKJACK::get_random_index(int size) {
    std::uniform_int_distribution<> distribution(0, size - 1);
    return distribution(generator); 
}


void BLACKJACK::GAME_RESET(bool new_game) {
    if (!new_game) {
        LAST_BET = BET_AMOUNT;
    } else {
        YOU_HAVE = 1000;
        LAST_BET = 0;
    }
    BET_AMOUNT = 0;
    PC_CARDS_COUNT = 0;
    PC_POINTS = 0;
    PLAYER_CARDS_COUNT = 0;
    PLAYER_POINTS = 0;
    PC_CARDS.clear();
    PLAYER_CARDS.clear();
    CARDS_LEFT = CARD_DECK;
}

//int BLACKJACK::CHECK_PC_POINTS() {
//    int total_pc_points = 0;
//
//    for (int i = 0; i < PC_CARDS.size(); ++i) {
//        total_pc_points += DECK[PC_CARDS[i]].second;
//    }
//
//    if (total_pc_points > 21) {
//        for (int i = 0; i < PC_CARDS.size(); ++i) {
//            if (PC_CARDS[i][0] == 'A') {
//                total_pc_points -= 10;
//            }
//        }
//    }
//    return total_pc_points;
//}
//
//int BLACKJACK::CHECK_PLAYER_POINTS() {
//    int total_player_points = 0;
//
//    for (int i = 0; i < PLAYER_CARDS.size(); ++i) {
//        total_player_points += DECK[PLAYER_CARDS[i]].second;
//    }
//
//    if (total_player_points > 21) {
//        for (int i = 0; i < PLAYER_CARDS.size(); ++i) {
//            if (PLAYER_CARDS[i][0] == 'A') {
//                total_player_points -= 10;
//            }
//        }
//    }
//    return total_player_points;
//}

int BLACKJACK::CHECK_POINTS(std::vector<std::string>& CARDS) {
    int total_points = 0;

    for (int i = 0; i < CARDS.size(); ++i) {
        total_points += DECK[CARDS[i]].second;
    }

    if (total_points > 21) {
        for (int i = 0; i < CARDS.size(); ++i) {
            if (CARDS[i][0] == 'A') {
                total_points -= 10;
            }
        }
    }

    return total_points;
}

int BLACKJACK::CHECK_FOR_WIN() {
    if (PC_POINTS > 21) { // Player won (Dealer bust)
        //GAME_RESET(false);
        return 0;
    } else if (PLAYER_POINTS > PC_POINTS && PC_POINTS < 21) { // PLayer won (more points)
        //GAME_RESET(false);
        return 0;
    } else if (PLAYER_POINTS == 21 && PLAYER_CARDS_COUNT == 2 && PC_CARDS_COUNT > 2) { // PLayer won (Blackjack)
        //GAME_RESET(false);
        return 0;
    } else if (PLAYER_POINTS > 21) { // Dealer won (Player bust)
        //GAME_RESET(false);
        return 1;
    } else if (PC_POINTS > PLAYER_POINTS && PLAYER_POINTS < 21) { // Dealer won (more points)
        //GAME_RESET(false);
        return 1;
    } else if (PC_POINTS == 21 && PC_CARDS_COUNT == 2 && PLAYER_CARDS_COUNT > 2) { // Dealer won (Blackjack)
        //GAME_RESET(false);
        return 1;
    } else if (PC_POINTS == PLAYER_POINTS && !(PLAYER_POINTS == 21 && PLAYER_CARDS_COUNT == 2) && !(PC_POINTS == 21 && PC_CARDS_COUNT == 2)) { // Draw 
        //GAME_RESET(false);
        return 2;
    } else if (PC_POINTS == PLAYER_POINTS && PC_CARDS_COUNT == 2 && PLAYER_CARDS_COUNT == 2) { // Draw
        //GAME_RESET(false);
        return 2;
    } else {
        return -1;
    }
}

void BLACKJACK::START_GAME(int &bet) {
    BET_AMOUNT = bet;
    YOU_HAVE -= BET_AMOUNT;
    //std::cout << CARDS_LEFT.size() << std::endl;

    for (int i = 0; i < 2; ++i) {
        int tmp_index = get_random_index(CARDS_LEFT.size());
        std::string tmp_card = CARDS_LEFT[tmp_index];
        PLAYER_CARDS.push_back(tmp_card);
        CARDS_LEFT.erase(CARDS_LEFT.begin() + tmp_index);
        PLAYER_POINTS += DECK[tmp_card].second;
        ++PLAYER_CARDS_COUNT;
    }
    for (int i = 0; i < 2; ++i) {
        int tmp_index = get_random_index(CARDS_LEFT.size());
        std::string tmp_card = CARDS_LEFT[tmp_index];
        PC_CARDS.push_back(tmp_card);
        CARDS_LEFT.erase(CARDS_LEFT.begin() + tmp_index);
        ++PC_CARDS_COUNT;
    }

    PC_POINTS += DECK[PC_CARDS[0]].second;
}

int BLACKJACK::HIT() {
    int tmp_index = get_random_index(CARDS_LEFT.size());
    std::string tmp_card = CARDS_LEFT[tmp_index];
    PLAYER_CARDS.push_back(tmp_card);
    CARDS_LEFT.erase(CARDS_LEFT.begin() + tmp_index);
    PLAYER_POINTS = CHECK_POINTS(PLAYER_CARDS);
    ++PLAYER_CARDS_COUNT;

    if (PLAYER_POINTS > 21) {
        PC_POINTS = CHECK_POINTS(PC_CARDS);
        //GAME_RESET(false);
        return 1;
    } else {
        return 0;
    }
}

int BLACKJACK::STAND() {
    PC_POINTS = CHECK_POINTS(PC_CARDS);

    while (PC_POINTS < 17) {
        int tmp_index = get_random_index(CARDS_LEFT.size());
        std::string tmp_card = CARDS_LEFT[tmp_index];
        PC_CARDS.push_back(tmp_card);
        CARDS_LEFT.erase(CARDS_LEFT.begin() + tmp_index);
        ++PC_CARDS_COUNT;
        PC_POINTS = CHECK_POINTS(PC_CARDS);
    }
    return CHECK_FOR_WIN();
}