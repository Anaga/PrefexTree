#include <algorithm>    // std::sort
#include <iostream>     // std::cout, fgetc
#include <fstream>      // std::ifstream
#include <map>          // std::map, find, emplace
#include <string>       // std::string, lenght, substr, push_back
#include <vector>       // std::vector, push_back

using namespace std;

#define N 10
#define MIN_WORD_LEN 4

// Helper funtion, return true for char [a..z][A..Z]
bool isLetter(char ch){
    if ((ch>='a') && (ch<='z')) return true;
    if ((ch>='A') && (ch<='Z')) return true;
    return false;
}

// Helper funtion, return copy if string in lower case.
// Modify only [A..Z] characters.
string toLower(string s){
    char ch;
    string lower;
    char delta = 'a'-'A';
    for (size_t i=0; i<s.length(); i++){
        ch = s.at(i);
        if ((ch>='A') && (ch<='Z')) ch+=delta; //up from capital letter to lower letter (char delta - 32)
        lower.push_back(ch);
    }
    return lower;
}

// Helper funtion,
// to sort long in descending order,
// and sort string in ascending order
bool compItems(pair<long, string> a, pair<long, string> b){
    if (a.first > b.first) return true;
    if (a.first == b.first) {
        if (a.second < b.second) return true;
    }
    return false;
}


// Function to generate new words from input item.
// item consist of count and source word.
//
// If new word exist in map, function update count,
// otherwise insert new word to map with count from input pair.
void generateWords(pair<long, string> item, map<string, long> *m){
    string const source = item.second;
    long count = item.first;
    size_t genWordLen = MIN_WORD_LEN;
    size_t const lenght = source.length();
    string newWord;
    map<string, long>::iterator it;

    for (size_t i=0; i<=lenght-MIN_WORD_LEN; i++){
        genWordLen = MIN_WORD_LEN+i;
        //cout << "genWordLen is : " << genWordLen << ", i is :" << i << endl;
        for (size_t start = 0; start<=lenght-genWordLen; start++) {
            count = item.first;
            newWord = source.substr(start, genWordLen);
            //cout << "Word source is : " << source << " : new word " << newWord << endl;
            it = m->find(newWord);
            if (it == m->end()){
                m->emplace(newWord,count);
                //cout << "insert  new  word '" << newWord << "' with count " << count << endl;
            }else {
                it->second+=count;
                //cout << "update exist word '" << newWord << "' with count " << it->second << endl;
            }
        }
    }//end of main loop
}

// Function with static vars to collect char in one word.
// Flag isReady will be set to true when word is copmleate.
// But function return collected word at any call.
// (Eaven if is not compleate)
string grabOneWord(const char ch, bool *isReady){
    static string word = "";
    static bool startWord = false;
    *isReady = false;
    if (isLetter(ch) && (!startWord)){
        //we start to collect new word
        startWord = true;
        word = "";
    }
    if (isLetter(ch) && (startWord)){
        //we continue to collect word
        word.push_back(ch);
    }
    if (!isLetter(ch) && (startWord)){
        cout << word << endl;
        //stop collect word
        startWord = false;
        *isReady = true;
    }
    return word;
}

// Main function working with file.
// First - get file size and try to estimate reading time.
// Second - read file char by char, and call grabOneWord.
// When grabOneWord set wordIsCompleat to true, add this word to map,
// or update count of this word.
//
// Last - show some statistics.
string readFile(string qsFileName, map<string, long> *m){
    string message;
    ifstream input (qsFileName, std::ifstream::in);
    if (!input.is_open() )    {
        message = "Can't open file ";
        cout << message << qsFileName << endl;
        return message;
    }

    // get length of file:
    input.seekg (0, ios::end);
    long long iFileSize = input.tellg();
    long long iTimeOut = iFileSize/10000000;
    cout <<  "File size "<< iFileSize << " in bytes\nTo parse it, this can take " << iTimeOut<<" sec \n";
    input.seekg (0, ios::beg);


    long totalWords = 0;
    long longWords = 0;
    long unicWords = 0;
    char ch;
    string oneWord;
    bool wordIsCompleat = false;
    map<string, long>::iterator it;
    while (input.good()) {
        ch = static_cast<char> (input.get() );
        oneWord = grabOneWord(ch,&wordIsCompleat);
        if (!wordIsCompleat) continue;

        totalWords++;
        if (oneWord.length()>=MIN_WORD_LEN) {
            string lowerWord = toLower(oneWord);
            longWords++;

            it = m->find(lowerWord);
            if (it == m->end()){
                unicWords++;
                m->emplace(lowerWord,1);
            }else {
                it->second++;
            }
        }
    }
    input.close();

    cout << "Ok, in file " << qsFileName << ", all word count is " << totalWords <<
            ", long word is " << longWords << " count, unique long words is " <<unicWords << endl;

    message = "Ok";
    return message;
}

// Function to make new map with short words.
// It use pair<long, string> myItem to pass input word and count to
// function generateWords.
//
// For general English text new map is about 10 times bigger, them original map.
map<string, long> generateExtraMap(map<string, long> originalMap){
    pair<long, string> myItem;
    map<string, long> newMap;
    map<string, long>::const_iterator i=originalMap.begin();
    while (i!=originalMap.end()) {
        //cout << "my Map: " << i->first << " : "<< i->second << endl;
        myItem.first = i->second;
        myItem.second = i->first;
        generateWords(myItem, &newMap);
        ++i;
    }
    return newMap;
}

// Functin to copy all data from map to vector, and
// count total words count in extended map.
long fillVector(vector<pair<long, string>> *toFill, map<string, long> fromMap){
    long total=0;
    pair<long, string> myItem;
    auto i=fromMap.begin();
    while (i!=fromMap.end()) {
        total+= i->second;
        myItem.first = i->second;
        myItem.second = i->first;
        toFill->push_back(myItem);
        ++i;
    }
    return total;
}

// Functin to sort vector items according to helper function compItems
// Then print out N items from the top.
void printVector(vector<pair<long, string>> toPrint, long totalCount, int topCount){
    // sort vector first
    sort(toPrint.begin(), toPrint.end(),compItems);
    cout << "Total words count is " << totalCount << endl;
    double percent;
    long intVal;
    int cur=0;
    for (auto myItem : toPrint){
        intVal = myItem.first;
        percent = static_cast<double>(intVal*100) / static_cast<double>(totalCount);
        if (myItem.second.length()<8) {
            cout << myItem.second << "\t\t : " << percent << "% \t: ("<<intVal<< ") of " << totalCount << endl;
        } else {
            cout << myItem.second << "\t : " << percent << "% \t: ("<<intVal<< ") of " << totalCount << endl;
        }
        cur++;
        if (cur>=topCount) break;
    }
}

// Main function to handle some exeptions and to do all job.
// First - readFile and fill myMap with unique words from file.
// (Most time consuming operation)
//
// Second - generate extended map, calling function generateWords foreach word in myMap.
//
// Next - copy all items from extended map to vector, call function fillVector.
// Last - sort and print N top items from vector.
void analyseLog(string fileName){
    string message;
    map<string, long> myMap;
    cout << "Start to read file :" << fileName << endl;
    message = readFile(fileName, &myMap);
    cout << message << endl;
    if (message != "Ok") {
        cout << "Somthing wrong with file '" << fileName << "' skip it!\n";
        return;
    }

    if (myMap.size()==0){
        cout << "We canot find words longer than "<< MIN_WORD_LEN <<" in '" << fileName << "' skip it!\n";
        return;
    }

    message = "Start to generate extended map, with new short words.\n";
    cout << message;

    map<string, long> extendedMap = generateExtraMap(myMap);
    message = "Extended map now have ";
    cout << message << extendedMap.size() << " elements\n";

    message = "Fill vector from extended map.\n";
    cout << message;

    long totalCount=0;
    vector<pair<long, string>> myVector;
    totalCount = fillVector(&myVector, extendedMap);

    message = "Print top N words and it percents. N is ";
    cout << message << N << endl;
    printVector(myVector, totalCount, N);

}

int main()
{
    string logFolder = "";
    string qsFileName = "s2.txt";
    
    analyseLog(qsFileName);

    qsFileName = "s.txt";
    analyseLog(logFolder +qsFileName);
    /*
    qsFileName = "QChar.md";
    analyseLog(logFolder+ "/" +qsFileName);

    qsFileName = "QtWebEngine5.12.html";
    analyseLog(logFolder+ "/" +qsFileName);

    qsFileName ="THREE-MEN-IN-A-BOAT.html";
    analyseLog(logFolder+ "/" +qsFileName);

    qsFileName ="textfile.log";
    analyseLog(logFolder+ "/" +qsFileName);

    qsFileName = "jsonfile.log";
    analyseLog(logFolder+ "/" +qsFileName);


    qsFileName = "aex-client.log";
    analyseLog(logFolder+ "/" +qsFileName);
    
    qsFileName = "tales_stable.pl.xml";
    analyseLog(logFolder+ "/" +qsFileName);
*/
    return 0;
}
