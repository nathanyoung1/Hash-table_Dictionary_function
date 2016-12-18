#include<iostream>
#include<vector>
#include<string>

using namespace std;


string capit(string word);                                                 // Capitalizes the characters of a given string

class Word
{
public:
  Word()                                                                    // Default constructor
  {
    theword = '\0';
    thedefinition ='\0';
    key = 0;
  };
  Word(string &giveword, string &givedefinition)                               // constructor
  {
    giveword = capit(giveword);                                                // Capitalizes the given word
    theword = giveword;
    thedefinition = givedefinition;
    key = generatekey();                                                // Generates a key
  }
  string theword;                                                              // member variables
  string thedefinition;
  int key;
  int generatekey()                                                               // Key generator
  {
    int newkey = 0;
    int i = 0;
    while (this->theword[i] != '\0')
    {
      newkey = newkey + theword[i++];
    }
    return newkey;
  }
};

int getnextprime(int n);                                                // finds the next prime after the given value

class Dictionary
{
public:
  Dictionary()                                                                  // Default constructor
  {
    size = 0;
    table.resize(101);
  }
  uint size;                                                                // member variable; size == number of current elements
  vector<vector<Word>> table;
  void insertit(Word &newword)                                                // The *dramatic voice* INSERT FUNCTION
  {
    bool rewrite = false;
    int hash = (newword.key) % (this->table.size());                           // creates new hash for given word
    for(uint i = 0; i < this->table[hash].size(); i++)                         // inspects for duplicate word
    {
      if(table[hash][i].theword == newword.theword)
      {
        this->table[hash][i].thedefinition = newword.thedefinition;
        rewrite = true;
        break;
      }
    }
    if(rewrite == false)
    {
      this->table[hash].push_back(newword);                                    // If word was not duplicated, increment size
      this->size++;
      if(this->size >= this->table.size())
      {
        this->rehashit();                                                // rehash table when loadfactor >= 1
      }
    }
  }
  bool containsit(string word)                                                // The *flamboyantly happy voice* CONTAINS FUNCTION!!!
  {
    string nothing = "";                                                       // creates new word class object
    Word searchby(word, nothing);                                              // for purposes of capitalizing the word in question
    int searchhash = (searchby.key) % this->table.size();                      // and generating a key to search by
      for(uint i = 0; i < this->table[searchhash].size(); i++)
      {
        if(this->table[searchhash][i].theword == searchby.theword)
        {return true;}
      }
      cout << "ERROR: Word not found" << endl;
      return false;
  }
  Word deleteit(string word)                                                  // The *dark batman voice* del... lete... fun... ction
  {
    string nothing = "";
    Word item(word, nothing);                                                // creates new word class for sames purposes as in containsit
    if (containsit(word) == false)
    {return item;}                                                            // no "nulptr"/"NULL"/"\0"/"0" equivalent for custom class objects?
    int searchhash = (item.key) % (this->table.size());
    for(uint i = 0; i < this->table[searchhash].size(); i++)
    {
      if(this->table[searchhash][i].theword == item.theword)                  // move the last word in the list at this hash address
      {                                                                       // to the current index, and delete the last item
        item = this->table[searchhash][i];
        //this->table[searchhash].erase(this->table[searchhash][i]);
        if (this->table[searchhash].size() > i)                                // check if current index is last element
        {this->table[searchhash][i] = move(this->table[searchhash][(this->table[searchhash].size()) - 1]);}
        this->table[searchhash].pop_back();
        this->size--;
        return item;
      }
    }
  }
  void rehashit()                                                             // The *normal monotone voice* rehash function...
  {
    int newsize = (getnextprime(this->size * 2));                              // determine size of new table
    vector<vector<Word>> oldtable = this->table;                               // copy current table into a temp vector
    vector<vector<Word>> newtable(newsize);
    this->table = newtable;
    for(uint i = 0; i < oldtable.size(); i++)
    {
      for(uint j = 0; j < oldtable[i].size(); j++)
      this->insertit(oldtable[i][j]);                                          // rehash all elements of old table
    }
  }
  void printdata()                                                            // The good stuff
  {
    double N = this->size;
    double TS = this->table.size();
    double loadfactor = N / TS;
    cout << "Number of words in dictionary: " << this->size << endl;
    cout << "Current table size: " << this->table.size() << endl;
    cout << "Current load factor: " << loadfactor << endl << endl;
  }
  void thepurpose(string word)                                                // of this program
  {
    string nothing = "";
    Word item(word, nothing);
    if (containsit(word) == false)
    {return;}
    int searchhash = (item.key) % (this->table.size());
    for (uint i = 0; i < this->table[searchhash].size(); i++)
    {
      if(this->table[searchhash][i].theword == item.theword)
      {
        cout << endl << this->table[searchhash][i].theword << ":" << endl;
        cout << this->table[searchhash][i].thedefinition << endl << endl;
        break;
      }
    }
  }
};


int getnextprime(int n)                                                // general algorithm found on some website
{
  bool isprime = false;
  int divisor = 6;
  while (isprime == false)
  {
    n++;
    if (n % 2 != 0 && n % 3 != 0)
    {
      while((divisor * 0.5) < n)
      {
        if (n % (divisor + 1) == 0 || n % (divisor - 1) == 0)
        {divisor += 6;}
        else
        {
          isprime = true;
          break;
        }
      }
    }
  }
  return n;
}

string capit(string word)                                                // HERE I AM!
{
  for(uint i = 0; i < word.length(); i++)
  {
    word[i] = toupper(word[i]);
  }
  return word;
}
