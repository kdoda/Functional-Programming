/***********************************************************************
* Program:
*    Project 10, MAD LIB PROGRAM
*    Professor Christensen, CS124
* Author:
*    Klevin Doda
* Summary: 
*    This program reads the file, which its name is given by the user
*    and asks user to give input according to what is in the file
*    with this syntax <name>. Those words are replaced and stored in a 
*    2 D array with the other regular words. Displays the 2 D array
*    and keeps prompting user if he wants to play again.
*
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

void getFileName(char fileName[]);
void askQuestion(char word[]); 
int readFile(char fileName[], char words[][32]); 
bool isPunct(char a);
void displayFile(char words[][32], int numWords);

/*****************************************************
 * Invokes getFileName by passing the fileName array
 * and reads the file given by user. Checks if an 
 * error occurred to display an error message.
 *****************************************************/
int main()
{
   char fileName[25];
   char words[256][32];
   int numWords;
   char playAgain;

   do
   {
      getFileName(fileName);
      cin.ignore();
      //cin.ignore() is required here to ignore the new line
      //when cin.getline() is invoked in askQestion function

      if ((numWords = readFile(fileName, words)) == -1) 
         cout << "Error reading file!" << endl;
      else
         displayFile(words, numWords);

      cout << endl << "Do you want to play again (y/n)? ";
      cin >> playAgain;
   } while (playAgain == 'y');
   
      
   cout << "Thank you for playing." << endl;

   return 0;
}

/*****************************************************
 * Prompts user for the file name and stores it in 
 * the array which is passed by reference.
 *****************************************************/
void getFileName(char fileName[])
{
   cout << "Please enter the filename of the Mad Lib: ";
   cin >> fileName;
}

/*****************************************************
 * Receives file name and a 2 D array to store the 
 * words in file. Reads the word in file and returns
 * the number of words.
 *****************************************************/
int readFile(char fileName[], char words[][32])
{
   ifstream fin(fileName);
   if (fin.fail())
      return -1;

   int count = 0;
   while (fin >> words[count])
   {
      //passing the word that needs to be replaced
      if (words[count][0] == '<' && isalpha(words[count][1]))
         askQuestion(words[count]);
      
      ++count;
   }
   //count is one greater, exactly the size
   return count; 
}

/*****************************************************
 * Receives the word that should be replaced.
 * Prompts the user in the appropriate output and 
 * replaces the word with what user provided as input.
 *****************************************************/
void askQuestion(char word[])
{
   //word[0] is < , to upper returns the ASCII code 
   // thus we need to typecast
   cout << "\t" << (char)toupper(word[1]);
   
   for (int i = 2; word[i] != '>' ; ++i)
   {
      if (word[i] == '_')
         cout << " ";
      else
         cout << word[i];
   }

   cout << ": ";
   cin.getline(word, 32);
   //replaces the word, since it is passed by reference
}

/*****************************************************
 * Receives a char and returns true if it is a 
 * punctuation.
 *****************************************************/
bool isPunct(char a)
{
   return (a == ',' || a == '.' || a == '!' || a == '?');
}

/*****************************************************
 * Receives the 2 D array and displays it. Checks for 
 * cases of punctuation, new line and quotes in order 
 * to print or not spaces.
 *****************************************************/
void displayFile(char words[][32], int numWords)
{
   cout << endl;
   bool before = false;
   bool after = false;

   for (int i = 0;i < numWords;++i)
   {
      before = after;
      after = true;
      if (words[i][0] == '<')
      {
         switch (words[i][1])
         {
            case '{': 
               after = false; //before is true 
               words[i][0] = '"';
               words[i][1] = '\0';
               break;
            case '}':
               before = false; //after is true
               words[i][0] = '"';
               words[i][1] = '\0';
               break;
            case '[':
               after = false; // before is true
               words[i][0] = '\'';
               words[i][1] = '\0';
               break;
            case ']':
               before = false; // after is true
               words[i][0] = '\'';
               words[i][1] = '\0';
               break;
            case '#':
               before = false;
               after = false;
               words[i][0] = '\n';
               words[i][1] = '\0';
               break;
         }
         
      }
      else if (isPunct(words[i][0]))
         before = false; // after is true
      
      if (before)
         cout << " ";

      cout << words[i];
   }
}
