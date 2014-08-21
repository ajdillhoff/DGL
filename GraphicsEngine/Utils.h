#pragma  once 

inline void memcpyquad(void *dest,const void * src,int nums=4)
{
	_asm
	{
		cld
			mov esi,src
			mov edi,dest
			mov ecx,nums
			rep movsd
	}
}

inline void memzeroquad(void *dest,int nums)
{
	_asm
	{
		    cld
			mov edi,dest 
			mov ecx,nums
			mov eax,0
			rep stosd
	}
}