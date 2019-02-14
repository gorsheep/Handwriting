//
//  main.cpp
//  Handwriting
//
//  Created by Даниил Волошин on 2/14/19.
//  Copyright © 2019 Даниил Волошин. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;





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
    
    cout << text << endl;
    cout << myChars << endl;
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


    cout << endl;
    return 0;
}
