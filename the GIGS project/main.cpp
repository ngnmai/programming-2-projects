/* COMP.CS.110 Project 2: GIGS
 * ===========================
 * The programm acessed the file and check if the file format is corrrect
 * or not.
 * The pogram then stores data from file text and then user can use
 * command to retrieve or edit data based on one's needs.
 * The commands available are below:
 * ARTISTS - Prints all known artist names
 * ARTIST <artist name> - Prints single artist's gigs
 * STAGES - Prints all known stage names and their locations
 * STAGE <stage name> - Prints all artists having a gig at the given stage
 * ADD_ARTIST <artist name> - Adds a new artist
 * ADD_GIG <artist name> <date> <town name> <stage name> - Adds a new gig for
 * an artist with the given date, town, and stage (the artist can't already
 * have a gig on the same date and there can't be other gigs at the same stage
 * at the same time)
 * CANCEL <artist name> <date> - Cancels artist's gigs after the given date
 * QUIT - end the program
 * */
/*Authors
* Name: Ngoc Mai Nguyen
* Student number: 50358236
* UserID: ddmang
* E-Mail: mai.n.nguyen@tuni.fi
* */
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "gigs.hh"
using namespace std;

// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

// Casual split func, if delim char is between "'s, ignores it.
std::vector<std::string> split(const std::string& str, char delim = ';')
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for ( char current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quotation = !inside_quotation;
        }
        else if ( current_char == delim && !inside_quotation )
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if ( result.back() == "" )
    {
        result.pop_back();
    }
    return result;
}

// Checks if the given date_str is a valid date, i.e. if it has the format
// dd-mm-yyyy and if it is also otherwise possible date.
bool is_valid_date(const std::string& date_str)
{
    std::vector<std::string> date_vec = split(date_str, '-');
    if ( date_vec.size() != 3 )
    {
        return false;
    }

    std::string year = date_vec.at(0);
    std::string month = date_vec.at(1);
    std::string day = date_vec.at(2);
    std::vector<std::string> month_sizes
            = { "31", "28", "31", "30", "31", "30",
                "31", "31", "30", "31", "30", "31" };

    if ( month < "01" || month > "12" )
    {
        return false;
    }
    if ( year < "0001" || year > FARTHEST_POSSIBLE_YEAR )
    {
        return false;
    }
    unsigned int year_int = stoi(year);
    bool is_leap_year = (year_int % 400 == 0) ||
                        (year_int % 100 != 0 && year_int % 4 == 0);
    if ( day >= "01" &&
        (day <= month_sizes.at(stoi(month) - 1) ||
        (month == "02" && is_leap_year && day <= "29")) )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    //get input for the name of the data file
    string filename;
    cout<<"Give a name for input file: ";
    getline(cin, filename);

    GIGS database(filename);
    if (not database.readfile()) {
        return EXIT_FAILURE;
    }

    string inputLine;
    vector <string> input;

    while (true)
    {
        cout << "gigs> ";
        getline(cin, inputLine);
        input = split(inputLine, ' ');
        //command QUIT: exit
        if(input[0] == "quit" || input[0] == "QUIT")
        {
            return EXIT_SUCCESS;
        }
        //command ARTISTS: printing all artists
        else if(input[0] == "artists" || input[0] == "ARTISTS")
        {
            database.print_all_artists();
        }
        //command ARTIST: printing the data related to the artist
        else if (input[0] == "artist" || input[0] == "ARTIST")
        {
            if (input.size() == 1)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                database.print_artist_gigs_list(input[1]);
            }

        }
        //command STAGES: printing all stages
        else if(input[0] == "stages" || input[0] == "STAGES")
        {
            database.print_all_stages();
        }
        //command STAGE: printing the data related to the stage
        else if((input[0] == "STAGE" || input[0] == "stage") && (input.size() > 1))
        {
            database.print_stage_data(input[1]);
        }
        //command ADD_ARTIST: adding artist
        else if (input[0] == "ADD_ARTIST" || input[0] == "add_artist") {
            if (input.size() == 1)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                database.add_artist(input[1]);
            }
        }
        //command ADD_GIG: adding gig details for artist
        else if (input[0] == "ADD_GIG" || input[0] == "add_gig") {
            if (input.size() != 5)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                database.add_gig(input[1], input[2], input[3], input[4]);
            }
        }
        //command CANCEL: cancel gig for artist

        else if (input[0] == "CANCEL" || input[0] == "cancel") {
            if (input.size() != 3)
            {
                cout << "Error: Invalid input." << endl;
            }
            else
            {
                database.cancel(input[1], input[2]);
            }
        }

        //none
        else {
            cout<<"Error: Invalid input."<<endl;
        }
    }


    return EXIT_SUCCESS;
}
