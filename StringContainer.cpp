#include <iostream>
#include "functions.h"


using namespace std;


int main() {
    string container;
    int totalWordCounter=0;
    string wordsInText[1000];
    string fileName = "container.txt";
    makeAllCharsLowercase();

    fillContainer(container, fileName);

    findUrls();

    string temp = container;

    collectStringArray(wordsInText, totalWordCounter, fileName);

    createWordTable(wordsInText, totalWordCounter, temp);


    return 0;
}

