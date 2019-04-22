/* strtok example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char str[] ="- This, a sample string.";
  char * pch;
  printf ("Splitting string \"%s\" into tokens:\n",str);
  pch = strtok (str," ,.-");
  while (pch != NULL)
  {
    printf ("%s\n",pch);
    pch = strtok (NULL, " ,.-");
  }
  return 0;
} 

//Este mejor
#include <iostream>
#include <string>

int main ()
{
    std::string s = "scott tiger mushroom";
    std::string delimiter = " "; //Indicamos que separe por espacios en blanco. 

    size_t pos = 0;
    std::string token;
    
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        std::cout << token << std::endl;
        s.erase(0, pos + delimiter.length());
    }
    
    std::cout << s << std::endl;
}
