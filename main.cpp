#include <QCoreApplication>

#include <QTimer>
#include <QTextStream>
#include <QDebug>
#include <QString>
#include <iostream>
#include <QFile>
#include <QDateTime>
#include <QSet>
#include <QLocale>

using namespace std;

struct item{
    int count;
    QString word;
};

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
    int genWordLen = 4;
    int const lenght = source.length();
    QString newWord;
    for (int i=0; i<=lenght-4; i++){
        genWordLen = 4+i;
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

        /*
    while (!file.atEnd()){
        file.getChar(&old_ch);
        ch = old_ch;
    */
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
            if (word.length()>3) {
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

    QMap<QString, long>::const_iterator i=myMap.begin();
    /*
    while (i!=myMap.end()) {
        cout << "my Map: " << qPrintable(i.key()) << " : "<< i.value() << endl;
        ++i;
    }*/
    message = "Start to generage extended map, with new short words.\n";
    cout << qPrintable(message);

    pair<long, string> myItem;
    //int expectedmapSize = 10*myMap.size();
    QMap<QString, long> extendedMap;
    i=myMap.begin();
    while (i!=myMap.end()) {
        //cout << "my Map: " << qPrintable(i.key()) << " : "<< i.value() << endl;
        myItem.first = i.value();
        myItem.second = qPrintable(i.key());
        generateWords(myItem, &extendedMap);
        ++i;
    }

    vector<pair<long, string>> myVector;
    cout << "extendedMap now have " << extendedMap.count() << " elements\n";
    i=extendedMap.begin();
    while (i!=extendedMap.end()) {
        //cout << "extended Map: " << qPrintable(i.key()) << " : "<< i.value() << endl;
        myItem.first = i.value();
        myItem.second = qPrintable(i.key());
        myVector.insert(myVector.end(), myItem);
        ++i;
    }

    sort(myVector.begin(), myVector.end());
    cout << "my sorted vector have " << myVector.size() << " elements\n";
    vector<pair<long, string>>::const_iterator j = myVector.end();
    int N=0;
    while (j!=myVector.begin()) {
        --j;
        N++;
        cout << N <<" my Vec: " << j->second << " : " << j->first << endl;
        if (N>100) break;
    }
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString qsFileName = "input.txt";
    analyseLog(qsFileName);
/*
    qsFileName = "s.txt";
    analyseLog(qsFileName);

    qsFileName = "Simple.txt";
    analyseLog(qsFileName);

    qsFileName = "QChar.md";
    analyseLog(qsFileName);

    qsFileName = "timing-4.log";
    analyseLog(qsFileName);

    qsFileName = "ThreeMenShort.txt";
    //analyseLog(qsFileName);

    qsFileName ="THREE-MEN-IN-A-BOAT.html";
    //analyseLog(qsFileName);

    qsFileName = "jsonfile.log";
    analyseLog(qsFileName);
*/
    return a.exec();
}
