#include "Asciimator.hpp"
#include "sorenutils.h"
using namespace std;

int main(){
   Asciimation animation;
   while(true){
      cls();
      alignOut("\033[0mWelcome to Asciimator!", 1, 2); cout<<endl;
      alignOut("This program will help you to create beautiful ASCII animations!", 1); cout<<endl;
      alignOut("Press CTRL+C to exit the program at any time.", 1); cout<<endl;
      alignOut("While in the editor, press CTRL+F to read a list of keyboard shortcuts that will help you navigate and control your animation however you please.", 1); cout<<endl;
      alignOut("To start, enter your Animation Name, which will also be the directory name for your animation; then the first frame of your animation will open in the editor, so let your imagination run wild!", 1); cout<<endl;
      animation.init(alignIn(1, "Enter your Animation Name: ")); cout<<endl;
      animation.makeAnimation();
      cls(); cout<<"Great Job! Your Animation will play in..."<<endl; wait(4, true, true);
      animation.playAnimation();
   };
   return 0;
}