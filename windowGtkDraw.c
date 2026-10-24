#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
// COMPILAR -> gcc $( pkg-config --cflags gtk4 ) -o windowGtkDraw.out windowGtkDraw.c $( pkg-config --libs gtk4 )

static void senha_oito (GtkWidget *widget, gpointer data){
    char password[8] = "";
    for (int n=0;n<8;n++){
        // por algum motivo gerar com essa constante fora printava ela inteira apos a senha, aqui resolveu, mas é temporario pq pode sobrecarregar o espaco da memoria
        const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        int r = rand()%62;
        int s = alphabet[r]; 
        password[n] = s;
    }
    g_print ("SUCESSO! Copie a sua senha: %s\n", password);
}
static void senha_doze (GtkWidget *widget, gpointer data){
    char password[12] = "";
    for (int n=0;n<12;n++){
        const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        int r = rand()%62;
        int s = alphabet[r]; 
        password[n] = s;
    }
    g_print ("SUCESSO! Copie a sua senha: %s\n", password);
}
static void senha_dzseis (GtkWidget *widget, gpointer data){
    char password[16] = "";
    for (int n=0;n<16;n++){
        const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        int r = rand()%62;
        int s = alphabet[r]; 
        password[n] = s;
    }
    g_print ("SUCESSO! Copie a sua senha: %s\n", password);
}

static void
activate (GtkApplication *app, gpointer userdata){
    // aqui sera os elementos que vou usar na janela criada (GTKWIDGET *ELEMENTO)
    GtkWidget *window;
    GtkWidget *btn;
    GtkWidget *grid;

    window=gtk_application_window_new (app); // cria o objeto Janela, pra manipular abaixo

    gtk_window_set_title(GTK_WINDOW (window),"Gerador de senhas"); //titulo
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 200); // dimensao da janela

    grid = gtk_grid_new ();
    gtk_window_set_child (GTK_WINDOW (window), grid);

    btn = gtk_button_new_with_label ("Senha de 8 digitos (CLI)"); //famosissimo botao hello world
    g_signal_connect (btn, "clicked", G_CALLBACK (senha_oito), NULL); // parec q aqui ta dando funçao ao botao
    gtk_grid_attach (GTK_GRID (grid), btn, 0,0,1,1); //appenda ao grid, parece que 0 0 é raiz, e 1 1 é pra ele encrer a lateral

    btn = gtk_button_new_with_label ("Senha de 12 digitos (CLI)"); 
    g_signal_connect (btn, "clicked", G_CALLBACK (senha_doze), NULL); 
    gtk_grid_attach (GTK_GRID (grid), btn, 0,1,1,1); 

    btn = gtk_button_new_with_label ("Senha de 12 digitos (CLI)"); 
    g_signal_connect (btn, "clicked", G_CALLBACK (senha_dzseis), NULL); 
    gtk_grid_attach (GTK_GRID (grid), btn, 0,2,1,1); 

    btn = gtk_button_new_with_label ("Fechar"); 
    g_signal_connect_swapped (btn, "clicked", G_CALLBACK (gtk_window_destroy), window); 
    gtk_grid_attach (GTK_GRID (grid), btn, 0,3,1,1); 

    gtk_window_present (GTK_WINDOW (window)); // desenhar a janela
}

int main(int argc, char **argv){
    GtkApplication *app; // chama aqla funçao acima lá
    int status; //inicio sem valor

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    printf("Saida com codigo %i \n", status); // debug pra ver status e sequencia de reproduçao
    return status;
}