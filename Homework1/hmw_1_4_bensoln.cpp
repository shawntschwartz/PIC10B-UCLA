// SubTasks for hmw_1_4
  // 1) Get lines from user
    // a) Prompt user repeatedly to request a line
    // b) Alert user if line cannot fit into buffer
  // 2) Insert line into buffer
    // a) Keep track of next available space in the buffer -> (step 3)
    // b) Keep track of room available in the buffer, if not -> (step 1.b)
    // c) Insert NULL bytes at the end of each line
  // 3) Set ptrs to the beginning of each line
  // 4) Print the lines in reverse at the end of the program
    // a) cout operator is overloaded for directly printing the char*

#include <iostream>
#include <string>

std::string GetLineFromUser()
{
  std::string line;
  std::cout << "Enter a line: ";
  getline(std::cin, line);
  return line;
}

// Assume caller has ensured the string "toInsert" can fit into the buffer
// with a null byte at the end
void InsertIntoBuffer(char *start, std::string toInsert)
{
  for (int i = 0; i < toInsert.size(); i++)
  {
    start[i] = toInsert[i];
  }
  start[toInsert.size()] = '\0';
}

void AlertUserBufferIsFull()
{
  std::cout << "Buffer is full! Stop." << std::endl;
}

int main()
{
  // Testing string input
    //std::string input = GetLineFromUser();
    // std::cout << input << std::endl;

  char buffer[1000];
  char* lines[100];
  char* nextSpace = buffer;
  int roomAvailable = 1000;
  int linesRead = 0;
  std::string cont;

  // Testing getting input lines from char buffer
  do {
    std::string line = GetLineFromUser();
    // std::cout << line << std::endl;
    std::cout << std::endl;

    if (line.size() + 1 > roomAvailable)
    {
      AlertUserBufferIsFull();
      break;
    }

    InsertIntoBuffer(nextSpace, line);
    lines[linesRead] = nextSpace; // next line pointer in the array is where we started at
    nextSpace += line.size() + 1; // +1 for the null byte '/0'
    roomAvailable -= line.size() + 1; // +1 for the null byte '/0'
    linesRead++;

    std::cout << "Continue (y/n)? ";
    std::cin >> cont;
    std::cin.ignore();
    std::cout << std::endl;
  } while (cont == "y");

  if (linesRead == 100 && cont == "y")
  {
    AlertUserBufferIsFull();
  }

  // Print Lines in Reverse Order
  for (int i = linesRead -1; i >= 0; i--)
  {
    std::cout << lines[i] << std::endl;
  }


  /*
  std::string line = GetLineFromUser();
  InsertIntoBuffer(buffer, line);
  std::cout << buffer << std::endl;
  */
  return 0;
}
