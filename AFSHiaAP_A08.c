#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>


static const char *dirpath = "/home/reyhanzo/shift4";
char ciph[] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
char enpath[1000], depath[1000];
int key = 17;

void encrypt(char change[])
{
	char b ; int i;
	for(i=0; i<strlen(change);i++){
		b = change[i];
		if(b != '/' ){
			int j =0;
			while(1){
			if(b == ciph[j]){
				change[i] = ciph[(j+17)%strlen(ciph)];
				break;
			}
			else
			j++;
		}
	}
	}
}

void decrypt(char change [])
{
	char b; int i;
	for(i=0; i<strlen(change);i++){
		b = change[i];
		if(b != '/' ){
			int j =0;
			while(1){
			if(b == ciph[j]){
				change[i] = ciph[(j-key)%strlen(ciph)];
				break;
			}
			else
			j++;
		}
	}
	}
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
  int res;
	char fpath[1000];
   
	
	strcpy(enpath,path);
	if(strcmp(enpath, ".") != 0 && strcmp(enpath, "..") != 0)encrypt(enpath);

	sprintf(fpath,"%s%s",dirpath,enpath);
	res = lstat(fpath, stbuf);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
			strcpy(enpath,path);
	if(strcmp(enpath, ".") != 0 && strcmp(enpath, "..") != 0)encrypt(enpath);
	sprintf(fpath,"%s%s",dirpath,enpath);
	}
	
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		
		//show
		char show[2000]
		snprintf(show, 2000, "%s/%s", fpath, de->d_name);

		//de->d_name
		stat(show, &st);

		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
       
		strcpy(depath, de->d_name);

		if(strcmp(depath, ".") !=0 && strcmp(depath, "..") != 0)
		{
			  struct passwd *pwd = getpwuid(st.st_uid);
				struct group *grp = getgrgid(st.st_gid);


				print("%s %s %s\n", depath, pwd->pw_name, grp->gr_name);
				if(pwd != NULL && grp != NULL)
				{
					if((strcmp(pwd->pw_name, "chipset") == 0 || strcmp(pwd->pw_name, "ic_controller") ==0 ) && strcmp(grp->gr_name, "rusak") == 0)
					{

					}

					else
					{
						decrypt(depath);
						res = (filler(buf, de->d_name, &st, 0));
						if(res!=0) break;
					}
					
				}
		}

		
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
		    struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else
	{
		strcpy(enpath,path);
		if(strcmp(enpath, ".") != 0 && strcmp(enpath, "..") != 0)encrypt(enpath);
		sprintf(fpath,"%s%s",dirpath,enpath);
	}
	
	int res = 0;
    	int fd = 0 ;
  
	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
