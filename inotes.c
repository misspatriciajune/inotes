//CMSC 125 ST-7L Lab Project
//iNotes - ICS-OS
//This application is basically the user's personal note keeper. The user can create, display, edit, save and delete notes.
//References: lights.c , vgademo.c

#include "../../sdk/dexsdk.h"

#define ADD 'a'
#define VIEW 'v'
#define VIEWALL 's'
#define QUIT 'q'
#define down_key 's'
#define display_all 'd'
#define back 'b'
#define editTitle 't'
#define editBody 'n'

#define YELLOW 30	
#define PINK 37		
#define BLUE 25		
#define VIOLET 13	
#define ORANGE 20	
#define ROYALBLUE 1
#define DARKBLUE 8
#define PALEYELLOW 62



typedef struct{						//structure declaration
	char noteTitle[50];
	char noteBody[250];
	char space[3];
}parameters;

parameters notes[50];

int flag=1;							//GLOBAL VAIABLE DECLARATION
int counter;

void header();						/*PRINTS MENU*/
void clear_screen();				/*CLEARS THE SCREEN*/
void close_app();					/*CLOSES APPLICATION*/
void add_notes();					/*CREATION OF NEW NOTES*/
void delete_notes(int i);			/*DELETION OF EXISTING NOTES*/
void view_note();					/*DISPLAY A NOTE*/
void viewall_notes();				/*DISPLAY ALL EXISTING NOTES*/
void edit_title(int i);				/*EDIT NOTE TITLE*/
void edit_body(int i);				/*EDIT NOTE BODY*/
void switches(int i);				/*SCROLLING TITLES*/
void erase();						/*COVERING A BLACK SECTION*/
void load();						/*LOADING TXT FILE*/

void fill_rect();					/*FILLING A BOX WITH COLOR*/
void fill_rect2();
void fill_rect3();
void fill_rect4();
void fill_rect5();
void fill_rect6();
void fill_rect7();
void fill_rect8();
void fill_rect9();	
void fill_rect10();

void add_title_rect();				/*DRAWING RECTANGLES*/
void add_title_rect2();
void add_title_rect3();
void add_rect_title();
void add_rect_title2();
void draw_rect();
void clearbox();
void edit_title_rect();
void edit_title_rect4();
void edit_title_rect5();
void edit_title_rect6();
void edit_title_rect7();
void note_title_rect();
void note_title_rect2();
void note_title_rect3();

int main()			//MAIN FUNCTION
{
	char keypress;
	//int counter;
	set_graphics(VGA_320X200X256);
	counter = 0;
	load();
	while(1){
		header();
		keypress = (char)getch();
		
		switch(keypress){
			case ADD:			//CREATE A NOTE
				add_notes();
				counter++;
				view_note();
				break;
			case VIEW:			//VIEW A NOTE
				view_note();
				break;
			case VIEWALL:		//VIEW ALL NOTES
				clear_screen();
				viewall_notes();
				break;
			case QUIT:			//QUIT APPLICATION
				close_app();
				return;
		}
	}
}

void load(){			//LOADING TXT FILE
	counter = 0;
	char *filename = "notes.txt";
	FILE *fp;
	FILE *fp_pak;
	char limits[500];
	char limits2[500];
	
	FILE *fp2;
	FILE *fp_pak2;
	char limits3[500];
	char limits4[500];
	
	fp_pak = fopen(filename, "r");
	
	if(fp_pak != NULL){
		fread(limits, (int)sizeof(char),500,fp_pak);
		strcpy(limits2, strtok(limits, "\n"));
		strcpy(notes[counter].noteTitle, limits2);
		counter++;

	}
	else {
	
	}
	fclose(fp_pak);
	
	

}

void add_notes(){	//FUNCTION FOR CREATING NEW NOTE
	char title[50];
	char note[250];
	char keypress;
	int ptr=0,x=20,y=12;
	char space[3];
	strcpy(space, "\n");
	char *filename = "notes.txt";
	FILE *fp = fopen(filename, "a");
	
	clear_screen();
	add_title_rect();
	
	write_text("Enter title of new note", 60, 3, VIOLET, 0);	
	
	do{
		keypress = (char)getch();
		if(keypress != '\n'){			//GET THE TITLE
			write_char(keypress,x,y,BLUE,0);
			x+=10;
			
			if (x > (320-30)){
		    	y+=10;
		    	x=10;
		    	}
			title[ptr++] = keypress;
		}
	}while(keypress != '\n');
	
	strcpy(notes[counter].noteTitle, title);	//STORE THE TITLE
	
	title[ptr-1] = '\0';
	//y+=20;
	add_title_rect2();
	write_text("Enter note here", 90, 70, VIOLET, 0);
	x=10, ptr=0;
	y+=80;
	do{
		keypress = (char)getch();
		if(keypress != '\n'){			//GET INPUT
			write_char(keypress,x,y,BLUE,0);
			x+=9;
			if (x > (320-30)){
		    	y+=9;
		    	x=10;
		  	}
			note[ptr++] = keypress;
		}
	}while(keypress != '\n');
	
	strcpy(notes[counter].noteBody, note);	//STORE THE BODY
	strcpy(notes[counter].space,space);
	
	note[ptr-1] = '\0';
	add_title_rect3();
	write_text("1 - Save", 50, 185,BLACK, 0);
	write_text("2 - Discard", 150, 185,BLACK, 0);
	keypress = (char)getch();
	if(keypress == '1'){		//SAVING THE NOTE TO THE TXT FILE
		fwrite(notes[counter].noteTitle, sizeof(char), strlen(notes[counter].noteTitle), fp);
		fwrite(notes[counter].space, sizeof(char), strlen(notes[counter].space), fp);
		fwrite(notes[counter].noteBody, sizeof(char), strlen(notes[counter].noteBody), fp);
		fwrite(notes[counter].space, sizeof(char), strlen(notes[counter].space), fp);
		fclose(fp);
	}
	else if(keypress == '2'){	//IF DISCARD
		free(notes[counter].noteTitle);
		free(notes[counter].noteBody);
		view_note();
	}
	clear_screen();
}

void view_note(){	//VIEWING A NOTE

	int i,j;
	int moves;
	char keypress;
	clear_screen();
			
	note_title_rect2();
	write_text("LEGEND:",10,185,DARKBLUE,0);
	write_text("Add-A",90,185,DARKBLUE,0);
	write_text("Scroll-S",150,185,DARKBLUE,0);
	write_text("Back-B",236,185,DARKBLUE,0);
			
		if(counter == 0){	//IF NO NOTES ARE EXISTING
			write_text("iNotes is empty!", 80, 50, ORANGE, 0);
			write_text("No notes available", 70, 60, ORANGE, 0);
			
			switches( i);
		}
		else{	//IF NOTES ARE AVAILABLE
			
			note_title_rect();
			write_text("NOTE TITLES", 100, 3, PINK, 0);
				flag=1;	
			while(flag==1){		
				for(i=0;i<counter;i++){
					write_text(notes[i].noteTitle, 10,i*10+13, WHITE, 0);	//DISPLAY ALL EXISTING NOTE TITLES
				}//end of for
				
				for(i=0;i<counter;i++){
					switches( i);
				}
			}//end of while
		getch();
		clear_screen();
	}//end of else			
}

void switches(int i){		//THIS IS THE FUNCTION FOR THE SWITCHES ON THE TITLE OF TE NOTES
		char keypress;
			keypress=(char)getch();
			switch(keypress){
				case ADD:	//ADDING NEW NOTE	
					add_notes();
					counter++;		//UPDATE NO OF NOTES
					view_note();
					break;
				case down_key:	//SCROLLING THROUGH THE TITLES
					if(i == 0){
						write_text(notes[i].noteTitle, 10,i*10+13, PALEYELLOW, 0);	//SELECTED TITLE
					}
					else{
						write_text(notes[i-1].noteTitle, 10,(i-1)*10+13, WHITE, 0);	//unselected one
						write_text(notes[i].noteTitle, 10,i*10+13, PALEYELLOW, 0);	//SELECTED TITLE	
					}
						
					if (keypress=(char)getch()){ 
						if(keypress=='\n'){		//IF ENTERED, DISPLAY THE CONTENTS OF THAT NOTE
							clear_screen();
							add_rect_title();	
							add_rect_title2();	
							write_text("Note Title", 100, 5, PINK, 0);
							write_text(notes[i].noteTitle, 10,25, WHITE, 0);	//DISPLAYING THE TITLE
							write_text("Note", 130, 70, PINK, 0);
							write_text(notes[i].noteBody,10, 80, WHITE, 0);		//DISPLAYING THE BODY
							note_title_rect3();
							write_text("1 - EDIT TITLE",20, 	170, DARKBLUE, 0);
							write_text("2 - EDIT BODY",170, 	170, DARKBLUE, 0);
							write_text("3 - DELETE",20, 180, DARKBLUE, 0);
							write_text("4 - BACK",170, 180, DARKBLUE, 0);
							
							keypress = (char)getch();
							if(keypress == '1'){		//GO TO EDIT TITLE FUNCTION
								edit_title(i);
								view_note();
								break;
							}
							else if(keypress == '2'){	//GO TO EDIT BODY FUNCTION
								edit_body(i);
								view_note();
								break;
							}
							else if(keypress == '3'){	//GO TO DELETE FUNCTION
								delete_notes(i);
								counter--;
								view_note();
								break;
							}
							else if(keypress == '4'){	//GO TO VIEW A NOTE FUNCTION
								view_note();
								break;
							}						
						} //end of if
					}//end of if	
				break;
						
				case back:		//GO BACK TO MAIN MENU
					flag=0;
					clear_screen();
					header();
					//main();
					//getch();
					break;
						
			}//end of switch
}

void delete_notes(int i){	//	DELETING A NOTE
	int j=0;
	
	free(notes[i].noteTitle);
	free(notes[i].noteBody);
	
	for(j=i; j<counter;j++){
		free(notes[j].noteTitle);
		free(notes[j].noteBody);
	
		if(j+1 == NULL){
		
		}
		else{
			strcpy(notes[j].noteTitle, notes[j+1].noteTitle);
			strcpy(notes[j].noteBody, notes[j+1].noteBody);
		}
	
	}
	//counter--;
	clear_screen();
	
}

void viewall_notes(){	//VIEWING ALL THE NOTES
	int i;
	clear_screen();
	
	clearbox();
	if(counter == 0){
		write_text("iNotes is empty!", 80, 50, ORANGE, 0);
		write_text("No notes available", 70, 60, ORANGE, 0);
	}
	else{
		for(i=0;i<counter;i++){	
			write_text(notes[i].noteTitle, 5,i*40+10, ORANGE, 0);
			write_text(notes[i].noteBody,10, i*40+30, GREEN, 0);
		}
	}
	getch();
	clear_screen();
}
		
void edit_title(int i){					//EDITING THE BODY
	char otitle[50];	//original title
	char ntitle[50];	//new title
	char keypress;
	int ptr=0,x=10,y=70;
	char *filename = "notes.txt";
	FILE *fp = fopen(filename, "a");
	clear_screen();	
	strcpy( otitle,notes[i].noteTitle);
	edit_title_rect();
	write_text("TITLE", 120,5, VIOLET, 0);
	
	edit_title_rect7();
	write_text(otitle, 10,20, DARKBLUE, 0);			//DISPLAY THE TITLE
	
	edit_title_rect4();
	write_text("ENTER NEW TITLE", 80,50, VIOLET, 0);	//ASK FOR THE NEW TITLE
	
	do{									//GET EACH CHARACTER BEING TYPE
		keypress = (char)getch();
		if(keypress != '\n'){
			write_char(keypress,x,y,BLUE,0);
			x+=10;
			if (x > (320-30)){
		    	y+=10;
		    	x=10;
		  	}
			ntitle[ptr++] = keypress;
		}
	}while(keypress != '\n');
	free(notes[i].noteTitle);							//DELETE THE PREVIOUS TITLE
	strcpy(notes[i].noteTitle, ntitle);					//STORE NEW TITLE
	ntitle[ptr-1] = '\0';
	fwrite(notes[i].noteTitle, sizeof(char), strlen(notes[i].noteTitle), fp);	//UPDATE
	
	getch();
	clear_screen();
}

void edit_body(int i){				//EDITING THE NOTE CONTENTS

	char obody[250];	//original body
	char nbody[250];	//new body
	char keypress;
	int ptr=0,x=30,y=100;
	char *filename = "notes.txt";
	FILE *fp = fopen(filename, "a");
	clear_screen();	
	strcpy( obody,notes[i].noteBody);		
	edit_title_rect();
	write_text("BODY", 150,4, VIOLET, 0);
	edit_title_rect6();
	write_text(obody, 10,23, DARKBLUE, 0);			//DISPLAY THE BODY
	edit_title_rect5();
	write_text("ENTER NEW BODY", 82,85, VIOLET, 0);	//ASKS FOR THE NEW BODY
	
	do{
		keypress = (char)getch();				//GETS EACH CHARACTER BEING TYPED
		if(keypress != '\n'){
			write_char(keypress,x,y,BLUE,0);
			x+=10;
			if (x > (320-30)){
		    	y+=10;
		    	x=10;
		  	}
			nbody[ptr++] = keypress;
		}
	}while(keypress != '\n');
	free(notes[i].noteBody);					//DELETE THE PREVIOUS BODY
	strcpy(notes[i].noteBody, nbody);			//STORE THE NEW BODY
	nbody[ptr-1] = '\0';
	fwrite(notes[i].noteBody, sizeof(char), strlen(notes[i].noteBody), fp);	//UPDATE
	
	getch();
	clear_screen();

}

void close_app(){						//CLOSES THE APPLICATION
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void clear_screen(){					//CLEAR THE SCREEN BLACK
	int i, j;
	for(i=0; i<320; i++)
		for(j=0; j<200; j++)
			write_pixel(i,j,BLACK);
}

										//DRAW RECTANGLES
void draw_rect(){		
    int x,y,w,h;
  	x=0;y=0;w=320;h=100;
   	fill_rect(x,y,107,h);
    fill_rect2(108,y,106,h);
    fill_rect3(214,y,106,h);
}

void add_rect_title(){			//DRAW RECTANGLES
 	int x,y,w,h;
 	x=0; y=0; w=320; h=60;
    fill_rect2(x,y,w,h);	
    fill_rect2(x,62,w,100);	
}

void add_rect_title2(){			//DRAW RECTANGLES
	int x,y,w,h;
	x=2; y=2; w=315;h=58;
    fill_rect4(x,y,w,h);	
    fill_rect4(x,64,w,92);
}

void note_title_rect(){			//DRAW RECTANGLES
 	int x,y,w,h;
  	x=0; y=0; w=320; h=10;
    fill_rect5(x,y,w,h);	 
}

void add_title_rect(){			//DRAW RECTANGLES
	int x,y,w,h;
    x=0;y=0;w=320;h=10;
    fill_rect2(x,y,w,h);	 
}

void edit_title_rect(){			//DRAW RECTANGLES
	int x,y,w,h;
  	x=0; y=0;w=320;h=15;
    fill_rect2(x,y,w,h);	
}

void edit_title_rect4(){		//DRAW RECTANGLES
	int x,y,w,h;
  	x=0;y=45;w=320; h=15;
    fill_rect2(x,y,w,h);	
}

void edit_title_rect5(){		//DRAW RECTANGLES
	int x,y,w,h;
  	x=0;y=80;w=320;h=15;
    fill_rect2(x,y,w,h);	 
}

void edit_title_rect6(){		//DRAW RECTANGLES
	 int x,y,w,h;
  	 x=0;y=15; w=320;h=80;
     fill_rect9(x,y,w,h);	
}

void edit_title_rect7(){		//DRAW RECTANGLES
	 int x,y,w,h;
   	 x=0;y=15;w=320; h=30;
     fill_rect9(x,y,w,h);	
}

void add_title_rect2(){//DRAW RECTANGLES
	 int x,y,w,h;
  	 x=0; y=70;w=320;h=10;
     fill_rect2(x,y,w,h);	 
}

void add_title_rect3(){//DRAW RECTANGLES
	int x,y,w,h;
  	x=0;y=180;w=320;h=20;
    fill_rect8(x,y,w,h);	 
}

void note_title_rect2(){//DRAW RECTANGLES
	int x,y,w,h;
  	x=0;y=180;w=320;h=20;
   	fill_rect(x,y,w,h);	
}

void note_title_rect3(){//DRAW RECTANGLES
 	int x,y,w,h;
  	x=0;y=160;w=320;h=40;
    fill_rect3(x,y,w,h);	
}

void clearbox(){//DRAW RECTANGLES
 	int x,y,w,h;
  	x=0;y=0;w=320;h=280;
    fill_rect10(x,y,w,h);	
}

void fill_rect9(int x, int y, int w, int h){		//WHITE RECTANGLE
   	int i,j;
   	for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,WHITE);
}

void fill_rect7(int x, int y, int w, int h){		//GREEN RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,GREEN);
}

void fill_rect5(int x, int y, int w, int h){		//DARKBLUE RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,DARKBLUE);
}

void fill_rect10(int x, int y, int w, int h){		//WHITE RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,WHITE);
}


void fill_rect6(int x, int y, int w, int h){		//VIOLET RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,VIOLET);
}

void fill_rect(int x, int y, int w, int h){			//PINK RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,PINK);
}

void fill_rect2(int x, int y, int w, int h){		//YELLOW RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,YELLOW);
}

void fill_rect3(int x, int y, int w, int h){		//BLUE RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,BLUE);
}

void fill_rect4(int x, int y, int w, int h){		//BLACK RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,BLACK);
}

void fill_rect8(int x, int y, int w, int h){		//ORANGE RECTANGLE
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(j,i,ORANGE);
}
	
void header(){										//PRINTS THE MENU
	//clear_screen();
	draw_rect();
	write_text("iNOTES",130,40,BLACK,1); //title
	write_text("Your notekeeper",95,50,BLACK,1); //title

	write_text("A - ADD NOTE",90,120,WHITE,0); 
	write_text("V - VIEW A NOTE",90,130,WHITE,0);
	write_text("S - DISPLAY NOTES",90,140,WHITE,0);
	write_text("Q - QUIT",90,150,WHITE,0);
	
}

