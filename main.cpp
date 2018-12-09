#include <QCoreApplication>

#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QFile>
#include <QDateTime>
#include <QMap>
#include <QLocale>

using namespace std;

#define N 20
#define MIN_WORD_LEN 4

bool checkFile(QString qsFileName){
    QString message;

    QFile file(qsFileName);
    if (!file.exists()){
        message = "Can't find file %1 to read\n";
        message = message.arg(qsFileName);
        cout <<  qPrintable(message);
        return false;
    }

    if(!file.open(QFile::ReadOnly | QFile::Text))  {
        message = "Can't open the file %1 for reading\n";
        message = message.arg(qsFileName);
        cout <<  qPrintable(message);
        return false;
    }
    file.close();
    return true;
}

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

QString readFile(QString qsFileName, QMap<QString, long> *m){
    QString word;
    QChar ch;
    //char old_ch;
    bool startWord = false;
    long count=0;
    long longWords = 0;
    long unicWords = 0;

    QFile file(qsFileName);
    file.open(QFile::ReadOnly | QFile::Text);

    QTextStream inputConsole(&file);
    inputConsole.setAutoDetectUnicode(true);
    inputConsole.setCodec("UTF-8");
    while (!inputConsole.atEnd()) {
        inputConsole >> ch;
        if (ch.isLetter() && (!startWord)){
            //we start to collect new word
            startWord = true;
            word = "";
        }
        if (ch.isLetter() && (startWord)){
            //we continue to collect word
            word.append(ch);
        }
        if (!ch.isLetter() && (startWord)){
            // qDebug() << word;
            count++;
            if (word.length()>=MIN_WORD_LEN) {
                QString lowerWord = word.toLower();
                long count = 1;
                if (!m->contains(lowerWord)){
                    unicWords++;
                }else {
                    count = m->value(lowerWord);
                    count++;
                }
                m->insert(lowerWord,count);
                //qDebug() << "insert " << lowerWord << " with value " << count;

                //generateWords(word, m);
                longWords++;
                // qDebug() << word;
            }
            //stop collect word
            startWord = false;
        }
    }

    QString message = "Ok, in file %1, all word count is %2, long word is %3 count, unique long words is %4\n";
    message = message.arg(qsFileName).arg(count).arg(longWords).arg(unicWords);

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

long fillVector(vector<pair<long, string>> *toFill, QMap<QString, long> fromMap){
    long total=0;
    pair<long, string> myItem;
    QMap<QString, long>::const_iterator i=fromMap.begin();
    while (i!=fromMap.end()) {
        total+= i.value();
        myItem.first = i.value();
        myItem.second = qPrintable(i.key());
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
        cout << myItem.second << "\t : " << percent << "% \t: ("<<intVal<< ") of " << totalCount << endl;
        cur++;
        if (cur>=topCount) break;
    }
}

void analyseLog(QString fileName){
    QDateTime qdtStart = QDateTime::currentDateTime();
    qint64 startMilSec = QDateTime::currentMSecsSinceEpoch();
    QFile file(fileName);

    qint64 iFileSize = file.size();
    qint64 iTimeOut = iFileSize/10000000;
    QString message = "File size %1 in bytes\nTo parse it, this can take %2 sec \n";
    message = message.arg(iFileSize).arg(iTimeOut);
    cout <<  qPrintable(message);

    if (!checkFile(fileName)){
        cout << "Can't handl file" << qPrintable(fileName);
        return;
    }

    QMap<QString, long> myMap;
    message = readFile(fileName, &myMap);
    cout << qPrintable(message );

    QDateTime qdtStop = QDateTime::currentDateTime();
    qint64 stpoMilSec = QDateTime::currentMSecsSinceEpoch();
    qint64 delta = stpoMilSec - startMilSec;
    message = "Start time %1\n"
              "Stop  time %2\n"
              "Delta %3 milsec\n";
    QString qsTimeFormat = "hh:mm:ss.z";
    message = message.arg(qdtStart.toString(qsTimeFormat)).arg(qdtStop.toString(qsTimeFormat)).arg(delta);
    cout << qPrintable(message);

    message = "Start to generate extended map, with new short words.\n";
    cout << qPrintable(message);

    QMap<QString, long> extendedMap = generateExtraMap(myMap);
    message = "Extended map now have %1 elements\n";
    message =  message.arg(extendedMap.count());
    cout << qPrintable(message);

    message = "Fill vector from extended map.\n";
    cout << qPrintable(message);

    long totalCount=0;
    vector<pair<long, string>> myVector;
    totalCount = fillVector(&myVector,extendedMap);

    message = "Print top N words and it percents. N is ";
    cout << qPrintable(message) << N << endl;
    printVector(myVector, totalCount, N);

}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString qsFileName = "s2.txt";
    analyseLog(qsFileName);

    qsFileName = "s.txt";
    analyseLog(qsFileName);

    qsFileName = "Simple.txt";
    analyseLog(qsFileName);

    qsFileName = "QChar.md";
    analyseLog(qsFileName);

    qsFileName = "timing-4.log";
  //  analyseLog(qsFileName);

    qsFileName = "QtWebEngine5.12.html";
    analyseLog(qsFileName);

    qsFileName ="THREE-MEN-IN-A-BOAT.html";
  //  analyseLog(qsFileName);

    qsFileName = "jsonfile.log";
   // analyseLog(qsFileName);

    return a.exec();
}
