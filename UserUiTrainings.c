#include <gtk/gtk.h>
#include <glib/gstdio.h>
// COMPILAR -> gcc $( pkg-config --cflags gtk4 ) -o UserUiTrainings.out UserUiTrainings.c $( pkg-config --libs gtk4 )
// esse codigo nao foi escrito a mao ainda, peguei do doc oficial do gtk.org para demonstraçao mesmo
// na teoria ele deve pegar o layout montado externamente no builder.ui, formato xml.

int counter = 0;

static void senha_oito (GtkWidget *widget, gpointer data){
    char password[8] = "";
    for (int n=0;n<8;n++){
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
static void increaser (GtkWidget *widget, gpointer data){
    counter++;
    g_print ("contador em: %i\n", counter);
}

static void activate (GtkApplication *app,gpointer user_data){
  GtkBuilder *builder = gtk_builder_new ();
  gtk_builder_add_from_file (builder, "builder.ui", NULL);

  GObject *window = gtk_builder_get_object (builder, "window");
  gtk_window_set_application (GTK_WINDOW (window), app);

  GObject *button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (senha_oito), NULL);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (senha_doze), NULL);

  button = gtk_builder_get_object (builder, "button-increase");
  g_signal_connect (button, "clicked", G_CALLBACK (increaser), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (gtk_window_close), window);

  gtk_widget_set_visible (GTK_WIDGET (window), TRUE);

  g_object_unref (builder); // tirar o builder da memoria
}

int main (int argc,char *argv[]){

  GtkApplication *app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);

  int status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}