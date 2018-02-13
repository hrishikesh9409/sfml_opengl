#include "display.h"

using namespace std;

int main(){
    const int width = 800;
    const int height = 640;

    Display d;
    d.render(width, height);

    return 0;
} 
