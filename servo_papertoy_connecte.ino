/* 
 *  Premiere création certe assez simple pour certains mais qui est pour moi un grand pas, il y a quelques semaines j'étais encore à faire du "code" sous scratch.
 Cette création m'a permis d'utiliser les notions utilisés dans le mooc et je me suis inspiré sur l'internet pour la partie html / css pour la création des boutons
 Ce projet pourrait être modifié en ajoutant une webcam avec une vision de 180° ou bien arrosé la plante qui manque d'eau en insérant un petit verre ...
   
 Matériel nécessaire à la réalisation  : 
  - Carte Arduino
  - Shield Ethernet
  - resistance 220 ohms
  - led
  - servo moteurs
*/
#include <SPI.h>
#include <Ethernet.h>
#include <Servo.h> 
int led = 4; // Led sur la broche 4
Servo microservo; 
int pos = 0; 
byte mac[] = { 0xDA, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };   //Adresse Mac de l'arduino
byte ip[] = { 192, 168, 0, 40 };                      // Adresse IP de l'arduino 
byte gateway[] = { 192, 168, 0, 1 };                   // Adresse du router
byte subnet[] = { 255, 255, 255, 0 };                  //Masque sous-réseau
EthernetServer server(3500);                             //Port "3500" ouvert sur la box
String readString;

void setup() {
 // Moniteur réglé sur 9600 baups
  Serial.begin(9600);
   while (!Serial) {
    ; 
  }
  pinMode(led, OUTPUT); 
  microservo.attach(7); // servo sur la broche 7
  // Démarrage de la connection 
  Ethernet.begin(mac, ip, gateway, subnet);
  server.begin();
  Serial.print("l'adresse ip est : ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {   
      if (client.available()) {
        char c = client.read();
     
       
        if (readString.length() < 100) {
            readString += c;
           }

           if (c == '\n') {          
           Serial.println(readString); 
     
           client.println("HTTP/1.1 200 OK"); 
           client.println("Content-Type: text/html");
           client.println();     
           client.println("<HTML>");
           client.println("<HEAD>");
           client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
           client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
           client.println("<link rel='stylesheet' type='text/css' href='http://randomnerdtutorials.com/ethernetcss.css' />");
           client.println("<TITLE>Random Nerd Tutorials Project</TITLE>");
           client.println("</HEAD>");
           client.println("<BODY>");
           client.println("<H1>Personnage connecte</H1>");
           client.println("<hr />");
           client.println("<br />");  
           client.println("<H2>Gremlins n'en fait qu'a sa tete</H2>");
           client.println("<br />");  
           client.println("<a href=\"/?button1on\"\">Allume</a>");
           client.println("<a href=\"/?button1off\"\">Eteins</a><br />");   
           client.println("<br />");     
           client.println("<br />"); 
           client.println("<a href=\"/?button2on\"\">Tourner gauche</a>");
           client.println("<a href=\"/?button2off\"\">Tourner droite</a><br />"); 
             
           client.println("<br />"); 
           client.println("</BODY>");
           client.println("</HTML>");
/*
 * Created by Rui Santos
 */
     
           delay(1);
           //stopping client
           client.stop();
           //Contrôle de l'arduino si le bouton 1 est pressé
           if (readString.indexOf("?button1on") >0){
               digitalWrite(led, HIGH);
               delay (100);
               digitalWrite(led, LOW);
               delay (100);
               digitalWrite(led, HIGH);
               delay (100);
               digitalWrite(led, LOW);
               delay (100);               
               digitalWrite(led, HIGH);
               delay (100);
               digitalWrite(led, LOW);
               delay (100);
               digitalWrite(led, HIGH);
           }
           if (readString.indexOf("?button1off") >0){
               digitalWrite(led, LOW);
           }
           if (readString.indexOf("?button2on") >0){
                for(pos = 0; pos < 180; pos += 1)  // orientation de 0° à 180°
                {                                 
                  microservo.write(pos);              
                  delay(15);                      
                } 
           }
           if (readString.indexOf("?button2off") >0){
                for(pos = 180; pos>=1; pos-=1)     // Orientation de 180° à 0 °
                {                                
                  microservo.write(pos);               
                  delay(15);                      
                } 
           }
               readString="";  
           
         }
       }
    }
}
}
