#include "base.h"

int main(void)
{
    int r = (i_rnd(100));
    printsln("Zahl eingeben!");
    int i = i_input();
    while (i != r)
    {
        if (i > r)
        {
            printsln("Zu gross!");
        }
        else if (i < r)
        {
            printsln("Zu klein!");
        }
        else
        {
            break;
        }
        i = i_input();
    }
    printsln("Richtige Zahl!");
    return 0;
}