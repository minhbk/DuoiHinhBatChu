#include <gtk/gtk.h>
#include "play_ui.h"
#include "signup_ui.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "check.h"
#include "global_variable.h"

//click Dang nhap
int check=0;
static void on_button_signin_clicked(GtkWidget *widget,gpointer *entry)
{
	gchar *str;
  GtkWidget *entry_tk;
  GtkWidget *entry_pass;
  entry_tk=entry[0];
  entry_pass=entry[1];
  puts(gtk_entry_get_text(GTK_ENTRY(entry_tk)));
  puts(gtk_entry_get_text(GTK_ENTRY(entry_pass)));


  strcpy(user->name, gtk_entry_get_text(GTK_ENTRY(entry_tk)));
  strcpy(user->pass, gtk_entry_get_text(GTK_ENTRY(entry_pass)));
  user->state = state;
  user->next = NULL;


  puts("Bat dau dang nhap");
  if (request_sign_in(protocol, user, client_sock, state)){
    main_play();
  } else {
    puts("Error signin");
    // show_error();
  }

}

//Show error khi dang nhap
void show_error(GtkWidget *widget, gpointer window)
{
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(GTK_WINDOW(window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Tai khoan khong dung!");
	gtk_window_set_title(GTK_WINDOW(dialog),"Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


// tao icon cho chuong trinh
GdkPixbuf *create_pixbuf(const gchar *filename)
{
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(filename,&error);
	if(!pixbuf){
		fprintf(stderr, "%s\n",error->message );
		g_error_free(error);
	}
	return pixbuf;
}

void create_login_ui(int argc,char *argv[])
{
	GtkWidget *window;
	GtkWidget *button_signin;
	GtkWidget *button_signup;
	GtkWidget *halign1;

	GtkWidget *label_tk;
	GtkWidget *label_pass;

	GdkPixbuf *icon;
	GtkWidget *fixed;
	GtkWidget *statusbar;

	GtkWidget *entry_tk;
	GtkWidget *entry_pass;
  GtkWidget *user_infor[2];


	GtkWidget *image;

	GtkWidget *frame1;

	gtk_init(&argc,&argv);
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Đuổi hình bắt chữ");
	gtk_window_set_default_size(GTK_WINDOW(window),500,350);
	gtk_container_set_border_width(GTK_CONTAINER(window),30);
	fixed=gtk_fixed_new();

	//gtk_container_set_border_width(GTK_CONTAINER(window),10);
	button_signin=gtk_button_new_with_label("Đăng nhập");
	gtk_fixed_put(GTK_FIXED(fixed),button_signin,130,200);//set cach 2 ben le
	gtk_widget_set_size_request(button_signin,80,30);// set chieu dai rong button

	button_signup=gtk_button_new_with_label("Đăng kí");
	gtk_fixed_put(GTK_FIXED(fixed),button_signup,230,200);
	gtk_widget_set_size_request(button_signup,80,30);

	label_tk=gtk_label_new("Tài khoản");
	gtk_fixed_put(GTK_FIXED(fixed),label_tk,80,80);
	gtk_widget_set_size_request(label_tk,40,30);

	label_pass=gtk_label_new("Mật khẩu");
	gtk_fixed_put(GTK_FIXED(fixed),label_pass,80,120);
	gtk_widget_set_size_request(label_pass,40,30);

	statusbar = gtk_statusbar_new();
	gtk_fixed_put(GTK_FIXED(fixed),statusbar,180,160);
	gtk_widget_set_size_request(statusbar,150,30);


	user_infor[0]=gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(fixed),user_infor[0],180,80);
	gtk_widget_set_size_request(user_infor[0],100,30);
	user_infor[1]=gtk_entry_new();
	gtk_fixed_put(GTK_FIXED(fixed),user_infor[1],180,120);
	gtk_widget_set_size_request(user_infor[1],100,30);

	gtk_container_add(GTK_CONTAINER(window),fixed);

	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);//hien thi ow trung tam man hinh
	icon=create_pixbuf("huongdan.ico");
	gtk_window_set_icon(GTK_WINDOW(window),icon);
	gtk_widget_show_all(window);
	g_signal_connect(G_OBJECT(button_signin),"clicked",G_CALLBACK(on_button_signin_clicked),user_infor);
	g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(signup),NULL);

	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit),NULL);
	g_object_unref(icon);
	gtk_main();
}


