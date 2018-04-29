#include "regex.hh"
#include <iostream>


/* Initialize the regex operator to apply exactly once. */
RegexOperator::RegexOperator() {
    minRepeat = 1;
    maxRepeat = 1;
}

/* Deallocate memory for the regex operator */
RegexOperator::~RegexOperator() {
	matches.erase(matches.begin(), matches.end());
}


/* Returns the "minimum repeat count" value. */
int RegexOperator::getMinRepeat() const {
    return minRepeat;
}


/* Returns the "maximum repeat count" value. */
int RegexOperator::getMaxRepeat() const {
    return maxRepeat;
}


/* Sets the "minimum repeat count" value. */
void RegexOperator::setMinRepeat(int n) {
    assert(n >= 0);
    minRepeat = n;
}


/* Sets the "maximum repeat count" value. */
void RegexOperator::setMaxRepeat(int n) {
    assert(n >= -1);
    maxRepeat = n;
}


/* Clears the list of matches stored in the regex operator.  Typically done
 * in preparation to try to match the regex to a new string.
 */
void RegexOperator::clearMatches() {
    matches.clear();
}


/* Records a new match of the operator in the list of matches. */
void RegexOperator::pushMatch(const Range &r) {
    matches.push_back(r);
}


/* Reports how many times the regex operator has successfully matched in the
 * string.
 */
int RegexOperator::numMatches() const {
    return (int) matches.size();
}


/* Removes the last match the operator successfully matched against.  Used for
 * backtracking by the regex engine.
 */
Range RegexOperator::popMatch() {
    Range r = matches.back();
    matches.pop_back();
    return r;
}

// Initialize the matchchar operator to match a specific character
MatchChar::MatchChar(char specChar) {
	matchChar = specChar;
}

// Nothing dynamically allocated to delete
MatchChar::~MatchChar() {

}

// Find the range to match a specific character only 
bool MatchChar::match(const string &s, Range &r) const {
	// If the starting index is out of range can't match
	if (unsigned(r.start) >= s.size())
		return false;
	// Otherwise if the character matches, the end of the
	// range is the next character
	if (s[r.start] == matchChar) {
		r.end = r.start + 1;
		return true;
	}
	// If the character doesn't match, matchchar is false
	else {
		return false;
	}
}

// Initialize matching of any character at all
MatchAny::MatchAny() {
	
}

// Nothing to delete
MatchAny::~MatchAny() {

}

// Find the range to match any character
bool MatchAny::match(const string &s, Range &r) const {
	// If the start index is out of range, can't match
	if (unsigned(r.start) >= s.size())
		return false;
	// Otherwise any character will match so the end to
	// the range is just the next character
	r.end = r.start + 1;
	return true;
}

// Initialize matching to a subset by saving the subset of possible
// characters
MatchFromSubset::MatchFromSubset(string subset) {
	subsetMatch = subset;
}

// Nothing to deallocate
MatchFromSubset::~MatchFromSubset() {

}

// Find the range to match a character within a subset
bool MatchFromSubset::match(const string &s, Range &r) const {
	// If out of range, can't match
	if (unsigned(r.start) >= s.size())
		return false;
	// Otherwise check if can find the character at the start in the subset
	// If so return that character's range
	if (subsetMatch.find(s[r.start]) != string::npos) {
		r.end = r.start + 1;
		return true;
	}
	return false;
}

// Initialize excluding from subset by saving subset of impossible
// characters to match to
ExcludeFromSubset::ExcludeFromSubset(string subset) {
	subsetExclude = subset;
}

// Nothing to deallocate
ExcludeFromSubset::~ExcludeFromSubset() {

}

bool ExcludeFromSubset::match(const string &s, Range &r) const {
	// If out of range, can't match
	if (unsigned(r.start) >= s.size())
		return false;
	// Otherwise check if can find the character at the start in the subset
	// If we can't return that character's range since it is excluded  from
	// subset
	if (subsetExclude.find(s[r.start]) == string::npos) {
		r.end = r.start + 1;
		return true;
	}
	return false;
}

// Converts a string into a vector of Regex operators that implement the
// regular expression in a left to right manner
vector<RegexOperator *> parseRegex(const string &expr) {
	vector<RegexOperator *> parsed;
	unsigned int i = 0;
	// Go through the string regex character by character
	while (i < expr.size()) {
		RegexOperator *regex;
		// If the character is a backslash, then the next character is
		// included as a character and not an operator
		if (expr[i] == '\\') {
			regex = new MatchChar(expr[i + 1]);
			i += 1;
		}
		// If the character is a dot any character can match
		else if (expr[i] == '.') {
			regex = new MatchAny();
		}
		// If the character is the start of a bracket and there is no
		// exclude symbol
		else if (expr[i] == '[' && expr[i + 1] != '^') {
			// Create the subset to match to and add this to the regex
			string matchSubset;
			i += 1;
			// Add on characters to subset until reach end brackets
			while (expr[i] != ']') {
				matchSubset.push_back(expr[i]);
				i += 1;
			}
			regex = new MatchFromSubset(matchSubset);
		}
		// If there is an exclude symbol at the start of the bracket
		else if (expr[i] == '[') {
			string notMatchSubset;
			i += 2;
			// Add on characters to the non-match subset
			while (expr[i] != ']') {
				notMatchSubset.push_back(expr[i]);
				i += 1;
			}
			regex = new ExcludeFromSubset(notMatchSubset);
		}
		// Otherwise just add the character
		else {
			regex = new MatchChar(expr[i]);
		}
		i += 1;
		// If the match is optional allow for 0 or 1 inclusions
		if (expr[i] == '?') {
			regex->setMinRepeat(0);
			regex->setMaxRepeat(1);
			i += 1;
		}
		// The Kleene star allows for the previous character to be matched
		// zero to infinite times
		if (expr[i] == '*') {
			regex->setMinRepeat(0);
			regex->setMaxRepeat(INT_MAX);
			i += 1;
		}
		// The plus modifier allows for the previous character to be matched
		// one to infinite times
		else if (expr[i] == '+') {
			regex->setMinRepeat(1);
			regex->setMaxRepeat(INT_MAX);
			i += 1;
		}
		// Add the regex operator to the parsed string
		parsed.push_back(regex);
	}
	return parsed;
}

// To clear the regex delete the memory for every element of the regex
void clearRegex(vector<RegexOperator *> regex) {
	for (unsigned int i = 0; i < regex.size(); i++)
		delete regex[i];
}
