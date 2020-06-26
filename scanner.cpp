#include<iostream>
#include<fstream>
#include<string>
using namespace std;

/* Look for all **'s and complete them */

//=====================================================
// File scanner.cpp written by: Group Number: 16 
//=====================================================

// --------- Two DFAs ---------------------------------

// WORD DFA 
// Done by: Eric Perez
// RE:   Eric Perez
bool word (string s){
	//cout << " entering the word function." << endl;
	int state = 0;
	int charpos = 0;

	while (s[charpos] != '\0') 
		{
		char c = s[charpos];
		
		//state 0 = q0
		     if (state == 0 && (c == 'n' || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E'))
		state = 1; //q1
		else if (state == 0 &&  c == 'c')
		state = 3; //qc
		else if (state == 0 &&  c == 's')
		state = 6; //qs		
		else if (state == 0 &&  c == 't')
		state = 5; //qt
		else if (state == 0 && (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'r' || c == 'p' || c == 'j' || c == 'd' || c == 'w' || c == 'y'))
		state = 4; //qcon
	
		//state 1 = q01
		else if (state == 1 && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E'))
		state = 0; //q1
		else if (state == 1 &&  c == 'c')
		state = 3; //qc
		else if (state == 1 &&  c == 't')
		state = 5; //qt
		else if (state == 1 &&  c == 's')
		state = 6; //qs
		else if (state == 1 && (c == 'd' || c == 'j' || c == 'w' || c == 'y' || c == 'z'))
		state = 2; //q2	
		else if (state == 1 && (c == 'b' || c == 'g' || c == 'h' || c == 'k' || c == 'm' || c == 'r' || c == 'p'))
		state = 4; //qcon	
	
		//state 2 = q2
		else if (state == 2 && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E'))
		state = 0; //q0	
	
		//state 3 = qc
		else if (state == 3 &&  c == 'h')
		state = 4; //qcon	
	
		//state 4 = qcon
		else if (state == 4 && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c =='y' || c == 'I' || c == 'E'))
		state = 0; //q0	

		//state 5 = qt
		else if (state == 5 && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E'))
		state = 0; //q0
		else if (state == 5 &&  c == 's')
		state = 4; //qcon

		//state 6 = qs
		else if (state == 6 && (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'I' || c == 'E'))
		state = 0; //q0
		else if (state == 6 &&  c == 'h')
		state = 4; //qcon
	
	
		else return 0;
		//cout << "state: " << state << endl;
		charpos++;
    }//end of while

  if (state == 0 || state == 1) return(true);  // end in a final state
   else return(false);
}

// PERIOD DFA 
// Done by: Eric Perez
bool period (string s)
{  	if (s == ".") return 1;
	else return 0;
}

// ------ Three  Tables -------------------------------------

// TABLES Done by: Eric Perez

enum tokentype {CONNECTOR, DESTINATION, EOFM, ERROR, IS, OBJECT, PERIOD, PRONOUN, SUBJECT, VERB, VERBNEG, VERBPAST, VERBPASTNEG, WAS, WORD1, WORD2};

string tokenName[30] = {"CONNECTOR", "DESTINATION", "EOFM", "ERROR", "IS", "OBJECT", "PERIOD", "PRONOUN", "SUBJECT", "VERB", "VERBNEG", "VERBPAST", "VERBPASTNEG", "WAS", "WORD1", "WORD2"}; 

const int numRW = 19;
string reservedWords[numRW] = {"masu", "masen", "mashita","masendeshita","desu","deshita","o","wa","ni","watashi", "anata", "kare", "kanojo", "sore", "mata", "soshite","shikashi","dakara","eofm"};
string reservedWordsType[numRW] = {"VERB", "VERBNEG", "VERBPAST","VERBPASTNEG","IS","WAS","OBJECT","SUBJECT","DESTINATION","PRONOUN", "PRONOUN", "PRONOUN", "PRONOUN", "PRONOUN", "CONNECTOR", "CONNECTOR","CONNECTOR","CONNECTOR","EOFM"};

// ------------ Scaner and Driver ----------------------- 

ifstream fin;  // global stream for reading from the input file

// Scanner processes only one word each time it is called
// Gives back the token type and the word itself
// Done by: Eric Perez
int scanner(tokentype& tt, string& w){
  
  string input;
  fin >> input;							// Grab the next word from the file via fin
  // 1. If it is eofm, return right now. 
	//cout << input << endl;
	if (input == "eofm"){
		tt = EOFM; w = tokenName[2];
		return 2;
	}
	else {
		if (period(input)){
			tt = PERIOD; 
			w = tokenName[6];
			return 6;
		}
		else if (word(input)){					// if the word is an acceptable japanese word
			for (int i = 0; i < numRW; i++){
				if (input == reservedWords[i]){	// check it against the list of reseved words.
					switch(i){					// if it is in the reserved word array, return it's location in the array.
						case  0: tt = VERB; w = tokenName[9]; return  9; break; // verb
						case  1: tt = VERBNEG; w = tokenName[10];return 10; break; // verbneg
						case  2: tt = VERBPAST; w = tokenName[11];return 11; break; // verbpast
						case  3: tt = VERBPASTNEG; w = tokenName[12];return 12; break; // verbpastneg
						case  4: tt = IS; w = tokenName[4];return  4; break; // is
						case  5: tt = WAS; w = tokenName[13];return 13; break; // was
						case  6: tt = OBJECT; w = tokenName[5];return  5; break; // object
						case  7: tt = SUBJECT; w = tokenName[8];return  8; break; // subject
						case  8: tt = DESTINATION; w = tokenName[1];return  1; break; // destination
						case  9: tt = PRONOUN; w = tokenName[7];return  7; break; // pronoun
						case 10: tt = PRONOUN; w = tokenName[7];return  7; break; // pronoun
						case 11: tt = PRONOUN; w = tokenName[7];return  7; break; // pronoun
						case 12: tt = PRONOUN; w = tokenName[7];return  7; break; // pronoun
						case 13: tt = PRONOUN; w = tokenName[7];return  7; break; // pronoun
						case 14: tt = CONNECTOR; w = tokenName[0];return  0; break; // connector
						case 15: tt = CONNECTOR; w = tokenName[0];return  0; break; // connector
						case 16: tt = CONNECTOR; w = tokenName[0];return  0; break; // connector
						case 17: tt = CONNECTOR; w = tokenName[0];return  0; break; // connector
						case 18: tt = EOFM; w = tokenName[2];return  2; break; // eofm
						break;
					}//end of switch				
				} //end of reserved word if
			}// end of for loop
			if (input.at(input.length()-1) == 'I' || input.at(input.length()-1) == 'E'){
						tt = WORD2; w = tokenName[15];return 15;				// word 2 
					}
			else{ tt = WORD1; w = tokenName[14];return 14;}						// word 1
		} // end of word check
		else{
			cout << "Lexical error: " << input << " is not a valid token" << endl;
			tt = ERROR; 
			w = tokenName[3];
			return 3;
		}
		
//  4. Return the token type & string  (pass by reference)
	} // end of else if
  
}//the end of scanner



// The temporary test driver to just call the scanner repeatedly  
// This will go away after this assignment
// DO NOT CHANGE THIS!!!!!! 
// Done by:  Rika
int main()
{
  tokentype thetype;
  string theword; 
  string filename;

  cout << "Enter the input file name: ";
  cin >> filename;

  fin.open(filename.c_str());

  // the loop continues until eofm is returned.
   while (true)
    {
       scanner(thetype, theword);  // call the scanner which sets
                                   // the arguments  
       if (theword == "EOFM") break;  // stop now

       cout << "Type is:" << tokenName[thetype] << endl;
       cout << "Word is:" << theword << endl;   
    }

   cout << "End of file is encountered." << endl;
   fin.close();

}// end

