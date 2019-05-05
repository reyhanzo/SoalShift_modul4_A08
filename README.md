# SoalShift_modul4_A08
TUGAS SOAL SHIFT SISTEM OPERASI kelompok A08

## Soal 1

```
void enkripsi(char* kata)
{
    char dasar[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    for(int i=0; i<strlen(kata); i++){
        for(int j = 0 ; j<strlen(dasar); j++){
            if(kata[i] == dasar[j]){
                int indeks_baru = (j+17) % 94;
                kata[i] = dasar[indeks_baru];
                break;
            }
        }
    }
}

void dekripsi(char* kata)
{
    char dasar[100] = "qE1~ YMUR2\"`hNIdPzi%^t@(Ao:=CQ,nx4S[7mHFye#aT6+v)DfKL$r?bkOGB>}!9_wV']jcp5JZ&Xl|\\8s;g<{3.u*W-0";
    for(int i=0; i<strlen(kata); i++){
        for(int j = 0 ; j<strlen(dasar); j++){
            if(kata[i] == dasar[j]){
                int indeks_baru = (j+(94-17)) % 94;
                kata[i] = dasar[indeks_baru];
                break;
            }
        }
    }
}

```
1. disini merupakan fungsi enkripsi dan dekripsi, untuk fungsi enkripsi digunakan untuk memimdahkan suatu char pada charlist ke char setelahnya sebanyak key (17), untuk fungsi dekripsi digunakan untuk memimdahkan suatu char pada charlist ke char sebelumnya sebanyak key (17)

```
	char fpath[1000];
	char sementara[1000];
    sprintf(sementara,"%s",path); 

    enkripsi(sementara); //kalo langsung enk path error
	sprintf(fpath, "%s%s",dirpath,sementara);

```
2. di fungsi getattr, readdir, dan read, terdapat fungsi yg digunakan untuk mengenkripsi isi dari file system itu, dibuat array char "sementara" untuk . lalu di enkripsi "sementara" , lalu print isi dari "sementara" ke dalam fpath.

```
while ((de = readdir(dp)) != NULL) {
		struct stat info;
        char cek[10000];
        strcpy(cek,fpath);
        strcat(cek,de->d_name);

        char file[1000];
		//
		if(strcmp(de->d_name,".")!=0 && strcmp(de->d_name,"..")!=0) dekripsi(de->d_name);
		//

        stat(cek,&info);
```
3. lalu di fungsi readdir, dibuat "cek" untuk memeriksa isi di dalam file system itu. lalu strcmp "." dan ".." diperlukan agar bisa berpindah baik itu menuju ke suatu file ataupun kembali ke file sebelumnya.


## Soal 2

## Soal 3
```
 struct passwd *user;
        user = getpwuid(info.st_uid); //mengambil user dari stat info.uid
        struct group *grup;
        grup = getgrgid(info.st_gid);//mengambil grup dari stat info.uid
        if( (strcmp(user->pw_name,"chipset") == 0 || strcmp(user->pw_name,"ic_controller") == 0) && strcmp(grup->gr_name,"rusak") == 0){
          if((info.st_mode & R_OK)==0){ //tdkbisa dibaca
              char txt[10000] = "/filemiris.txt";
              enkripsi(txt);
              char pathtxt[100000];
              sprintf(pathtxt,"%s%s",dirpath,txt);

              FILE *filetxt;
              filetxt = fopen(pathtxt,"a+");

              char waktu[21];
			  time_t now = time(NULL);
			  strftime(waktu, 20, "%H:%M:%S %Y-%m-%d", localtime(&now));//mengubah format waktu jd string
			
			  char isi[1000]; //apa yg mau ditulis di filemiris.txt
              strcpy(isi,de->d_name);
              strcat(isi,"_");
              char iduser[1000];
              sprintf(iduser,"%d_%d",user->pw_uid,grup->gr_gid);
              strcat(isi,iduser);
              strcat(isi,"_");
              strcat(isi,waktu);

              fprintf(filetxt,"%s\n",isi); //untuk print di filemiris
              fclose(filetxt);
              remove(cek);
          }
        }
        else{ // tdk di remove
            struct stat st;
		    memset(&st, 0, sizeof(st));
		    st.st_ino = de->d_ino;
		    st.st_mode = de->d_type << 12;

            strcpy(file,de->d_name);
		    res = (filler(buf, file, &st, 0));
		    	if(res!=0) break;
        }
	}

	closedir(dp);
	return 0;
}

```
- Didalam fungsi readdir, di soal 3 diprlukan uid password dan group, maka harus di-get trelebih dahulu, baru di compare jika password_name adalah "chipset" atau "ic_controller" dan group_name adalah "rusak".
- 

## Soal 4

## Soal 5

