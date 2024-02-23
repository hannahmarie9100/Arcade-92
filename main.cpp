//Hannah Ali - hma220003

#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstring>
#include <iomanip>
using namespace std;

const string database = "database.dat";  
//your filestream for the database will connect to this variable

void addRecord(string record, ofstream& file)
{
    
    string name, initials, highscore, plays, revenue;
    
    long unsigned int start = 0;
    long unsigned int end = record.find('"');
    
    start = end + 1; //skipping the 1
    end = record.find('"', start); //finding first comma
    
    name = record.substr(start, end-start); //printing name
    
    cout << "RECORD ADDED" << endl;
    cout << "Name: " << name << endl;
    
    start = end + 2; //skipping space
    end = record.find(' ', start); //second comma
    
    highscore = (record.substr(start, end-start));
    
    cout << "High Score: " << highscore << endl;
    
    int hs = stoi(highscore); //converting into int to print out without zeros
    
    start = end + 1;
    end = record.find(' ', start);
    
    initials = record.substr(start, end-start);
    
    cout << "Initials: " << initials << endl;
    
    start = end + 1;
    end = record.find(' ', start);
    
    plays = (record.substr(start, end-start));
    
    cout << "Plays: " << plays << endl;
    
    int p = stoi(plays); //convertins to get rid of zeros
    
    start = end + 2;
    end = record.find(' ', start);
    
    revenue = (record.substr(start, end-start));
    
    cout << "Revenue: $" << fixed << setprecision(2) << stod(revenue) << endl; 
    
    cout << endl;
    
    string dollars = revenue.substr(0, revenue.find('.')); //splitting to add zeros
    string change = revenue.substr(revenue.find('.')+1, revenue.length()-1); //splitting to add zeros
    
    int d = stoi(dollars);
    int c = stoi(change);
    
    revenue = dollars + "." + change;
    
    //printing out
    file << name << ", ";
    file << setw(9) << setfill('0') << right << hs << ", ";
    file << initials << ", ";
    file << setw(4) << setfill('0') << right << p << ", ";
    file << "$" << setw(4) << setfill('0') << d << "." << setw(2) << left << setfill('0') << c << endl;
    
    
}


void searchRecord(string name, fstream& file)
{
    string record;
    string foundname;
    // string fullName;
    name = name.substr(name.find(' ')+1);
    
    file.clear();
    file.seekg(0, ios::beg);
    
    while(getline(file, record))
    {
        
        string fullName = record.substr(0, record.find(','));
        
        long unsigned int found = record.find(name);
        
        if(found != string::npos)
        {
            cout << record.substr(0, record.find(',')) << " FOUND" << endl;
        
        long unsigned int start = 0;
        long unsigned int end = record.find(',', start);
        
       
        // cout << "Name: " << foundname.substr(start, end-start) << endl;
        
        start = end + 2;
        end = record.find(',', start);
        
        int h = stoi(record.substr(start, end-start));
        
        cout << "High Score: " << h << endl;
        
        start = end + 2;
        end = record.find(',', start);
        
        cout << "Initials: " << record.substr(start, end-start) << endl;
        
        start = end + 1;
        end = record.find(',', start);
        
        
        int p = stoi(record.substr(start, end-start));
        
        cout << "Plays: " << p << endl;
        
        
        start = end + 4;
        
        double d = stod(record.substr(start-1, record.length()));
        
        cout << "Revenue: $" << fixed << setprecision(2) <<  d << endl << endl;
    }else
    {
        // cout << name << " was not found." << endl;
    }
    
    }
    file.close();
    
    

}


void editRecord(string command, fstream& file)
{
    
    string name, fieldNum, value, record, compname;
    string hs, i, p, r;
    int highscore, plays;
    double revenue;
    
    long unsigned int start = 3; //starting after the first number, to just get name
    long unsigned int end = command.find('"', start);
    
    name = command.substr(start, end-start);
    
    start = end + 2;
    end = command.find(' ', start);
    
    fieldNum = command.substr(start, end-start);
    
    
    start = end+1;
    end = command.find('\n', start);
    
    value = command.substr(start, record.length()-1);
    
    // cout << name << " " << fieldNum << " " << value; // checking - correct
    
    long int pointer, lastpointer;
    
    lastpointer = 0;
    
     file.clear();
    file.seekg(0, ios::beg);
    
    while(getline(file, record))
    {
        compname = record.substr(0, record.find(','));
        
        if(name == compname) //if we have found the name
        {
            pointer = lastpointer;
            file.seekg(pointer);
            
            if(stoi(fieldNum) == 1) //highscore changed 
            {
                //same logic as addRecord
                file << name << ", ";
                
                start = 0;
                end = record.find(',', start);
                
                start = end+2;
                end = record.find(',', start);
                
                //inputting value instead of original highscore
                highscore = stoi(value);
                
                file << setw(9) << setfill('0') << highscore << ","; 
                
                start = end+1;
                end = record.find(',', start);
                
                i = record.substr(start, end-start);
                
                file << i << ",";
                
                start = end+1;
                end = record.find(',', start);
                
                p = record.substr(start, end-start);
                
                file << p << ",";
                
                plays = stoi(p);
                
                start = end+1;
                end = record.find('\n', start);
                
                r = record.substr(start, record.length()-1);
                
                revenue = stod(record.substr(start+2, record.length()-1));
                
                file << r;
                
            
                cout << name << " UPDATED" << endl;
                cout << "UPDATE TO high score - VALUE " << value << endl;
                cout << "Name: " << name << endl;
                cout << "High Score: " << value << endl;
                cout << "Initials:" << i << endl;
                cout << "Plays: " << plays << endl;
                cout << "Revenue: $" << fixed << setprecision(2) << revenue << endl << endl;
                
            }else if(stoi(fieldNum) == 2) //initials changed
            {
                //same logic as addrecord
                file << name << ", ";
                
                start = 0;
                end = record.find(',', start);
                
                start = end+2;
                end = record.find(',', start);
                
                hs = record.substr(start, end-start);
                highscore = stoi(hs);
                
                file << hs << ", "; 
                
                start = end+1;
                end = record.find(',', start);
                
                //inputting value instead of original initials
                i = value.substr(0, value.length());
                
                file << i << ",";
                
                start = end+1;
                end = record.find(',', start);
                
                p = record.substr(start, end-start);
                
                file << p << ",";
                
                plays = stoi(p);
                
                start = end+1;
                end = record.find('\n', start);
                
                r = record.substr(start, record.length()-1);
                
                revenue = stod(record.substr(start+2, record.length()-1));
                
                file << r; 
                
                
                cout << name << " UPDATED" << endl;
                cout << "UPDATE TO initials - VALUE " << value << endl;
                cout << "Name: " << name << endl;
                cout << "High Score: " << highscore << endl;
                cout << "Initials: " << i << endl;
                cout << "Plays: " << plays << endl;
                cout << "Revenue: $" << revenue << endl << endl;
                
            }else if(stoi(fieldNum) == 3) //plays changed
            {
                //same logic as addRecord
                 file << name << ", ";
                
                start = 0;
                end = record.find(',', start);
                
                start = end+2;
                end = record.find(',', start);
                
                hs = record.substr(start, end-start);
                highscore = stoi(hs);
                
                file << hs << ","; 
                
                start = end+1;
                end = record.find(',', start);
                
                i = record.substr(start, end-start);
                
                file << i << ", ";
                
                start = end+1;
                end = record.find(',', start);
                
                //inputting value instead of original plays
                plays = stoi(value);
                
                file << fixed << setw(4) << setfill('0') << plays << ",";
                
                start = end+1;
                end = record.find('\n', start);
                
                revenue = stod(value)*.25;
                
                file << " $" << setprecision(2) << setw(7) << setfill('0') << revenue; 
                
                
                cout << name << " UPDATED" << endl;
                cout << "UPDATE TO plays - VALUE " << value << endl;
                cout << "Name: " << name << endl;
                cout << "High Score: " << highscore << endl;
                cout << "Initials:" << i << endl;
                cout << "Plays: " << plays << endl;
                cout << "Revenue: $" << revenue << endl << endl;
            }
        }
        
        lastpointer = file.tellg(); //holding place of last pointer 
    }
    
}

void deleteRecord(string record, fstream& file)
{
    ofstream outputFile("temp.txt", ios::out);
    
    file.clear();
    file.seekg(0, ios::beg); //resetting pointer
    
    record = record.substr(2, record.length()-1);
    
    bool found = false;
    
    string cur;
    string deletedRecord;
    
    string name;
    string NameToDelete = record.substr(0, record.length());
    
    
    while(getline(file, cur))
    {
        
        name = cur.substr(0, cur.find(','));
        
        if(name != NameToDelete) //if this isnt the name we need
        {
            outputFile << cur << endl; //print out to file
        }else //if found
        {
            deletedRecord = cur; //this is the deleted record, hold to print out later
            
            found = true;
        }
        
    }
    
    if(found)
    {
        file.close();
    
        remove(database.c_str()); //deleting old file
        
        rename("temp.txt", database.c_str()); //renaming file to database.dat
        
        //same logic as addRecord
        cout << "RECORD DELETED" << endl;
        
        long unsigned int start = 0;
        long unsigned int end = deletedRecord.find(',');
            
        cout << "Name: " << deletedRecord.substr(start, end-start) << endl;
        
        start = end + 2;
        end = deletedRecord.find(',', start);
        
        cout << "High Score: " << stoi(deletedRecord.substr(start, end-start)) << endl;
        
        start = end + 2;
        end = deletedRecord.find(',', start);
        
        cout << "Initials: " << deletedRecord.substr(start, end-start) << endl;
        
        start = end + 2;
        end = deletedRecord.find(',', start);
        
        cout << "Plays: " << stoi(deletedRecord.substr(start, end-start)) << endl;
        
        start = end+3;
        
        cout << "Revenue: $" << stod(deletedRecord.substr(start)) << endl << endl;
    }else
    {
        cout << "Record given could not be deleted." << endl << endl;
        file.close();
        
        //still need to rename temp file and remove old file
    
        remove(database.c_str());
    
        rename("temp.txt", database.c_str());
    }
    
    
}

bool Validate(string line)
{
    int digit = line.at(0);
    int counter = 0;
    long unsigned int start = 0;
    long unsigned int end = 0;
    
    if(line.at(1) == ' ')
    {
    
        if(digit == '1') //we are at add
        {
            
            if(line.at(2) == '"') //checking for first quote
            {
                if(line.find('"', 2) > 0) //checking for second quote
                {
                    for(long unsigned int i = line.find('"', 3); i < line.length()-1; i++)
                    {
                        if(line.at(i) == ' ')
                        {
                            counter++;
                        }
                    }
                    
                    if(counter == 4) //four spaces
                    {
                        start = line.find('"', 3)+2; //starting after Name
                        end = line.find(' ', start); //finding after highscore
                        if((line.substr(start, end-start)).length() < 10)
                        {
                            for(long unsigned int i = start; i < end; i++)
                            {
                                if(isdigit(line.at(i)))
                                {
                                    //they are digits
                                }else
                                {
                                    return false; //there is one thats not a digit
                                }
                            }
                        }else
                        {
                            return false;
                        }
                        
                        //found only digits, keep going
                        
                        start = end+1;
                        end = line.find(' ', start);
                        
                        if(end-start < 4)
                        {
                            for(long unsigned int i = start; i < end; i++)
                            {
                                if(isspace(line.at(i)))
                                {
                                    return false; //found space, stop
                                }else
                                {
                                    //no space
                                }
                            }
                        }else
                            return false;
                        
                        //found no space, keep going
                        
                        start = end+1;
                        end = line.find(' ', start);
                        
                        if(end-start < 5)
                        {
                            for(long unsigned int i = start; i < end; i++)
                            {
                                if(isdigit(line.at(i)))
                                {
                                    //is a digit
                                }else
                                {
                                    return false;
                                }
                            }
                        }else
                            return false;
                        
                        //found all digits, keep going
                        
                        start = end + 1;
                        end = line.find('.', start)-1; //just going to decimal
                        
                        
                        if(end-start < 5)
                        {
                            if(line.at(start) == '$')
                            {
                                if(line.at(end+1) == '.')
                                {
                                    start = end+2;
                                    end = line.length();
                                    
                                    if(end-start == 2)
                                    {
                                        return true;
                                    }
                                }
                            }else
                                return false;
                        }
                    
                        
                        
                    }else
                    {
                        return false;
                    }
                }
            }
            
        }else if(digit == '2') //search function
        {
            return true;
        }else if(digit == '3') //edit function
        {
            if(line.at(2) == '"') //checking for first quote
            {
                if(line.find('"', 2) > 0) //checking for second quote
                {
                    for(long unsigned int i = line.find('"', 3); i < line.length()-1; i++)
                    {
                        if(line.at(i) == ' ')
                        {
                            counter++;
                        }
                    }
                    
                    if(counter == 2)
                    {
                        start = line.find('"', 5)+2;
                        end = line.find(' ', start);
                        
                        string choice = line.substr(start, end-start);
                        
                        
                        if(choice == "1")
                        {
                            start = end+1;
                            end = line.length()-1;
                            
                            if(end-start < 10)
                            {
                                for(long unsigned int i = start; i < end; i++)
                                {
                                    if(isdigit(line.at(i)))
                                    {
                                        
                                    }else
                                    {
                                        return false;
                                    }
                                }
                                
                                return true;
                            }
                            
                        }else if(choice == "2")
                        {
                            start = line.find('"', 5)+2;
                            end = line.find(' ', start);
                            
                        
                                start = end+1;
                                end = line.length();
                                
                                if((line.substr(start, end-start)).length() < 4)
                                {
                                    for(long unsigned int i = start; i < end; i++)
                                    {
                                        if(isspace(line.at(i)))
                                        {
                                            return false;
                                        }else
                                        {
                                            
                                        }
                                    }
                                }else
                                    return false;
                                
                                return true;
                            
                        }else if(choice == "3")
                        {
                            start = end+1;
                            end = line.length();
                            
                            if((line.substr(start, end-start)).length() < 5)
                            {
                                for(long unsigned int i = start; i < end; i++)
                                {
                                    if(isdigit(line.at(i)))
                                    {
                                        
                                    }else
                                    {
                                        return false;
                                    }
                                }
                                
                                return true;
                            }else
                                return false;
                            
                        }else
                        {
                            return false;
                        }
                        
                        
                    }
                    
                }
            }
           
        
        }else if(digit == '4') //delete function
        {
            return true;
        }
    }
        
    
    return false;
    
}


int main(){
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */
   string temp;  //variable for database filename
   string batch; //variable for batch filename

   cout << "Enter Database Name: ";
   cin >> temp;

   ifstream infile(temp, ios::binary);
   ofstream outfile(database, ios::binary);
   string line;
   
   if (infile)
        while (infile.good())
        {
            getline(infile, line);
            if (line != "")
                outfile << line << "\n";
        }

   infile.close();
   outfile.close();
/* ################  DO NOT MODIFY CODE IN THIS BLOCK ###################### */

   //add your code for main here
   
   cout << "Enter Batch Name: ";
   cin >> batch;
   
   infile.open(batch); //opening files back up to be able to manipulate
   outfile.open(database, ios::binary | ios::app);
   fstream file(database);
   
 
   string record;
   
   if(outfile)
   {
       if(infile) //opened successfully
       {
           while(getline(infile, record))
           {
              if(Validate(record)) //checking to see if correct
              {
                  if(record.at(0) == '1')
                  {
                      addRecord(record, outfile);
                  }else if(record.at(0) == '2')
                  {
                      file.open(database, ios::in | ios::app);
                          searchRecord(record, file);
                          file.close();
                  }else if(record.at(0) == '3')
                  {
                      file.open(database, ios::in | ios::out); //do not want to append, want to overwrite
                      
                          editRecord(record, file);
                          file.close();
                  }else if(record.at(0) == '4')
                  {
                      file.open(database, ios::in | ios::out);
                      
                          deleteRecord(record, file);
                          file.close();
                  }
              }else
              {
                  cout << endl << record << " is INVALID" << endl << endl; //line was incorrect
              }
           
               
           }
       }
   }

}

