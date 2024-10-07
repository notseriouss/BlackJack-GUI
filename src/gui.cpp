#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>
#include "gui.h"
#include "func.h"


void logger::info_gui(const std::string &text) {
    std::string output = "[INFO_GUI] " + text;
    std::cout << output << std::endl;
}

void logger::info_func(const std::string &text) {
    std::string output = "--- [INFO_FUNC] " + text;
    std::cout << output << std::endl;
}


// FOR GUI
const std::filesystem::path path = std::filesystem::current_path().parent_path().parent_path().parent_path();
const float X_FOR_CARDS = 278.0f;
const short CARDS_AMOUNT = 10;
bool GAME_IS_RUNNING = false;
std::vector<Card> pc_cards;
std::vector<Card> player_cards;


void INIT_CARDS(std::vector<Card>& cards, bool reset = false) {
    if (reset) {
        for (Card& card : cards) {
            card.is_visible = false;
            card.card_name = "";
        }
    } else {
        cards.resize(CARDS_AMOUNT);
    }
}


void GUI_RESET(sf::Text &TEXT_score_pc, sf::Text &TEXT_score_player, sf::Text &TEXT_you_have, sf::Text &TEXT_bet_amount, sf::Text &TEXT_won_lose_draw, int &you_have) {
    TEXT_won_lose_draw.setString(std::string("        "));
    TEXT_won_lose_draw.setFillColor(sf::Color::White);
    logger::info_gui(std::string("[RESETED] -- text_won_lose_draw --> '0'"));
    TEXT_score_pc.setString(std::string("  "));
    logger::info_gui(std::string("[RESETED] -- text_score_pc --> '0'"));
    TEXT_score_player.setString(std::string("  "));
    logger::info_gui(std::string("[RESETED] -- text_score_player --> '0'"));
    TEXT_bet_amount.setString(std::string("Bet amount: "));
    logger::info_gui(std::string("[RESETED] -- text_bet_amount --> 'Bet amount: '"));
    TEXT_you_have.setString(std::string("You have: " + std::to_string(you_have)));
    logger::info_gui(std::string("[RESETED] -- text_bet_amount --> 'You have: '"));
    INIT_CARDS(pc_cards, true);
    logger::info_gui(std::string("[RESETED] -- INIT_pc"));
    INIT_CARDS(player_cards, true);
    logger::info_gui(std::string("[RESETED] -- INIT_player"));
}

void show_ui() {
    BLACKJACK GAME;
    std::cout << "SEED = " << GAME.get_SEED() << std::endl;

    sf::RenderWindow window({1600u, 1000u}, "Blackjack game", sf::Style::Close);
    window.setFramerateLimit(144);

    sf::Font font;
    if (!font.loadFromFile(path.string() + "/resources/fonts/arial.ttf")) { return; }

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile(path.string() + "/resources/images/table/table.jpg")) { return; }
    sf::Sprite background(backgroundTexture);



    // BUTTON_RESET
    sf::RectangleShape BUTTON_reset({100, 100});
    BUTTON_reset.setFillColor(sf::Color(132, 23, 76));
    BUTTON_reset.setPosition(1475, 25);
    sf::Text TEXT_reset("Reset", font, 20);
    TEXT_reset.setFillColor(sf::Color::White);
    TEXT_reset.setPosition(1497, 65);

    // BUTTON_CONFIRM
    sf::RectangleShape BUTTON_confirm({50, 40});
    BUTTON_confirm.setFillColor(sf::Color(0, 118, 251));
    BUTTON_confirm.setPosition(1525, 771);
    sf::Text TEXT_confirm("Confirm", font, 12);
    TEXT_confirm.setFillColor(sf::Color::White);
    TEXT_confirm.setPosition(1528, 783);
    // BUTTON_CLEAR
    sf::RectangleShape BUTTON_clear({106, 80});
    BUTTON_clear.setFillColor(sf::Color(0, 118, 251));
    BUTTON_clear.setPosition(1358, 820);
    sf::Text TEXT_clear("Clear", font, 26);
    TEXT_clear.setFillColor(sf::Color::White);
    TEXT_clear.setPosition(1378, 845);
    // BUTTON_LAST_BET
    sf::RectangleShape BUTTON_last_bet({106, 80});
    BUTTON_last_bet.setFillColor(sf::Color(0, 118, 251));
    BUTTON_last_bet.setPosition(1469, 820);
    sf::Text TEXT_last_bet("Last bet", font, 26);
    TEXT_last_bet.setFillColor(sf::Color::White);
    TEXT_last_bet.setPosition(1474, 845);

    // BUTTON_HIT
    sf::RectangleShape BUTTON_hit({300, 80});
    BUTTON_hit.setFillColor(sf::Color(37, 181, 122));
    BUTTON_hit.setPosition(488, 460);
    sf::Text TEXT_hit("Hit", font, 24);
    TEXT_hit.setFillColor(sf::Color::White);
    sf::FloatRect hitTextBounds = TEXT_hit.getLocalBounds(); 
    TEXT_hit.setOrigin(hitTextBounds.left + hitTextBounds.width / 2.0f,
                       hitTextBounds.top + hitTextBounds.height / 2.0f);
    TEXT_hit.setPosition(BUTTON_hit.getPosition().x + BUTTON_hit.getSize().x / 2.0f,
                        BUTTON_hit.getPosition().y + BUTTON_hit.getSize().y / 2.0f);
    // BUTTON_STAND
    sf::RectangleShape BUTTON_stand({300, 80});
    BUTTON_stand.setFillColor(sf::Color(193, 68, 68));
    BUTTON_stand.setPosition(813, 460);
    sf::Text TEXT_stand("Stand", font, 24);
    TEXT_stand.setFillColor(sf::Color::White);
    sf::FloatRect standTextBounds = TEXT_stand.getLocalBounds();
    TEXT_stand.setOrigin(standTextBounds.left + standTextBounds.width / 2.0f,
                       standTextBounds.top + standTextBounds.height / 2.0f);
    TEXT_stand.setPosition(BUTTON_stand.getPosition().x + BUTTON_stand.getSize().x / 2.0f,
                         BUTTON_stand.getPosition().y + BUTTON_stand.getSize().y / 2.0f);
    // BUTTON_BET_1
    sf::Texture TEXTURE_for_bet_button_1;
    if (!TEXTURE_for_bet_button_1.loadFromFile(path.string() + "/resources/images/bets/bet_1_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_1;
    SPRITE_for_bet_button_1.setTexture(TEXTURE_for_bet_button_1);
    SPRITE_for_bet_button_1.setPosition(1004, 766);
    SPRITE_for_bet_button_1.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_1({50, 50});
    BUTTON_bet_1.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_1.setPosition(1003, 765);
    // BUTTON_BET_5
    sf::Texture TEXTURE_for_bet_button_5;
    if (!TEXTURE_for_bet_button_5.loadFromFile(path.string() + "/resources/images/bets/bet_5_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_5;
    SPRITE_for_bet_button_5.setTexture(TEXTURE_for_bet_button_5);
    SPRITE_for_bet_button_5.setPosition(1059, 766);
    SPRITE_for_bet_button_5.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_5({50, 50});
    BUTTON_bet_5.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_5.setPosition(1058, 765);
    // BUTTON_BET_10
    sf::Texture TEXTURE_for_bet_button_10;
    if (!TEXTURE_for_bet_button_10.loadFromFile(path.string() + "/resources/images/bets/bet_10_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_10;
    SPRITE_for_bet_button_10.setTexture(TEXTURE_for_bet_button_10);
    SPRITE_for_bet_button_10.setPosition(1114, 766);
    SPRITE_for_bet_button_10.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_10({50, 50});
    BUTTON_bet_10.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_10.setPosition(1113, 765);
    // BUTTON_BET_20
    sf::Texture TEXTURE_for_bet_button_20;
    if (!TEXTURE_for_bet_button_20.loadFromFile(path.string() + "/resources/images/bets/bet_20_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_20;
    SPRITE_for_bet_button_20.setTexture(TEXTURE_for_bet_button_20);
    SPRITE_for_bet_button_20.setPosition(1169, 766);
    SPRITE_for_bet_button_20.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_20({50, 50});
    BUTTON_bet_20.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_20.setPosition(1168, 765);
    // BUTTON_BET_50
    sf::Texture TEXTURE_for_bet_button_50;
    if (!TEXTURE_for_bet_button_50.loadFromFile(path.string() + "/resources/images/bets/bet_50_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_50;
    SPRITE_for_bet_button_50.setTexture(TEXTURE_for_bet_button_50);
    SPRITE_for_bet_button_50.setPosition(1224, 766);
    SPRITE_for_bet_button_50.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_50({50, 50});
    BUTTON_bet_50.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_50.setPosition(1223, 765);
    // BUTTON_BET_100
    sf::Texture TEXTURE_for_bet_button_100;
    if (!TEXTURE_for_bet_button_100.loadFromFile(path.string() + "/resources/images/bets/bet_100_without-background.png")) { return; }
    sf::Sprite SPRITE_for_bet_button_100;
    SPRITE_for_bet_button_100.setTexture(TEXTURE_for_bet_button_100);
    SPRITE_for_bet_button_100.setPosition(1279, 766);
    SPRITE_for_bet_button_100.setScale(0.096f, 0.096f);

    sf::RectangleShape BUTTON_bet_100({50, 50});
    BUTTON_bet_100.setFillColor(sf::Color(0, 118, 251));
    BUTTON_bet_100.setPosition(1278, 765);


    // SCORE_PC
    sf::RectangleShape SQUARE_score_pc(sf::Vector2f(100.0f, 100.0f));
    SQUARE_score_pc.setFillColor(sf::Color::White);
    SQUARE_score_pc.setPosition(10, 10);
    sf::Text TEXT_score_pc("  ", font, 48);
    TEXT_score_pc.setFillColor(sf::Color::Black);
    TEXT_score_pc.setPosition(35, 30);

    sf::RectangleShape SQUARE_score_player(sf::Vector2f(100.0f, 100.0f));
    SQUARE_score_player.setFillColor(sf::Color::White);
    SQUARE_score_player.setPosition(10, 890);
    sf::Text TEXT_score_player("  ", font, 48);
    TEXT_score_player.setFillColor(sf::Color::Black);
    TEXT_score_player.setPosition(35, 910);

    // TEXT_BET_AMOUNT
    sf::Text TEXT_bet_amount("Bet amount: ", font, 18);
    TEXT_bet_amount.setFillColor(sf::Color::White);
    TEXT_bet_amount.setPosition(1358, 780);

    // TEXT_YOU_HAVE
    sf::Text TEXT_you_have("You have: " + std::to_string(GAME.YOU_HAVE), font, 18);
    TEXT_you_have.setFillColor(sf::Color::White);
    TEXT_you_have.setPosition(1353, 940);

    // TEXT_WON_LOSE_DRAW
    sf::Text TEXT_won_lose_draw("        ", font, 48);
    TEXT_won_lose_draw.setFillColor(sf::Color::White);
    TEXT_won_lose_draw.setPosition(1138, 470);


    // AREA_CARDS_DEALER
    sf::RectangleShape AREA_cards_dealer(sf::Vector2f(1055, 155));
    AREA_cards_dealer.setFillColor(sf::Color(96, 96, 96)); 
    AREA_cards_dealer.setPosition(273, 25);
    // AREA_CARDS_PLAYER
    sf::RectangleShape AREA_cards_player(sf::Vector2f(1055, 155));
    AREA_cards_player.setFillColor(sf::Color(96, 96, 96)); 
    AREA_cards_player.setPosition(273, 820);
    // AREA_BET
    sf::RectangleShape AREA_bet(sf::Vector2f(227, 210));
    AREA_bet.setFillColor(sf::Color(37, 82, 59, 205));
    AREA_bet.setPosition(1353, 765);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Check for mouse button press
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x),
                                          static_cast<float>(event.mouseButton.y));


                    if (BUTTON_reset.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("RESET_BUTTON PRESSED"));
                        BUTTON_reset.setFillColor(sf::Color(109, 18, 64));
                        GAME.GAME_RESET(true);
                        GUI_RESET(TEXT_score_pc, TEXT_score_player, TEXT_you_have, TEXT_bet_amount, TEXT_won_lose_draw, GAME.YOU_HAVE);
                    }

                    if (BUTTON_confirm.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("CONFIRM_BUTTON PRESSED"));
                        BUTTON_confirm.setFillColor(sf::Color(0, 85, 176));

                        if (GAME.BET_AMOUNT == 0) {
                            logger::info_func(std::string("GAME.BET_AMOUNT = " + std::to_string(GAME.BET_AMOUNT) + " | CAN NOT RUN THE GAME"));
                            continue;
                        }
                        if (GAME.BET_AMOUNT > GAME.YOU_HAVE) {
                            logger::info_func(std::string("GAME.BET_AMOUNT = " + std::to_string(GAME.BET_AMOUNT) + " > GAME.YOU_HAVE = " + std::to_string(GAME.YOU_HAVE) + " | BET CAN NOT BET HIGHER THAN MONEY YOU HAVE"));
                            continue;
                        }
                        if (GAME_IS_RUNNING) {
                            logger::info_gui(std::string("GAME_IS_RUNNING = " + std::to_string(GAME_IS_RUNNING) + " | GAME IS ALREADY RUNNING, CAN NOT START ANOTHER ONE"));
                            continue;
                        }

                        GUI_RESET(TEXT_score_pc, TEXT_score_player, TEXT_you_have, TEXT_bet_amount, TEXT_won_lose_draw, GAME.YOU_HAVE);

                        GAME_IS_RUNNING = true;
                        logger::info_gui(std::string("GAME_IS_RUNNING --> " + std::to_string(GAME_IS_RUNNING)));

                        GAME.LAST_BET = GAME.BET_AMOUNT;
                        logger::info_func(std::string("GAME.LAST_BET --> " + std::to_string(GAME.BET_AMOUNT)));

                        GAME.START_GAME(GAME.BET_AMOUNT);
                        logger::info_func(std::string("GAME.START_GAME("+std::to_string(GAME.BET_AMOUNT)+")"));

                        INIT_CARDS(pc_cards, false);
                        logger::info_gui(std::string("INIT_pc(false)"));
                        INIT_CARDS(player_cards, false);
                        logger::info_gui(std::string("INIT_player(false)"));

                        // PLAYER'S CARD 1
                        player_cards[0].card_name = GAME.PLAYER_CARDS[0];
                        player_cards[0].is_visible = true;
                        if (!player_cards[0].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/"+player_cards[0].card_name+".png")) { return; }
                        player_cards[0].SPRITE_for_card.setTexture(player_cards[0].TEXTURE_for_card);
                        player_cards[0].SPRITE_for_card.setPosition(X_FOR_CARDS+(0*105), 825);
                        player_cards[0].SPRITE_for_card.setScale(0.2f, 0.2f);
                        logger::info_gui(std::string("PLAYER'S CARD 1 CREATED"));
                        // PLAYER'S CARD 2
                        player_cards[1].card_name = GAME.PLAYER_CARDS[1];
                        player_cards[1].is_visible = true;
                        if (!player_cards[1].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/"+player_cards[1].card_name+".png")) { return; }
                        player_cards[1].SPRITE_for_card.setTexture(player_cards[1].TEXTURE_for_card);
                        player_cards[1].SPRITE_for_card.setPosition(X_FOR_CARDS+(1*105), 825);
                        player_cards[1].SPRITE_for_card.setScale(0.2f, 0.2f);
                        logger::info_gui(std::string("PLAYER'S CARD 2 CREATED"));
                        // DEALER'S CARD 1
                        pc_cards[0].card_name = GAME.PC_CARDS[0];
                        pc_cards[0].is_visible = true;
                        if (!pc_cards[0].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/"+pc_cards[0].card_name+".png")) { return; }
                        pc_cards[0].SPRITE_for_card.setTexture(pc_cards[0].TEXTURE_for_card);
                        pc_cards[0].SPRITE_for_card.setPosition(X_FOR_CARDS+(0*105), 30);
                        pc_cards[0].SPRITE_for_card.setScale(0.2f, 0.2f);
                        logger::info_gui(std::string("DEALER'S CARD 1 CREATED"));
                        // DEALER'S CARD 2
                        pc_cards[1].card_name = GAME.PC_CARDS[1];
                        pc_cards[1].is_visible = true;
                        if (!pc_cards[1].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/card_back.png")) { return; }
                        pc_cards[1].SPRITE_for_card.setTexture(pc_cards[1].TEXTURE_for_card);
                        pc_cards[1].SPRITE_for_card.setPosition(X_FOR_CARDS+(1*105), 30);
                        pc_cards[1].SPRITE_for_card.setScale(0.2f, 0.2f);
                        logger::info_gui(std::string("DEALER'S CARD 2 CREATED"));

                        TEXT_score_pc.setString(std::to_string(GAME.PC_POINTS));
                        logger::info_gui(std::string("text_score_pc --> "+std::to_string(GAME.PC_POINTS)));

                        TEXT_score_player.setString(std::to_string(GAME.PLAYER_POINTS));
                        logger::info_gui(std::string("text_score_player --> "+std::to_string(GAME.PLAYER_POINTS)));

                        TEXT_you_have.setString("You have: " + std::to_string(GAME.YOU_HAVE));
                        logger::info_gui(std::string("text_you_have --> "+std::to_string(GAME.YOU_HAVE)));

                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));
                        logger::info_gui(std::string("text_bet_amount --> "+std::to_string(GAME.YOU_HAVE)));
                    }

                    if (BUTTON_hit.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("HIT_BUTTON PRESSED"));
                        BUTTON_hit.setFillColor(sf::Color(33, 126, 88));

                        if (!GAME_IS_RUNNING) {
                            logger::info_gui(std::string("GAME_IS_RUNNING = " + std::to_string(GAME_IS_RUNNING) + " | GAME IS NOT RUNNING"));
                            continue;
                        }

                        int hit = GAME.HIT();
                        player_cards[GAME.PLAYER_CARDS_COUNT-1].card_name = GAME.PLAYER_CARDS[GAME.PLAYER_CARDS_COUNT-1];
                        player_cards[GAME.PLAYER_CARDS_COUNT-1].is_visible = true;
                        if (!player_cards[GAME.PLAYER_CARDS_COUNT-1].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/"+player_cards[GAME.PLAYER_CARDS_COUNT-1].card_name+".png")) { return; }
                        player_cards[GAME.PLAYER_CARDS_COUNT-1].SPRITE_for_card.setTexture(player_cards[GAME.PLAYER_CARDS_COUNT-1].TEXTURE_for_card);
                        player_cards[GAME.PLAYER_CARDS_COUNT-1].SPRITE_for_card.setPosition(X_FOR_CARDS+((GAME.PLAYER_CARDS_COUNT-1)*105), 825);
                        player_cards[GAME.PLAYER_CARDS_COUNT-1].SPRITE_for_card.setScale(0.2f, 0.2f);
                        logger::info_gui(std::string("PLAYER'S CARD" + std::to_string(GAME.PLAYER_CARDS_COUNT) + "CREATED"));

                        TEXT_score_player.setString(std::to_string(GAME.PLAYER_POINTS));

                        if (hit == 1) {
                            logger::info_gui(std::string("PLAYER LOST"));
                            TEXT_won_lose_draw.setString(std::string("You lost"));
                            TEXT_won_lose_draw.setFillColor(sf::Color(246, 42, 15));
                            TEXT_bet_amount.setString("Bet amount: ");
                            TEXT_score_pc.setString(std::to_string(GAME.PC_POINTS));
                            TEXT_you_have.setString("You have: " + std::to_string(GAME.YOU_HAVE));
                            logger::info_gui(std::string("text_you_have --> "+std::to_string(GAME.YOU_HAVE)));
                            GAME_IS_RUNNING = false;
                            GAME.GAME_RESET(false);
                        }
                    }

                    if (BUTTON_stand.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("STAND_BUTTON PRESSED"));
                        BUTTON_stand.setFillColor(sf::Color(154, 39, 39));

                        if (!GAME_IS_RUNNING) {
                            logger::info_gui(std::string("GAME_IS_RUNNING = " + std::to_string(GAME_IS_RUNNING) + " | GAME IS NOT RUNNING"));
                            continue;
                        }

                        int stand = GAME.STAND();

                        for (int i = 0; i < GAME.PC_CARDS.size(); ++i) {
                            pc_cards[i].card_name = GAME.PC_CARDS[i];
                            pc_cards[i].is_visible = true;
                            if (!pc_cards[i].TEXTURE_for_card.loadFromFile(path.string() + "/resources/images/cards/"+pc_cards[i].card_name+".png")) { return; }
                            pc_cards[i].SPRITE_for_card.setTexture(pc_cards[i].TEXTURE_for_card);
                            pc_cards[i].SPRITE_for_card.setPosition(X_FOR_CARDS+(i*105), 30);
                            pc_cards[i].SPRITE_for_card.setScale(0.2f, 0.2f);
                            logger::info_gui(std::string("DEALER'S CARD PRINTED"));
                        }

                        if (stand == 0) {
                            logger::info_gui(std::string("PLAYER WON"));
                            TEXT_won_lose_draw.setString(std::string("You won"));
                            TEXT_won_lose_draw.setFillColor(sf::Color(63, 255, 5));
                            GAME.YOU_HAVE += GAME.BET_AMOUNT*2;
                        } else if (stand == 1) {
                            logger::info_gui(std::string("PLAYER LOST"));
                            TEXT_won_lose_draw.setString(std::string("You lost"));
                            TEXT_won_lose_draw.setFillColor(sf::Color(246, 42, 15));
                        } else if (stand == 2) {
                            logger::info_gui(std::string("DRAW"));
                            TEXT_won_lose_draw.setString(std::string("Draw"));
                            GAME.YOU_HAVE += GAME.BET_AMOUNT;
                        } else {
                            return;
                        }
                        //
                        TEXT_bet_amount.setString("Bet amount: ");
                        TEXT_score_pc.setString(std::to_string(GAME.PC_POINTS));
                        TEXT_you_have.setString("You have: " + std::to_string(GAME.YOU_HAVE));
                        logger::info_gui(std::string("text_you_have --> "+std::to_string(GAME.YOU_HAVE)));
                        GAME_IS_RUNNING = false;
                        GAME.GAME_RESET(false);
                    }





                    // BET
                    if (BUTTON_clear.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("CLEAR_BUTTON PRESSED"));
                        BUTTON_clear.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT = 0;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: "));
                    }

                    if (BUTTON_last_bet.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("LAST_BET_BUTTON PRESSED"));
                        BUTTON_last_bet.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT = GAME.LAST_BET;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.LAST_BET)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.LAST_BET)));
                    }

                    if (BUTTON_bet_1.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_1_BUTTON PRESSED"));
                        BUTTON_bet_1.setFillColor(sf::Color(0, 85, 176));
                    
                        GAME.BET_AMOUNT += 1;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));
                    }

                    if (BUTTON_bet_5.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_5_BUTTON PRESSED"));
                        BUTTON_bet_5.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT += 5;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));
                    }

                    if (BUTTON_bet_10.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_10_BUTTON PRESSED"));
                        BUTTON_bet_10.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT += 10;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));;
                    }

                    if (BUTTON_bet_20.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_20_BUTTON PRESSED"));
                        BUTTON_bet_20.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT += 20;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));;
                    }

                    if (BUTTON_bet_50.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_50_BUTTON PRESSED"));
                        BUTTON_bet_50.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT += 50;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));
                    }

                    if (BUTTON_bet_100.getGlobalBounds().contains(mousePos)) {
                        logger::info_gui(std::string("BET_100_BUTTON PRESSED"));
                        BUTTON_bet_100.setFillColor(sf::Color(0, 85, 176));

                        GAME.BET_AMOUNT += 100;
                        logger::info_func(std::string("GAME.BET_AMOUNT --> " + std::to_string(GAME.BET_AMOUNT)));
                        TEXT_bet_amount.setString(std::string("Bet amount: " + std::to_string(GAME.BET_AMOUNT)));
                    }




                }
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    BUTTON_hit.setFillColor(sf::Color(37, 181, 122));
                    BUTTON_stand.setFillColor(sf::Color(193, 68, 68));
                    BUTTON_bet_1.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_bet_5.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_bet_10.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_bet_20.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_bet_50.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_bet_100.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_confirm.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_last_bet.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_clear.setFillColor(sf::Color(0, 118, 251));
                    BUTTON_reset.setFillColor(sf::Color(132, 23, 76));
                }
            }
        }

        window.clear(sf::Color(35, 122, 128));
        window.draw(background);

        // Draw AREA_CARDS_DEALER
        window.draw(AREA_cards_dealer);
        // Draw AREA_CARDS_PLAYER
        window.draw(AREA_cards_player);
        // Draw AREA_BET
        window.draw(AREA_bet);

        // Draw TEXT_BET_AMOUNT
        window.draw(TEXT_bet_amount);
        // Draw TEXT_YOU_HAVE
        window.draw(TEXT_you_have);

        // CARD_SPRITES_PC

        // Draw BUTTON_HIT
        window.draw(BUTTON_hit);
        window.draw(TEXT_hit);

        // Draw BUTTON_STAND
        window.draw(BUTTON_stand);
        window.draw(TEXT_stand);

        // Draw BUTTON_CONFIRM
        window.draw(BUTTON_confirm);
        window.draw(TEXT_confirm);

        // Draw BUTTON_CLEAR
        window.draw(BUTTON_clear);
        window.draw(TEXT_clear);

        // Draw BUTTON_LAST_BET
        window.draw(BUTTON_last_bet);
        window.draw(TEXT_last_bet);

        // Draw BUTTON_RESET
        window.draw(BUTTON_reset);
        window.draw(TEXT_reset);

        // Draw BUTTON_BET_1
        window.draw(BUTTON_bet_1);
        window.draw(SPRITE_for_bet_button_1);
        // Draw BUTTON_BET_5
        window.draw(BUTTON_bet_5);
        window.draw(SPRITE_for_bet_button_5);
        // Draw BUTTON_BET_10
        window.draw(BUTTON_bet_10);
        window.draw(SPRITE_for_bet_button_10);
        // Draw BUTTON_BET_20
        window.draw(BUTTON_bet_20);
        window.draw(SPRITE_for_bet_button_20);
        // Draw BUTTON_BET_50
        window.draw(BUTTON_bet_50);
        window.draw(SPRITE_for_bet_button_50);
        // Draw BUTTON_BET_100
        window.draw(BUTTON_bet_100);
        window.draw(SPRITE_for_bet_button_100);


        // Draw SCORE_PC
        window.draw(SQUARE_score_pc);
        window.draw(TEXT_score_pc);

        // Draw SCORE_PLAYER
        window.draw(SQUARE_score_player);
        window.draw(TEXT_score_player);

        window.draw(TEXT_won_lose_draw);

        

        for (auto &card : pc_cards) {
            if (card.is_visible) {
                window.draw(card.SPRITE_for_card);
            }
        }

        for (auto &card : player_cards) {
            if (card.is_visible) {
                window.draw(card.SPRITE_for_card);
            }
        }       


        window.display();
    }
}




