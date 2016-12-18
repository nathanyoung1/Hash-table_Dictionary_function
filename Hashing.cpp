#include <fstream>
#include "Hashing.h"

using std::fstream;

int main(int argc, char* argv[])
{

  ifstream inputfile(argv[1]);

  if(!inputfile.is_open())
  {
    cout << "usage: [filename.json]" << endl << "Please enter a valid filename" << endl;
  }
  else{
  Dictionary ourdictionary;
  string theword;
  string thedefinition;



  // Appreciate my work... look at it ... appreciate it
  /*
  inputfile >> theword;
  theword.erase(0, 2);
  theword.erase(theword.length() - 2, theword.length());
  cout << theword << endl;
  getline(inputfile, thedefinition);
  thedefinition.erase(0, 2);
  thedefinition.erase(thedefinition.length() - 2, thedefinition.length());
  cout << thedefinition <<  endl;

  Word newword(theword, thedefinition);

  cout << newword.theword << endl;
  ourdictionary.insertit(newword);

  ourdictionary.thepurpose("CHILOSTOMATOUS");
*/
// char c;
  while(!inputfile.eof())
  {
    getline(inputfile, theword, ':');                                          // get the word
    if(inputfile.good() == false)                                              // check if we're even still in the file
    {break;}
    theword.erase(0, 2);                                                      // get rid of the formatting
    theword.erase(theword.length() - 1);
    getline(inputfile, thedefinition, '\n');                                    // get the definition
    thedefinition.erase(0, 2);                                                // get rid of the formatting
    thedefinition.erase(thedefinition.length() - 2, thedefinition.length());
    Word newword(theword, thedefinition);                                       // make the Word class object
    ourdictionary.insertit(newword);                                             // add it to the dictionary class object

    }
  ourdictionary.printdata();                                                    // display the table size load factor and such

  string usrinput;

  while(!cin.eof())                                                           // check for EOF
  {
    cout << "What word do you want the definition of? ";
    cin >> usrinput;
    if (cin.eof())
    {break;}
    ourdictionary.thepurpose(usrinput);                                         // look up the word
  }
}
  return 0;
}
