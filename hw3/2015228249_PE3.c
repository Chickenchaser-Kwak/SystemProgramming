#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

ino_t get_inode(char*);
void printpathto(ino_t);
void inum_to_name(ino_t, char*, int );

int main()
{
	printpathto( get_inode( "." ) );
	putchar('\n');
	return 0;
}

void printpathto( ino_t this_inode )
{
	ino_t my_inode;
	char total_name[BUFSIZ] = {0};

	while( get_inode("..") != this_inode )
	{
		char tempBuf[BUFSIZ];
		char dir_name[BUFSIZ];

		chdir( ".." );
		inum_to_name( this_inode, dir_name, BUFSIZ );

		strncpy( tempBuf, total_name, BUFSIZ );
		strncpy( total_name, dir_name, BUFSIZ );
		strncat( total_name, tempBuf, BUFSIZ-strlen(dir_name) );

//		strncpy( its_name+strlen(parent_name) , its_name, strlen(its_name) );
//		strncpy( its_name, parent_name, strlen(parent_name) );

		this_inode = get_inode( "." );

	}
	printf("%s", total_name);
}

void inum_to_name(ino_t inode_to_find, char *namebuf, int buflen )	// get file name of inumber from current directory
{
	DIR* dir_ptr;
	struct dirent* direntp;
	dir_ptr = opendir( "." );
	if( dir_ptr == NULL )
	{
		perror( "." );
		exit(1);
	}

	while( (direntp = readdir( dir_ptr )) != NULL )
	{
		if( direntp->d_ino == inode_to_find )
		{
			strncpy(namebuf, "/", buflen );
			strncpy(namebuf+1, direntp->d_name, buflen-1 );
			namebuf[buflen-1] = "\0";
			closedir( dir_ptr );
			return;
		}
	}
	fprintf( stderr, "error looking for inum &d\n", inode_to_find );
	exit(1);
}

ino_t get_inode( char* fname )
{
	struct stat info;
	if( stat( fname, &info )==-1 )
	{
		fprintf( stderr, "Cannot stat " );
		perror( fname );
		exit(1);
	}
	return info.st_ino;
}
