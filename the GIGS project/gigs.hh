/*
 *  Authors
 * Name: Ngoc Mai Nguyen
 * Student number: 50358236
 * UserID: ddmang
 * E-Mail: mai.n.nguyen@tuni.fi
 * */

#ifndef GIGS_HH
#define GIGS_HH

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

//using STAGE_DATA = map<string, map<string, vector<string>>>;
//using ARTIST_GIGS_LIST = map<string, set<string>>;

using STAGE_DATA = map<string, set<string>>; // stage -> set of artists
using STAGE_NAME = map<string, set<string>>; // for printing our all stage names only // stage -> booked date
using ARTIST_GIGS_LIST = map<string, map<string, vector<string>>>; // artist name -> date -> stage

class GIGS
{
    public:
        GIGS(const string & infile);
        bool is_valid_date(const std::string& date_str);
        bool readfile();

        void print_all_stages();
        void print_all_artists();
        void print_artist_gigs_list(const string & artist);
        void print_stage_data(const string & stage);
        bool add_artist(const string & new_artist);
        bool add_gig(const string & artist, const string & date, const string & town, const string & name_stage);
        bool cancel(const string & artist, const string & date);
    private:
        vector <string> split(const string & str, char delim);
        bool comparing_date(string date1, string date);
        string filename_;
        STAGE_DATA stage_data;
        ARTIST_GIGS_LIST artist_gigs_list;
        STAGE_NAME stage_name;
};

#endif
