#include <QCoreApplication>

#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <QFile>
#include <QDateTime>
#include <QMap>
#include <QLocale>

#include <iostream>
#include <map>
#include <string>

using namespace std;

#define N 20
#define MIN_WORD_LEN 4

void generateWords(pair<long, string> item, QMap<QString, long> *m){

    QString const source = QString::fromStdString(item.second);
    long count = item.first;
    int genWordLen = MIN_WORD_LEN;
    int const lenght = source.length();
    QString newWord;
    for (int i=0; i<=lenght-MIN_WORD_LEN; i++){
        genWordLen = MIN_WORD_LEN+i;
        //qDebug() << "genWordLen is : " << genWordLen << ", i is :" << i ;
        for (int start = 0; start<=lenght-genWordLen; start++) {
            count = item.first;
            newWord=source.mid(start, genWordLen);
          //qDebug() << "Word source is : " << source << ": new word" << newWord ;
            if (m->contains(newWord)){
                count += m->value(newWord);
            }
            m->insert(newWord,count);
            //qDebug() << "insert newWord " << newWord << " with value " << count;
        }
    }
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
    FILE *file;
    string message;

    map<string, long>::iterator it;

    file = fopen(qsFileName.data(), "r");

    if (file == nullptr) {
        message = "Can't open file ";
        cout << message << qsFileName << endl;
        return message;
    }
    while ( ! feof(file) ) {
        ch =static_cast<char>( fgetc(file) );
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
    fclose(file);
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

QMap<QString, long> generateExtraMap(QMap<QString, long> originalMap){
    pair<long, string> myItem;
    QMap<QString, long> newMap;
    QMap<QString, long>::const_iterator i=originalMap.begin();
    while (i!=originalMap.end()) {
        //cout << "my Map: " << qPrintable(i.key()) << " : "<< i.value() << endl;
        myItem.first = i.value();
        myItem.second = qPrintable(i.key());
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
    cout << "start to read file " << fileName << endl;
    message = readFile(fileName, &myMap);
    cout << message;

    message = "Start to generate extended map, with new short words.\n";
    cout << message;

    map<string, long> extendedMap; // = generateExtraMap(myMap);
    message = "Extended map now have";
    cout << message << extendedMap.size() << "elements\n";

    message = "Fill vector from extended map.\n";
    cout << message;

    long totalCount=0;
    vector<pair<long, string>> myVector;
    totalCount = fillVector(&myVector,myMap);

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
/*
*/
    return 0;
}
