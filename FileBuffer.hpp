#include <stdlib.h>
#include <stdio.h>
#include <vector>

class FileBuffer{
  
  public:
    FileBuffer(void); 

    void OpenFile(char *aPath);
    void CloseFile(void);

    UINT getSize(void);
    BYTE getByte( UINT aPosition );
     
  private:
    std::vector<BYTE>  Buffer;
    char              *FilePath;
};
