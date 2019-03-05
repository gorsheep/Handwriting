//
//  main.cpp
//  Handwriting
//
//  Created by Даниил Волошин on 2/14/19.
//  Copyright © 2019 Даниил Волошин. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <map>
using namespace std;

//#define WIDTH 4960
//#define HEIGHT 7014
#define WIDTH 10
#define HEIGHT 15


//Функция, которая заполянет мой std::map моей кодировкой (в будущем добавить заполнением из файла)
void fillEncoding(std::map<string, int> &encoding){
    encoding["А"]=1;     encoding["Б"]=2;     encoding["В"]=3;     encoding["Г"]=4;     encoding["Д"]=5;
    encoding["Е"]=6;     encoding["Ё"]=7;     encoding["Ж"]=8;     encoding["З"]=9;     encoding["И"]=10;
    encoding["Й"]=11;    encoding["К"]=12;    encoding["Л"]=13;    encoding["М"]=14;    encoding["Н"]=15;
    encoding["О"]=16;    encoding["П"]=17;    encoding["Р"]=18;    encoding["С"]=19;    encoding["Т"]=20;
    encoding["У"]=21;    encoding["Ф"]=22;    encoding["Х"]=23;    encoding["Ц"]=24;    encoding["Ч"]=25;
    encoding["Ш"]=26;    encoding["Щ"]=27;    encoding["Ъ"]=28;    encoding["Ы"]=29;    encoding["Ь"]=30;
    encoding["Э"]=31;    encoding["Ю"]=32;    encoding["Я"]=33;
    
    encoding["а"]=34;    encoding["б"]=35;    encoding["в"]=36;    encoding["г"]=37;    encoding["д"]=38;
    encoding["е"]=39;    encoding["ё"]=40;    encoding["ж"]=41;    encoding["з"]=42;    encoding["и"]=43;
    encoding["й"]=44;    encoding["к"]=45;    encoding["л"]=46;    encoding["м"]=47;    encoding["н"]=48;
    encoding["о"]=49;    encoding["п"]=50;    encoding["р"]=51;    encoding["с"]=52;    encoding["т"]=53;
    encoding["у"]=54;    encoding["ф"]=55;    encoding["х"]=56;    encoding["ц"]=57;    encoding["ч"]=58;
    encoding["ш"]=59;    encoding["щ"]=60;    encoding["ъ"]=61;    encoding["ы"]=62;    encoding["ь"]=63;
    encoding["э"]=64;    encoding["ю"]=65;    encoding["я"]=66;
    
    encoding["0"]=67;    encoding["1"]=68;    encoding["2"]=69;    encoding["3"]=70;    encoding["4"]=71;
    encoding["5"]=72;    encoding["6"]=73;    encoding["7"]=74;    encoding["8"]=75;    encoding["9"]=76;
    
    encoding["-"]=77;    encoding["—"]=78;    encoding["."]=79;    encoding[","]=80;    encoding["!"]=81;
    encoding["?"]=82;    encoding["("]=83;    encoding[")"]=84;    encoding["\""]=85;   encoding[";"]=86;
    encoding[":"]=87;    encoding["%"]=88;
}


//Функция, которая проверяет, нет ли в тексте неподдерживаемых символов
void allIncluded(string text, string chars){
    
    bool included = false; //буферная переменная (для каждого символа)
    bool allIncluded = true; //общая переменная (для всех символов)
    
    for (int i=0; i<text.length(); i++) {
        for (int j=0; j<chars.length(); j++) {
            if (text[i]==chars[j]) {
                included = true;
            }
        }
        
        if (included==false) {
            cout << i << "-го символа нет в азбуке" << endl;
            allIncluded = false;
            break;
        }
        
        included = false;
    }
    
    if (allIncluded) {
        cout << "С нашим текстом все в порядке" << endl;
        cout << endl;
    }else{
        cout << "В тексте есть некорректные символы" << endl;
        cout << endl;
    }
    
}


//Функция, которая пишет из .ppm файла в буферный массив
void readFile(int cWidth, int cHeight, int bufArray[cWidth*cHeight][3], ifstream &f){
    
    int r1,g1,b1,r2,g2,b2,r3,g3,b3,r4,g4,b4,r5,g5,b5,r6,g6,b6,r7,g7,b7,r8,g8,b8;
    int j=0;
    
    while (f >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4 >> r5 >> g5 >> b5 >> r6 >> g6 >> b6 >> r7 >> g7 >> b7 >> r8 >> g8 >> b8) {
        
        bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
        bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
        bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
        bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
        bufArray[j+4][0]=r5; bufArray[j+4][1]=g5; bufArray[j+4][2]=b5;
        bufArray[j+5][0]=r6; bufArray[j+5][1]=g6; bufArray[j+5][2]=b6;
        bufArray[j+6][0]=r7; bufArray[j+6][1]=g7; bufArray[j+6][2]=b7;
        bufArray[j+7][0]=r8; bufArray[j+7][1]=g8; bufArray[j+7][2]=b8;
        
        j+=8;
        
    }//end of while
    
    f.clear();                 // clear fail and eof bits
    f.seekg(0, std::ios::beg); // back to the start!
}

//Функция, которая добавляет выбранный символ в заданное место на холсте
void addToCanvas(int curPosi, int curPosj, string character, std::map<string, int> &encoding, vector< vector<int> > &canvas){
    
    //Номер символа в моей кодировке
    int idx;
    idx=encoding[character];
    
    //Имя файла                     !!!ВНИМАНИЕ!!!      !!!СМОТРИ КАКОЕ РАСШИРЕНИЕ У ТВОИХ ФАЙЛОВ!!!
    srand(time(0));
    string fileName = "Symbols/char" + to_string(idx) + "/" + to_string(idx) + "-" + to_string(1+(rand()%8)) + ".pbm";
    
    //Открываем файл символа
    ifstream charObj;
    charObj.open(fileName);
    
    //Создаем буферный .txt файл без стандартной шапки
    ofstream tempFileObj;
    tempFileObj.open("temp.txt");
    
    //Считываем cWidth и cHeight и заполняем буферный .txt файл
    string line="";
    int cWidth=0;
    int cHeight=0;
    int lineCount=0; //счетчик прочитанных строк
    while(getline(charObj, line))
    {
        lineCount++;
        if(lineCount==3){
            cWidth=stoi(line.substr(0, line.find(' ')));
            cHeight=stoi(line.substr(line.find(' ')+1));
        }
        
        if ((line!="P3")&&(line!="# 8-bit ppm RGB")&&(line!=to_string(cWidth)+" "+to_string(cHeight))&&(line!="255")) {
            tempFileObj << line << endl;
        }
    }
    tempFileObj.close();
    
    //Открываем буферный .txt файл для чтения в массив
    ifstream tempFileObj2;
    tempFileObj2.open("temp.txt");
    
    //Создаем буферный массив для символа
    int bufArray[cWidth*cHeight][3];
    
    //Заполняем буферный массив данными из .txt файла
    readFile(cWidth, cHeight, bufArray, tempFileObj2);
    
    
    //Записываем данные из буферного массива в массив холста
    for (int i=0; i<cWidth*cHeight; i++) {
        int bufi = curPosi-cHeight+1+floor(i/cWidth);
        int bufj = curPosj+i%cWidth;
        int n=(bufi-1)*WIDTH+bufj-1;
        canvas[n][0]=bufArray[i][0]; canvas[n][1]=bufArray[i][1]; canvas[n][2]=bufArray[i][2];
    }
    
    
    
    
    charObj.close();
    tempFileObj.close();
    remove("temp.txt");
}




        
    





int main() {
    
    //Разбираемся с файлами
    ifstream fileObj1;
    fileObj1.open("text.txt"); //файл с текстом
    
    ifstream fileObj2;
    fileObj2.open("myChars.txt"); //файл с поддерживаемыми символами
    
    ofstream canvasObj;
    canvasObj.open("canvas.ppm"); //файл холста
    
    string line; //буферный string для построчного чтения файлов

    
    string text = ""; //переменная моего текста
    string myChars = ""; //переменная моей "азбуки"
    

    //Записать первый файл в string
    while(getline(fileObj1, line))
    {
        //cout << line << endl;
        text += line;
    }
    
    //Записать второй файл в string
    while(getline(fileObj2, line))
    {
        //cout << line << endl;
        myChars += line;
    }
    
    
    //Проверяем, есть ли в нашем тексте неподдерживаемые символы
    allIncluded(text, myChars);
    
    
    //Создаем массив (вектор) холста (4960x7014=34789440)
    cout << "Генерируем массив холста..." << endl;
    vector< vector<int> > canvas(WIDTH*HEIGHT, vector<int>(3));
    cout << "Массив сгенерирован" << endl << endl;;
    
    //Заполняем массив холста белым
    cout << "Заполняем массив холста белым..." << endl;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        canvas[i][0]=255; canvas[i][1]=255; canvas[i][2]=255;
    }
    cout << "Массив заполнен успешно" << endl << endl;
    
    
    //Создаем переменную курсора
    int curPosi=10; //значение строки
    int curPosj=3; //значение столбца
    
    //Создаем map кодировки
    std::map<string, int> encoding;
    fillEncoding(encoding);
    
    cout << "Добавляем букву в массив холста..." << endl;
    addToCanvas(curPosi, curPosj, "Ю", encoding, canvas);
    
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        //cout << canvas[i][0] << endl;
    }
    
    
    canvasObj << "P3" << endl;
    canvasObj << WIDTH << " " << HEIGHT << endl;
    canvasObj << "255" << endl;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        canvasObj << canvas[i][0] << " " << canvas[i][1] << " " << canvas[i][2] << endl;
    }
    
    canvasObj.close();
    
    
    /*
    //ТЕСТ ЧТЕНИЯ PPM
    int bufArray[92*122][3];
    ifstream fileObjTest;
    fileObjTest.open("32-1.txt");
    readf(92, 122, bufArray, fileObjTest);
    for (int i=0; i<92*122; i++) {
        cout << bufArray[i][0] << " " <<  bufArray[i][1] << " "<<  bufArray[i][2] << endl;
    }
    
    
    //СОЗДАТЬ PPM
    ofstream fileObjTest2("32-1Gen.ppm");
    fileObjTest2 << "P3" << endl;
    fileObjTest2 << 92 << " " << 122 << endl;
    fileObjTest2 << "255" << endl;
    for (int i=0; i<92*122; i++) {
        fileObjTest2 << bufArray[i][0] << " " << bufArray[i][1] << " " << bufArray[i][2] << endl;
    }
    */
    
    
    


    cout << endl;
    return 0;
}
