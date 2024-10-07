#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <string>

// FOR GUI
const extern std::filesystem::path path;
const extern float X_FOR_CARDS;
const extern short CARDS_AMOUNT;
extern bool GAME_IS_RUNNING;


struct logger {
    static void info_gui(const std::string &text);
    static void info_func(const std::string &text);
};

struct Card {
    sf::Texture TEXTURE_for_card;
    sf::Sprite SPRITE_for_card;
    std::string card_name;
    bool is_visible;
};

extern std::vector<Card> pc_cards;
extern std::vector<Card> player_cards;

void INIT_CARDS(std::vector<Card>& cards, bool reset);
//std::string getMainCppFullPath();
void GUI_RESET(sf::Text &TEXT_score_pc, sf::Text &TEXT_score_player, sf::Text &TEXT_you_have, sf::Text &TEXT_bet_amount, sf::Text &TEXT_won_lose_draw, int &you_have);
void show_ui();

