#include "minishell.h"

static void handle_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    // write(1, "\nmandeha ny cltr + c\n\n", 25);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
    g_signal = 1;
}

void init_signals(void)
{
    struct sigaction sa;

    sa.sa_handler = &handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    sigaction(SIGINT, &sa, NULL);
    signal(SIGQUIT, SIG_IGN);
}