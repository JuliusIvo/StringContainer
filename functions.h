#pragma once
#include <fstream>
#include <string>
#include <iterator>
#include <algorithm>
#include <iomanip>
#include <iostream>

using namespace std;

#include <regex>
using namespace std;

bool isValidURL(string url)
{
  const regex pattern("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)");

  if (url.empty()){
     return false;
  }

  if(regex_match(url, pattern)){
    return true;
  }
  else{
    return false;
  }
}

void findUrls(){
    cout << "naudojamas textinis failas: text1.txt" << endl;
    ifstream fd("text1.txt");
    string urlContainer;
    while(!fd.eof()){
        fd >> urlContainer;
        if(isValidURL(urlContainer)){
            cout << "texte rastas url: " << urlContainer << endl;
        }
    }
    fd.close();
}

void fillContainer(string &container, string fileName) {
	ifstream fd(fileName);

	getline(fd, container, '\0');

	fd.close();
}

bool wordWasFound(string container, string word) {
	size_t found = container.find(word);
	if (found!=string::npos) {
		return true;
	}
	else {
		return false;
	}
}

void SkipBOM(ifstream &in)
{
    char test[3] = {0};
    in.read(test, 3);
    if ((unsigned char)test[0] == 0xEF &&
        (unsigned char)test[1] == 0xBB &&
        (unsigned char)test[2] == 0xBF)
    {
        return;
    }
    in.seekg(0);
}

void makeAllCharsLowercase(){
    ifstream fd("Text.txt");
    int ascii;
    string tempo[sizeof(fd)];
    char temp[sizeof(fd)];
    int i=0;
    while(!fd.eof()){
    fd >> temp;
    tempo[i]=temp;
        for (int j=0; j<tempo[i].length(); j++){
            if(temp[j]>='A' && temp[j]<='Z'){
                ascii = temp[j];
                ascii = ascii+32;
                temp[j]=ascii;
            }
        }
        tempo[i] = temp;
        i++;
    }

    fd.close();
    ofstream fr("container.txt");
    for (int i=0; i<sizeof(fd); i++){
        fr << tempo[i] << " ";
    }
    fr.close();
}

void collectStringArray(string wordsInText[], int &totalWordCounter, string fileName){
    ifstream fd(fileName);
    SkipBOM(fd);
    char temp[sizeof(fd)];
    int i=0;
    while(!fd.eof()){
        fd >> temp;
        wordsInText[i]=temp;
        for(int j=0; j<wordsInText[i].length(); j++){
            if (temp[j] < 48 && temp[j] <57){
               char delete_char=temp[j];
                wordsInText[i].erase(remove(wordsInText[i].begin(), wordsInText[i].end(), delete_char) ,   wordsInText[i].end());

            }
        }
        i++;
    }
    totalWordCounter=i;
    fd.close();
}

int countFoundWords(string &temp, string word) {

	int counter = 0;
	if(wordWasFound(temp, word)){
            size_t found = temp.find(word);
	while(wordWasFound(temp, word)) {
		found = temp.find(word, found + counter);
		if (found != string::npos) {
			counter++;
            }
        if(found<temp.length()){
            temp.erase(found, word.length());
            }
        }
	}
    else {return counter=0;}
	return counter;
}

void printContainer(string container){
    ofstream fr("container.txt");
    fr << container;
    fr.close();
    cout << "container was printed to container.txt" << endl;
}

void createWordTable(string wordsInText[], int totalWordCounter, string temp){
    ofstream fr("dataTable.txt");
    int counter=0;
    fr << "------------------------------------------------" << endl;
    fr << setw(2) << left << "word" << setw(35) << right << "times" << endl;
    fr << "------------------------------------------------" << endl;
    for (int i=0; i<totalWordCounter; i++){
        if(wordsInText[i]=="a"){
            i++;
        }
        counter = countFoundWords(temp, wordsInText[i]);
        if(counter==0){
            i++;
        }
        else {
            fr << setw(5) << left << wordsInText[i] << setw(35) << right << counter  << endl;
            fr << "------------------------------------------------" << endl;
        }
    }
    fr.close();

    cout << "cross reference table was created." << endl;
}
