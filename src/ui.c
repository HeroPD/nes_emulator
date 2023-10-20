#include <gtk/gtk.h>
#include <rom.h>

static void activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  size_t gameLength;
  load_rom("../games/pacman-usa-namco.nes", &gameLength);
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 1000);
  gtk_window_present (window);
}

int main (int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new ("nes.emulator", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
