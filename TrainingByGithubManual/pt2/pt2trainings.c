#include <stdio.h>
#include <gtk/gtk.h>
// compila -> bash comp pt2trainings

static void app_activate (GApplication *app, gpointer *userdata){
	GtkWidget *win;
	GtkWidget *scroll;
	GtkWidget *box;
	GtkWidget *txt;
	GtkTextBuffer *tb;
	gchar *apresentacao;

	apresentacao = 
		"Sou um Programador Front End, focado em criar as melhores e mais amigáveis interfaces de usuário para a sua empresa. Consigo criar as melhores soluções para elevar o nivel de seu website profissional, focando na simplicidade de comandos simples, mas poderosos!";

	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Texto Scrollavel");
	gtk_window_set_default_size (GTK_WINDOW (win), 300,100);

	scroll = gtk_scrolled_window_new ();
	gtk_window_set_child (GTK_WINDOW (win), scroll);

	txt = gtk_text_view_new ();
	tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (txt));
	gtk_text_buffer_set_text (tb, apresentacao, -1);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (txt), GTK_WRAP_WORD_CHAR);

	gtk_scrolled_window_set_child (GTK_SCROLLED_WINDOW (scroll), txt);

	gtk_window_present (GTK_WINDOW (win));
}

int main(int argc, char *argv[]){
	GtkApplication *app;
	int status;

	app = gtk_application_new ("com.example.kalc", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	printf("Saida com código %i\n", status);
	return status;
};