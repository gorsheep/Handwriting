//
//  main.cpp
//  Handwriting
//
//  Created by Даниил Волошин on 2/14/19.
//  Copyright © 2019 Даниил Волошин. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;


void readftest(int cWidth, int cHeight, int bufArray[cWidth*cHeight][3], ifstream &f){
    
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


//Function that fills the bufArray from the file of the char
void readf(int cWidth, int cHeight, int bufArray[cWidth*cHeight][3], ifstream &file){
    int r1,g1,b1,r2,g2,b2,r3,g3,b3,r4,g4,b4,r5,g5,b5,r6,g6,b6,r7,g7,b7,r8,g8,b8;
    
    
    int j=0;//j - счетчик пикселей в блоке (сколько пикселей я прочитал на данный момент)
    
    while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4 >> r5 >> g5 >> b5 >> r6 >> g6 >> b6 >> r7 >> g7 >> b7 >> r8 >> g8 >> b8) {
        
        bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
        bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
        bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
        bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
        bufArray[j+4][0]=r5; bufArray[j+4][1]=g5; bufArray[j+4][2]=b5;
        bufArray[j+5][0]=r6; bufArray[j+5][1]=g6; bufArray[j+5][2]=b6;
        bufArray[j+6][0]=r7; bufArray[j+6][1]=g7; bufArray[j+6][2]=b7;
        bufArray[j+7][0]=r8; bufArray[j+7][1]=g8; bufArray[j+7][2]=b8;
        
        j+=8;
        
        //m - число полных строк в блоке
        int m=floor(cWidth/8);
        
        if (j==m*8) {
            break;
        }
    }//end of while
    
    //n - число пикселей в неполной строчке
    int n=cWidth-floor(cWidth/8)*8;
    
    switch (n) {
        case 1:
            while (file >> r1 >> g1 >> b1) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                j+=1;
            }
            break;
            
        case 2:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                j+=2;
            }
            break;
            
        case 3:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
                j+=3;
            }
            break;
            
        case 4:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
                bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
                j+=4;
            }
            break;
            
        case 5:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4 >> r5 >> g5 >> b5) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
                bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
                bufArray[j+4][0]=r5; bufArray[j+4][1]=g5; bufArray[j+4][2]=b5;
                j+=5;
            }
            break;
            
        case 6:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4 >> r5 >> g5 >> b5 >> r6 >> g6 >> b6) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
                bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
                bufArray[j+4][0]=r5; bufArray[j+4][1]=g5; bufArray[j+4][2]=b5;
                bufArray[j+5][0]=r6; bufArray[j+5][1]=g6; bufArray[j+5][2]=b6;
                j+=6;
            }
            break;
            
        case 7:
            while (file >> r1 >> g1 >> b1 >> r2 >> g2 >> b2 >> r3 >> g3 >> b3 >> r4 >> g4 >> b4 >> r5 >> g5 >> b5 >> r6 >> g6 >> b6 >> r7 >> g7 >> b7) {
                bufArray[j][0]=r1; bufArray[j][1]=g1; bufArray[j][2]=b1;
                bufArray[j+1][0]=r2; bufArray[j+1][1]=g2; bufArray[j+1][2]=b2;
                bufArray[j+2][0]=r3; bufArray[j+2][1]=g3; bufArray[j+2][2]=b3;
                bufArray[j+3][0]=r4; bufArray[j+3][1]=g4; bufArray[j+3][2]=b4;
                bufArray[j+4][0]=r5; bufArray[j+4][1]=g5; bufArray[j+4][2]=b5;
                bufArray[j+5][0]=r6; bufArray[j+5][1]=g6; bufArray[j+5][2]=b6;
                bufArray[j+6][0]=r7; bufArray[j+6][1]=g7; bufArray[j+6][2]=b7;
                j+=7;
            }
            break;
            
        default:
            break;
    }//end of switch
        
    
    
    
    
    
    
    
    file.clear();                 // clear fail and eof bits
    file.seekg(0, std::ios::beg); // back to the start!
}





int main() {
    
    //Deal with files
    ifstream fileObj1;
    fileObj1.open("text.txt");
    ifstream fileObj2;
    fileObj2.open("myChars.txt");
    string line; //буферный string

    
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
    
    cout << endl;
    
    //Проверяем текст на некорректные символы (реализовать это как функцию?)
    bool included = false; //буферная переменная (для каждого символа)
    bool allIncluded = true; //общая переменная (для всех символов)
    
    for (int i=0; i<text.length(); i++) {
        for (int j=0; j<myChars.length(); j++) {
            if (text[i]==myChars[j]) {
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
    }else{
        cout << "В тексте есть некорректные символы" << endl;
    }
    
    
    //ТЕСТ ЧТЕНИЯ PPM
    int bufArray[92*122][3];
    ifstream fileObjTest;
    fileObjTest.open("32-1.txt");
    readftest(92, 122, bufArray, fileObjTest);
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
    
    
    
    


    cout << endl;
    return 0;
}
