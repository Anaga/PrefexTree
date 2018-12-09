#include <algorithm>    // std::sort
#include <iostream>     // std::cout, fgetc
#include <fstream>      // std::ifstream
#include <map>          // std::map, find, emplace
#include <string>       // std::string, lenght, substr, push_back
#include <vector>       // std::vector, push_back

using namespace std;

#define N 20
#define MIN_WORD_LEN 3

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

bool isLetter(char ch){
    if ((ch>='a') && (ch<='z')) return true;
    if ((ch>='A') && (ch<='Z')) return true;
    return false;
}

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

string readFile(string qsFileName, map<string, long> *m){
    string word;
    char ch;

    bool startWord = false;
    long count=0;
    long longWords = 0;
    long unicWords = 0;
    string message;

    map<string, long>::iterator it;

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

    while (input.good()) {
        ch = static_cast<char> (input.get() );
        //cout << ch;
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
            //cout << word << endl;
            count++;
            if (word.length()>=MIN_WORD_LEN) {
                string lowerWord = toLower(word);
                long count = 1;
                it = m->find(lowerWord);

                if (it == m->end()){
                    unicWords++;
                    m->emplace(lowerWord,count);
                }else {
                    it->second++;
                    count = it->second;
                }
                //cout << "insert '" << lowerWord << "' with value " << count << endl;
                longWords++;
            }
            //stop collect word
            startWord = false;
        }
    }
    input.close();
    //fclose(file);
    cout << "Ok, in file " << qsFileName << ", all word count is " << count <<
            ", long word is " << longWords << " count, unique long words is " <<unicWords << endl;

    message = "Ok";
    return message;
}

bool compItems(pair<long, string> a, pair<long, string> b){
    if (a.first > b.first) return true;
    if (a.first == b.first) {
        if (a.second < b.second) return true;
    }
    return false;
}

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
    string qsFileName = "s2.txt";
    analyseLog(qsFileName);

    qsFileName = "s.txt";
    analyseLog(qsFileName);

    qsFileName = "QChar.md";
    analyseLog(qsFileName);

    qsFileName = "QtWebEngine5.12.html";
    analyseLog(qsFileName);

    qsFileName ="THREE-MEN-IN-A-BOAT.html";
    analyseLog(qsFileName);

    qsFileName ="textfile.log";
    analyseLog(qsFileName);

    qsFileName = "jsonfile.log";
    analyseLog(qsFileName);
/*

*/
    return 0;
}
