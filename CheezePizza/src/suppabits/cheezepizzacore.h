#ifndef CheezePizzaCore_H_
#define CheezePizzaCore_H_

#define SAFE_DELETE(ptr) { if(ptr) { delete ptr; ptr = NULL; } }

#define SAFE_DELETE_ARRAY(arr) { if(arr) { delete[] arr; arr = NULL;} }

#define SAFE_SHUTDOWN(ptr) { if(ptr) { ptr->Shutdown(); ptr = NULL;} }

#define SAFE_DELETE_STL_VECTOR(stl_vector) \
{ \
	for(unsigned int _STLVectorIndex = 0; _STLVectorIndex < stl_vector.size(); ++_STLVectorIndex) \
	{ \
		delete stl_vector[_STLVectorIndex]; \
	} \
	stl_vector.~vector(); \
}

char* ChzStrDuplicate(const char* SrcString);
char* ChzStrLower(const char* SrcString);

#endif