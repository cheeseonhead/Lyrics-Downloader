#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>

char nm[5000],at[5000],al[5000],gr[5000],trash[5000];
char cmd[50000],site[50000],sn[100000],an[10000],ln[10000];

FILE *music_list = fopen("Music.txt","r"),*fout;

bool get_info()
{
	if(fgets(nm,1000,music_list)==NULL)return 0;
	fgets(at,1000,music_list);
	fgets(trash,1000,music_list);
	fgets(al,1000,music_list);
	fgets(trash,1000,music_list);
	fgets(gr,1000,music_list);
	for(int i=0;i<21;i++)
	{
		fgets(trash,1000,music_list);
	//	trash[strlen(trash)-1] = 0;
	//	puts(trash);
	}
	
	//puts("--------");
	
	nm[strlen(nm)-1] = 0;
	at[strlen(at)-1] = 0;
	al[strlen(al)-1] = 0;
	gr[strlen(gr)-1] = 0;
	
	return 1;
}

void print_info()
{
	puts(nm);
	puts(at);
	puts(al);
	puts(gr);
}

void print_UTF()
{
	for(int i=0;nm[i];i+=3)
		printf("%X %X %X\n",nm[i],nm[i+1],nm[i+2]);
	for(int i=0;at[i];i+=3)
		printf("%X %X %X\n",at[i],at[i+1],at[i+2]);
	for(int i=0;al[i];i+=3)
		printf("%X %X %X\n",al[i],al[i+1],al[i+2]);
}
	
void html_encoding()
{
	//sn html
	memset(sn,0,sizeof(sn));
	for(int i=0;at[i];i++)
	{
		char t[3];int pnt = strlen(sn);
		sprintf(t,"%%%X",at[i]&255);
		//printf("t ");puts(t);
		for(int j=0;j<3;j++)
			sn[pnt++] = t[j];
	}
	//puts(sn);
	
	//an html
	memset(an,0,sizeof(an));
	for(int i=0;al[i];i++)
	{
		char t[3];int pnt = strlen(an);
		sprintf(t,"%%%X",al[i]&255);
		//puts(t);
		for(int j=0;j<3;j++)
			an[pnt++] = t[j];
	}
	
	//ln html
	memset(ln,0,sizeof(ln));
	for(int i=0;nm[i];i++)
	{
		char t[3];int pnt = strlen(ln);
		sprintf(t,"%%%X",nm[i]&255);
		//puts(t);
		for(int j=0;j<3;j++)
			ln[pnt++] = t[j];
	}
}

void cmd_str()
{
	sprintf(site,"\"http://lyrics.oiktv.com/search.php?sn=&an=%s&ln=%s&lrc=&sx=all\"",an,ln);
	//puts(site);
	sprintf(cmd,"wget -x -E -nc %s",site);
	puts(cmd);
}

int main()
{
	freopen("Site_Artist.txt","w",stdout);
	while(get_info())
	{
		html_encoding();
		cmd_str();
		system(cmd);
	}
	return 0;
}
