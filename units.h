#include <string>
#include <vector>
#include <set>

using namespace std;

/**
* Represents a numeric value and its units.
*/
class UValue {

    /** Data member that stores value. */
    double value;
    /** Data member that stores value's units. */
    string units;

    public:

        /**
        * Constructor that takes a value and some units, then stores them
        * into the UValue object.
        */
        UValue(double value, const string &units);

        /** Member function that returns stored value. */
        double get_value() const;
        /** Member function that returns units. */
        string get_units() const;

};

/**
* Declaration of function for unit conversions.
*/
UValue convert_to(const UValue &input, const string &to_units);

/**
* Keeps track of conversions. This includes units being converted between and
* their corresponding multiplier.
*/
class UnitConverter {

    /**
    * Keeps track of the units being converted between and the multiplier.
    */
    struct Conversion {
        string from_units;
        double multiplier;
        string to_units;
    };

    /** Data member for storing collection of conversions that object knows. */
    vector<Conversion> conversion;

    public:

        /** Default constructor. */
        UnitConverter();

        /** Constructor that takes a vector containing the units to be converted
        * between and the multiplier and stores it into the UnitConverter
        * object.
        */
        UnitConverter(const vector<Conversion> &conversion);

        /** Member function that adds new conversions to the converter. */
        void add_conversion(const string &from_units, double multiplier,
            const string &to_units);

        /** Member function that looks up and performs the conversion.
        * If conversion fails, throws exception with error message.
        */
        UValue convert_to(const UValue &v, const string &to_units,
            set<string> seen) const;

        /** Two-argument version of convert_to member function. */
        UValue convert_to(const UValue &v, const string &to_units) const;

};
