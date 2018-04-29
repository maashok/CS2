#include "regex.hh"
#include <iostream>

// Find first match of regular expression in a string
Range find(vector<RegexOperator *> regex, const string &s);

// Checks if a regex completely matches a string
bool match(vector<RegexOperator *> regex, const string &s);

