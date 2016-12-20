#include <gtk/gtk.h>
//#include "check.h"
#include <stdio.h>
#include <string.h>

// void on_button_signup_clicked_pass(GtkWidget *widget,gpointer window)
// {
	
//       if(a==0){FILE *f1;
//       f1=fopen("password.txt","a+");
//     fputs(gtk_entry_get_text(GTK_ENTRY(window)),f1);
//     fputs("\n",f1);
//     //g_print("123");
//     //
//     fclose(f1);}

	
// }

 void on_button_signup_clicked_tk(GtkWidget *widget, gpointer *entry)
{

  GtkWidget *entry_tk = entry[0];
  GtkWidget *entry_pass = entry[1];
  GtkWidget *entry_pass_conf = entry[2];

  char name[30];
  char pass[30];
  char pass_conf[30];
  strcpy(name, gtk_entry_get_text(GTK_ENTRY(entry_tk)));
  strcpy(pass, gtk_entry_get_text(GTK_ENTRY(entry_pass)));
  strcpy(pass_conf, gtk_entry_get_text(GTK_ENTRY(entry_pass_conf)));

  if (strcmp(pass, pass_conf)!=0){
    puts("Loi! Mat khau khong trung nhau!");
  } else {
    strcpy(user->name, name);
    strcpy(user->pass, pass);
    user->state = state;
    user->next = NULL;

    if (request_signup(protocol, user, client_sock, state)){
      puts("Dang ki thanh cong!");
    } else {
      puts("Tai khoan da ton tai!");
    }
  }

	// gchar *str;
	// if(check_username(gtk_entry_get_text(GTK_ENTRY(window))))
	//   {g_print("Tài khoản đã tồn tại\n");a=1;}
	
	// else {
	//     FILE *f1;
	//     f1=fopen("password.txt","a+");
	//   fputs(gtk_entry_get_text(GTK_ENTRY(window)),f1);
	//   fputs("\t",f1);
  //   a=0;
	//   //g_print("456");
	//   fclose(f1);
	// }
}


void show_error_signup(GtkWidget *widget,gpointer window)
{
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(GTK_WINDOW(window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Tài khoản đã tồn tại!");
	gtk_window_set_title(GTK_WINDOW(dialog),"Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


void show_error_signup_pass_same(GtkWidget *widget,gpointer window)
{
	GtkWidget *dialog;
	dialog=gtk_message_dialog_new(GTK_WINDOW(window),
		GTK_DIALOG_DESTROY_WITH_PARENT,
		GTK_MESSAGE_ERROR,
		GTK_BUTTONS_OK,
		"Mật khẩu không trùng nhau!");
	gtk_window_set_title(GTK_WINDOW(dialog),"Error");
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);
}


void signup(int argc, char *argv[])
{


  GtkWidget *window;
  GtkWidget *fixed,*image;
  
  GtkWidget *label_tk;
  GtkWidget *label_pass;
  GtkWidget *label_pass_conf;

  GtkWidget *button_signup;

  // GtkWidget *entry_tk;
  // GtkWidget *entry_pass;
  // GtkWidget *entry_pass_conf;
  GtkWidget *user_infor[3];

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Sign Up");
  gtk_window_set_default_size(GTK_WINDOW(window),400,300);
  gtk_container_set_border_width(GTK_CONTAINER(window),30);

  fixed=gtk_fixed_new();
  button_signup=gtk_button_new_with_label("Đăng kí");
  gtk_fixed_put(GTK_FIXED(fixed),button_signup,120,250);//set cach 2 ben le
  gtk_widget_set_size_request(button_signup,80,30);// set chieu dai rong button


  label_tk=gtk_label_new("Tài khoản");
  gtk_fixed_put(GTK_FIXED(fixed),label_tk,10,50);//set cach 2 ben le
  gtk_widget_set_size_request(label_tk,40,30);//set chieu dai, rong label

  label_pass=gtk_label_new("Mật khẩu");
  gtk_fixed_put(GTK_FIXED(fixed),label_pass,10,90);
  gtk_widget_set_size_request(label_pass,40,30);
	
  label_pass_conf=gtk_label_new("Mật khẩu Confirm");
  gtk_fixed_put(GTK_FIXED(fixed),label_pass_conf,10,130);
  gtk_widget_set_size_request(label_pass_conf,40,30);

  user_infor[0]=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),user_infor[0],150,50);
  gtk_widget_set_size_request(user_infor[0],150,30);
  user_infor[1]=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),user_infor[1],150,90);
  gtk_widget_set_size_request(user_infor[1],150,30);
  user_infor[2]=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),user_infor[2],150,130);
  gtk_widget_set_size_request(user_infor[2],150,30);

  gtk_container_add(GTK_CONTAINER(window),fixed);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(on_button_signup_clicked_tk),user_infor);
  // g_signal_connect(G_OBJECT(button_signup),"clicked",G_CALLBACK(on_button_signup_clicked_pass),entry_pass);
  
    

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

  
}



