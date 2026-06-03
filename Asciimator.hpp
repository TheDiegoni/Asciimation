#ifdef _WIN32 // Windows (sia 32 che 64 bit)
	#include <windows.h>
#endif
#include <iostream>
#include <fstream>
#include <string>
#include "sorenutils.h"
using namespace std;

#ifndef ASCIIMATOR_HPP
   #define ASCIIMATOR_HPP

    class Frame{
		public:
	    	string chr[9999], path;
   	    	int delay, layers=0, frame=0;
			void frameOut(int layer=-1, bool play=false){
				if(layer==-1){layer=layers-1;};
				for(int i=0; i<layers; i++){
					if(i==layer && !play){cout<<chr[i].substr(0, chr[i].size()/sizeof(chr[i][0])-1)<<'_'<<"\n";}
					 else{
						if(i==layers-1){cout<<chr[i].substr(0, chr[i].size()/sizeof(chr[i][0])-1);}
						 else{cout<<chr[i];};
					 };
				};
			}
			void init(string pt, int num){
				for(int i=0; chr[i]!=""; i++){chr[i]="";}; delay=0; layers=0;
				path=pt;	frame=num;
				fstream file(path+"Frame"+to_string(frame)+".txt", fstream::in);
				if(file.fail()){
					cls();
					cout<<"failed to access directory, redirected to main";
					file.open("Frame"+to_string(frame)+".txt", fstream::in);
				};
				if(!file.fail()){
					file>>delay; file.ignore();
					while(getline(file, chr[layers])){
						chr[layers]+='\n';
						layers++;
					};
					chr[layers]+='\n';
					layers++;
					file.close();
				};
				if(layers<=0){
					layers=1;
					chr[0]="\033[00m\n";
				};
			}
			void saveFrame(){
				fstream file(path+"Frame"+to_string(frame)+".txt", fstream::out);
				if(file.fail()){
					cls();
					cout<<"failed to access directory, redirected to main";
					file.open("Frame"+to_string(frame)+".txt", fstream::out);
				};
				if(!file.fail()){
					if(delay<=0){cout<<endl<<"Set Delay (ms): "; cin>>delay;};
					file<<delay<<'\n';
					for(int i=0; i<layers-1; i++){file<<chr[i];};
					file<<chr[layers-1].substr(0, chr[layers-1].size()/sizeof(chr[layers-1][0])-1);
					file.close();
				};
			}
			short int makeFrame(bool an=false){
				fstream file; int layer=layers-1;
				#ifdef _WIN32
					INPUT_RECORD in[1]; DWORD cNumRead, fdwSave;
					GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &fdwSave);

					SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE);
					while(true){
						cls(); frameOut(layer);
						ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), in, 1, &cNumRead);
						if(in[0].Event.KeyEvent.bKeyDown){
							if(in[0].Event.KeyEvent.uChar.AsciiChar>=32 && in[0].Event.KeyEvent.uChar.AsciiChar<=126){
								if(chr[layer][chr[layer].size()/sizeof(chr[layer][0])-1]=='\n'){
									chr[layer][chr[layer].size()/sizeof(chr[layer][0])-1]=in[0].Event.KeyEvent.uChar.AsciiChar;
									chr[layer]+="\n";
								}else{chr[layer]+=in[0].Event.KeyEvent.uChar.AsciiChar;};
							}
							 else{
								switch(in[0].Event.KeyEvent.uChar.AsciiChar){
									case 3:
										_exit(0);
									case 4:
										SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
										cout<<endl<<"Set Delay (ms): "; cin>>delay;
										SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE);
										break;
									case 6:
										cls();
										SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
										cout<<"\033[0mCTRL+C - Exit without Saving"<<endl;
										cout<<"CTRL+D - Set Delay"<<endl;
										cout<<"CTRL+F - Command List"<<endl;
										cout<<"CTRL+G - Change Text Color"<<endl;
										cout<<"CTRL+X - Exit and Save"<<endl;
										cout<<"Arrow Keys - Move in the Frame"<<endl;
										if(an){
											cout<<"CTRL+B/PGUP - Previous Frame"<<endl;
											cout<<"CTRL+N/PGDOWN - Next Frame"<<endl;
											cout<<"CTRL+P - Play Animation"<<endl;
											cout<<"CTRL+O - Play Animation with Specified Position"<<endl;
										};
										SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), (ENABLE_WINDOW_INPUT | ENABLE_EXTENDED_FLAGS) & ~ENABLE_QUICK_EDIT_MODE);
										system("pause");
										break;
									case 7:
										if(chr[layer].size()/sizeof(chr[layer][0])>=6 && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-6]=='\033' && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-5]=='[' && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-4]!='0' && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-2]=='m'){
											chr[layer][chr[layer].size()/sizeof(chr[layer][0])-3]=chr[layer][chr[layer].size()/sizeof(chr[layer][0])-3]+1;
											if(chr[layer][chr[layer].size()/sizeof(chr[layer][0])-3]>='8'){chr[layer][chr[layer].size()/sizeof(chr[layer][0])-3]='0';};
										}else{chr[layer].pop_back(); chr[layer]+="\033[30m\n";};
										break;
									case 8:
										if(layer==0 && chr[layer].size()/sizeof(chr[layer][0])<=6){}
										 else{
											if(chr[layer].size()/sizeof(chr[layer][0])>6 && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-6]=='\033' && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-5]=='[' && chr[layer][chr[layer].size()/sizeof(chr[layer][0])-2]=='m'){
												if(chr[layer][chr[layer].size()/sizeof(chr[layer][0])-4]!='0'){
													for(int i=0; i<=6; i++){
														if(layer==0 && chr[layer].size()/sizeof(chr[layer][0])<6){}
														 else{chr[layer].pop_back();};
													};
													chr[layer]+="\n";
												};
											}else{
												if(chr[layer].size()/sizeof(chr[layer][0])>0){
													if(chr[layer][chr[layer].size()/sizeof(chr[layer][0])-1]=='\n'){
														if(chr[layer].size()/sizeof(chr[layer][0])>1){
															chr[layer].pop_back(); chr[layer].pop_back();
															chr[layer]+="\n";
														}else{chr[layer].pop_back();};
													}else{chr[layer].pop_back();};
												};
												if(chr[layer].size()/sizeof(chr[layer][0])==0){
													shift(chr, layers, 0, layer);
													chr[layers-1]="";
													layer--; layers--;
												};
											};
										};
										break;
									case 9:
										for(int i=0; i<8; i++){chr[layer]+=" ";};
										break;
									case 13:
										shift(chr, layers, 1, layer);
										layer++; layers++;
										chr[layer]="\n";
										break;
									case 24:
										SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
										saveFrame();
										return 0;
									default:
										if(an){
											switch(in[0].Event.KeyEvent.uChar.AsciiChar){
												case 2:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return -1;
												case 14:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return 1;
												case 15:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return 3;
												case 16:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return 2;
											};
											switch(in[0].Event.KeyEvent.wVirtualKeyCode){
												case 33:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return -1;
												case 34:
													SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), fdwSave);
													saveFrame();
													return 1;
												case 38:
													if(layer>0){layer--;};
													break;
												case 40:
													if(layer<layers-1){layer++;};
													break;
											};
										};
								};
							 };
						};
					};
				#endif
				return 1;
         }
   };

    class Asciimation{
      public:
			string path;
			int framecount=0;
			Frame frame;
			void load(int currentframe=0){frame.init(path, currentframe);};
			void init(string p){
				fstream file;
				path=p+'/';
				system(("mkdir "+p).c_str());
				file.open(path+"FrameCount.txt", fstream::in);
				if(file.fail()){
					cls();
					cout<<"failed to access directory, redirected to main";
					file.open("FrameCount.txt", fstream::in);
				};
				if(!file.fail()){
					if(file.peek()!='\0'){file>>framecount;};
					file.close();
				};
				load();
			};
			void saveAnimation(){
				fstream file(path+"FrameCount.txt", fstream::out);
				if(file.fail()){
					cls();
					cout<<"failed to access directory, redirected to main";
					file.open("FrameCount.txt", fstream::out);
				};
				if(!file.fail()){
					file<<framecount;
					file.close();
				};
			}
			void playAnimation(float speed=1, int loop=1, int start=0, int end=-1){
				if(end==-1){end=framecount+1;};
				while(loop>0){
					for(int i=start; i<end; i++){
						load(i);
						cls(); frame.frameOut(-1, true);
						Sleep(frame.delay/speed);
					};
					loop--;
				};
				system("pause");
			};
			void makeAnimation(){
				int fn=0; fstream file; int st, en;
				while(true){
					switch(frame.makeFrame(true)){
						case 0:
							saveAnimation();
							return;
						case 1:
							fn++;	if(fn>=framecount){framecount=fn;};
							load(fn);
							break;
						case -1:
							if(fn>0){fn--;};
							load(fn);
							break;
						case 2:
							playAnimation();
							load(fn);
							break;
						case 3:
							cls();
							cout<<"Enter Start Frame: "; cin>>st;
							cout<<"Enter End Frame: "; cin>>en;
							playAnimation(1, 1, st, en+1);
							load(fn);
							break;
					};
				};
			};
	};
#endif