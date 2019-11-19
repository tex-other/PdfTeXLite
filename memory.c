#include "texmfmp.h"
// void*  dlmalloc(size_t);
// void*  dlrealloc(void*, size_t);
// void   dlfree(void*);
// void dlreset();
void *xmalloc(size_t newsize)
{
	void *ptr = malloc(newsize);
	if(!ptr)
	{
		fprintf(stderr, "Malloc Failed");
		abort();
	}
	memset(ptr, 0, newsize);
	return ptr;
}

void* xrealloc(void* oriptr, size_t newsize)
{
	void *ptr = realloc(oriptr, newsize);
	if(!ptr)
	{
		fprintf(stderr, "Realloc Failed");
		abort();
	}
	return ptr;
}

void xfree(void *oriptr)
{
	free(oriptr);
}


string
xstrdup (const_string s)
{
  string new_string = (string)xmalloc(strlen (s) + 1);
  return strcpy(new_string, s);
}

