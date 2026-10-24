#include <stdio.h>
#include <gtk/gtk.h>
// COMPILAR -> bash comp consoletrainings

// aprendizado via github.com/ToshioCP/Gtk4-tutorial (24/10/2026)

static void app_activate (GApplication *app, gpointer *userdata){
	GtkWidget *win;
	GtkWidget *box;
	GtkWidget *titlelab;
	GtkWidget *btn;
	GtkTextBuffer *tb;
	gchar *textoMuitoBomMesmo;

	textoMuitoBomMesmo = 
		"O ET abre caixas enviadas pelos inscritos, revelando componentes de computador, itens de moto e acessórios nerds. O unboxing traz surpresas e peças antigas que prometem projetos futuros no canal.";

	win = gtk_application_window_new (GTK_APPLICATION (app));
	gtk_window_set_title (GTK_WINDOW (win), "Calculadora");
	gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);

	box = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);
	gtk_box_set_homogeneous (GTK_BOX (box), TRUE);
	gtk_window_set_child (GTK_WINDOW (win), box);


	titlelab = gtk_text_view_new ();
	tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (titlelab));
	gtk_text_buffer_set_text (tb, textoMuitoBomMesmo, -1);
	gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (titlelab), GTK_WRAP_WORD_CHAR);
	/*
		Isso fez uma especie de input na janela, vai ser uma funçao muito util, portanto o programa sera arquivado assim mesmo e irei pra um novo.
		-> text_view
		-> text_buffer
	*/

	btn = gtk_button_new_with_label ("Fechar");
	g_signal_connect_swapped (btn, "clicked", G_CALLBACK (gtk_window_destroy), win);

	gtk_box_append (GTK_BOX (box), titlelab);
	gtk_box_append (GTK_BOX (box), btn);

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

/*

Como o conector (g_signal_connect) se comporta de fato, para manipular:

#define g_signal_connect (
  instance, -> memoria onde esta salvo o sinal
  detailed_signal, -> nome da memoria "activate"
  c_handler, -> chamador da funçao
  data -> parametros, se nao tem nenhum é NULL
)

POR QUE USA O ACTIVATE COMO 2° parametro?:
void activate (
  GApplication *self, <- memoria
  gpointer user_data <- nao tenho certeza ainda
)

*/