#include <stdio.h>
#include <gtk/gtk.h>
// compila -> bash comp pt3

int nb1 = 0;
int nb2 = 0;
int total = 0;

static void number1(GtkWidget *widget, gpointer *userdata) {
        nb1 = 1;
	puts("Numero 1 adicionado");
}
static void number2(GtkWidget *widget, gpointer *userdata) {
        nb1 = 2;
	puts("Numero 2 adicionado");
}
static void number3(GtkWidget *widget, gpointer *userdata) {
        nb1 = 3;
	puts("Numero 3 adicionado");
}
static void number4(GtkWidget *widget, gpointer *userdata) {
        nb1 = 4;
	puts("Numero 4 adicionado");
}
static void number5(GtkWidget *widget, gpointer *userdata) {
        nb1 = 5;
	puts("Numero 5 adicionado");
}
static void number6(GtkWidget *widget, gpointer *userdata) {
        nb1 = 6;
	puts("Numero 6 adicionado");
}
static void number7(GtkWidget *widget, gpointer *userdata) {
        nb1 = 7;
	puts("Numero 7 adicionado");
}
static void number8(GtkWidget *widget, gpointer *userdata) {
        nb1 = 8;
	puts("Numero 8 adicionado");
}
static void number9(GtkWidget *widget, gpointer *userdata) {
        nb1 = 9;
	puts("Numero 9 adicionado");
}
static void number0(GtkWidget *widget, gpointer *userdata) {
        nb1 = 0;
	puts("Numero 0 adicionado");
}



static void app_activate (GtkApplication *app, gpointer *userdata){
        GtkBuilder *builder;
	
	builder = gtk_builder_new();
	gtk_builder_add_from_file (builder, "builder.ui", NULL);

	GObject *win = gtk_builder_get_object (builder, "window");
	gtk_window_set_application (GTK_WINDOW (win), app);

	GObject *lb = gtk_builder_get_object (builder,"top-lb");

	GObject *btn = gtk_builder_get_object (builder, "btn1");
	g_signal_connect (btn, "clicked", G_CALLBACK (number1), NULL);

	btn = gtk_builder_get_object (builder, "btn2");
	g_signal_connect (btn, "clicked", G_CALLBACK (number2), NULL);
	
	btn = gtk_builder_get_object (builder, "btn3");
	g_signal_connect (btn, "clicked", G_CALLBACK (number3), NULL);
	
	btn = gtk_builder_get_object (builder, "btn4");
	g_signal_connect (btn, "clicked", G_CALLBACK (number4), NULL);

	btn = gtk_builder_get_object (builder, "btn5");
	g_signal_connect (btn, "clicked", G_CALLBACK (number5), NULL);

	btn = gtk_builder_get_object (builder, "btn6");
	g_signal_connect (btn, "clicked", G_CALLBACK (number6), NULL);
	
	btn = gtk_builder_get_object (builder, "btn7");
	g_signal_connect (btn, "clicked", G_CALLBACK (number7), NULL);
	
	btn = gtk_builder_get_object (builder, "btn8");
	g_signal_connect (btn, "clicked", G_CALLBACK (number8), NULL);

	btn = gtk_builder_get_object (builder, "btn9");
	g_signal_connect (btn, "clicked", G_CALLBACK (number9), NULL);
	
	btn = gtk_builder_get_object (builder, "btn0");
	g_signal_connect (btn, "clicked", G_CALLBACK (number0), NULL);

	btn = gtk_builder_get_object (builder, "exit");
	g_signal_connect_swapped (btn, "clicked", G_CALLBACK (gtk_window_close), win);

	gtk_widget_set_visible (GTK_WIDGET (win), TRUE);
	g_object_unref (builder);
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
