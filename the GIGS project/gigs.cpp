/*Authors
* Name: Ngoc Mai Nguyen
* Student number: 50358236
* UserID: ddmang
* E-Mail: mai.n.nguyen@tuni.fi
* */

#include "gigs.hh"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;
// Farthest year for which gigs can be allocated
const std::string FARTHEST_POSSIBLE_YEAR = "2030";

GIGS::GIGS(string const& filename): filename_(filename) {}

//split string
vector<string> GIGS::split( const string& str, char delim = ';' )
{
    vector<string> result = {""};
    bool inside_quatation = false;
    for ( auto current_char : str )
    {
        if ( current_char == '"' )
        {
            inside_quatation = !inside_quatation;
        }
        else if ( current_char == delim  && not inside_quatation )
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
//check date
bool GIGS::is_valid_date(const std::string& date_str)
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
//read file: take in 1 param (filename_)
//return bool

bool GIGS::readfile()
{
    ifstream input_file(filename_);

    if(not input_file)
    {
        cout << "Error: File could not be read." << endl;
        return false;
    }

    string line;
    vector <string> splited;
    while (getline(input_file, line))
    {
        splited = split(line);
        if(splited.size() != 4)
        {
            cout << "Error: Invalid format in file." <<endl;
            return false;
        }

        if (splited[0].empty() || splited[1].empty() || splited[2].empty() || splited[3].empty()){
            cout << "Error: Invalid format in file." <<endl;
            return false;
        }

        string artist = splited.at(0);
        string date = splited.at(1);
        string town = splited.at(2);
        string name_stage = splited.at(3);
        //merging town and stage
        string stage = town + ", " + name_stage;

        //checking valid date
        bool check_date = is_valid_date(date);
        if (!check_date) {
            cout << "Error: Invalid date." << endl;
            return false;
        }

        // update artist_gigs_list
        if (artist_gigs_list.find(artist) == artist_gigs_list.end())
        {
            artist_gigs_list.insert({artist, {}});
        }
        if (artist_gigs_list.at(artist).find(date) == artist_gigs_list.at(artist).end())
        {
            artist_gigs_list.at(artist).insert({date, {}});
        }
        else
        {
            cout << "Error: Already exists."<< endl; //checking double booking for artist
            return false;
        }
        artist_gigs_list.at(artist).at(date).push_back(stage);

        //update stage_data
        if ( stage_data.find(name_stage) == stage_data.end()) {
            stage_data.insert({name_stage, {}});
        }
        stage_data.at(name_stage).insert(artist);

        //update stage_name
        if (stage_name.find(stage) == stage_name.end()) {
            stage_name.insert({stage, {}});
        }
        set<string> booked_date = stage_name.at(stage);
        if (booked_date.find(date) != booked_date.end()) {
            cout << "Error: Already exists." << endl; // checking double booking for stage
            return false;
        }
        else {
            stage_name.at(stage).insert(date);
        }
    }

    input_file.close();
    return true;
}

//printing all the stages
//take 0 param
//return none, printing all the stages
void GIGS::print_all_stages()
{
    cout << "All gig places in alphabetical order: " <<endl;

    for (const auto & stage : stage_name) {
        cout << stage.first <<endl;
    }
}

//printing all the artists
//take 0 param
//return none, printing all the artists
void GIGS::print_all_artists()
{
    cout << "All artists in alphabetical order: " <<endl;

    for (const auto & artist : artist_gigs_list) {
        cout << artist.first <<endl;
    }
}

//printing all the stages where a certain artist played
//take 1 param: artist (string)
//return none, printing (string)
void GIGS::print_artist_gigs_list(const string & artist)
{
    if (artist_gigs_list.find(artist) == artist_gigs_list.end()) {
        cout << "Error: Not found." <<endl;
        return;
    }

    cout << "Artist " + artist + " has the following gigs in the order they are listed:" <<endl;

    for (const auto & date: artist_gigs_list.at(artist))
    {
        cout << "- " << date.first << " : ";
        string printed_stage = date.second[0];
        cout << printed_stage << endl;
    }
}

//print all the artists playing at a certain stage
//take 1 param: stage
//return none, printing string
void GIGS::print_stage_data(const string & name_stage)
{
    if (stage_data.find(name_stage) == stage_data.end()) {
        cout << "Error: Not found." <<endl;
        return;
    }

    cout << "Stage " + name_stage + " has gigs of the following artists:" <<endl;

    for (const auto & artist: stage_data.at(name_stage)) {
        cout <<"- " << artist <<endl;
    }
}

//adding new artist and check
bool GIGS::add_artist(const string & new_artist)
{
    if (artist_gigs_list.find(new_artist) == artist_gigs_list.end())
        {
            artist_gigs_list.insert({new_artist, {}});
            cout << "Artist added." << endl;
        }
    else
        {
            cout << "Error: Already exists."<< endl; //checking the existence of the artist name
            return false;
        }
    return true;
}

//adding new gig details for artist and check
bool GIGS::add_gig(const string & artist, const string & date, const string & town, const string & name_stage)
{
    //merging town and stage
    string stage = town + ", " + name_stage;

    //checking valid artist name
    if (artist_gigs_list.find(artist) == artist_gigs_list.end()) {
        cout << "Error: Not found." <<endl;
        return false;
    }
    //checking valid date
    bool check_date = is_valid_date(date);
    if (!check_date) {
        cout << "Error: Invalid date." << endl;
        return false;
    }

    // update artist_gigs_list
    if (artist_gigs_list.find(artist) == artist_gigs_list.end())
    {
        artist_gigs_list.insert({artist, {}});
    }
    if (artist_gigs_list.at(artist).find(date) == artist_gigs_list.at(artist).end())
    {
        artist_gigs_list.at(artist).insert({date, {}});
    }
    else
    {
        cout << "Error: Already exists."<< endl; //checking double booking for artist
        return false;
    }
    artist_gigs_list.at(artist).at(date).push_back(stage);

    //update stage_data
    if ( stage_data.find(name_stage) == stage_data.end()) {
        stage_data.insert({name_stage, {}});
    }
    stage_data.at(name_stage).insert(artist);

    //update stage_name
    if (stage_name.find(stage) == stage_name.end()) {
        stage_name.insert({stage, {}});
    }
    set<string> booked_date = stage_name.at(stage);
    if (booked_date.find(date) != booked_date.end()) {
        cout << "Error: Already exists." << endl; // checking double booking for stage
        return false;
    }
    else {
        stage_name.at(stage).insert(date);
    }

    cout << "Gig added." <<endl;
    return true;
}



//comparing dates
bool GIGS::comparing_date(string date1, string date2)
{
    std::vector<std::string> date_vec_1 = split(date1, '-');
    std::string year1 = date_vec_1.at(0);
    std::string month1 = date_vec_1.at(1);
    std::string day1 = date_vec_1.at(2);
    string date1_ = year1 + month1 + day1;
    int date_1 = stoi(date1_);

    std::vector<std::string> date_vec_2 = split(date2, '-');
    std::string year2 = date_vec_2.at(0);
    std::string month2 = date_vec_2.at(1);
    std::string day2 = date_vec_2.at(2);
    string date2_ = year2 + month2 + day2;
    int date_2 = stoi(date2_);

    if (date_1 < date_2)
    {
        return true;
    }
    else
    {
        return false;
    }
}




//cancel gig details for artist and check
bool GIGS::cancel(const string & artist, const string & date__)
{
    string date;
    //checking valid artist name
    if (artist_gigs_list.find(artist) == artist_gigs_list.end()) {
        cout << "Error: Not found." <<endl;
        return false;
    }
    //checking valid date
    bool check_date = is_valid_date(date__);
    if (!check_date) {
        cout << "Error: Invalid date." << endl;
        return false;
    }
    for (const auto & ele: artist_gigs_list.at(artist))
    {
        bool compare = comparing_date(date__, ele.first);
        if (compare)
        {
            date = ele.first;
            break;
        }
    }

    vector <string> temp_dates; //cancelled dates
    vector <string> temp_stages; //cancelled stage gigs
    bool flag_n = false;
    for (const auto & i: artist_gigs_list.at(artist))
    {
        if (i.first == date)
        {
            flag_n = true;
        }
        if (flag_n)
        {
            temp_dates.push_back(i.first);
            temp_stages.push_back(i.second[0]);
        }
    }
    unsigned int temp_dates_size = temp_dates.size();
    if (temp_dates.size() == 0)
    {
        cout << "Error: No gigs after the given date."<< endl;
        return false;
    }
    unsigned int temp_stages_size = temp_stages.size();
    //updating artist_gigs_list
    for (unsigned int i = 0; i < temp_dates_size; i++)
    {
        artist_gigs_list.at(artist).erase(temp_dates[i]);
    }
    bool count = true;
    set <string> empty;

    //separating the name...again
    vector <string> ble;
    vector <string> temp_name_stages;
    for (unsigned int i = 0; i < temp_stages_size; i++)
    {
        ble = split(temp_stages[i], ',');
        string ble2 = ble[1].substr(1,ble[1].length() - 1);
        temp_name_stages.push_back(ble2);
    }

    //updating stage_data
    for (const auto & i:stage_data)
    {
        if (i.second.find(artist) != i.second.end()) //exist
        {
            if (find(temp_name_stages.begin(), temp_name_stages.end(), i.first) != temp_name_stages.end())
            {
                stage_data.at(i.first).erase(artist);
            }

        }
    }
    map<string, set<string>> copy_stage_data = stage_data;
    for (const auto & i:copy_stage_data)
    {
        if (i.second == empty)
        {
            stage_data.erase(i.first);
        }
    }

    //updating stage_name
    for (unsigned int i = 0; i < temp_dates_size; i++)
    {
        for (const auto & j:stage_name)
        {
            if (j.second.find(temp_dates[i]) != j.second.end()) //exist
            {
                if (find(temp_stages.begin(), temp_stages.end(), j.first) != temp_stages.end())
                {
                    stage_name.at(j.first).erase(temp_dates[i]);
                }

            }
        }
    }
    map<string, set<string>> copy_stage_name = stage_name;
    for (const auto & i:copy_stage_name)
    {
        if (i.second == empty)
        {
            stage_name.erase(i.first);
        }
    }

    if (count)
    {
        cout << "Artist's gigs after the given date cancelled." << endl;
    }
    return true;
}

