#include "units.h"
#include <stdexcept>

/** Two-argument constructor, sets value and units of UValue object. */
UValue::UValue(double value, const string &units) {
    this->value = value;
    this->units = units;
}

/** Returns the value of a UValue object. */
double UValue::get_value() const {
    return value;
}

/** Returns the units of a UValue object. */
string UValue::get_units() const {
    return units;
}

/** Default constructor (no default arguments). */
UnitConverter::UnitConverter() {

}

/**
* Adds new conversions to the converter and throws exception if a conversion
* already exists.
* @param from_units units to be converted from as a string.
* @param multiplier multiplier between from_units and to_units as a double.
* @param to_units units to be converted to as a string.
* @return none.
*/
void UnitConverter::add_conversion(const string &from_units, double multiplier,
    const string &to_units) {

        /** Check each element of the object holding existing conversions. */
        for (unsigned int i = 0; i < conversion.size(); i++) {
            /** If the new conversion already exists, report error. */
            if ((from_units == conversion[i].from_units) &&
            (to_units == conversion[i].to_units)) {

                string duplicate_error = "Already have a conversion from " +
                from_units + " to " + to_units + "\n";

                throw invalid_argument(duplicate_error);
            }
        }

        /**
        * If not already in object, add conversion to vector of conversions.
        */

        /** Add conversion from first unit to second unit. */
        conversion.push_back({from_units, multiplier, to_units});
        /** Add conversion from second unit to first unit. */
        conversion.push_back({to_units, 1 / multiplier, from_units});
    }

/**
* Performs conversion from one unit to another. Throws exception if
* conversion cannot be performed.
* @param v UValue object containing value and units to be converted from.
* @param to_units the units to be converted to as a string.
* @param seen a set to hold units already seen.
* @return UValue object containing new value and units.
*/
UValue UnitConverter::convert_to(const UValue &v, const string &to_units,
set<string> seen) const {

    /** Add units to be converted from to seen. */
    seen.insert(v.get_units());

    /** Check each element of UnitConverter object for correct conversion. */
    for (unsigned int i = 0; i < conversion.size(); i++) {

        /**
        * If desired conversion found, multiply input value by multiplier and
        * return UValue object containing calculated results.
        */
        if ((v.get_units() == conversion[i].from_units) &&
        (to_units == conversion[i].to_units)) {
            UValue results{(v.get_value() * conversion[i].multiplier),
                to_units};
            return results;
            }
    }

    /** If one-step conversion not found, look for multi-step conversions. */
    for (unsigned int i = 0; i < conversion.size(); i++) {
        try {
            /**
            * If conversion has same from_units as v and conversion[i].to_units
            * has not been seen yet, convert v into a new UValue object v2
            * with units conversion[i].to_units, then return whatever
            * convert_to(v2, to_units, seen) does.
            */
            if ((v.get_units() == conversion[i].from_units) &&
            (seen.count(conversion[i].to_units) == 0)) {
                UValue v2{(v.get_value() * conversion[i].multiplier),
                    conversion[i].to_units};
                return convert_to(v2, to_units, seen);
            }
        }
        /** If calling convert_to recursively throws exception, ignore it. */
        catch (invalid_argument){
        }
    }

    /** If no conversion path found, report failure. */
    string missing_error = "Don't know how to convert from " + v.get_units()
     + " to " + to_units + "\n";
    throw invalid_argument(missing_error);
}

/**
* Two-argument version of convert_to that calls three-argument convert_to.
* @param v UValue object containing value and units to be converted from.
* @param to_units the units to be converted to as a string.
* @return UValue object containing new value and units.
*/
UValue UnitConverter::convert_to(const UValue &v, const string &to_units)
const {
    return convert_to(v, to_units, set<string>{});
}
