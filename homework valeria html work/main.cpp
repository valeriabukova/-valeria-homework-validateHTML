//
//  main.cpp
//  homework valeria html work
//
//  Created by Valeria  Bukova on 08.12.2024.
//

#include <iostream>

using namespace std;


const char* findChar(const char* str, char c) {
    while (*str) {
        if (*str == c) return str;
        str++;
    }
    return nullptr;
}


void copySubstring(char* dest, const char* src, int length) {
    for (int i = 0; i < length; i++) {
        dest[i] = src[i];
    }
    dest[length] = '\0';
}

bool compareStrings(const char* str1, const char* str2) {
    while (*str1 && *str2) {
        if (*str1 != *str2) return false;
        str1++;
        str2++;
    }
    return *str1 == '\0' && *str2 == '\0';
}


bool validateHTML(const char* htmlContent) {
    const int MAX_TAGS = 100;
    const char* tags[MAX_TAGS];
    int top = -1;

    const char* pos = htmlContent;

    while ((pos = findChar(pos, '<')) != nullptr) {
       
        const char* endTag = findChar(pos, '>');
        if (!endTag) {
            cout << "Помилка: не знайдено закриваючий символ '>'." << endl;
            return false;
        }

        // Витягуємо тег
        int tagLength = endTag - pos - 1;
        if (tagLength <= 0) {
            cout << "Помилка: порожній тег." << endl;
            return false;
        }

        char tag[101];
        copySubstring(tag, pos + 1, tagLength);

        pos = endTag + 1;

       
        if (tag[0] == '/') {
            
            const char* closingTag = tag + 1;

            if (top == -1) {
                cout << "Помилка: закриваючий тег </" << closingTag << "> не має пари." << endl;
                return false;
            }

            if (!compareStrings(tags[top], closingTag)) {
                cout << "Помилка: тег </" << closingTag << "> не відповідає відкритому тегу <" << tags[top] << ">." << endl;
                return false;
            }

            top--;
        } else {
            
            if (top == MAX_TAGS - 1) {
                cout << "Помилка: занадто багато вкладених тегів." << endl;
                return false;
            }

            tags[++top] = tag;
        }
    }

    
    if (top != -1) {
        cout << "Помилка: залишилися незакриті теги. Наприклад: <" << tags[top] << ">." << endl;
        return false;
    }

    cout << "HTML-файл валідний." << endl;
    return true;
}

int main() {
    
    cout << "Введіть HTML-код (одним рядком): ";
    char htmlContent[1000];
    cin.getline(htmlContent, 1000);

   
    validateHTML(htmlContent);

    return 0;
}
