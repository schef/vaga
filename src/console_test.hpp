#ifndef __CONSOLE_TEST_HPP__
#define __CONSOLE_TEST_HPP__

#include "logger.hpp"
#include "console.hpp"

class ConsoleTest {
    static void test(int argc, char *argv[]) {
        if (argc == 3) {
            if (!strcmp(argv[1], "str")) {
                loggif("str: %s\n", argv[2]);

            } else if (!strcmp(argv[1], "int")) {
                loggif("int: %d\n", Console::getNum(argv[2]));

            } else if (!strcmp(argv[1], "hex")) {
                uint32_t bufferLen = Console::getHexLen(argv[2]);
                uint8_t *buffer = new uint8_t[bufferLen];
                Console::getHex(argv[2], buffer);
                loggif("hex: ");
                loggbln(buffer, bufferLen, ' ');
                delete[] buffer;

            } else {
                Console::printError(argc, argv);
            }
        } else {
            Console::printError(argc, argv);
        }
    }

    static void onSms(bool status) {
        loggif("%s\n", status ? "true" : "false");
    }

    static void modem(int argc, char *argv[]) {
        if (argc == 2) {
            if (!strcmp(argv[1], "sms")) {
                Modem::getInstance().sendSms("+385912895204", "DELA!!!", onSms);

            } else {
                Console::printError(argc, argv);
            }

        } else if (argc == 3) {
            if (!strcmp(argv[1], "power")) {
                if (!strcmp(argv[2], "on")) {
                    Modem::getInstance().setPower(1);
                } else if (!strcmp(argv[2], "off")) {
                    Modem::getInstance().setPower(0);
                } else {
                    Console::printError(argc, argv);
                }

            } else if (!strcmp(argv[1], "write")) {
                Modem::getInstance().write(argv[2]);

            } else if (!strcmp(argv[1], "writen")) {
                Modem::getInstance().write(argv[2], false);

            } else if (!strcmp(argv[1], "writesms")) {
                if (!strcmp(argv[2], "start")) {
                    Modem::getInstance().write("AT+CMGS=\"+385912895203\"");
                } else if (!strcmp(argv[2], "end")) {
                    Modem::getInstance().write(26, false);
                }

            } else {
                Console::printError(argc, argv);

            }
        } else {
            Console::printError(argc, argv);
        }
    }

public:
    static void registerCommands() {
        loggif("\n");
        Console::getInstance().registerCommand(
                Console::cmd_list_t{"test", "<str|int|hex> <DATA>", "Conversion examples", test});
        Console::getInstance().registerCommand(
                Console::cmd_list_t{"modem", "<power|write> <DATA>", "Conversion examples", modem});
    }
};

#endif