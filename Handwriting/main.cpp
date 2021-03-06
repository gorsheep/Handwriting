//
//  main.cpp
//  Handwriting
//
//  Created by Даниил Волошин on 2/14/19.
//  Copyright © 2019 Даниил Волошин. All rights reserved.


//  ТЕКУЩИЕ КОСЯКИ
//  * Рандомность начертания буквы определяется её горизонтальным положением. Это надо исправить, чтобы строки начинались по-разному
//  * У некоторых символов в нижнем правом углу возникают битые пикселы
//  * Даже если в тексте найдены неподдерживаемые символы, программа все равно продолжит пытаться что-то записать (добавить bool флаг)
//  * Не работает символ тире ("—")
//  * Программа создает лишь один лист (если текста больше, то просто заполняется один лист и все)


//  WARNING!!!
//  Типичные ошибки:
//  * Перепутать расширение файлов (.ppm и .pbm)
//  * Неверно задать curPos


//  Требования к изображениям символов:
//  * Ширина символа не менее 8 пикселей
//  * Высота символа строго 110 пикселей
//  * Файлов в каждой папке должно быть 8


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

#define WIDTH 4960
#define HEIGHT 7014
#define TRACKING 10      //трекинг
#define CHARHEIGHT 110   //высота символов
#define LEADING 30       //интерлиньяж
#define LEFTMARGIN 550   //отступ слева
#define RIGHTMARGIN 600  //отступ справа
//#define RIGHTMARGIN 2600  //отступ справа для двух колонок
#define SPACE 100        //расстояние между словами



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
            cout << i << "-го символа нет в азбуке (" << text[i-2] << text[i-1] << "|" << text[i] << text[i+1] << "|" << text[i+2] << ")" << endl;
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
void addToCanvas(int *curPosi, int *curPosj, string character, std::map<string, int> &encoding, vector< vector<int> > &canvas){
    
    //Номер символа в моей кодировке
    int idx=encoding[character];
    
    //Запоминаем изначальное текущее положение буквы
    int initCurPosi = *curPosi;
    
    //Если текущий символ -- запятая или точка с запятой, то сдвигаем ее чуть-чуть вниз
    if ((character==",")||(character==";")) {
        *curPosi+=20;
    }
    else{
        //Тверкаем значение curPosi, чтобы буквы не лежали на одной линии
        *curPosi+=-8+(*curPosj%9);
        //cout << *curPosi << endl;
    }
    
    //Имя файла                     !!!ВНИМАНИЕ!!!      !!!СМОТРИ КАКОЕ РАСШИРЕНИЕ У ТВОИХ ФАЙЛОВ!!!
    //Рандомная буква выбирается за счет to_string(1+(*curPosj%8)), то есть сидом рандома является горизонатльное положение буквы
    //на холсте. Это очень плохо! Потому что если две строчки подряд начинаются с одинаковых символов (слов), то они будут иметь
    //одинаковое начертание. Это надо исправить!
    string fileName = "Symbols/char" + to_string(idx) + "/" + to_string(idx) + "-" + to_string(1+(*curPosj%8)) + ".pbm";
    //cout << fileName << endl << endl;
    
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
    
    if ((*curPosi-cHeight<0)||(*curPosj+cWidth-1>WIDTH)) {
        cout << "НЕВЕРНО ВЫБРАНО ПОЛОЖЕНИЕ КУРСОРА" << endl;
    }else{
        
        //Открываем буферный .txt файл для чтения в массив
        ifstream tempFileObj2;
        tempFileObj2.open("temp.txt");
        
        //Создаем буферный массив для символа
        int bufArray[cWidth*cHeight][3];
        
        //Заполняем буферный массив данными из .txt файла
        readFile(cWidth, cHeight, bufArray, tempFileObj2);
        
        //cout << "Буферный массив успешно создан" << endl << endl;
        
        //Записываем данные из буферного массива в массив холста
        for (int i=0; i<cWidth*cHeight; i++) {
            int bufi = *curPosi-cHeight+1+floor(i/cWidth);
            int bufj = *curPosj+i%cWidth;
            int n=(bufi-1)*WIDTH+bufj-1;
            canvas[n][0]=bufArray[i][0]; canvas[n][1]=bufArray[i][1]; canvas[n][2]=bufArray[i][2];
        }
        
        //Корректируем значения curposi и curposj
        *curPosi=initCurPosi;
        *curPosj+=cWidth+TRACKING;
        //Если дошли до конца строки на листе
        if (*curPosj>=WIDTH-RIGHTMARGIN) {
            *curPosj=LEFTMARGIN;
            *curPosi+=LEADING+110; //110 - высота всех символов
        }
        
        
        tempFileObj2.close();
    }
    
    
    charObj.close();
    tempFileObj.close();
    remove("temp.txt");
}




        
    





int main() {
    
    //cout << "и"[0] << " " << "и"[1] << endl;
    
    //Разбираемся с файлами
    ifstream fileObj1;
    fileObj1.open("text.txt"); //файл с текстом
    
    ifstream fileObj2;
    fileObj2.open("myChars.txt"); //файл с поддерживаемыми символами
    
    ofstream canvasObj;
    canvasObj.open("canvas.ppm"); //файл холста
    
    string line;         //буферный string для построчного чтения файлов
    string text = "";    //переменная моего текста
    string myChars = ""; //переменная моей "азбуки" (нужна для проверки на неподдерживаемые символы)
    
    //Переменные курсора
    int curPosi=500; //значение строки
    int curPosj=LEFTMARGIN; //значение столбца
    
    
    //Записываем файл с текстом в string (чтобы проверить, есть ли в тексте неподдерживаемые символы)
    while(getline(fileObj1, line))
    {
        //cout << line << endl;
        text += line;
    }
    
    //Записываем файл с кодировкой в string (чтобы проверить, есть ли в тексте неподдерживаемые символы)
    while(getline(fileObj2, line))
    {
        //cout << line << endl;
        myChars += line;
    }
    
    //Проверяем, есть ли в нашем тексте неподдерживаемые символы
    allIncluded(text, myChars);
    fileObj1.close();
    
    //Создаем map кодировки
    std::map<string, int> encoding;
    fillEncoding(encoding);
    
    //Создаем массив (вектор) холста (4960x7014=34789440)
    cout << "Генерируем массив холста..." << endl << endl;
    vector< vector<int> > canvas(WIDTH*HEIGHT, vector<int>(3));
    cout << "Массив сгенерирован" << endl << endl;;
    
    //Заполняем массив холста белым
    cout << "Заполняем массив холста белым..." << endl;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        canvas[i][0]=255; canvas[i][1]=255; canvas[i][2]=255;
    }
    cout << "Массив заполнен успешно" << endl << endl;
    
    
    //Заново создаем объект файла с текстом (чтобы уже посимвольно его читать)
    ifstream textObj;
    textObj.open("text.txt");
    
    
    //Построчно читаем файл с текстом
    while(getline(textObj, line))
    {
        //Если попался enter
        if (line.length()==0) {
            //cout << "Хм, у нас тут enter" << endl;
            curPosj=LEFTMARGIN;
            //curPosi+=LEADING+110; //110 - высота всех символов
            curPosi+=110; //110 - высота всех символов
        }
        
        //Посимвольно читаем текущую строку
        for (int i=0; i<line.length(); i++) {
            
            bool isNormal = true;   //флаг, который показывает, является ли текущий символ нормальным (однобайтовым)
            string curChar;         //буферная переменная текущего символа
            
            
            //Если попался пробел
            if (line[i]==' ') {
                curPosj+=SPACE;
                //Если дошли до конца строки на листе
                if (curPosj>=WIDTH-RIGHTMARGIN) {
                    curPosj=LEFTMARGIN;
                    curPosi+=LEADING+110; //110 - высота всех символов
                }
            }
            
            //Если попался двубайтный символ из нашей кодировки (всратые непонятные символы будут пропущены)
            if ((line[i]=="Ы"[0])||(line[i]=="ё"[0])||(line[i]=="—"[0])) {
                curChar=line.substr(i,2);
                //cout << curChar << endl;
                i++;
                isNormal = false;
                addToCanvas(&curPosi, &curPosj, curChar, encoding, canvas);
            }
            
            //Если попался нормальный символ
            if ((isNormal)&&(line[i]!=' ')) {
                curChar=line[i];
                //cout << curChar << endl;
                addToCanvas(&curPosi, &curPosj, curChar, encoding, canvas);
            }
            
            
            
        }//конец посимвольного цикла
        
        //в конце строки делаем enter
        curPosj=LEFTMARGIN;
        curPosi+=LEADING+110; //110 - высота всех символов
    
    }//конец цикла while

    
    /*
    
    cout << "Добавляем букву \"Ю\" в массив холста..." << endl;
    addToCanvas(&curPosi, &curPosj, "Ю", encoding, canvas);
    cout << "Буква добавлена в массив" << endl << endl;
    
    cout << "Добавляем букву \"Я\" в массив холста..." << endl;
    addToCanvas(&curPosi, &curPosj, "Я", encoding, canvas);
    cout << "Буква добавлена в массив" << endl << endl;
     
    */
    
    
    //Запись файла холста занимает около двух минут
    cout << "Записываем массив холста в .ppm файл холста..." << endl;
    canvasObj << "P3" << endl;
    canvasObj << WIDTH << " " << HEIGHT << endl;
    canvasObj << "255" << endl;
    for (int i=0; i<WIDTH*HEIGHT; i++) {
        canvasObj << canvas[i][0] << " " << canvas[i][1] << " " << canvas[i][2] << endl;
        int percentMarker = floor(WIDTH*HEIGHT*0.01);
        if (i%percentMarker==0) {
            cout << floor(i/percentMarker) << "%" << endl;
        }
    }
    
    
    
    
    
    
    


    cout << endl;
    fileObj1.close();
    fileObj2.close();
    canvasObj.close();
    return 0;
}
