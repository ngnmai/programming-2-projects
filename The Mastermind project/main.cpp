/* Mastermind
 *
 * Desc:
 *   This program implements a Mastermind game. First a secret series of
 * four colors is either given or drawn. The series can have several
 * identical colors, but none of the four positions can be empty.
 * The user tries to guess which colors the secret series has and in which
 * order they occur there. For this purpose, the user gives their own
 * series of four colors, and the program tells how many colors in the
 * guess was totally correct (correct color in correct position) and how
 * many of them were correct in color (but incorrect in position). After
 * that the user guesses again and so on.
 *   At first, the user is asked, if the game board will be filled with
 * randomly drawn colors, or with user-given ones. (The latter way is not
 * very sensible, but it is useful in testing purposes.) In the first
 * option, a seed value for the random number generator will be asked next.
 * In the latter option, the user is asked to input four colors (the first
 * letters of the colors, i.e. a string consisting of four characters).
 *   On each round, the user is asked for a new guess. The player wins if
 * all colors in the guess are totally correct. The player loses if they
 * have used the maximum number (10) of guesses without the right one.
 *   The program checks if the user-given colors are among accepted ones.
 * When the game ends, the program tells if the player won or lost.
 *
 * Program author
 * Name: Mai Nguyen
 * Student number: 50358236
 * UserID: ddmang
 * E-Mail: mai.n.nguyen@tuni.fi
 *
 * Notes about the program and it's implementation:
 * The program includes 3 functions and 1 main function of the game loop.
 * The 3 functions are used for getting and evaluating input from users
 * as the secret series or the guess input and printing the previous
 * guesses. The main function is for the game loop, where the game happens.
 * The program also includes 1 class object. Though simple and not used
 * a lot, the class is meant for new developers to edit the function to
 * modify the color series or any thing related.
 * */

#include <iostream>
#include <vector>
#include <stdlib.h>
#include "colors.cpp"
#include <algorithm>


using namespace std;

// Maximum number of guesses
// (Not used in the template code)
const unsigned int GUESS_MAX = 10; // Not in use, yet

// Number of colors in a series
const unsigned int SIZE = 4;

// Length of the suffix part when printing a row.
// The suffix consists of three vertical lines ('|') and two digits, where one
// tells the amount of totally correct colors and the other tells the amount
// of correct colors in incorrect positions.
const unsigned int SUFFIX_LENGTH_IN_PRINT = 5;

// Text printed at the beginning of the program
const string INFO_TEXT = "Colors in use: \
B = Blue, R = Red, Y = Yellow, G = Green, O = Orange, V = Violet";

// TODO: Do you need more constants?
char color_code[6] = { 'b', 'r', 'y', 'g', 'o', 'v' };

// Reads the input way, either random or listing way,
// and fills the color series in the user-desired way.
// Repeats the question until the user enters either R or L.
//ONLY TO GET SECRET SERIES
void get_input(vector <char>& secret)
{
    cout << "Enter an input way (R = random, L = list): ";
    string input_str;
    cin >> input_str;
    //vector <char> series;
    if (input_str == "R" or input_str == "r")
    {
        cout << "Enter a seed value: ";
        int seed = 0;
        cin >> seed;
        srand(seed);
        for (int i = 0; i < 4; i++)
            secret.push_back(color_code[rand() % 6]);
        //secret = series;
        //return series;
    }
    else if (input_str == "L" or input_str == "l")
    {
        bool accepted = false;
        while (not accepted)
        {
            cout << "Enter four colors (four letters without spaces): ";
            string colors = "";
            cin >> colors;
            if (colors.length() == 4)
            {
                for (int index = 0; index < 4; ++index)
                {
                    bool found = false;
                    for (int index2 = 0; index2 < 6; index2++)
                    {
                        if (colors[index] == color_code[index2])
                        {
                            found = true;
                            break;
                        }
                    }
                    if (!found)
                    {
                        cout << "Unknown color" << endl;
                        colors = "";
                        break;
                    }
                }
                if (colors.length() == 4) {
                    secret = { colors[0], colors[1], colors[2], colors[3] };
                    accepted = true;
                }
            }
            else
            {
                cout << "Wrong size" << endl;
            }
        }
    }
    else
    {
        cout << "Bad input" << endl;
        get_input(secret);
    }

}

// Prints a line consisting of the given character c.
// The length of the line is given in the parameter line_length.
void print_line_with_char(char c, unsigned int line_length)
{
    for (unsigned int i = 0; i < line_length; ++i)
    {
        cout << c;
    }
    cout << endl;
}


//Getting input from player's guess
void guess(vector <char>& valid_guess)
{
    cout << "ROW> ";
    string input_guess = "";
    cin >> input_guess;
    if (input_guess == "Q" or input_guess == "q") {
        valid_guess.push_back(input_guess[0]);

    }
    else
    {
        if (input_guess.length() == 4)
        {
            for (int index = 0; index < 4; ++index)
            {
                bool found = false;
                for (int index2 = 0; index2 < 6; index2++)
                {
                    if (input_guess[index] == color_code[index2])
                    {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Unknown color" << endl;
                    guess(valid_guess);
                }
            }
            for (int i = 0; i < 4; i++)
            {
                valid_guess.push_back(input_guess[i]);
            }

        }
        else {
            cout << "Wrong size" << endl;
            guess(valid_guess);
        }
    }
}

// Implements the actual game loop, where user-given guesses are read
// and compared to the secret row.
// On each round, all rows given so far are printed.
int main()
{
    cout << INFO_TEXT << endl;
    print_line_with_char('*', INFO_TEXT.size());
    //Getting the secret series
    vector <char> secret_series;
    get_input(secret_series);
    Colors correct_series(secret_series);

    //memorizing previous guesses
    vector <Colors> prev_guess;

    //count for correct character in correct order
    int count1 = 0;
    //count for correct character but not in correct order
    int count2 = 0;

    //count for number of guesses
    int g = 0;

    // TODO: Play the game, i.e. repeatedly read a user given number series
    // and compare it with the secret one
    bool flag = true;
    vector <int> prev_count1;
    vector <int> prev_count2;
    while (flag)
    {
        vector <char> valid_guess;
        guess(valid_guess);
        if (valid_guess.size() == 1)
        {
            flag = false;
            break;
        }
        Colors guess(valid_guess);
        prev_guess.push_back(valid_guess);
        vector <char> temp_vector = guess.get_series();
        vector <char> temp_index;

        vector <char> copy_correct_series = correct_series.series_;
        //Checking correct character in correct order
        for (int index = 0; index < 4; index++)
        {
            if (guess.series_[index] == correct_series.series_[index])
            {
                count1 = count1 + 1;
                temp_index.push_back(index);
                temp_vector[index] = ' ';
                copy_correct_series[index] = ' ';

            }
        }
        prev_count1.push_back(count1);

        //Checking correct character not in correct order
        for (int index = 0; index < 4; index++)
        {
            if (temp_vector[index] != ' ')
            {
                for (int index3 = 0; index3 < 4; index3++)
                {
                    if (temp_vector[index] == copy_correct_series[index3])
                    {
                        count2 = count2 + 1;
                        temp_vector[index] = ' ';
                        copy_correct_series[index3] = ' ';
                        break;
                    }
                }
            }
        }

        prev_count2.push_back(count2);

        //printing the prev guesses and counts
        g = g + 1;
        print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);
        for (unsigned i = 0; i < prev_guess.size(); i++)
        {
            Colors printed = prev_guess[i];
            cout << "|" << printed.print_series() << " | " << prev_count1[i] << " | " << prev_count2[i] << " |" << endl;
        }
        print_line_with_char('=', 2 * (SIZE + SUFFIX_LENGTH_IN_PRINT) + 1);

        //checking the winning situation
        if (count1 == 4) {
            cout << "You won: Congratulations!" << endl;
            flag = false;
            break;
        }
        else if (g == GUESS_MAX) {
            cout << "You lost: Maximum number of guesses done" << endl;
            flag = false;
            break;
        }
        count1 = 0;
        count2 = 0;
    }



    return 0;
}

