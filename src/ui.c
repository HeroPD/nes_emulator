#include <gtk/gtk.h>
#include "rom.h"
#include "nes6502.h"
#include "log.h"

gpointer background_task(gpointer data) {
  size_t gameLength;
  Mapper *mapper = load_rom("../games/pacman-usa-namco.nes", &gameLength);
  Bus bus;

  bus.ram = calloc(64 * 1024, sizeof(uint8_t));
  cpu6502 cpustate;
  cpustate.pc = read_prg(mapper, 0xFFFF) << 8 | read_prg(mapper, 0xFFFC);
  cpustate.sp = 0xff;
  while (1) {
    nes_clock(&cpustate, &bus);
  }
  free_rom(mapper);
  return NULL;
}

static void activate (GtkApplication* app, gpointer user_data) {
  GtkWidget *window;
  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Window");
  gtk_window_set_default_size (GTK_WINDOW (window), 1000, 1000);
  gtk_window_present (window);

  init_logfile();
  log_debug("\n\nEmulator started\n\n");
  GThread *thread = g_thread_new("background", background_task, NULL);
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
