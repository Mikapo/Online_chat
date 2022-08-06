#include "Core/Chat_client.h"

void start_client()
{
    Chat_client client;
    client.start();
}

#ifdef _WIN32
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    start_client();
}
#endif

int main()
{
    start_client();
}
