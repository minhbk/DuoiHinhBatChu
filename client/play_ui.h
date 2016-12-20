#include <gtk/gtk.h>
#include <time.h>
#include <unistd.h>
#include "global_variable.h"


GtkWidget *label_show_score;
GtkWidget *label_show_goiy;
GtkWidget *image;
GtkWidget *label_show_causo;
GtkWidget *label_show_nameuser;
GtkWidget *entry_answer;
GtkWidget *label_show_score_play_with;


static void on_button_answer_clicked_answer(GtkWidget *widget,gpointer window)
{ 

  send_answer(protocol, user, client_sock, state, gtk_entry_get_text(GTK_ENTRY(window)));
  recv_result(protocol, user, client_sock);
  state = PLAYING;
  do {
    request_question(protocol, user, client_sock, state);
    recv(client_sock, protocol, sizeof(Protocol), 0);
  }while (protocol->message == NOT_SHOW_QUESTION);

  if (protocol->message == QUESTION){

    char number[5];
    char score[5];
    char competitor_score[5];

    sprintf(number, "%d", protocol->question.number);
    gtk_label_set_text(GTK_LABEL(label_show_causo),number);
    

    sprintf(score, "%d", protocol->your_score);
    gtk_label_set_text(GTK_LABEL(label_show_score),score);

    sprintf(competitor_score, "%d", protocol->competitor_score);
    gtk_label_set_text(GTK_LABEL(label_show_score_play_with),competitor_score);

    gtk_label_set_text(GTK_LABEL(label_show_goiy),protocol->question.suggestion);


    int image_size;
    image_size = protocol->question.image_size;
    state = protocol->state;

    protocol->state = state;
    protocol->message = REQUEST_IMAGE;
    send(client_sock, protocol, sizeof(Protocol), 0);


    char image_name[30];
    strcpy(image_name, "question/");
    strcat(image_name, user->name);
    strcat(image_name, ".jpg");

    recv_image(image_name, image_size, client_sock);


    gtk_image_set_from_file(GTK_IMAGE(image),image_name);
  } else if (protocol->message == WIN){
    puts("------------------");
    puts("BAN DA THANG CUOC!");
    puts("------------------");
    gtk_main_quit();
  } else if (protocol->message == LOSE){
    puts("------------------");
    puts("BAN DA THUA CUOC!");
    puts("------------------");
    gtk_main_quit();
  }
}

void main_play()
{

  state = request_play(protocol, user, client_sock, state);
  ready(protocol, user, client_sock, state);

  recv(client_sock, protocol, sizeof(Protocol), 0);
  char sug[30];
  int image_size;
  strcpy(sug, protocol->question.suggestion);
  image_size = protocol->question.image_size;
  state = protocol->state;

  protocol->state = state;
  protocol->message = REQUEST_IMAGE;
  send(client_sock, protocol, sizeof(Protocol), 0);


  char image_name[30];
  strcpy(image_name, "question/");
  strcat(image_name, user->name);
  strcat(image_name, ".jpg");

  recv_image(image_name, image_size, client_sock);


  GtkWidget *window;
  GtkWidget *fixed;
  GtkWidget *label_nameuser;

  GtkWidget *label_score;
  GtkWidget *label_goiy;
  GtkWidget *label_causo;
  GtkWidget *label3;

  GtkWidget *button_answer;
  GtkWidget *button_cancel;
  GtkWidget *button3;
  GtkWidget *label_score_play_with;

  //gtk_init(&argc, &argv);
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "Play game");
  gtk_window_set_default_size(GTK_WINDOW(window),800,600);
  gtk_container_set_border_width(GTK_CONTAINER(window),30);

  fixed=gtk_fixed_new();
  image = gtk_image_new_from_file(image_name);
  gtk_fixed_put(GTK_FIXED(fixed),image,10,10);//set cach 2 ben le
  gtk_widget_set_size_request(image,300,200);// set chieu dai rong button
 
  label_nameuser=gtk_label_new("Player:");
  gtk_fixed_put(GTK_FIXED(fixed),label_nameuser,50,300);
  gtk_widget_set_size_request(label_nameuser,80,30);

  label_show_nameuser=gtk_label_new(user->name);
  // gtk_label_set_text(GTK_LABEL(label_show_nameuser),str_user);
  gtk_fixed_put(GTK_FIXED(fixed),label_show_nameuser,150,300);
  gtk_widget_set_size_request(label_show_nameuser,80,30);

  label_score_play_with=gtk_label_new("Competitor score:");
  gtk_fixed_put(GTK_FIXED(fixed),label_score_play_with,430,200);
  gtk_widget_set_size_request(label_score_play_with,80,30);

  label_show_score_play_with=gtk_label_new("0");
  gtk_fixed_put(GTK_FIXED(fixed),label_show_score_play_with,580,200);
  gtk_widget_set_size_request(label_show_score_play_with,80,30);

  button_answer=gtk_button_new_with_label("Answer: ");
  gtk_fixed_put(GTK_FIXED(fixed),button_answer,600,450);//set cach 2 ben le
  gtk_widget_set_size_request(button_answer,80,80);// set chieu dai rong button
 

  label_score=gtk_label_new("Score: ");
  gtk_fixed_put(GTK_FIXED(fixed),label_score,430,80);//set cach 2 ben le
  gtk_widget_set_size_request(label_score,40,30);//set chieu dai, rong label

  label_causo=gtk_label_new("Number                       / 10");
  gtk_fixed_put(GTK_FIXED(fixed),label_causo,430,130);//set cach 2 ben le
  gtk_widget_set_size_request(label_causo,40,30);

  label_goiy=gtk_label_new("Suggest: ");
  gtk_fixed_put(GTK_FIXED(fixed),label_goiy,450,300);
  gtk_widget_set_size_request(label_goiy,40,30);


  label_show_score=gtk_label_new("0");
  gtk_fixed_put(GTK_FIXED(fixed),label_show_score,550,80);
  gtk_widget_set_size_request(label_show_score,150,30);

  char number[5];
  sprintf(number, "%d", protocol->question.number);
  label_show_causo=gtk_label_new(number);
  gtk_fixed_put(GTK_FIXED(fixed),label_show_causo,450,130);
  gtk_widget_set_size_request(label_show_causo,150,30);

  label_show_goiy=gtk_label_new(protocol->question.suggestion);
  gtk_fixed_put(GTK_FIXED(fixed),label_show_goiy,550,300);
  gtk_widget_set_size_request(label_show_goiy,150,30);
  entry_answer=gtk_entry_new();
  gtk_fixed_put(GTK_FIXED(fixed),entry_answer,300,450);
  gtk_widget_set_size_request(entry_answer,300,80);

  gtk_container_add(GTK_CONTAINER(window),fixed);
  gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(button_answer),"clicked",G_CALLBACK(on_button_answer_clicked_answer),entry_answer);

  g_signal_connect(G_OBJECT(window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);

  gtk_widget_show_all(window);

  gtk_main();

}
