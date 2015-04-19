// Cheng, Allan
// 996078337

#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>

void findIP(string, char*);
bool searchNext(string, string, int);

int main(int argc, char *argv[])
{
  string input;
  ifstream IPfile;

  IPfile.open(argv[2]);
  while (true)
  {
    IPfile >> input;
    if (IPfile.eof())
      break;
    findIP(input, argv[1]);
  }

  IPfile.close();
}

void findIP(string find, char *file)
{
  string IP, AS, IP2, AS2;
  int bit, byte, divide, remainder, count, count2, num, num2, i;
  bool match = false, test;
  ifstream DB;

  DB.open(file);

  while(!DB.eof())
  {
    DB >> IP >> byte >> AS;
    count = 0; num = 0;
    while(find[count] != IP[count] && !DB.eof()) //until first number of IP match
      DB >> IP >> byte >> AS;
    count++; 
    while (find[count] == IP[count] && find[count] != '.')
      count++;

    if (find[count] != IP[count]) //until first 8 bytes matches since all prefix >8
      continue;

  
    divide = (byte/8) - 1; //attempt to find largest prefix match
    remainder = byte % 8;
    count++;
    count2 = count;

    while(match == false) //after first 8 bytes match
    {
      if (divide == 0 && remainder == 0) //everything is matched
      {
        match = true;
        DB >> IP2 >> bit >> AS2;
        while( IP2[count-2] == find[count-2])
        {
          if (searchNext(find, IP2, bit) == true)
          {
            IP = IP2;
            byte = bit;
            AS2 = AS;
          }
            DB >> IP2 >> bit >> AS2;
        }
        cout << IP << "/" << byte << " " << AS << " " << find << endl;
        return;
      }
      else if (divide == 0) //remainder != 0
      {
        num = 0;
        while (find[count2] != '.' && count2 < find.length()) //convert 2nd 8bits of input to num
        {
          num *= 10;
          num = num + (find[count2] - 48);
          count2++;
        }

        count2 = count;
        num2 = 0;
        test = false;

        while(test == false)
        {
          count2 = count;
          while (IP[count2] != '.' && count2 < IP.length()) //convert into int
          {
            num2 *= 10;
            num2 = num2 + (IP[count2] - 48);
            count2++;
          }  

          unsigned int comp1, comp2, prefix;
          prefix = 8 - remainder;
          comp1 = num >> prefix;
          comp2 = num2 >> prefix;

          if (comp1 == comp2)
          {
            match = true;
            test = true;

            DB >> IP2 >> bit >> AS2;
            while( IP2[count-2] == find[count-2] && !DB.eof())
            {
              if( searchNext(find, IP2, bit) == true)
              {
                IP = IP2;
                byte = bit;
                AS2 = AS;
              }

              DB >> IP2 >> bit >> AS2;
            }
            cout << IP << "/" << byte << " " << AS << " " << find << endl;
            return;
          }
          else
          {
            DB >> IP >> byte >> AS;

            divide = (byte/8) - 1;
            remainder = byte % 8;
            count2 = count;
            break;
          }  
        }
      } //else if
      else //divide > 1 - so match next 8 bits
      {
        while (divide != 0)
        {
          while (find[count2] == IP[count2] && find[count2] != '.' && count2 < (find.length()-1))
            count2++;
          if(find[count2] != IP[count2]) //doesn't match
          {
            if (DB.eof())
              break;
            DB >> IP >> byte >> AS;
            divide = (byte/8) - 1; //attempt to find largest prefix match
            remainder = byte % 8;
            count2 = count;
            break;
          }
          else //matched 2nd set of 8 bits
          {
            divide--;
            count2++;
          }
        }
      } //else
    }

//exit(0);
  }

  DB.close();
}

bool searchNext(string input, string IP, int bit)
{
  int i = 0, temp, prefix, remain, num = 0, num2 = 0;
  unsigned int convert, after, after2;

  while (input[i] == IP[i] && input[i] != '.')
    i++;

  if (input[i] != IP[i])
    return false;

  prefix = (bit / 8) - 1;
  remain = bit % 8;
  i++;

  while (prefix != 0)
  {
    while (input[i] == IP[i] && input[i] != '.' && (i < input.length()))
      i++;

    if(input[i] != IP[i])
      return false;
    else
      prefix--;

    i++;
  }

  if (remain != 0)
  { 
    temp = i;
    while (input[i] != '.') //convert 2nd 8 byte into int
    {
      num *= 10;
      num = num + (input[i] - 48);
      i++;
    }  
    i = temp;
    while (IP[i] != '.')
    {
      num2 *= 10;
      num2 = num2 + (IP[i] - 48);
      i++;
    }

    convert = 8 - remain;
    after = num >> convert;
    after2 = num2 >> convert;

    if (after != after2)
      return false;

    return true;
  }
}
