/* Muistipeli
 *
 * Kuvaus:
 * Ohjelma totetuttaa muistipelin.
 * Pelaaja syöttää aluksi parien määrän, siemenluvun, pelaajien määrän ja nimet.
 * Pelaajat syöttävät vuorollaan kordinaatit kortteihin, jos koordinaatit
 * ovat oikein (löytyvät taulusta, tai eivät ole jo arvattu, tai eivät ole
 * sama kortti) kortit kääntyvät.
 * Jos kortit ovat samat, pelaajalle lisätään pari ja hänen vuoro jatkuu.
 * Jos paria ei löytynyt vuoro vaihtuu.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Oskari Kolehmainen
 * Opiskelijanumero: 050340147
 * Käyttäjätunnus: shosko
 * E-Mail: oskari.kolehmainen@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * */

#include <player.hh>
#include <card.hh>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

const string INPUT_AMOUNT_OF_CARDS = "Enter the amount of cards (an even number): ";
const string INPUT_SEED = "Enter a seed value: ";
const string INPUT_AMOUNT_OF_PLAYERS = "Enter the amount of players (one or more): ";
const string INPUT_CARDS = "Enter two cards (x1, y1, x2, y2), or q to quit: ";
const string INVALID_CARD = "Invalid card.";
const string FOUND = "Pairs found.";
const string NOT_FOUND = "Pairs not found.";
const string GIVING_UP = "Why on earth you are giving up the game?";
const string GAME_OVER = "Game over!";

using Game_row_type = vector<Card>;
using Game_board_type = vector<vector<Card>>;

// Muuntaa annetun numeerisen merkkijonon vastaavaksi kokonaisluvuksi
// (kutsumalla stoi-funktiota).
// Jos annettu merkkijono ei ole numeerinen, palauttaa nollan
// (mikä johtaa laittomaan korttiin myöhemmin).
//
// Converts the given numeric string to the corresponding integer
// (by calling stoi).
// If the given string is not numeric, returns 0
// (which leads to an invalid card later).
unsigned int stoi_with_check(const string& str)
{
    bool is_numeric = true;
    for(unsigned int i = 0; i < str.length(); ++i)
    {
        if(not isdigit(str.at(i)))
        {
            is_numeric = false;
            break;
        }
    }
    if(is_numeric)
    {
        return stoi(str);
    }
    else
    {
        return 0;
    }
}

// Täyttää pelilaudan (kooltaan rows * columns) tyhjillä korteilla.
//
// Fills the game board, the size of which is rows * columns, with empty cards.
void init_with_empties(Game_board_type& g_board, unsigned int rows, unsigned int columns)
{
    g_board.clear();
    Game_row_type row;
    for(unsigned int i = 0; i < columns; ++i)
    {
        Card card;
        row.push_back(card);
    }
    for(unsigned int i = 0; i < rows; ++i)
    {
        g_board.push_back(row);
    }
}

// Etsii seuraavan tyhjän kohdan pelilaudalta (g_board) aloittamalla
// annetusta kohdasta start ja jatkamalla tarvittaessa alusta.
// (Kutsutaan vain funktiosta init_with_cards.)
//
// Finds the next free position in the game board (g_board), starting from the
// given position start and continuing from the beginning if needed.
// (Called only by the function init_with_cards.)
unsigned int next_free(Game_board_type& g_board, unsigned int start)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Aloitetaan annetusta arvosta
    //
    // Starting from the given value
    for(unsigned int i = start; i < rows * columns; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY) // vaihdettu
        {
            return i;
        }
    }
    // Jatketaan alusta
    //
    // Continuing from the beginning
    for(unsigned int i = 0; i < start; ++i)
    {
        if(g_board.at(i / columns).at(i % columns).get_visibility() == EMPTY)
        {
            return i;
        }
    }
    // Tänne ei pitäisi koskaan päätyä
    //
    // You should never reach this
    std::cout << "No more empty spaces" << std::endl;
    return rows * columns - 1;
}

// Alustaa annetun pelilaudan (g_board) satunnaisesti arvotuilla korteilla
// annetun siemenarvon (seed) perusteella.
//
// Initializes the given game board (g_board) with randomly generated cards,
// based on the given seed value.
void init_with_cards(Game_board_type& g_board, int seed)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();
    unsigned int columns = g_board.at(0).size();

    // Arvotaan täytettävä sijainti
    //
    // Drawing a cell to be filled
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, rows * columns - 1);
    // Hylätään ensimmäinen satunnaisluku (joka on aina jakauman alaraja)
    //
    // Wiping out the first random number (that is always the lower bound of the distribution)
    distr(randomEng);

    // Jos arvotussa sijainnissa on jo kortti, valitaan siitä seuraava tyhjä paikka.
    // (Seuraava tyhjä paikka haetaan kierteisesti funktion next_free avulla.)
    //
    // If the drawn cell is already filled with a card, next empty cell will be used.
    // (The next empty cell is searched for circularly, see function next_free.)
    for(unsigned int i = 0, c = 'A'; i < rows * columns - 1; i += 2, ++c)
    {
        // Lisätään kaksi samaa korttia (parit) pelilaudalle
        //
        // Adding two identical cards (pairs) in the game board
        for(unsigned int j = 0; j < 2; ++j)
        {
            unsigned int cell = distr(randomEng);
            cell = next_free(g_board, cell);
            g_board.at(cell / columns).at(cell % columns).set_letter(c);
            g_board.at(cell / columns).at(cell % columns).set_visibility(HIDDEN);
        }
    }
}

// Tulostaa annetusta merkistä c koostuvan rivin,
// jonka pituus annetaan parametrissa line_length.
// (Kutsutaan vain funktiosta print.)
//
// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
// (Called only by the function print.)
void print_line_with_char(char c, unsigned int line_length)
{
    for(unsigned int i = 0; i < line_length * 2 + 7; ++i)
    {
        cout << c;
    }
    cout << endl;
}

// Tulostaa vaihtelevankokoisen pelilaudan reunuksineen.
//
// Prints a variable-length game board with borders.
void print(const Game_board_type& g_board)
{
    // Selvitetään annetun pelilaudan rivien ja sarakkeiden määrät
    //
    // Finding out the number of rows and columns of the game board
    unsigned int rows = g_board.size();

    unsigned int columns = g_board.at(0).size();

    print_line_with_char('=', columns);
    cout << "|   | ";
    for(unsigned int i = 0; i < columns; ++i)
    {
        cout << i + 1 << " ";
    }
    cout << "|" << endl;
    print_line_with_char('-', columns);
    for(unsigned int i = 0; i < rows; ++i)
    {
        cout << "| " << i + 1 << " | ";
        for(unsigned int j = 0; j < columns; ++j)
        {
            g_board.at(i).at(j).print();

            cout << " ";
        }
        cout << "|" << endl;
    }
    print_line_with_char('=', columns);
}

// Kysyy käyttäjältä tulon ja sellaiset tulon tekijät, jotka ovat
// mahdollisimman lähellä toisiaan.
//
// Asks the desired product from the user, and calculates the factors of
// the product such that the factor as near to each other as possible.
void ask_product_and_calculate_factors(unsigned int& smaller_factor, unsigned int& bigger_factor)
{
    unsigned int product = 0;
    while(not (product > 0 and product % 2 == 0))
    {
        std::cout << INPUT_AMOUNT_OF_CARDS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }

    for(unsigned int i = 1; i * i <= product; ++i)
    {
        if(product % i == 0)
        {
            smaller_factor = i;
        }
    }
    bigger_factor = product / smaller_factor;
}

// Lisää funktioita
// More functions

// kysytään käyttäjältä pelaajien määrä
int ask_player_count(){
    unsigned int product = 0;
    while(!(product > 0))
    {
        std::cout << INPUT_AMOUNT_OF_PLAYERS;
        string product_str = "";
        std::getline(std::cin, product_str);
        product = stoi_with_check(product_str);
    }
    return product;
}

// Kysytään käyttäjältä pelaajien nimet
// ja tallennetaan ne vektoriin
void ask_players(std::vector<Player>& pelaajat, int maara){
    std::string mjono = " ";
    for(int i = 0; i < maara; ++i){
        std::cin >> mjono;
        pelaajat.push_back(mjono);
    }

}
//tulostetaan kaikkien pelaajien tulokset
void print_player_scores(std::vector<Player>& pel){
    for (int i = 0; i < (int)pel.size(); ++i){
        pel.at(i).print();
    }
}
// tarkistetaan montako paria on löytynyt
int pairs_found(std::vector<Player>& pel){
    int tulos =0;
    for (int i = 0; i < (int)pel.size(); ++i){
        tulos += pel.at(i).number_of_pairs();
    }
    return tulos;
}
// tarkistetaan kuka on voittanut pelin
void winner(std::vector<Player>& pel){
    int max = 0;
    Player* pelaaja = 0;
    for (int i = 0; i < (int)pel.size(); ++i){
        if ((int)pel.at(i).number_of_pairs() > max){
            max = (int)pel.at(i).number_of_pairs();
            pelaaja = &pel.at(i);
        }
    }
    int laskuri = 0;
    for (int i = 0; i < (int)pel.size(); ++i){
        if ((int)pel.at(i).number_of_pairs() == max){
            laskuri += 1;
        }
    }
    if (laskuri == 1){
        std::cout << pelaaja->get_name() << " has won with "
                  << pelaaja->number_of_pairs() << " pairs." << std::endl;

    } else {
        std:: cout << "Tie of " << laskuri << " players with " << max << " pairs." << std::endl;
    }
}

int main()
{
    Game_board_type game_board;
    std::vector<Player> pelaajat;

    unsigned int factor1 = 1;
    unsigned int factor2 = 1;
    ask_product_and_calculate_factors(factor1, factor2);
    init_with_empties(game_board, factor1, factor2);

    string seed_str = "";
    std::cout << INPUT_SEED;
    std::getline(std::cin, seed_str);
    int seed = stoi_with_check(seed_str);
    init_with_cards(game_board, seed);

    // Lisää koodia
    // More code

    //vektori, johon käyttäjän syöttämät koordinaatit talletetaan
    std::vector<string> koordinaatit;
    // tulostettava teksti pelaajien määrän mukaan
    int maara = ask_player_count();
    if(maara == 1){
        std::cout << "List "<<maara << " player: " ;
    } else {
        std::cout << "List "<<maara << " players: " ;
    }
    //kutustaan fuktiota ask_players
    ask_players(pelaajat,maara);

    //alustetaan muuttujia joita tarvitaan pelin kulun aikana.
    unsigned int parit = game_board.size()*game_board.at(0).size() / 2 ;
    unsigned int loydetty = 0;
    unsigned int vuoro = 0;
    print(game_board);

    //while loop, joka toimii niin pitkään kunnes kaikki parit on löydetty.
    while (loydetty < parit){

        //tarkistetaan vuorossa oleva pelaaja
        //jos vuoro >= pelaajien määrän nollataan laskuri
        if(vuoro >= pelaajat.size()){
            vuoro = 0;
        }
        //kysytään pelaajalta kordinaatit kortteihin
        std::cout << pelaajat.at(vuoro).get_name() << ": " << INPUT_CARDS;
        string product_str = "";
        for(int i = 0; i < 4; ++i){
            std::cin >> product_str;
            if(product_str == "q"){
                std::cout << GIVING_UP << std::endl;
                return EXIT_SUCCESS;
            } else {
                koordinaatit.push_back(product_str);
            }
        }

        //muutetaan string muotoiset koordinaatit int muotoisiksi
        //syöte on 1 suurempi, joten vähennettään siitä -1
        int toka = stoi_with_check(koordinaatit.at(0))-1;
        int eka = stoi_with_check(koordinaatit.at(1))-1;
        int neljas = stoi_with_check(koordinaatit.at(2))-1;
        int kolmas = stoi_with_check(koordinaatit.at(3))-1;
        if(eka < 0|| toka < 0 || kolmas <0 || neljas<0){
            std::cout << INVALID_CARD << std::endl;
            koordinaatit.clear();
            continue;
        }

        //ensimmäinen virhesyöte
        //jos syöte menee laudan ohi, tulostetan ilmoitus ja palataan alkuun
        if(eka > (int)game_board.size()  ||
                toka > (int)game_board.at(0).size() ||
                kolmas > (int)game_board.size() ||
                neljas > (int)game_board.at(0).size()){
            std::cout << INVALID_CARD << std::endl;
            koordinaatit.clear();
            continue;
        }

        //toinen virhesyöte
        //jos syöteet ovat samat, tulostetan ilmoitus ja palataan alkuun
        if (eka == kolmas && toka == neljas) {
            std::cout << INVALID_CARD << std::endl;
            koordinaatit.clear();
            continue;
        }

        // kolmas virheilmoitus
        // jos syöte osuu tyhjään korttiin, tulostetan ilmoitus ja palataan alkuun
        if(game_board.at(eka).at(toka).get_visibility()== EMPTY ||
                game_board.at(kolmas).at(neljas).get_visibility()== EMPTY){
            std::cout << INVALID_CARD << std::endl;
            koordinaatit.clear();
            continue;
        }

        //jos syöte oli validi, käännetään kaksi korttia
        game_board.at(eka).at(toka).turn();
        game_board.at(kolmas).at(neljas).turn();
        print(game_board);

        // jos löytyy pari, toteutetaan seuraavat toiminnot
        // muutetaan näiden korttien näkyvyys tyhjäksi.
        // lisätään pelaajalle pari.
        // tulostetaan pelaajien tulokset
        // tulostetaan pelikenttä
        // tyhjennetään koordinaatit vektori
        // lasketaan löydettyjen korttien määrä
        if(game_board.at(eka).at(toka).get_letter() == game_board.at(kolmas).at(neljas).get_letter()){
            std::cout << FOUND << std::endl;
            game_board.at(eka).at(toka).set_visibility(EMPTY);
            game_board.at(kolmas).at(neljas).set_visibility(EMPTY);
            pelaajat.at(vuoro).add_card(game_board.at(eka).at(toka));
            print_player_scores(pelaajat);
            print(game_board);
            koordinaatit.clear();
            loydetty = pairs_found(pelaajat);
            continue;
        }
        // jos paria ei löytynyt
        // tulostetaan pelaajien tulokset
        // käänetään löytyneet kortit takaisin
        // tulostetaan pelikenttä
        // tyhjennetään koordinaatit vektori
        // vaihdetaan pelivuoroa
        // lasketaan löydettyjen korttien määrä
        if(game_board.at(eka).at(toka).get_letter() != game_board.at(kolmas).at(neljas).get_letter()){
            std::cout << NOT_FOUND << std::endl;
            print_player_scores(pelaajat);
            game_board.at(eka).at(toka).turn();
            game_board.at(kolmas).at(neljas).turn();
            print(game_board);
            koordinaatit.clear();
            vuoro +=1;
            loydetty = pairs_found(pelaajat);
        }
    }

    //peli päättyy
    //selvitetään voittaja
    std::cout<<GAME_OVER << std::endl;
    winner(pelaajat);
    return EXIT_SUCCESS;
}

