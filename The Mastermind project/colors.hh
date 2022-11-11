/* Mastermind
 * Program author
 * Name: Mai Nguyen
 * Student number: 50358236
 * UserID: ddmang
 * E-Mail: mai.n.nguyen@tuni.fi
 * */
#include <vector>
#include <string>
using namespace std;

class Colors
{
public:
    Colors(vector <char> color_series);
    vector <char> series_;
    string print_series() const;
    vector <char> get_series();
private:
};
