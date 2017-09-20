#include "ui/BattleshipApplication.hpp"

int main(int argc, char *argv[]) {
    std::setlocale(LC_ALL, "");

    int res;

    try {
        BattleshipApplication app;
        app.handleArgs(argc, argv);
        res = app();
    } catch (const NCursesException *e) {
        std::cerr << e->message << std::endl;
        res = e->errorno;
    } catch (const NCursesException &e) {
        std::cerr << e.message << std::endl;
        res = e.errorno;
    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        res = EXIT_FAILURE;
    }

    return res;
}