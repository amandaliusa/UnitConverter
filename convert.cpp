#include <iostream>
#include <string>
#include "units.h"
#include <stdexcept>
#include <fstream>

using namespace std;

/** Initializes conversions.
* @param filename string representing name of file with conversions to load.
* @return UnitConverter object that contains starting conversions.
*/
UnitConverter init_converter(const string &filename) {
    UnitConverter initial;
    ifstream file{filename};

    /** Make sure file was opened successfully. */
    if (!file.is_open()) {
        throw invalid_argument("Couldn't open file \n");
    }

    /** Read data until the end of the filename and add conversions to
    * UnitConverter object.
    */
    while (file.good()) {
        string from_units, to_units;
        double multiplier;

        file >> from_units >> multiplier >> to_units;

        initial.add_conversion(from_units, multiplier, to_units);
    }

    return initial;
}

int main() {
    double value;
    string units, to_units;
    UnitConverter u;

    try {
        /** Initialize UnitConverter object with default conversions. */
        u = init_converter("load_conversions.txt");
    }
    catch (invalid_argument e) {
        /** If the file cannot be loaded or contains the same conversion twice,
        * report error and exit program.
        */
        cout << e.what();
        return 1;
    }

    /** Prompt user for input to be converted. */
    cout << "Enter value with units: ";
    cin >> value >> units;

    /** Initialize UValue object with the user's input. */
    UValue v {value, units};

    /** Prompt user for units to be converted to. */
    cout << "Convert to units: ";
    cin >> to_units;

    try {
        /** Initialize UValue object with converted output. */
        UValue output = u.convert_to(v, to_units);

        /** If conversion successful, report success. */
        cout << "Converted to: " << output.get_value() << " " <<
        output.get_units() << "\n";
    }
    catch (invalid_argument e) {
        /** If conversion unsuccesful, report failure. */
        cout << "Couldn't convert to " << to_units << "!\n";
        cout << e.what();
    }

    return 0;
}
