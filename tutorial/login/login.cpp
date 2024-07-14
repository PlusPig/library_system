
#include "../global.h"
void login();

void test_login_plus();

int main() {
    test_login_plus();
}

// 旧版代码
void login() {
    bool quit = false;
    while (!quit) {
        system("cls");
        printf("welcome\n"
               "login or register?\n"
               "please input your choice\n"
               "<a>login <b>register <q>quit\n");
        char c;
        cin >> c;
        switch (c) {
            case 'a':
                if (login_or_register(true)) {
                    printf("login success\n");
                } else {
                    printf("login fail\n");
                }
                quit = true;
                break;
            case 'b':
                if (login_or_register(false)) {
                    printf("register success\n");
                } else {
                    printf("register fail\n");
                }
                quit = true;
                break;
            case 'q':
                quit = true;
                break;
            default:
                break;
        }
    }
    system("pause");
}