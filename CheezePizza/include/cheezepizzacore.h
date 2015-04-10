#ifndef CheezePizzaCore_H_
#define CheezePizzaCore_H_

#define SAFE_DELETE(ptr) { if(ptr) { delete ptr; ptr = NULL; } }
#define SAFE_DELETE_ARRAY(arr) { if(arr) { delete[] arr; arr = NULL;} }
#define SAFE_SHUTDOWN(ptr) { if(ptr) { ptr->Shutdown(); delete ptr; ptr = NULL;} }

char* ChzStrDuplicate(const char* SrcString);
char* ChzStrLower(const char* SrcString);

#endif