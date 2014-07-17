#include "Application.hpp"

int main()
{
    srand(time(NULL));
    Application app(700, 700);
    app.run();

    return 0;
}
