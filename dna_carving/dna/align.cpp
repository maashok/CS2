//
//  align.cpp
//  dna_alignment
//
//  Created by Erika DeBenedictis on 1/27/13.
//  Copyright (c) 2014 California Institute of Technology. All rights reserved.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

// scoring values
#define GAP_SCORE -5
#define MISMATCH -1
#define MATCHING 2

/**
 * @brief Packages the score and instruction string the align function returns
 */
struct align_result {
    int score;      // score of this alignment
    string inst;    // instruction on how to align the inputs

    align_result(int s, string i) {
        this->score = s;
        this->inst = i;
    }
    align_result() {
        this->score = 0;
        this->inst = "";
    }
};

// memo_type will allow us to hash the string input to align
// with its output for memoization
typedef unordered_map<string, align_result> memo_type;

/**
 * @brief Function takes two strings, s and t, and produces an align_result
 * of the highest alignment score and its corresponding instruction str.
 */
align_result align(string s, string t, memo_type &memo) {
    // if this result is memoized, use recorded result  
    string key = s + "," + t;
    if (memo.count(key) > 0){
      return memo[key];
    }
    // If string s is empty, then we have gaps in the first string
    // and the second string as is
    if (s.size() == 0 && t.size() != 0) {
		string inst(t.size(), 't');
		align_result answer(GAP_SCORE * t.size(), inst);
		memo[key] = answer;
		return answer;
	}
	// If string t is empty, then we have gaps in the second string
	// and the first string as is
	else if (t.size() == 0 && s.size() != 0) {
		string inst (s.size(), 's');
		align_result answer(GAP_SCORE * s.size(), inst);
		memo[key] = answer;
		return answer;
	}
	// If both strings are empty, there is no score
	else if (s.size() == 0 && t.size() == 0){
		memo[key] = align_result();
		return align_result();
	}
	// Possibility 1 - Try to align s and t without the first
	// character of s, and then add in the score for that lone character
	align_result poss1 = align(s.substr(1), t, memo);
	poss1.score += -5;
	poss1.inst = 's' + poss1.inst;
	// Possibility 2 - Try to align s and t without the first character
	// of t, and then add in the score for that lone character
	align_result poss2 = align(s, t.substr(1), memo);
	poss2.score += -5;
	poss2.inst = 't' + poss2.inst;
	// Possibility 3 - Try to align s and t, starting at the second
	// character of both, and then add in the score depending on 
	// whether the first characters match or don't
	align_result poss3 = align(s.substr(1), t.substr(1), memo);
	if (s.at(0) == t.at(0)) {
		poss3.score += 2;
		poss3.inst = '|' + poss3.inst;
	}
	else {
		poss3.score += -1;
		poss3.inst = '*' + poss3.inst;
	}
	// Of the three, whichever has maximum score is the optimal
	// alignment
	align_result answer;
	if (poss1.score > poss2.score && poss1.score > poss3.score)
		answer = poss1;
	else if (poss2.score > poss1.score && poss2.score > poss3.score)
		answer = poss2;
	else
		answer = poss3;
    /* Before you return your calculated  align_result object,
       memoize it like so:*/
    memo[key] = answer;
    return answer;
}

/**
 * @brief Wrapper function to print the results of align
 */
void DNA_align(string s, string t) {
    cout << endl << "Calling DNA align on strings " << s << ", " << t << endl;

    // create the memoization system
    memo_type memo;

    align_result answer = align(s, t, memo);
    string ans = answer.inst;
    // Printing section
    // line where string s will be printed, spaces inserted
    string line1 = "";
    // line where string t will be printed, spaces inserted
    string line2 = "";
    // description of the relationship between s and t here (* | s t)
    string line3 = "";

    int j = 0;      // running index in s
    int k = 0;      // running index in t

    for (unsigned int m = 0; m < ans.length(); m++) {
        // i is the next element in our instruction string ans
        string i = ans.substr(m, 1);

        // only in s
        if(i.compare("s") == 0){
            line1 += s[j]; j++;
            line2 += " ";
            line3 += "s";
        }

        // only in t
        else if (i.compare("t") == 0){
            line1 += " ";
            line2 += t[k]; k++;
            line3 += "t";
        }

        // mismatch
        else if (i.compare("*") == 0){
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "*";
        }

        // match
        else {
            line1 += s[j]; j++;
            line2 += t[k]; k++;
            line3 += "|";
        }
    }
    cout << line1 << endl << line2 << endl << line3 << endl;
	cout << "Score: " << answer.score << endl;
}

int main(){
    // some test cases to begin with
    DNA_align("",   "a");
    DNA_align("b",  "");
    DNA_align("a", "a");
    DNA_align("b",  "a");
    DNA_align("b",  "ba");
    DNA_align("ab", "ba");
    DNA_align("ab", "b");
    DNA_align("abracadabra", "avada kedavra");
    DNA_align("ACTGGCCGT", "TGACGTAA");
    return 0;
}
