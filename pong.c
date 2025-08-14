#include <ncurses.h>
#include <stdio.h>

#define HEIGHT 25
#define WIDTH 80

int racket_left_y, racket_right_y;  // Coordiates of rackets
int ball_x = WIDTH / 2;
int ball_y = HEIGHT / 2;
int ball_move_x = 1;
int ball_move_y = 1;

void Draw(int score_p1, int score_p2) {
    int row, col;
    getmaxyx(stdscr, row, col);
    move(row / 2 - HEIGHT / 2 + HEIGHT + 2, col / 2 - 1);
    printw("%d - %d \n", score_p1, score_p2);
    move(row / 2 - HEIGHT / 2, col / 2 - WIDTH / 2);
    for (int i = 0; i < WIDTH + 2; i++) printw("_");  // upper perekladina
    printw("\n");
    for (int y = 0; y < HEIGHT; y++) {
        move(row / 2 - HEIGHT / 2 + y + 1, col / 2 - WIDTH / 2);
        printw("|");
        for (int x = 0; x < WIDTH; x++) {
            if (x == 3 && y >= racket_left_y - 1 && y <= racket_left_y + 1)
                printw("|");
            else if (x == WIDTH - 4 && y >= racket_right_y - 1 && y <= racket_right_y + 1)
                printw("|");
            else if (x == ball_x && y == ball_y)
                printw("@");
            else if (x == WIDTH / 2)
                printw("#");
            else
                printw(" ");
        }
        printw("|\n");
    }
    move(row / 2 - HEIGHT / 2 + HEIGHT, col / 2 - WIDTH / 2);
    for (int i = 0; i < WIDTH + 2; i++) printw("-");  // lower perekladina
    printw("\n");
}

void MoveRacket(char key) {
    if (key == 'm') {
        if (racket_right_y + 3 == 25) {
            return;
        }
        racket_right_y++;
        return;
    }
    if (key == 'k') {
        if (racket_right_y - 1 == 0) {
            return;
        }
        racket_right_y--;
        return;
    }
    if (key == 'a') {
        if (racket_left_y - 1 == 0) {
            return;
        }
        racket_left_y--;
        return;
    }
    if (key == 'z') {
        if (racket_left_y + 3 == 25) {
            return;
        }
        racket_left_y++;
        return;
    }
    if (key == ' ') {
        return;
    }
}

void MoveBall() {
    int next_x = ball_x + ball_move_x;
    int next_y = ball_y + ball_move_y;
    int pong = 0;

    if (next_x == 3 && next_y >= racket_left_y - 1 && next_y <= racket_left_y + 1) {
        ball_move_x = -ball_move_x;
        if ((next_y == racket_left_y + 1 || next_y == racket_right_y + 1) && (ball_move_y) < 0) {
            ball_move_y = -ball_move_y;
        }
        if ((next_y == racket_left_y + -1 || next_y == racket_right_y + -1) && (ball_move_y) > 0) {
            ball_move_y = -ball_move_y;
        }
        pong = 1;
    }
    if (next_x == WIDTH - 4 && next_y >= racket_right_y - 1 && next_y <= racket_right_y + 1) {
        ball_move_x = -ball_move_x;
        if ((next_y == racket_left_y + 1 || next_y == racket_right_y + 1) && ball_move_y < 0) {
            ball_move_y = -ball_move_y;
        }
        if ((next_y == racket_left_y + -1 || next_y == racket_right_y + -1) && ball_move_y > 0) {
            ball_move_y = -ball_move_y;
        }
        pong = 1;
    }
    if (next_y == -1 || next_y == HEIGHT - 1) {
        ball_move_y = -ball_move_y;
    }
    ball_y += ball_move_y;

    if (((next_x == 3 && ball_y == racket_left_y) || (next_x == WIDTH - 4 && ball_y == racket_right_y)) &&
        pong != 1) {
        ball_move_x = -ball_move_x;
    }
    pong = 0;
    ball_x += ball_move_x;
}

int SetGoal() {
    if (ball_x == 2)
        return 2;
    else if (ball_x == WIDTH - 3)
        return 1;
    return 0;
}

void PrintStartMenu() {
    int row, col;
    getmaxyx(stdscr, row, col);
    printw(
        "                                                     PPPPPPPPPPPPPPPPP    iiii                      "
        "                                          "
        "PPPPPPPPPPPPPPPPP                                                      \n");
    printw(
        "                                                     P::::::::::::::::P  i::::i                     "
        "                                          "
        "P::::::::::::::::P                                                     \n");
    printw(
        "                                                     P::::::PPPPPP:::::P  iiii                      "
        "                                          "
        "P::::::PPPPPP:::::P                                                    \n");
    printw(
        "                                                     PP:::::P     P:::::P                           "
        "                                          PP:::::P   "
        "  P:::::P                                                   \n");
    printw(
        "                                                     P::::P     P:::::iiiiiinnnn  nnnnnnnn      "
        "ggggggggg   ggggg                             P::::P     "
        "P:::::P ooooooooooo  nnnn  nnnnnnnn      ggggggggg   ggggg\n");
    printw(
        "                                                     P::::P     P:::::i:::::n:::nn::::::::nn   "
        "g:::::::::ggg::::g                             P::::P     "
        "P:::::oo:::::::::::oon:::nn::::::::nn   g:::::::::ggg::::g\n");
    printw(
        "                                                     P::::PPPPPP:::::P i::::n::::::::::::::nn "
        "g:::::::::::::::::g                             "
        "P::::PPPPPP:::::o:::::::::::::::n::::::::::::::nn g:::::::::::::::::g\n");
    printw(
        "                                                     P:::::::::::::PP  "
        "i::::nn:::::::::::::::g::::::ggggg::::::gg      ---------------        "
        "P:::::::::::::PPo:::::ooooo:::::nn:::::::::::::::g::::::ggggg::::::gg\n");
    printw(
        "                                                     P::::PPPPPPPPP    i::::i "
        "n:::::nnnn:::::g:::::g     g:::::g       -:::::::::::::-        "
        "P::::PPPPPPPPP  o::::o     o::::o n:::::nnnn:::::g:::::g     g:::::g \n");
    printw(
        "                                                     P::::P            i::::i n::::n    "
        "n::::g:::::g     g:::::g       ---------------        P::::P     "
        "     o::::o     o::::o n::::n    n::::g:::::g     g:::::g \n");
    printw(
        "                                                     P::::P            i::::i n::::n    "
        "n::::g:::::g     g:::::g                              P::::P     "
        "     o::::o     o::::o n::::n    n::::g:::::g     g:::::g \n");
    printw(
        "                                                     P::::P            i::::i n::::n    "
        "n::::g::::::g    g:::::g                              P::::P     "
        "     o::::o     o::::o n::::n    n::::g::::::g    g:::::g \n");
    printw(
        "                                                     PP::::::PP         i::::::in::::n    "
        "n::::g:::::::ggggg:::::g                            PP::::::PP "
        "       o:::::ooooo:::::o n::::n    n::::g:::::::ggggg:::::g \n");
    printw(
        "                                                     P::::::::P         i::::::in::::n    "
        "n::::ng::::::::::::::::g                            P::::::::P "
        "       o:::::::::::::::o n::::n    n::::ng::::::::::::::::g \n");
    printw(
        "                                                     P::::::::P         i::::::in::::n    n::::n "
        "gg::::::::::::::g                            P::::::::P "
        "        oo:::::::::::oo  n::::n    n::::n gg::::::::::::::g \n");
    printw(
        "                                                     PPPPPPPPPP         iiiiiiiinnnnnn    nnnnnn   "
        "gggggggg::::::g                            PPPPPPPPPP "
        "          ooooooooooo    nnnnnn    nnnnnn   gggggggg::::::g \n");
    printw(
        "                                                                                                    "
        "       g:::::g                                       "
        "                                                    g:::::g \n");
    printw(
        ".                                                                                              "
        "gggggg      g:::::g                                       "
        "                                        gggggg      g:::::g \n");
    printw(
        "                                                                                               "
        "g:::::gg   gg:::::g                                       "
        "                                        g:::::gg   gg:::::g \n");
    printw(
        "                                                                                                "
        "g::::::ggg:::::::g                                       "
        "                                         g::::::ggg:::::::g \n");
    printw(
        "                                                                                                  "
        "gg:::::::::::::g                                       "
        "                                           gg:::::::::::::g  \n");
    printw(
        "                                                                                                    "
        " ggg::::::ggg                                        "
        "                                              ggg::::::ggg    \n");
    printw(
        "                                                                                                    "
        "    gggggg                                           "
        "                                                 gggggg      \n");
    printw("\n");
    move(row / 2 - HEIGHT / 2 + HEIGHT + 4, col / 2 - WIDTH / 2);
    printw(
        "Control: a/z - left racket up/down; k/m - right racket "
        "up/down;  blank - skip turn                                         \n");
    move(row / 2 - HEIGHT / 2 + HEIGHT + 5, col / 2 - WIDTH / 2 + 32);
    printw(
        "ONE INPUT PER TURN"
        "                                                              \n");
}

void PrintGameOver(int s_p1, int s_p2) {
    clear();
    printw("\n");
    printw("       GGGGGGGGGGGGG \n");
    printw("     GGG::::::::::::G\n");
    printw("   GG:::::::::::::::G\n");
    printw("  G:::::GGGGGGGG::::G\n");
    printw(
        " G:::::G       GGGGGG aaaaaaaaaaaaa     mmmmmmm    mmmmmmm      eeeeeeeeeeee            "
        "ooooooooooovvvvvvv           vvvvvvveeeeeeeeeeee   rrrrr   rrrrrrrrr\n");
    printw(
        "G:::::G               a::::::::::::a  mm:::::::m  m:::::::mm  ee::::::::::::ee        "
        "oo:::::::::::ov:::::v         v:::::ee::::::::::::ee r::::rrr:::::::::r\n");
    printw(
        "G:::::G               aaaaaaaaa:::::am::::::::::mm::::::::::me::::::eeeee:::::ee     "
        "o:::::::::::::::v:::::v       v:::::e::::::eeeee:::::er:::::::::::::::::r\n");
    printw(
        "G:::::G    GGGGGGGGGG          a::::am::::::::::::::::::::::e::::::e     e:::::e     "
        "o:::::ooooo:::::ov:::::v     v:::::e::::::e     e:::::rr::::::rrrrr::::::r\n");
    printw(
        "G:::::G    G::::::::G   aaaaaaa:::::am:::::mmm::::::mmm:::::e:::::::eeeee::::::e     o::::o     "
        "o::::o v:::::v   v:::::ve:::::::eeeee::::::er:::::r     r:::::r\n");
    printw(
        "G:::::G    GGGGG::::G aa::::::::::::am::::m   m::::m   m::::e:::::::::::::::::e      o::::o     "
        "o::::o  v:::::v v:::::v e:::::::::::::::::e r:::::r     rrrrrrr\n");
    printw(
        "G:::::G        G::::Ga::::aaaa::::::am::::m   m::::m   m::::e::::::eeeeeeeeeee       o::::o     "
        "o::::o   v:::::v:::::v  e::::::eeeeeeeeeee  r:::::r\n");
    printw(
        " G:::::G       G::::a::::a    a:::::am::::m   m::::m   m::::e:::::::e                o::::o     "
        "o::::o    v:::::::::v   e:::::::e           r:::::r\n");
    printw(
        "  G:::::GGGGGGGG::::a::::a    a:::::am::::m   m::::m   m::::e::::::::e               "
        "o:::::ooooo:::::o     v:::::::v    e::::::::e          r:::::r\n");
    printw(
        "   GG:::::::::::::::a:::::aaaa::::::am::::m   m::::m   m::::me::::::::eeeeeeee       "
        "o:::::::::::::::o      v:::::v      e::::::::eeeeeeee  r:::::r\n");
    printw(
        "     GGG::::::GGG:::Ga::::::::::aa:::m::::m   m::::m   m::::m ee:::::::::::::e        "
        "oo:::::::::::oo        v:::v        ee:::::::::::::e  r:::::r\n");
    printw(
        "        GGGGGG   GGGG aaaaaaaaaa  aaammmmmm   mmmmmm   mmmmmm   eeeeeeeeeeeeee          ooooooooooo "
        "          vvv           eeeeeeeeeeeeee  rrrrrrr\n");
    if (s_p1 > s_p2)
        printw("                                                                         First player won\n");
    else
        printw(
            "                                                                         Second player won\n");
    refresh();
}

int main() {
    initscr();
    nodelay(stdscr, TRUE);
    PrintStartMenu();
    char key;
    int score_p1 = 0;
    int score_p2 = 0;
    ball_move_x = ball_move_x;
    racket_left_y = (HEIGHT - 1) / 2;
    racket_right_y = (HEIGHT - 1) / 2;
    while (score_p1 < 3 && score_p2 < 3) {
        key = getch();
        MoveRacket(key);
        MoveBall();
        Draw(score_p1, score_p2);
        refresh();
        halfdelay(1);
        napms(100);
        if (SetGoal() == 1) {
            score_p1++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_move_x = -ball_move_x;
        } else if (SetGoal() == 2) {
            score_p2++;
            ball_x = WIDTH / 2;
            ball_y = HEIGHT / 2;
            ball_move_x = -ball_move_x;
        }
    }
    PrintGameOver(score_p1, score_p2);
    return 0;
}