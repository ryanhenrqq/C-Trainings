#include <gtk/gtk.h>
// COMPILAR -> gcc $( pkg-config --cflags gtk4 ) -o windowGtkDraw windowGtkDraw.c $( pkg-config --libs gtk4 )


static void
activate (GtkApplication *app, gpointer userdata){
    GtkWidget *window;

    window=gtk_application_window_new (app); // cria o objeto Janela, pra manipular abaixo

    gtk_window_set_title(GTK_WINDOW (window),"Gerador de senhas"); //titulo
    gtk_window_set_default_size (GTK_WINDOW (window), 300, 200); // dimensao da janela
    
    gtk_window_present (GTK_WINDOW (window)); // desenhar a janela
}

int main(int argc, char **argv){
    GtkApplication *app; // chama aqla funçao acima lá
    int status; //inicio sem valor

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    printf("Saida com codigo %i", status); // debug pra ver status e sequencia de reproduçao
    return status;
}