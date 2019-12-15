#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[] )
{
	int nResult = mkdir( argv[1],0755 );
	if( nResult == 0 )
	{
		printf( "폴더 생성 성공" );
	}
	else if( nResult == -1 )
	{
		perror( "폴더 생성 실패 - 폴더가 이미 있거나 부정확함\n" );
	}
	return 0;
}
