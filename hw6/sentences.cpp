#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void readWords(char* filename, vector<vector<string> >& words);

// client interface
void generateSentences(vector<vector<string> >& words, ofstream& ofile);

// recursive helper function
void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences);

void readWords(char* filename,vector<vector<string> >& words)
{
  ifstream ifile(filename);
  if(ifile.fail())
  {
    cout << "Failed to open file!" << endl;
    return;
  }
  words.resize(4);
  for(int i=0; i<4; i++) // parses each type of word
  {
    string line;
    getline(ifile, line);
    if(ifile.fail())
    {
      cout << "Unable to extract line." << endl;
      return;
    }
    stringstream ss(line);
    string word;
    ss >> word;
    while(!ss.fail())
    {
      words[i].push_back(word); // populates vector
      ss >> word;
    }
  }
}

void generateSentences(vector<vector<string> >& words, ofstream& ofile)
{
  string sentence = "The"; // all sentences start with "The"
  int numSentences = 0;
  genHelper(words, ofile, 0, sentence, numSentences);
  ofile << numSentences << " sentences."; // outputs number of sentences at the end
}

void genHelper(vector<vector<string> >& words,
	       ofstream& ofile,
	       int currentOption,
	       string sentence,
	       int& numSentences)
{
  if(currentOption == 4) // sentence is done
  {
    sentence += '.'; // all sentences end with "."
    ofile << sentence << endl; // outputs to file
    numSentences++;
    return;
  }

  if(words[currentOption].size() == 0 || currentOption == 0 || currentOption == 3) // if no adjective/adverbs, skips
  {
    genHelper(words, ofile, currentOption + 1, sentence, numSentences);
  }

  for (unsigned int i=0; i<words[currentOption].size(); i++) // recurses on each word of a type
  {
    genHelper(words, ofile, currentOption + 1, sentence + " " + words[currentOption][i], numSentences);
  }
}

int main(int argc, char* argv[])
{
  if(argc < 3){
    cerr << "Usage ./sentences input_file output_file" << endl;
  }
  vector<vector<string> > words;

  // Parse the file
  readWords(argv[1], words);

  // Check the status of parsing
  if(words.size() < 4){
    cerr << "Input file requires 4 lines of words" << endl;
    return 1;
  }

  // Open the output file
  ofstream ofile(argv[2]);
 
  // generate all the sentence options writing them to ofile
  generateSentences(words, ofile);

  ofile.close();

  return 0;
}
