# minishell

**signal**

Changer l'état du processus au premier plan, utiliser signal.

Les signaux sont un mécanisme asynchrone de communication inter-processus.
Les signaux sont envoyés à un ou plusieurs processus. Ce signal est en général associé
à un évènement.
Un signal est envoyé à un processus en utilisant l’appel système : kill(int pid, int signal);
Le processus visé reçoit le signal sous forme d’un drapeau.
Le processus est interrompu et réalise éventuellement un traitement de ce signal.
Certains signaux peuvent être lancés à partir d’un terminal grâce aux caractères spéciaux
comme intr, quit dont la frappe est transformée en l’envoi des signaux SIGINT et SIGQUIT.
La valeur de pid indique le PID du processus auquel le signal est envoyé.

Ex: rendre programme insensible à la frappe du caractère de contrôle intr sur le
terminal de contrôle du processus.

Ctr D envoi EOF (signal SIGINT) au shell pour quitter

```c
void got_the_blody_signal(int n) {
signal(SIGINT, got_the_blody_signal);
printf(" gotcha!! your (%d) signal is useless \n");
}
main() {
signal(SIGINT, got_the_blody_signal);
printf(" kill me now !! \n");
for(;;);
}
```
http://www-igm.univ-mlv.fr/~dr/NCSPDF/chapitre11.pdf

**stat**

Récupère l'état du fichier pointé par path et remplit le tampon buf (structure).
- si path n'existe pas -> errno renvoie une erreur et on retoune erreur.
- (mystat.st_mode & S_IFMT) == S_IFDIR -> vérifie si path est un dossier.
si oui -> on definie errno = EISDIR (is a directory) et on retourne erreur.

**cursor movements**

CUR_RIGHT="\033[1C"

\b	retour arrière

**fork**

```c
pid_t	pid = 0;
int		status = 0;

// On fork
pid = fork();
if (pid == -1)
    perror("fork");
// Si le fork a reussit, le processus pere attend l'enfant (process fork)
else if (pid > 0) {
    // Par defaut le processus parent n'attend pas son fils donc utiliser wait
    // On block le processus parent jusqu'a ce que l'enfant termine puis
    // on kill le processus enfant
    waitpid(pid, &status, 0);
    kill(pid, SIGTERM);
} else {
    // Le processus enfant execute la commande ou exit si execve echoue
    // Exec remplace le programme courant par un autre (le programme de la cmd), d'où l'utilisation de fork()
    //
    if (execve(cmd[0], cmd, NULL) == -1)
        perror("shell");
    exit(EXIT_FAILURE);
}
```
https://segfault42.github.io/posts/minishell/

waitpid : permet de savoir q'une commande est terminé.
L'appel système waitpid() suspend l'exécution du processus appelant jusqu'à ce que le fils spécifié par son pid ait changé d'état. Par défaut, waitpid() n'attend que les fils terminés. (man waitpid)

avantages fork() : si si child crash, le parent n'est pas affecté

**pipe**

Connecter l’entrée d’un processus avec la sortie d’un autre

**flux de redirection | < << > >>**

https://openclassrooms.com/fr/courses/43538-reprenez-le-controle-a-laide-de-linux/40444-les-flux-de-redirection

**autre cde**

ps : liste statique des processus;
top : liste dynamique des processus;
Ctrl + C & kill : arrêter un processus.